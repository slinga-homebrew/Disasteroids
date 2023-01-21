#include <jo/jo.h>
#include "explosion.h"
#include "../main.h"
#include "../assets/alien.h"
#include "alien.h"

EXPLOSION g_Explosions[MAX_EXPLOSIONS] = {0};
SHIP_DEBRIS g_GameplayShipDebris[MAX_SHIP_DEBRIS] = {0};

//
// Disasteroid Explosions
//

// reset explosions
void initExplosions(void)
{
    memset(g_Explosions, 0, sizeof(g_Explosions));
}

// update explosions
void updateExplosions(void)
{
    PEXPLOSION explosion = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_Explosions); i++)
    {
        explosion = &g_Explosions[i];

        if(explosion->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        explosion->curPos.x += explosion->curPos.dx;
        explosion->curPos.y += explosion->curPos.dy;
        explosion->destroyFrames--;

        if(explosion->destroyFrames <= 0)
        {
            explosion->objectState = OBJECT_STATE_INACTIVE;
            continue;
        }
    }
}

// draw explosions to the screen
void drawExplosions(void)
{
    PEXPLOSION explosion = NULL;
    jo_3d_mesh* mesh = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_Explosions); i++)
    {
        explosion = &g_Explosions[i];

        if(explosion->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        // draw explosion
        mesh = g_Assets.explosion;

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, g_Game.hudColor);
            jo_3d_translate_matrix_fixed(explosion->curPos.x, explosion->curPos.y, 0);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();
    }
}

// create a new explosion
void spawnExplosion(PDISASTEROID disasteroid)
{
    PEXPLOSION explosion = NULL;
    int randomX = 0;
    int randomY = 0;

    // find an unused explosion
    for(unsigned int i = 0; i < COUNTOF(g_Explosions); i++)
    {
        PEXPLOSION temp = NULL;

        temp = &g_Explosions[i];

        if(temp->objectState == OBJECT_STATE_INACTIVE)
        {
            explosion = temp;
            break;
        }
    }

    if(explosion == NULL)
    {
        // all explosion spots are used, nothing we can do
        return;
    }

    randomX = jo_random(10) - 5;
    randomY = jo_random(10) - 5;

    explosion->curPos.x = disasteroid->curPos.x + toFIXED(randomX);
    explosion->curPos.y = disasteroid->curPos.y + toFIXED(randomY);

    // shot should follow the ship's nose
    explosion->curPos.dx = jo_random(0x4000) - 0x2000;
    explosion->curPos.dy = jo_random(0x4000) - 0x2000;

    explosion->destroyFrames = jo_random(EXPLOSION_TIMER) + EXPLOSION_TIMER/2;

    explosion->objectState = OBJECT_STATE_ACTIVE;

    return;
}

//
// Ship Debris
//

// reset ship debris
void initShipDebris(void)
{
    memset(g_GameplayShipDebris, 0, sizeof(g_GameplayShipDebris));
}

// update ship debris
void updateShipDebris(void)
{
    PSHIP_DEBRIS shipDebris = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_GameplayShipDebris); i++)
    {
        shipDebris = &g_GameplayShipDebris[i];

        if(shipDebris->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        shipDebris->curPos.x += shipDebris->curPos.dx;
        shipDebris->curPos.y += shipDebris->curPos.dy;
        shipDebris->destroyFrames--;

        if(shipDebris->destroyFrames <= 0)
        {
            shipDebris->objectState = OBJECT_STATE_INACTIVE;
            continue;
        }
    }
}

// draw ship debris to the screen
void drawShipDebris(void)
{
    PSHIP_DEBRIS debris = NULL;
    jo_3d_mesh* mesh = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_GameplayShipDebris); i++)
    {
        debris = &g_GameplayShipDebris[i];

        if(debris->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        // draw ship debris
        mesh = g_Assets.shipDebris[debris->size][debris->playerID];

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, debris->color);
            jo_3d_translate_matrix_fixed(debris->curPos.x, debris->curPos.y, 0);
            jo_3d_rotate_matrix(0, 0, debris->curPos.rot);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();
    }
}

// create new ship debris
void spawnShipDebris(PPLAYER player, SHIP_DEBRIS_SIZE size)
{
    PSHIP_DEBRIS debris = NULL;
    int randomX = 0;
    int randomY = 0;

    // find an unused projectile
    for(unsigned int i = 0; i < COUNTOF(g_GameplayShipDebris); i++)
    {
        PSHIP_DEBRIS temp = NULL;

        temp = &g_GameplayShipDebris[i];

        if(temp->objectState == OBJECT_STATE_INACTIVE)
        {
            debris = temp;
            break;
        }
    }

    if(debris == NULL)
    {
        // all ship debris spots are used, nothing we can do
        return;
    }

    randomX = jo_random(20) - 10;
    randomY = jo_random(20) - 10;

    debris->curPos.x = player->curPos.x + toFIXED(randomX);
    debris->curPos.y = player->curPos.y + toFIXED(randomY);

    debris->curPos.dx = jo_random(0x4000) - 0x2000;
    debris->curPos.dy = jo_random(0x4000) - 0x2000;

    debris->curPos.rot = jo_random(360);
    debris->curPos.drot = 1;

    debris->size = size;
    debris->playerID = player->playerID;
    debris->color = player->color;

    debris->destroyFrames = jo_random(SHIP_DEBRIS_TIMER/8) + SHIP_DEBRIS_TIMER;
    debris->objectState = OBJECT_STATE_ACTIVE;

    return;
}

// create alien ship debris
void spawnAlienDebris(PALIEN alien, SHIP_DEBRIS_SIZE size)
{
    PSHIP_DEBRIS debris = NULL;
    int randomX = 0;
    int randomY = 0;

    // find an unused projectile
    for(unsigned int i = 0; i < COUNTOF(g_GameplayShipDebris); i++)
    {
        PSHIP_DEBRIS temp = NULL;

        temp = &g_GameplayShipDebris[i];

        if(temp->objectState == OBJECT_STATE_INACTIVE)
        {
            debris = temp;
            break;
        }
    }

    if(debris == NULL)
    {
        // all ship debris spots are used, nothing we can do
        return;
    }

    randomX = jo_random(20) - 10;
    randomY = jo_random(20) - 10;

    debris->curPos.x = alien->curPos.x + toFIXED(randomX);
    debris->curPos.y = alien->curPos.y + toFIXED(randomY);

    debris->curPos.dx = jo_random(0x4000) - 0x2000;
    debris->curPos.dy = jo_random(0x4000) - 0x2000;

    debris->curPos.rot = jo_random(360);
    debris->curPos.drot = 1;

    debris->size = size;
    debris->playerID = 0;
    debris->color = g_Game.hudColor;

    debris->destroyFrames = jo_random(SHIP_DEBRIS_TIMER/4) + SHIP_DEBRIS_TIMER;
    debris->objectState = OBJECT_STATE_ACTIVE;

    return;
}
