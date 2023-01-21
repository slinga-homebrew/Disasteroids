#pragma once
#include <jo/jo.h>

typedef enum _OBJECT_ACTIVE
{
    OBJECT_STATE_INACTIVE = 0,
    OBJECT_STATE_ACTIVE,
} OBJECT_ACTIVE;

// position and velocity of a game object
typedef struct _FIXED_POSITION
{
    jo_fixed x;
    jo_fixed y;
    jo_fixed rot;

    jo_fixed dx;
    jo_fixed dy;
    jo_fixed drot;

} FIXED_POSITION, *PFIXED_POSITION;

typedef struct _GAME_OBJECT
{
    OBJECT_ACTIVE objectState;

    // movement
    FIXED_POSITION curPos;

    //FIXED_POSITION oldPos;
    //FIXED_POSITION startPos;

} GAME_OBJECT, *PGAME_OBJECT;

void boundGameplayObject(PGAME_OBJECT gameObject);
