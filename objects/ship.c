#include <jo/jo.h>
#include "../main.h"
#include "../assets/alien.h"
#include "alien.h"
#include "explosion.h"

// rotation angle of the ships on the title screen
int g_TitleShipRot = 0;

int g_TitleShipFrames = 0;

// count all players that are alive
unsigned int countAlivePlayers(void)
{
    PPLAYER player = NULL;
    int count = 0;

    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        player = &g_Players[i];

        if(player->numLives > 0)
        {
            count++;
        }
    }

    return count;
}

// initialize players
void initPlayers(void)
{
    // re-spawn all players
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        PPLAYER player = &g_Players[i];
        int color = player->color; // save existing player color

        // zero out the rest of the struct
        memset(player, 0, sizeof(PLAYER));

        player->playerID = i;

        // activate the player if the controller port is connected
        if (!jo_is_input_available(player->playerID))
        {
            // controller not plugged in
            continue;
        }

        // check if the player already had a color
        // this is annoying, but allows the player to have keep the same
        // color between multiple games
        if(color == 0)
        {
            player->color = popPlayerColor();
        }
        else
        {
            player->color = color;
        }

        player->numLives = g_Game.numLives;
        player->objectState = OBJECT_STATE_ACTIVE;
    }
}

// rotate the title ships
void updateTitleScreenShips(void)
{
    g_TitleShipFrames++;

    if((g_TitleShipFrames & 1) == 0)
    {
        // ships rotate in different directions in VS mode
        if(g_Game.gameType == GAME_TYPE_VERSUS)
        {
            g_TitleShipRot--;
        }
        else
        {
            g_TitleShipRot++;
        }
    }
}

// title ships rotating around center of screen
void drawTitleScreenShips(void)
{
    int xPos = 0;
    int yPos = 18;
    int rot = 0;

    for(unsigned int i = 0; i < COUNTOF(g_Assets.titleScreenShips); i++)
    {
        int color = g_Assets.randomizedColors[i];
        jo_3d_mesh* mesh = NULL;

        if(g_Game.gameType == GAME_TYPE_VERSUS)
        {
            mesh = g_Assets.titleScreenShipsVs[i];
            rot = g_TitleShipRot + (i*30) + 181;
        }
        else
        {
            mesh = g_Assets.titleScreenShips[i];
            rot = g_TitleShipRot + (i*30);
        }

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, color);
            jo_3d_translate_matrix(xPos, yPos, 0);
            jo_3d_rotate_matrix(0, 0, rot);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();
    }
}

// spawn individual player
void spawnPlayer(PPLAYER player, int angle, int respawnTimer)
{
    jo_fixed horizontalRadius = 0;
    jo_fixed verticalRadius = 0;

    // spawn positions change depending on game type
    if(g_Game.gameType == GAME_TYPE_VERSUS)
    {
        verticalRadius = toFIXED(80.0);
        horizontalRadius = toFIXED(120.0);
        angle += 7;
    }
    else
    {
        // GAME_TYPE_COOP
        verticalRadius = toFIXED(40.0);
        horizontalRadius = toFIXED(40.0);
    }

    player->curPos.x = jo_fixed_mult(horizontalRadius, slCos(angle * 182));
    player->curPos.y = jo_fixed_mult(verticalRadius, slSin(angle * 182));
    player->curPos.dx = 0;
    player->curPos.dy = 0;
    player->curPos.rot = (angle + 90);

    if(g_Game.gameType == GAME_TYPE_VERSUS)
    {
        // in versus mode, the ships face in
        player->curPos.rot += 180;
    }

    player->curPos.rot %= 360;
    player->score.wave = g_Game.wave; // player made it to the current wave

    // add a small randomization to prevent all starting players from
    // blinking in unision
    player->invulnerabilityFrames = INVULNERABILITY_TIMER + jo_random(16);

    if(respawnTimer != 0)
    {
        player->respawnFrames = respawnTimer + jo_random(16);
    }
    else
    {
        player->respawnFrames = 0;
    }
}

// draw players to the screen
void drawPlayers(void)
{
    PPLAYER player = NULL;
    jo_3d_mesh* mesh = NULL;

    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        player = &g_Players[i];

        if(player->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        if(player->respawnFrames > 0)
        {
            continue;
        }

        /*
        if(g_Game.debug >= 1)
        {
            jo_printf(0, 0, "z %d    ", player->curPos.rot);
            jo_printf(0, 1, "cos(z) %d    ", jo_cos(player->curPos.rot) >> 16);
            jo_printf(0, 2, "sin(z) %d    ", jo_sin(player->curPos.rot) >> 16);
            jo_printf(0, 3, "x %d    ", (player->curPos.x) >> 16);
            jo_printf(0, 4, "y %d    ", (player->curPos.y) >> 16);
        }
        */

        // draw ship
        mesh = g_Assets.ships[i];

        // blink the player if they are invulnerable
        if((player->invulnerabilityFrames > 0) && ((player->invulnerabilityFrames & 0x8) == 0x8))
        {
            continue;
        }

        jo_3d_push_matrix();
        {
            jo_3d_camera_look_at(&g_Game.camera);
            jo_3d_set_mesh_color(mesh, player->color);
            //jo_3d_set_scale(2, 2, 1);
            jo_3d_translate_matrix_fixed(player->curPos.x, player->curPos.y, 0);
            jo_3d_rotate_matrix(0, 0, player->curPos.rot);
            jo_3d_mesh_draw(mesh);
        }
        jo_3d_pop_matrix();

        if(player->isThrusting)
        {
            // draw thrust
            mesh = g_Assets.shipThrusts[i];

            jo_3d_push_matrix();
            {
                jo_3d_camera_look_at(&g_Game.camera);
                jo_3d_set_mesh_color(mesh, player->color);
                jo_3d_translate_matrix_fixed(player->curPos.x, player->curPos.y, 0);
                jo_3d_rotate_matrix(0, 0, player->curPos.rot);
                jo_3d_mesh_draw(mesh);
            }
            jo_3d_pop_matrix();
        }
    }
}

// destroy the player and spawn ship debris
void destroyPlayer(PPLAYER player)
{
    int angle = 0;
    player->numLives--;

    jo_audio_play_sound(&g_Assets.popPCM);

    // spawn ship debris
    spawnShipDebris(player, SHIP_DEBRIS_SIZE_SMALL);
    spawnShipDebris(player, SHIP_DEBRIS_SIZE_SMALL);
    spawnShipDebris(player, SHIP_DEBRIS_SIZE_LARGE);
    spawnShipDebris(player, SHIP_DEBRIS_SIZE_LARGE);

    if(player->numLives <= 0)
    {
        player->objectState = OBJECT_STATE_INACTIVE;
        return;
    }

    // respawn the player
    angle = (jo_random(12) - 1) * 30;

    spawnPlayer(player, angle, RESPAWN_TIMER);

    return;
}

// spawn starting players
void spawnPlayers(void)
{
    int numPlayers = 0;
    int playerDelta = 0; //
    int startingDelta = 0; // 30
    PPLAYER player = NULL;
    int playerCount = 0;

    numPlayers = countAlivePlayers();

    if(numPlayers == 0)
    {
        // rare edge case where all players AND disasteroids are dead
        return;
    }

    // change spacing depending on number of players
    playerDelta = 360/numPlayers;

    startingDelta = (jo_random(12) - 1) * 30;

    for(unsigned int i = 0; i < MAX_PLAYERS; i++)
    {
        int angle = 0;

        player = &g_Players[i];

        if(player->objectState != OBJECT_STATE_ACTIVE)
        {
            // only spawn active players
            continue;
        }

        angle = ((playerDelta*playerCount) + startingDelta);

        spawnPlayer(player, angle, 0);

        playerCount++;
    }

    return;
}
