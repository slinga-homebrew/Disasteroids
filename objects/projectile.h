#pragma once
#include "objects.h"
#include "alien.h"
#include "player.h"

// projectiles fired by the player/alien
typedef struct _PROJECTILE
{
    GAME_OBJECT;

    int color;

    // who owns the projectile, needed for scoring
    int playerID;

    // how many frames to last for
    int destroyFrames;

    // how many frames to wait before drawing
    // this is useful for the alien ship
    // otherwise the bullets appear to be coming from within the ship
    int ignoreFrames;

    // allow screen wrapping
    bool boundProjectile;

} PROJECTILE, *PPROJECTILE;

// player projectiles
void initProjectiles(void);
void drawProjectiles(void);
void updateProjectiles(void);
void spawnProjectile(PPLAYER player);

// alien projectiles
void initAlienProjectiles(void);
void drawAlienProjectiles(void);
void updateAlienProjectiles(void);
void spawnAlienProjectile(PALIEN alien, bool screenWrap);
