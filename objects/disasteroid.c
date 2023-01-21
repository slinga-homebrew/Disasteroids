#include <jo/jo.h>
#include "../main.h"
#include "../assets/assets.h"
#include "disasteroid.h"
#include "explosion.h"

// title screen rings of disasteroids
#define RING_1_NUM_DISASTEROIDS (10)
#define RING_2_NUM_DISASTEROIDS (15)
#define DEGREE_DELTA_RING_1 (DEGREES_IN_CIRCLE/RING_1_NUM_DISASTEROIDS)
#define DEGREE_DELTA_RING_2 (DEGREES_IN_CIRCLE/RING_2_NUM_DISASTEROIDS)

static int getNumberOfDisasteroids(void);
static jo_fixed getSpeedIncrementOfDisasteroids(void);

DISASTEROID g_Disasteroids[MAX_DISASTEROIDS] = {0};

//
// Disasteroids
//

// draw disasteroids to the screen
void drawDisasteroids(void)
{
    PDISASTEROID disasteroid = NULL;
    jo_3d_mesh* mesh = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_Disasteroids); i++)
    {
        disasteroid = &g_Disasteroids[i];

        if(disasteroid->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        // draw disasteroid
        mesh = g_Assets.disasteroids[disasteroid->size][disasteroid->type];

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, g_Game.hudColor);
            jo_3d_translate_matrix_fixed(disasteroid->curPos.x, disasteroid->curPos.y, 0);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();
    }
}

// initializes two spinning rings of disasteroids
void initTitleScreenDisasteroids(void)
{
    PDISASTEROID disasteroid = NULL;

    memset(g_Disasteroids, 0, sizeof(g_Disasteroids));

    for(unsigned int i = 0; i < RING_1_NUM_DISASTEROIDS; i++)
    {
        disasteroid = &g_Disasteroids[i];

        disasteroid->curPos.rot = i * DEGREE_DELTA_RING_1 * 182;
        disasteroid->titleRadius = toFIXED(105);
        disasteroid->curPos.drot = -0x60;
        disasteroid->size = 1;//jo_random(DIASTEROID_SIZE_MAX) - 1;
        disasteroid->type = jo_random(NUM_DISASTEROID_VARIATIONS) - 1;
        disasteroid->objectState = OBJECT_STATE_ACTIVE;
    }

    for(unsigned int i = 0; i < RING_2_NUM_DISASTEROIDS; i++)
    {
        disasteroid = &g_Disasteroids[i+RING_1_NUM_DISASTEROIDS];

        disasteroid->curPos.rot = i * DEGREE_DELTA_RING_2 *182;
        disasteroid->titleRadius = toFIXED(130);
        disasteroid->curPos.drot = 0x70;
        disasteroid->size = 1;//jo_random(DIASTEROID_SIZE_MAX) - 1;
        disasteroid->type = jo_random(NUM_DISASTEROID_VARIATIONS) - 1;
        disasteroid->objectState = OBJECT_STATE_ACTIVE;
    }
}

// reset disasteroids
void initDisasteroids(void)
{
    memset(g_Disasteroids, 0, sizeof(g_Disasteroids));
}

// randomize the location, size, and velocity of a disasteroid
void randomizeDisasteroid(PDISASTEROID disasteroid)
{
    jo_fixed horizontalRadius = 0;
    jo_fixed verticalRadius = 0;
    jo_fixed difficultyIncrement = 0;
    int angle = 0;

    angle = jo_random(360);

    // spawn positions change depending on game type
    if(g_Game.gameType == GAME_TYPE_COOP)
    {
        verticalRadius = toFIXED(jo_random(20) + 90);
        horizontalRadius = toFIXED(jo_random(30) + 120);
        angle += 7;
    }
    else
    {
        // GAME_TYPE_VERUS
        verticalRadius = toFIXED(40.0);
        horizontalRadius = toFIXED(40.0);
    }

    difficultyIncrement = getSpeedIncrementOfDisasteroids();

    disasteroid->curPos.x = jo_fixed_mult(horizontalRadius, slCos(angle * 182));
    disasteroid->curPos.y = jo_fixed_mult(verticalRadius, slSin(angle * 182));

    disasteroid->curPos.dx = toFIXED(jo_random(4)) - toFIXED(2);
    disasteroid->curPos.dy = toFIXED(jo_random(4)) - toFIXED(2);

    if(disasteroid->curPos.dx > 0)
    {
        disasteroid->curPos.dx += difficultyIncrement;
    }
    else
    {
        disasteroid->curPos.dx -= difficultyIncrement;
    }

    if(disasteroid->curPos.dy > 0)
    {
        disasteroid->curPos.dy += difficultyIncrement;
    }
    else
    {
        disasteroid->curPos.dy -= difficultyIncrement;
    }

    if (disasteroid->curPos.dx >= 0 && disasteroid->curPos.dx < toFIXED(0.25))
    {
        disasteroid->curPos.dx += toFIXED(0.25);
    }
    else if(disasteroid->curPos.dy < 0 && disasteroid->curPos.dx > toFIXED(-0.25))
    {
        disasteroid->curPos.dx -= toFIXED(0.25);
    }

    if (disasteroid->curPos.dy >= 0 && disasteroid->curPos.dy < toFIXED(0.25))
    {
        disasteroid->curPos.dy += toFIXED(0.25);
    }
    else if(disasteroid->curPos.dy < 0 && disasteroid->curPos.dy > toFIXED(-0.25))
    {
        disasteroid->curPos.dy -= toFIXED(0.25);
    }

    disasteroid->size = jo_random(DIASTEROID_SIZE_MAX) - 1;
    disasteroid->type = jo_random(NUM_DISASTEROID_VARIATIONS) - 1;
    disasteroid->objectState = OBJECT_STATE_ACTIVE;
}

// update the disasteroids
void updateDisasteroids(void)
{
    PDISASTEROID disasteroid = NULL;

    if(g_Game.disasteroidSpawnFrames > 0)
    {
        g_Game.disasteroidSpawnFrames--;
        return;
    }

    for(unsigned int i = 0; i < COUNTOF(g_Disasteroids); i++)
    {
        disasteroid = &g_Disasteroids[i];

        if(disasteroid->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        disasteroid->curPos.x += disasteroid->curPos.dx;
        disasteroid->curPos.y += disasteroid->curPos.dy;

        boundGameplayObject((PGAME_OBJECT)disasteroid);
    }
}

// rotate the title Disasteroids
void updateTitleScreenDisasteroids(void)
{
    for(unsigned int i = 0; i < COUNTOF(g_Disasteroids); i++)
    {
        PDISASTEROID disasteroid = &g_Disasteroids[i];

        if(disasteroid->objectState == OBJECT_STATE_INACTIVE)
        {
            continue;
        }

        // disasteroids rotate in different directions in VS mode
        if(g_Game.gameType == GAME_TYPE_VERSUS)
        {
            disasteroid->curPos.rot -= disasteroid->curPos.drot;
        }
        else
        {
            disasteroid->curPos.rot += disasteroid->curPos.drot;
        }
    }
}

// draw the disasteroids
void drawTitleScreenDisasteroids(void)
{
    PDISASTEROID disasteroid = NULL;
    jo_3d_mesh* mesh = NULL;
    int color = 0;

    if(g_Game.gameState == GAME_STATE_TITLE_SCREEN)
    {
        // on the title screen the disasteroids are mint green
        color = JO_COLOR_Mint;
    }
    else
    {
        color = g_Game.hudColor;
    }

    for(unsigned int i = 0; i < COUNTOF(g_Disasteroids); i++)
    {

        disasteroid = &g_Disasteroids[i];

        if(disasteroid->objectState == OBJECT_STATE_INACTIVE)
        {
            continue;
        }

        disasteroid->curPos.x = jo_fixed_mult(disasteroid->titleRadius, slCos(disasteroid->curPos.rot));
        disasteroid->curPos.y = jo_fixed_mult(disasteroid->titleRadius, slSin(disasteroid->curPos.rot));

        mesh = g_Assets.disasteroids[disasteroid->size][disasteroid->type];

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, color);
            jo_3d_translate_matrix_fixed(disasteroid->curPos.x, disasteroid->curPos.y, 0);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();
    }
}

// destroy the disasteroid, split it in half, and award points
void destroyDisasteroid(PDISASTEROID disasteroid, PPROJECTILE projectile)
{
    PPLAYER player = NULL;
    int numExplosions = 0;

    if(disasteroid->objectState == OBJECT_STATE_INACTIVE)
    {
        // should be impossible
        return;
    }

    if(projectile)
    {
        // award points if this is coop mode
        if(g_Game.gameType == GAME_TYPE_COOP)
        {
            // lookup the player to give them points
            player = &g_Players[projectile->playerID];
            player->score.points += DISASTEROID_DESTROY_POINTS;
        }

        // destroy the projectile as well
        projectile->objectState = OBJECT_STATE_INACTIVE;
    }

    // split the Disasteroid in two
    splitDisasteroid(disasteroid);
    splitDisasteroid(disasteroid);

    // spawn explosion particles
    numExplosions = jo_random(5) + 5;

    for(int i = 0; i < numExplosions; i++)
    {
        spawnExplosion(disasteroid);
    }

    // play sound effect
    jo_audio_play_sound(&g_Assets.popPCM);

    // destroy the existing Disasteroid
    disasteroid->objectState = OBJECT_STATE_INACTIVE;

    return;
}

// split a medium or large disasteroid in two
void splitDisasteroid(PDISASTEROID disasteroid)
{
    PDISASTEROID newDisasteroid = NULL;

    // only split medium and large asteroids
    if(disasteroid->size == DISASTEROID_SIZE_SMALL)
    {
        return;
    }

    // find an unused disasteroid
    for(unsigned int i = 0; i < COUNTOF(g_Disasteroids); i++)
    {
        PDISASTEROID temp = NULL;

        temp = &g_Disasteroids[i];

        if(temp->objectState != OBJECT_STATE_INACTIVE)
        {
            // already used
            continue;
        }

        newDisasteroid = temp;
    }

    if(newDisasteroid == NULL)
    {
        // Disasteroids array is full, nothing we can do
        return;
    }

    randomizeDisasteroid(newDisasteroid);

    // the new asteroid should spawn on top of the old
    newDisasteroid->curPos.x = disasteroid->curPos.x;
    newDisasteroid->curPos.y = disasteroid->curPos.y;

    // new disasteroids must be smaller as well
    newDisasteroid->size = disasteroid->size - 1;

    return;
}

// spawn a new wave of disasteroids
void spawnDisasteroids(void)
{
    PDISASTEROID disasteroid = NULL;
    int numDisasteroids = 0;

    numDisasteroids = getNumberOfDisasteroids();

    if(numDisasteroids > MAX_DISASTEROIDS)
    {
        numDisasteroids = MAX_DISASTEROIDS;
    }

    memset(g_Disasteroids, 0, sizeof(g_Disasteroids));

    for(int i = 0; i < numDisasteroids; i++)
    {
        disasteroid = &g_Disasteroids[i];
        randomizeDisasteroid(disasteroid);
    }

    g_Game.disasteroidSpawnFrames = DISASTEROID_SPAWN_TIMER;
}

// returns true if at least one Disasteroid is still alive
bool checkAliveDisasteroids(void)
{
    PDISASTEROID disasteroid = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_Disasteroids); i++)
    {
        disasteroid = &g_Disasteroids[i];

        if(disasteroid->objectState == OBJECT_STATE_ACTIVE)
        {
            // at least one active Disasteroid
            return true;
        }
    }

    // no active Disasteroid
    return false;
}

// higher waves should have more Disasteroids
static int getNumberOfDisasteroids(void)
{
    int startingDisasteroids = 0;
    int numDisasteroids = 0;

    if(g_Game.gameType == GAME_TYPE_COOP)
    {
        startingDisasteroids = 3;
    }
    else
    {
        startingDisasteroids = 2;
    }

    numDisasteroids = startingDisasteroids + (g_Game.wave/2);

    return numDisasteroids;
}

// higher waves should have more faster Disasteroids
static int getSpeedIncrementOfDisasteroids(void)
{
    return (0x100 * g_Game.wave);
}
