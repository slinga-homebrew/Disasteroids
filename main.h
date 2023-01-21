#pragma once

#include <jo/jo.h>
#include <string.h>
#include "util.h"
#include "state.h"
#include "gameplay_constants.h"
#include "objects/player.h"

#define GAME_VERSION "1.00"
#define MAX_DEBUG_LEVEL (1)

// supported game types
typedef enum _GAME_TYPE
{
    GAME_TYPE_COOP = 0,
    GAME_TYPE_VERSUS,
    GAME_TYPE_MAX,
} GAME_TYPE;

// number of lives per game
typedef enum _GAME_LIVES
{
    GAME_LIVES_1,
    GAME_LIVES_3,
    GAME_LIVES_6,
    GAME_LIVES_9,
    GAME_LIVES_MAX,
} GAME_LIVES;

// represents game state
typedef struct _GAME
{
    // current game state
    GAME_STATE gameState;

    // coop or versus
    GAME_TYPE gameType;

    jo_camera camera;

    // debug level
    int debug;

    // number of lives (1, 3, 6, 9)
    int numLives;

    // changeable HUD color
    jo_color hudColor;

    // is the game is paused
    bool isPaused;

    // is the game finished?
    bool isGameOver;

    // how many frames since all players were dead
    int gameOverFrames;

    // how long to wait before moving diasteroids
    int disasteroidSpawnFrames;

    // current game wave
    // higher = more disasteroids, faster speed
    int wave;

    // hack to cache controller inputs
    // used for menus by player 1
    INPUTCACHE input;

} GAME, *PGAME;

// globals
extern PLAYER g_Players[MAX_PLAYERS];
extern GAME g_Game;
