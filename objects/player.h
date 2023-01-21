#pragma once
#include "objects.h"

// records whether or not an input has been pressed that frame
typedef struct _inputCache{

    bool pressedUp;
    bool pressedDown;
    bool pressedLeft;
    bool pressedRight;
    bool pressedAC;
    bool pressedB;
    bool pressedX;
    bool pressedY;
    bool pressedZ;
    bool pressedStart;
    bool pressedLT;
    bool pressedRT;
} INPUTCACHE, *PINPUTCACHE;

typedef struct _SCORE
{
    unsigned int wave;   // last wave player was alive for
    unsigned int points; // player score
} SCORE, *PSCORE;

// This structure represents the player
typedef struct _PLAYER
{
    GAME_OBJECT;

    // 0-11, controller ID
    int playerID;

    int color;

    int numLives;

    // did player hit boost this frame?
    bool isThrusting;

    // timers (in frames)
    int invulnerabilityFrames; // how long player in invulerable

    int respawnFrames; // how long before respawning player after death

    SCORE score;

    // hack to cache controller inputs
    INPUTCACHE input;

} PLAYER, *PPLAYER;
