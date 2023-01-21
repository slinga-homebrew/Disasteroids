#include <jo/jo.h>
#include "star.h"
#include "../main.h"
#include "../assets/assets.h"

STAR g_Stars[MAX_STARS] = {0};

// number of frames to strobe stars for
int g_StarStrobeFrames = 0;

static void initStar(PSTAR star);

// initialize background stars
void initStars(void)
{
    for(unsigned int i = 0; i < COUNTOF(g_Stars); i++)
    {
        initStar(&g_Stars[i]);
    }

    g_StarStrobeFrames = 0;
}

// randomize location and color of star
static void initStar(PSTAR star)
{
    star->color = jo_random(COUNTOF(g_Assets.randomizedColors)) - 1;
    star->curPos.x = toFIXED(SCREEN_MIN_X_INT + jo_random(SCREEN_MAX_X_INT *2));
    star->curPos.y = toFIXED(SCREEN_MIN_Y_INT + jo_random(SCREEN_MAX_Y_INT * 2));
    star->destroyFrames = jo_random(STAR_LIFE_TIMER);
    star->objectState = OBJECT_STATE_ACTIVE;
}

// update background stars
void updateStars(void)
{
    PSTAR star = NULL;

    if(g_StarStrobeFrames > 0)
    {
        g_StarStrobeFrames--;
    }

    for(unsigned int i = 0; i < COUNTOF(g_Stars); i++)
    {
        star = &g_Stars[i];
        
        if(star->objectState == OBJECT_STATE_INACTIVE)
        {
            continue;
        }

        if(g_StarStrobeFrames > 0)
        {
            // if we are strobing, change the color of the star
            if(((g_StarStrobeFrames + i) & 0x7) == 0)
            {
                star->color++;

                if((unsigned int)star->color >= COUNTOF(g_Assets.randomizedColors))
                {
                    star->color = 0;
                }
            }
        }
  
        star->destroyFrames--;
        
        // check if we need to destroy the star
        if(star->destroyFrames <= 0)
        {
            initStar(star);
            continue;
        }
    }
}

// draw background star
void drawStars(void)
{  
    jo_3d_mesh* mesh = NULL;
    PSTAR star = NULL;
    int color = 0;

    for(unsigned int i = 0; i < COUNTOF(g_Stars); i++)
    {
        star = &g_Stars[i];

        if(star->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }
       
        mesh = g_Assets.stars[star->color];
        color = g_Assets.randomizedColors[star->color];

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, color);
            jo_3d_translate_matrix_fixed(star->curPos.x, star->curPos.y, 0);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();
    }
}

// enable star strobing timer
void strobeStars(void)
{
    g_StarStrobeFrames = STAR_STROBE_TIMER;
}
