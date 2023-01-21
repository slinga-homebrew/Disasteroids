#include <jo/jo.h>
#include "../main.h"
#include "../assets/alien.h"
#include "alien.h"

PROJECTILE g_Projectiles[MAX_PROJECTILES] = {0};
PROJECTILE g_AlienProjectiles[MAX_ALIEN_PROJECTILES] = {0};
extern ALIEN g_Alien;

//
// Player projectiles
//

// reset projectiles
void initProjectiles(void)
{
    memset(g_Projectiles, 0, sizeof(g_Projectiles));
}

// update projectiles
void updateProjectiles(void)
{
    PPROJECTILE projectile = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_Projectiles); i++)
    {
        projectile = &g_Projectiles[i];

        if(projectile->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        projectile->curPos.x += projectile->curPos.dx;
        projectile->curPos.y += projectile->curPos.dy;
        projectile->destroyFrames--;

        boundGameplayObject((PGAME_OBJECT)projectile);

        if(projectile->destroyFrames <= 0)
        {
            projectile->objectState = OBJECT_STATE_INACTIVE;
            continue;
        }
    }
}

// draw projectiles to the screen
void drawProjectiles(void)
{
    PPROJECTILE projectile = NULL;
    jo_3d_mesh* mesh = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_Projectiles); i++)
    {
        projectile = &g_Projectiles[i];

        if(projectile->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        // draw player projectile
        mesh = g_Assets.shipProjectiles[projectile->playerID];

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, projectile->color);
            jo_3d_translate_matrix_fixed(projectile->curPos.x, projectile->curPos.y, 0);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();
    }
}

// create a new projectile
void spawnProjectile(PPLAYER player)
{
    PPROJECTILE projectile = NULL;

    if(player->invulnerabilityFrames > 0)
    {
        // can't shoot if invulnerable
        return;
    }

    // find an unused projectile
    for(unsigned int i = 0; i < COUNTOF(g_Projectiles); i++)
    {
        PPROJECTILE temp = NULL;

        temp = &g_Projectiles[i];

        if(temp->objectState == OBJECT_STATE_INACTIVE)
        {
            projectile = temp;
            break;
        }
    }

    if(projectile == NULL)
    {
        // all projectile spots are used, nothing we can do
        return;
    }

    // TODO: should shoot from the nose of the ship instead of the center
    projectile->curPos.x = player->curPos.x + jo_fixed_mult(toFIXED(20/3), slCos((player->curPos.rot - 90) * 182));
    projectile->curPos.y = player->curPos.y + jo_fixed_mult(toFIXED(20/3), slSin((player->curPos.rot - 90) * 182));

    // shot should follow the ship's nose
    projectile->curPos.dx = jo_fixed_mult(PROJECTILE_SPEED, slCos((player->curPos.rot - 90) * 182)) + player->curPos.dx;
    projectile->curPos.dy = jo_fixed_mult(PROJECTILE_SPEED, slSin((player->curPos.rot - 90) * 182)) + player->curPos.dy;

    projectile->color = player->color;
    projectile->playerID = player->playerID;
    projectile->destroyFrames = PROJECTILE_TIMER;

    projectile->objectState = OBJECT_STATE_ACTIVE;

    return;
}

//
// Alien projectiles
//

// reset alien projectiles
void initAlienProjectiles(void)
{
    memset(g_AlienProjectiles, 0, sizeof(g_AlienProjectiles));
}

// update projectiles
void updateAlienProjectiles(void)
{
    PPROJECTILE projectile = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_AlienProjectiles); i++)
    {
        projectile = &g_AlienProjectiles[i];

        if(projectile->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        projectile->curPos.x += projectile->curPos.dx;
        projectile->curPos.y += projectile->curPos.dy;
        projectile->destroyFrames--;

        // don't wrap the projectiles on the SSMTF screen
        if(projectile->boundProjectile == true)
        {
            boundGameplayObject((PGAME_OBJECT)projectile);
        }

        if(projectile->destroyFrames <= 0)
        {
            projectile->objectState = OBJECT_STATE_INACTIVE;
            continue;
        }
    }
}

// draw projectiles to the screen
void drawAlienProjectiles(void)
{
    PPROJECTILE projectile = NULL;
    jo_3d_mesh* mesh = NULL;

    if(g_Alien.objectState == OBJECT_STATE_INACTIVE)
    {
        // stop drawing if the alien despawned
        return;
    }

    for(unsigned int i = 0; i < COUNTOF(g_AlienProjectiles); i++)
    {
        projectile = &g_AlienProjectiles[i];

        if(projectile->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        if(projectile->ignoreFrames > 0)
        {
            projectile->ignoreFrames--;
            continue;
        }

        // draw alien projectile
        mesh = g_Assets.shipProjectiles[0];

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, g_Game.hudColor);
            jo_3d_translate_matrix_fixed(projectile->curPos.x, projectile->curPos.y, 0);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();
    }
}

// create a new alien projectile
void spawnAlienProjectile(PALIEN alien, bool screenWrap)
{
    PPROJECTILE projectile = NULL;
    int angle = 0;

    // find an unused projectile
    for(unsigned int i = 0; i < COUNTOF(g_AlienProjectiles); i++)
    {
        PPROJECTILE temp = NULL;

        temp = &g_AlienProjectiles[i];

        if(temp->objectState == OBJECT_STATE_INACTIVE)
        {
            projectile = temp;
            break;
        }
    }

    if(projectile == NULL)
    {
        // all projectile spots are used, nothing we can do
        return;
    }

    projectile->curPos.x = alien->curPos.x;
    projectile->curPos.y = alien->curPos.y;

    if(alien->logic == ALIEN_GAMEPLAY_LOGIC_SHOOT)
    {
        // gameplay, shoot at any angle
        angle = (jo_random(10) * 36);
    }
    else
    {
        // SSMTF logo screen
        // bound angle to (-90, 90) so shoots don't hit the text
        angle = (jo_random(10) * 18) - 90;
    }

    // shot should follow the ship's nose
    projectile->curPos.dx = jo_fixed_mult(PROJECTILE_SPEED, slCos((angle - 90) * 182)) + alien->curPos.dx;
    projectile->curPos.dy = jo_fixed_mult(PROJECTILE_SPEED, slSin((angle - 90) * 182)) + alien->curPos.dy;

    projectile->destroyFrames = PROJECTILE_TIMER * 2;
    projectile->ignoreFrames = 2;

    projectile->objectState = OBJECT_STATE_ACTIVE;
    projectile->boundProjectile = screenWrap;

    return;
}
