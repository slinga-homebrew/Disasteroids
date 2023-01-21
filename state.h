#pragma once

// various game states
// each game state has it's own input/update/draw routines
typedef enum
{
    GAME_STATE_UNINITIALIZED = 0,
    GAME_STATE_SSMTF_LOGO,
    GAME_STATE_TITLE_SCREEN,
    GAME_STATE_GAMEPLAY,
} GAME_STATE;

void transitionState(GAME_STATE newState);
