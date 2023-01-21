#include <jo/jo.h>
#include "../main.h"
#include "../assets/assets.h"
#include "alien.h"
#include "projectile.h"

ALIEN g_Alien = {0};

//
// SSMTF Alien
//

// initialize SSMTF alien
void initSsmtfAlien(void)
{
    memset(&g_Alien, 0, sizeof(g_Alien));

    // starts off the screen and moves left to right
    g_Alien.curPos.x = toFIXED(-300);
    g_Alien.curPos.y = toFIXED(-38);

    g_Alien.size = ALIEN_SIZE_LARGE;
    g_Alien.logic = ALIEN_SSMTF_LOGIC_0;
    g_Alien.isShooting = false;
    g_Alien.frame = 0;

    initAlienProjectiles();

    g_Alien.objectState = OBJECT_STATE_ACTIVE;
}

// move the SSMTF alien around the SSMTF text
void updateSsmtfAlien(void)
{
    if(g_Alien.objectState != OBJECT_STATE_ACTIVE)
    {
        return;
    }

    g_Alien.frame++;

    if( g_Alien.logic == ALIEN_SSMTF_LOGIC_0)
    {
        g_Alien.curPos.x += toFIXED(1);

        if(g_Alien.curPos.x >= toFIXED(-106))
        {
           g_Alien.logic = ALIEN_SSMTF_LOGIC_1;
        }
    }
    else if( g_Alien.logic == ALIEN_SSMTF_LOGIC_1)
    {
        g_Alien.curPos.y -= toFIXED(1);

        if(g_Alien.curPos.y <= toFIXED(-56 ))
        {
           g_Alien.logic = ALIEN_SSMTF_LOGIC_2;
        }
    }
    else if( g_Alien.logic == ALIEN_SSMTF_LOGIC_2)
    {
        g_Alien.curPos.x += toFIXED(1);

        if(g_Alien.curPos.x >= toFIXED(107))
        {
           g_Alien.logic = ALIEN_SSMTF_LOGIC_3;
        }

        g_Alien.isShooting = true;
    }
    else if( g_Alien.logic == ALIEN_SSMTF_LOGIC_3)
    {
        g_Alien.curPos.y += toFIXED(1);

        if(g_Alien.curPos.y >= toFIXED(-38))
        {
           g_Alien.logic = ALIEN_SSMTF_LOGIC_4;
        }
        g_Alien.isShooting = false;
    }
    else
    {
        g_Alien.curPos.x += toFIXED(1);
    }

    // spawn an alien shot every 8 frames
    if(g_Alien.isShooting == true && ((g_Alien.frame & 0x3) == 0))
    {
        spawnAlienProjectile(&g_Alien, false);
    }

    return;
}

//
// Gameplay Alien
//

// initialize SSMTF alien
void initAlien(void)
{
    memset(&g_Alien, 0, sizeof(g_Alien));
}

void spawnAlien(void)
{
    int dir = 0;

    dir  = jo_random(2) - 1;

    // starts off the screen and moves left to right

    if(dir == 0)
    {
        g_Alien.curPos.x = toFIXED(-300 - jo_random(300));
        g_Alien.curPos.y = toFIXED(0);
        g_Alien.curPos.dx = toFIXED(1);
    }
    else
    {
        g_Alien.curPos.x = toFIXED(300 + jo_random(300));
        g_Alien.curPos.y = toFIXED(0);
        g_Alien.curPos.dx = toFIXED(-1);
    }

    g_Alien.size = ALIEN_SIZE_SMALL;
    g_Alien.logic = ALIEN_GAMEPLAY_LOGIC_ENTER;
    g_Alien.isShooting = false;

    initAlienProjectiles();

    g_Alien.objectState = OBJECT_STATE_ACTIVE;
}

// move the SSMTF alien around the SSMTF text
void updateAlien(void)
{
    if(g_Alien.objectState != OBJECT_STATE_ACTIVE)
    {
        return;
    }

    g_Alien.frame++;

    g_Alien.curPos.x += g_Alien.curPos.dx;
    g_Alien.curPos.dy += jo_random(0x4000) - toFIXED(0.125);

    if(g_Alien.curPos.dy < toFIXED(-1))
    {
        g_Alien.curPos.dy = toFIXED(-1);
    }
    else if(g_Alien.curPos.dy > toFIXED(1))
    {
        g_Alien.curPos.dy = toFIXED(1);
    }

    g_Alien.curPos.y += g_Alien.curPos.dy;

    if(g_Alien.curPos.y < toFIXED(-100))
    {
        g_Alien.curPos.y = toFIXED(-100);
        g_Alien.curPos.dy = toFIXED(0.5);
    }
    else if(g_Alien.curPos.y > toFIXED(100))
    {
        g_Alien.curPos.y = toFIXED(100);
        g_Alien.curPos.dy = toFIXED(-0.5);
    }

    // logic
    if(g_Alien.logic == ALIEN_GAMEPLAY_LOGIC_ENTER)
    {
        if(g_Alien.curPos.x >= toFIXED(-120) && g_Alien.curPos.x <= toFIXED(120))
        {
            g_Alien.logic = ALIEN_GAMEPLAY_LOGIC_SHOOT;
        }
        g_Alien.isShooting = false;
    }
    else if(g_Alien.logic == ALIEN_GAMEPLAY_LOGIC_SHOOT)
    {
        if(g_Alien.curPos.x <= toFIXED(-120) || g_Alien.curPos.x >= toFIXED(120))
        {
            g_Alien.logic = ALIEN_GAMEPLAY_LOGIC_LEAVE;
        }
        g_Alien.isShooting = true;
    }
    else
    {
        if(g_Alien.curPos.x <= toFIXED(-150) || g_Alien.curPos.x >= toFIXED(150))
        {
            g_Alien.objectState = OBJECT_STATE_INACTIVE;
        }
        g_Alien.isShooting = false;
    }

    // spawn an alien shot every 16 frames
    if(g_Alien.isShooting == true)
    {
        // shoot five times a second
        if((g_Alien.frame & 0x3F) == 0  ||
           (g_Alien.frame & 0x3F) == 16 ||
           (g_Alien.frame & 0x3F) == 32 ||
           (g_Alien.frame & 0x3F) == 48)
        {
            spawnAlienProjectile(&g_Alien, false);
        }
    }

    return;
}

// draw the alien
void drawAlien(void)
{
    int color = g_Game.hudColor;

    if(g_Alien.objectState != OBJECT_STATE_ACTIVE)
    {
        return;
    }

    jo_3d_push_matrix();
    {
        jo_3d_mesh* mesh = g_Assets.alien;
        jo_3d_camera_look_at(&g_Game.camera);
        jo_3d_set_mesh_color(mesh, color);
        jo_3d_translate_matrix_fixed(g_Alien.curPos.x, g_Alien.curPos.y, 0);

        if(g_Alien.size == ALIEN_SIZE_LARGE)
        {
            jo_3d_set_scale(4, 4, 1);
        }
        else
        {
            jo_3d_set_scale(2, 2, 1);
        }

        jo_3d_mesh_draw(mesh);
    }
    jo_3d_pop_matrix();

    return;
}

void destroyAlien(PALIEN alien)
{
    jo_audio_play_sound(&g_Assets.popPCM);

    // spawn ship debris
    spawnAlienDebris(alien, SHIP_DEBRIS_SIZE_SMALL);
    spawnAlienDebris(alien, SHIP_DEBRIS_SIZE_SMALL);
    spawnAlienDebris(alien, SHIP_DEBRIS_SIZE_SMALL);
    spawnAlienDebris(alien, SHIP_DEBRIS_SIZE_SMALL);
    spawnAlienDebris(alien, SHIP_DEBRIS_SIZE_SMALL);
    spawnAlienDebris(alien, SHIP_DEBRIS_SIZE_SMALL);

    alien->objectState = OBJECT_STATE_INACTIVE;

    return;
}
