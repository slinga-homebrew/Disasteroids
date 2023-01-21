#include "collision.h"
#include "main.h"
#include "assets/assets.h"
#include "objects/ship.h"
#include "objects/disasteroid.h"

extern DISASTEROID g_Disasteroids[MAX_DISASTEROIDS];
extern PROJECTILE g_Projectiles[MAX_PROJECTILES];
extern PROJECTILE g_AlienProjectiles[MAX_ALIEN_PROJECTILES];
extern ALIEN g_Alien;

// collision detection
static void checkForAlienProjectilesCollision(void);
static void checkForAlienPlayersCollision(void);
static void checkForDisasteroidProjectilesCollision(PDISASTEROID disasteroid);
static void checkForDisasteroidPlayersCollision(PDISASTEROID disasteroid);
static void checkForPlayerProjectilesCollision(PPLAYER player);
static void checkForPlayerPlayersCollision(PPLAYER player);
static void checkForPlayerAlienProjectilesCollision(PPLAYER player);

// collision utility functions
static int checkForCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2);
static void incrementScoreByPlayerID(int playerID, int amount);
static void backoffPlayers(PPLAYER playerA, PPLAYER playerB);

//
// Alien
//

// check if the alien collides with:
// - projectile
// - player
void checkForAlienCollisions(void)
{
    if(g_Alien.objectState != OBJECT_STATE_ACTIVE)
    {
        return;
    }

    checkForAlienProjectilesCollision();
    checkForAlienPlayersCollision();

    return;
}

// check if alien is hit by a player projectile
static void checkForAlienProjectilesCollision(void)
{
    PPROJECTILE projectile = NULL;
    int result = 0;

    if(g_Alien.objectState != OBJECT_STATE_ACTIVE)
    {
        return;
    }

    // check if the alien collided with any of the projectiles
    for(unsigned int k = 0; k < COUNTOF(g_Projectiles); k++)
    {
        projectile = &g_Projectiles[k];

        if(projectile->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        result = checkForCircleCollision(toINT(g_Alien.curPos.x), toINT(g_Alien.curPos.y), ALIEN_SHIP_RADIUS,
                                         toINT(projectile->curPos.x), toINT(projectile->curPos.y), PROJECTILE_RADIUS);
        if(result != 0)
        {
            // destroy alien and award points
            destroyAlien(&g_Alien);
            incrementScoreByPlayerID(projectile->playerID, ALIEN_DESTROY_POINTS);
            return;
        }
    }

    return;
}

// check if alien is hit by a player
static void checkForAlienPlayersCollision(void)
{
    PPLAYER player = NULL;
    int result = 0;

    if(g_Alien.objectState != OBJECT_STATE_ACTIVE)
    {
        return;
    }

    // check if the alien collided with any of the players
    for(unsigned int j = 0; j < COUNTOF(g_Players); j++)
    {
        player = &g_Players[j];

        if(player->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        if(player->invulnerabilityFrames > 0)
        {
            // player is invulnerable, can't damage
            continue;
        }

        result = checkForCircleCollision(toINT(g_Alien.curPos.x), toINT(g_Alien.curPos.y), ALIEN_SHIP_RADIUS,
                                         toINT(player->curPos.x), toINT(player->curPos.y), PLAYER_SHIP_RADIUS);
        if(result != 0)
        {
            // destroy alien and player
            // no points are awarded
            destroyAlien(&g_Alien);
            destroyPlayer(player);
            return;
        }
    }
}

//
// Disasteroid
//

// check if any disasteroid collides with:
// - projectile
// - player
void checkForDisasteroidCollisions(void)
{
    PDISASTEROID disasteroid = NULL;

    // iterate through all disasteroids
    for(unsigned int i = 0; i < COUNTOF(g_Disasteroids); i++)
    {
        disasteroid = &g_Disasteroids[i];

        if(disasteroid->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        checkForDisasteroidProjectilesCollision(disasteroid);
        checkForDisasteroidPlayersCollision(disasteroid);
    }
}

// check if disasteroid is hit by a player projectile
static void checkForDisasteroidProjectilesCollision(PDISASTEROID disasteroid)
{
    PPROJECTILE projectile = NULL;
    int result = 0;
    int radius = 0;

    if(disasteroid->objectState != OBJECT_STATE_ACTIVE)
    {
        return;
    }

    // check if any of the disasteroids collided with any of the projectiles
    for(unsigned int k = 0; k < COUNTOF(g_Projectiles); k++)
    {
        projectile = &g_Projectiles[k];

        if(projectile->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        // add two because we have variance in sizes
        radius = getDisasteroidRadiusSize(disasteroid->size) + 2;

        result = checkForCircleCollision(toINT(disasteroid->curPos.x), toINT(disasteroid->curPos.y), radius,
                                         toINT(projectile->curPos.x), toINT(projectile->curPos.y), PROJECTILE_RADIUS);
        if(result != 0)
        {
            // destroy the disasteroid
            destroyDisasteroid(disasteroid, projectile);
            return;
        }
    }

    return;
}

// check if disasteroid is hit by a player
static void checkForDisasteroidPlayersCollision(PDISASTEROID disasteroid)
{
    PPLAYER player = NULL;
    int result = 0;
    int radius = 0;

    if(disasteroid->objectState != OBJECT_STATE_ACTIVE)
    {
        return;
    }

    // check if any of the disasteroids collided with any of the players
    for(unsigned int j = 0; j < COUNTOF(g_Players); j++)
    {
        player = &g_Players[j];

        if(player->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        if(player->invulnerabilityFrames > 0)
        {
            // player is invulnerable, can't damage
            continue;
        }

        // add two because we have variance in sizes
        radius = getDisasteroidRadiusSize(disasteroid->size) + 2;

        result = checkForCircleCollision(toINT(disasteroid->curPos.x), toINT(disasteroid->curPos.y), radius,
                                        toINT(player->curPos.x), toINT(player->curPos.y), PLAYER_SHIP_RADIUS);
        if(result != 0)
        {
            // destroy diasteroid and player
            destroyDisasteroid(disasteroid, NULL);
            destroyPlayer(player);
            return;
        }
    }
}

//
// Player
//

// check if any players collides with:
// - projectile
// - alien projectile
// - other player
// we already checked for player vs disasteroid collision
void checkForPlayerCollisions(void)
{
    PPLAYER player = NULL;

    // iterate through all Asteroids
    for(unsigned int i = 0; i < COUNTOF(g_Players); i++)
    {
        player = &g_Players[i];

        if(player->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        checkForPlayerProjectilesCollision(player);
        checkForPlayerAlienProjectilesCollision(player);
        checkForPlayerPlayersCollision(player);
    }
}

// check if player is hit by a player projectile
static void checkForPlayerProjectilesCollision(PPLAYER player)
{
    PPROJECTILE projectile = NULL;
    int result = 0;

    if(player->objectState == OBJECT_STATE_INACTIVE)
    {
        return;
    }

    if(player->invulnerabilityFrames > 0)
    {
        // can't shoot invulnerable player
        return;
    }

    // check if any of the Disasteroids collided with any of the projectiles
    for(unsigned int k = 0; k < COUNTOF(g_Projectiles); k++)
    {
        projectile = &g_Projectiles[k];

        if(projectile->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        if(projectile->playerID == player->playerID)
        {
            // can't shoot yourself
            continue;
        }

        result = checkForCircleCollision(toINT(player->curPos.x), toINT(player->curPos.y), PLAYER_SHIP_RADIUS,
                                         toINT(projectile->curPos.x), toINT(projectile->curPos.y), PROJECTILE_RADIUS);
        if(result != 0)
        {
            if(g_Game.gameType == GAME_TYPE_COOP)
            {
                // in coop bounce the player around
                player->curPos.dx += projectile->curPos.dx;
                player->curPos.dy += projectile->curPos.dy;
            }
            else
            {
                // in versus kill the player
                destroyPlayer(player);
                incrementScoreByPlayerID(projectile->playerID, PVP_DESTROY_POINTS);
            }

            projectile->objectState = OBJECT_STATE_INACTIVE;

            return;
        }
    }

    return;
}

// check if player is hit by an alien projectile
static void checkForPlayerAlienProjectilesCollision(PPLAYER player)
{
    PPROJECTILE projectile = NULL;
    int result = 0;

    if(player->objectState == OBJECT_STATE_INACTIVE)
    {
        return;
    }

    if(g_Alien.objectState == OBJECT_STATE_INACTIVE)
    {
        // not technically correct, but skip check if
        // alien despawned
        return;
    }

    if(player->invulnerabilityFrames > 0)
    {
        // can't shoot invulnerable player
        return;
    }

    // check if the player collided with any of the alien projectiles
    for(unsigned int k = 0; k < COUNTOF(g_AlienProjectiles); k++)
    {
        projectile = &g_AlienProjectiles[k];

        if(projectile->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        result = checkForCircleCollision(toINT(player->curPos.x), toINT(player->curPos.y), PLAYER_SHIP_RADIUS,
                                         toINT(projectile->curPos.x), toINT(projectile->curPos.y), PROJECTILE_RADIUS);
        if(result != 0)
        {
            // kill the player
            destroyPlayer(player);
            projectile->objectState = OBJECT_STATE_INACTIVE;

            return;
        }
    }

    return;
}

// check if player is hit by a player
static void checkForPlayerPlayersCollision(PPLAYER playerA)
{
    PPLAYER playerB = NULL;
    int result = 0;

    if(playerA->objectState == OBJECT_STATE_INACTIVE)
    {
        return;
    }

    if(playerA->invulnerabilityFrames > 0)
    {
        return;
    }

    // check if any of the Asteroids collided with any of the players
    for(unsigned int j = 0; j < COUNTOF(g_Players); j++)
    {
        playerB = &g_Players[j];

        if(playerB->objectState != OBJECT_STATE_ACTIVE)
        {
            continue;
        }

        if(playerA->playerID >= playerB->playerID)
        {
            // don't perform collision detection against your self
            // don't perform collision detection against players multiple times
            continue;
        }

        if(playerB->invulnerabilityFrames > 0)
        {
            // player is invulnerable, can't damage
            continue;
        }

        result = checkForCircleCollision(toINT(playerA->curPos.x), toINT(playerA->curPos.y), PLAYER_SHIP_RADIUS,
                                         toINT(playerB->curPos.x), toINT(playerB->curPos.y), PLAYER_SHIP_RADIUS);
        if(result != 0)
        {
            // bounce players off each other
            backoffPlayers(playerA, playerB);
            return;
        }
    }

    return;
}

//
// Collision utility functions
//

// rewind colliding players so they are no longer colliding
static void backoffPlayers(PPLAYER playerA, PPLAYER playerB)
{
    int result = 0;
    jo_fixed dx = 0;
    jo_fixed dy = 0;
    jo_fixed newDx = 0;
    jo_fixed newDy = 0;

    if(playerA->curPos.dx > playerB->curPos.dx)
    {
        dx = toFIXED(1);
    }
    else
    {
        dx = toFIXED(-1);
    }

    if(playerA->curPos.dy > playerB->curPos.dy)
    {
        dy = toFIXED(1);
    }
    else
    {
        dy = toFIXED(-1);
    }

    for(int i = 0; i < 10; i++)
    {
        playerA->curPos.x -= dx;
        playerA->curPos.y -= dy;

        playerB->curPos.x += dx;
        playerB->curPos.y += dy;

        result = checkForCircleCollision(toINT(playerA->curPos.x), toINT(playerA->curPos.y), PLAYER_SHIP_RADIUS,
                                         toINT(playerB->curPos.x), toINT(playerB->curPos.y), PLAYER_SHIP_RADIUS);
        if(result == 0)
        {
            // no longer colliding
            break;
        }
    }

    newDx = JO_ABS(playerA->curPos.dx) + JO_ABS(playerB->curPos.dx);
    newDy = JO_ABS(playerA->curPos.dy) + JO_ABS(playerB->curPos.dy);

    newDx = jo_fixed_mult(newDx, toFIXED(0.65));
    newDy = jo_fixed_mult(newDy, toFIXED(0.65));

    if(dx > 0)
    {
        playerA->curPos.dx = -newDx;
        playerB->curPos.dx = newDx;
    }
    else
    {
        playerA->curPos.dx = newDx;
        playerB->curPos.dx = -newDx;
    }

    if(dy > 0)
    {
        playerA->curPos.dy = -newDy;
        playerB->curPos.dy = newDy;
    }
    else
    {
        playerA->curPos.dy = newDy;
        playerB->curPos.dy = -newDy;
    }
}

// returns true if two circles intersect
// uses the distance formula without using sqrt
static int checkForCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2)
{
    int distance1 = 0;
    int distance2 = 0;

    distance1 = ((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1));
    distance2 = (r1 + r2) * (r1 + r2);

    if(distance2 > distance1)
    {
        return 1;
    }

    return 0;
}

// adds amount to the player score
static void incrementScoreByPlayerID(int playerID, int amount)
{
    PPLAYER player = NULL;

    if(playerID < 0 || playerID > 11)
    {
        return;
    }

    player = &g_Players[playerID];
    player->score.points += amount;

    return;
}
