#include <jo/jo.h>
#include "main.h"
#include "gameplay.h"
#include "assets/assets.h"
#include "collision.h"
#include "pause.h"
#include "objects/alien.h"
#include "objects/ship.h"
#include "objects/disasteroid.h"
#include "objects/explosion.h"
#include "objects/projectile.h"
#include "objects/star.h"

// players
static void getGameplayPlayersInput(void);
static void updateGameplayPlayers(void);

// gameplay state
static void initNewGame(void);
static void initWave(void);
static void isGameOver(void);
static void isWaveOver(void);

// misc
static void drawGameplayWave(void);

//
// Gameplay Callbacks
//

// initialize new game
void gameplay_init(void)
{
    initNewGame();

    initPlayers();
    initExplosions();
    initShipDebris();
    initDisasteroids();
    initStars();
    initAlien();

    initWave();
}

// gameplay input callback
void gameplay_input(void)
{
    if(g_Game.gameState != GAME_STATE_GAMEPLAY)
    {
        return;
    }

    if(g_Game.isPaused == true)
    {
        return;
    }

    getGameplayPlayersInput();
}

// gameplay update callback
void gameplay_update(void)
{
    if(g_Game.gameState != GAME_STATE_GAMEPLAY)
    {
        return;
    }

    // update stars even if game is paused
    updateStars();

    if(g_Game.isPaused == true)
    {
        return;
    }

    // check for round and end game conditions
    isWaveOver();
    isGameOver();

    // game objects
    updateDisasteroids();
    updateProjectiles();
    updateAlienProjectiles();
    updateExplosions();
    updateShipDebris();
    updateGameplayPlayers();
    updateAlien();

    // collisions
    checkForAlienCollisions();
    checkForDisasteroidCollisions();
    checkForPlayerCollisions();

    return;
}

// draw gameplay elements
void gameplay_draw(void)
{
    if(g_Game.gameState != GAME_STATE_GAMEPLAY)
    {
        return;
    }

    // draw stars even if game is paused
    drawStars();

    if(g_Game.isPaused == true)
    {
        return;
    }

    //
    // Draw objects from least important to most important
    //

    drawExplosions();
    drawShipDebris();
    drawProjectiles();
    drawAlienProjectiles();
    drawDisasteroids();
    drawAlien();
    drawGameplayWave();
    drawPlayers();

    return;
}

//
// Players
//

// poll each player
static void getGameplayPlayersInput(void)
{
    PPLAYER player = NULL;

    // check inputs for all players
    for(unsigned int i = 0; i < COUNTOF(g_Players); i++)
    {
        player = &g_Players[i];

        if(player->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        // don't check inputs if the player is respawning
        if(player->respawnFrames > 0)
        {
            continue;
        }

        // is player attempting to change color?
        if (jo_is_input_key_pressed(player->playerID, JO_KEY_X))
        {
            if(player->input.pressedX == false)
            {
                pushPlayerColor(player->color);
                player->color = popPlayerColor();
            }
            player->input.pressedX = true;
        }
        else
        {
            player->input.pressedX = false;
        }

        // Is player rotating?
        if (jo_is_input_key_pressed(player->playerID, JO_KEY_LEFT))
        {
            if(player->input.pressedLeft == false)
            {
                player->curPos.drot = -Z_SPEED_INC;
            }
        }
        else if (jo_is_input_key_pressed(player->playerID, JO_KEY_RIGHT))
        {
            if(player->input.pressedRight == false)
            {
                player->curPos.drot = Z_SPEED_INC;
            }
        }
        else
        {
            // no rotation
            player->curPos.drot = 0;
        }

        if(player->invulnerabilityFrames > INVULNERABILITY_TIMER/2)
        {
            continue;
        }

        // Is player shooting a projectile?
        if (jo_is_input_key_pressed(player->playerID, JO_KEY_A) ||
            jo_is_input_key_pressed(player->playerID, JO_KEY_C))
        {
            if(player->input.pressedAC == false)
            {
                spawnProjectile(player);
                player->input.pressedAC = true;
            }
        }
        else
        {
            player->input.pressedAC = false;
        }


        // Is player thrusting?
        if (jo_is_input_key_pressed(player->playerID, JO_KEY_UP) ||
            jo_is_input_key_pressed(player->playerID, JO_KEY_B))
        {

            player->curPos.dx += jo_fixed_sin(jo_fixed_mult(toFIXED(player->curPos.rot), JO_FIXED_PI_DIV_180));
            player->curPos.dy -= jo_fixed_cos(jo_fixed_mult(toFIXED(player->curPos.rot), JO_FIXED_PI_DIV_180));
            player->isThrusting = true;
        }
        else
        {
            // not thrusting, apply friction
            player->curPos.dx -= jo_fixed_mult(FRICTION, player->curPos.dx);
            player->curPos.dy -= jo_fixed_mult(FRICTION, player->curPos.dy);
            player->isThrusting = false;
        }


        // bound max speed
        if(player->curPos.dx > MAX_SPEED_X)
        {
            player->curPos.dx = MAX_SPEED_X;
        }
        else if(player->curPos.dx < MIN_SPEED_X)
        {
            player->curPos.dx = MIN_SPEED_X;
        }

        if(player->curPos.dy > MAX_SPEED_Y)
        {
            player->curPos.dy = MAX_SPEED_Y;
        }
        else if(player->curPos.dy < MIN_SPEED_Y)
        {
            player->curPos.dy = MIN_SPEED_Y;
        }
    }
}

// update players
static void updateGameplayPlayers(void)
{
    PPLAYER player = NULL;

    for(unsigned int i = 0; i < COUNTOF(g_Players); i++)
    {
        player = &g_Players[i];

        if(player->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        // don't do anything if we are waiting to respawn
        if(player->respawnFrames > 0)
        {
            player->respawnFrames--;
            continue;
        }

        // update invulnerability frames
        if(player->invulnerabilityFrames > 0)
        {
            player->invulnerabilityFrames--;
        }

        // player position
        player->curPos.x += player->curPos.dx;
        player->curPos.y += player->curPos.dy;
        boundGameplayObject((PGAME_OBJECT)player);

        // to do move this to player update
        player->curPos.rot += player->curPos.drot;
        if(player->curPos.rot > DEGREES_IN_CIRCLE)
        {
            player->curPos.rot -= DEGREES_IN_CIRCLE;
        }
        else if(player->curPos.rot < -DEGREES_IN_CIRCLE)
        {
            player->curPos.rot += DEGREES_IN_CIRCLE;
        }
    }
}

//
// Gameplay State
//

// intialize game globals
static void initNewGame(void)
{
    g_Game.isPaused = false;
    g_Game.isGameOver = false;
    g_Game.wave = 0;
    g_Game.gameOverFrames = 0;
}

// start the next wave of disasteroids
static void initWave(void)
{
    g_Game.wave++;

    if(g_Game.wave > MAX_WAVE)
    {
        g_Game.wave = MAX_WAVE;
    }

    spawnPlayers();
    spawnDisasteroids();

    // spawn alien every 4 waves
    if((g_Game.wave & 0x3) == 0)
    {
        spawnAlien();
    }

    // remove all projectiles after every wave
    initProjectiles();

    initStars();

    if(g_Game.wave > 1)
    {
        // only strobe star on cleared waves
        strobeStars();

        playCDTrack(VICTORY_TRACK);
    }
}

// checks if the current wave of disasteroids is complete
static void isWaveOver(void)
{
    bool result = false;

    result = checkAliveDisasteroids();
    if(result == false)
    {
        // implement timer
        initWave();
        return;
    }

    return;
}

// checks if the game is over
static void isGameOver(void)
{
    int numPlayers = 0;

    //
    // check if we are waiting for the game over timer
    //
    if(g_Game.isGameOver == true)
    {
        g_Game.gameOverFrames--;
        if(g_Game.gameOverFrames <= 0)
        {
            pauseGame(GAME_OVER_TRACK);
        }

        return;
    }

    //
    // Check if the game is over
    //
    numPlayers = countAlivePlayers();

    if(g_Game.gameType == GAME_TYPE_COOP)
    {
        // COOP ends if all players are dead
        if(numPlayers == 0)
        {
            g_Game.isGameOver = true;
            g_Game.gameOverFrames = GAME_OVER_TIMER;
            return;
        }
    }
    else // versus mode
    {
        // versus mode ends when there's one player standing
        // check is for <= 1 in case both players kill each other
        // simultaneously
        if(numPlayers <= 1)
        {
            g_Game.isGameOver = true;
            g_Game.gameOverFrames = GAME_OVER_TIMER;
            return;
        }
    }

    // players are still alive
    return;
}

//
// Misc
//

// draws the current wave number on score
static void drawGameplayWave(void)
{
    int wave = 0;
    int color = 0;
    int xPos = 0;
    int yPos = 0;
    int xScale = 2;
    int yScale = 2;
    int letterSpacing = 6;
    unsigned char digit1 = 0;
    unsigned char digit2 = 0;

    color = g_Game.hudColor;

    wave = g_Game.wave;

    yPos = -80;
    xPos = -4;

    digit1 = (wave / 10) + '0';
    digit2 = (wave % 10) + '0';

    drawLetter(digit1, color, xPos + (letterSpacing * -1), yPos, xScale, yScale);
    drawLetter(digit2, color, xPos + (letterSpacing * 1), yPos, xScale, yScale);
}
