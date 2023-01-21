#pragma once
#include "objects.h"

// background star
typedef struct _STAR
{
    GAME_OBJECT;

    int destroyFrames; // how many frames each star is alive for
    int type;
    int color;

} STAR, *PSTAR;

void initStars(void);
void updateStars(void);
void drawStars(void);
void strobeStars(void);
