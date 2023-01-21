#pragma once
#include "objects.h"
#include "alien.h"
#include "disasteroid.h"

// explosion particles
typedef struct _EXPLOSION
{
    GAME_OBJECT;

    int destroyFrames; // how many frames each piece is alive for

    int color;

} EXPLOSION, *PEXPLOSION;

// ship debris size
typedef enum _SHIP_DEBRIS_SIZE
{
    SHIP_DEBRIS_SIZE_SMALL = 0,
    SHIP_DEBRIS_SIZE_LARGE = 1,
    SHIP_DEBRIS_SIZE_MAX = 2,
} SHIP_DEBRIS_SIZE;

// exploded ship parts
typedef struct _SHIP_DEBRIS
{
    GAME_OBJECT;

    int playerID;

    int color;

    int destroyFrames; // how many frames each piece is alive for

    SHIP_DEBRIS_SIZE size;

} SHIP_DEBRIS, *PSHIP_DEBRIS;

// Disasteroid Explosions
void initExplosions(void);
void updateExplosions(void);
void drawExplosions(void);
void spawnExplosion(PDISASTEROID disasteroid);

// Ship Debris
void initShipDebris(void);
void drawShipDebris(void);
void updateShipDebris(void);
void spawnShipDebris(PPLAYER player, SHIP_DEBRIS_SIZE size);
void spawnAlienDebris(PALIEN alien, SHIP_DEBRIS_SIZE size);
