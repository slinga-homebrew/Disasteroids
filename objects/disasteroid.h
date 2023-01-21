#pragma once
#include "objects.h"
#include "projectile.h"

// different sizes for the disasteroids
typedef enum _DISASTEROID_SIZE
{
    DISASTEROID_SIZE_SMALL = 0,
    DISASTEROID_SIZE_MEDIUM = 1,
    DISASTEROID_SIZE_LARGE = 2,
    DIASTEROID_SIZE_MAX = 3,
} DISASTEROID_SIZE;

// radius of the various disasteroids
typedef enum _DISASTEROID_RADIUS_SIZE
{
    DISASTEROID_RADIUS_SIZE_SMALL = 4,
    DISASTEROID_RADIUS_SIZE_MEDIUM = 7,
    DISASTEROID_RADIUS_SIZE_LARGE = 10,
} DISASTEROID_RADIUS_SIZE;

// Disasteroid
typedef struct _DISASTEROID
{
    GAME_OBJECT;

    DISASTEROID_SIZE size; // small, medium, large

    int type; // 16 variations per size

    jo_fixed titleRadius; // used in the title screen, how far to rotate around the options

} DISASTEROID, *PDISASTEROID;

void initTitleScreenDisasteroids(void);
void updateTitleScreenDisasteroids(void);
void drawTitleScreenDisasteroids(void);

void initDisasteroids(void);
void updateDisasteroids(void);
void drawDisasteroids(void);
void destroyDisasteroid(PDISASTEROID disasteroid, PPROJECTILE projectile);
void splitDisasteroid(PDISASTEROID disasteroid);
void spawnDisasteroids(void);
bool checkAliveDisasteroids(void);
