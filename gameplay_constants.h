#pragma once

//
// all gameplay related #defines
//

#define MAX_PLAYERS         (12)
#define DEGREES_IN_CIRCLE   (360)
#define FRAMES_PER_SECOND   (60)
#define FPS                 FRAMES_PER_SECOND

// screen size
#define SCREEN_MIN_X_INT (-160)
#define SCREEN_MAX_X_INT (160)
#define SCREEN_MIN_Y_INT (-120)
#define SCREEN_MAX_Y_INT (120)

#define SCREEN_MIN_X (toFIXED(SCREEN_MIN_X_INT))
#define SCREEN_MAX_X (toFIXED(SCREEN_MAX_X_INT))
#define SCREEN_MIN_Y (toFIXED(SCREEN_MIN_Y_INT))
#define SCREEN_MAX_Y (toFIXED(SCREEN_MAX_Y_INT))

// ship speeds
#define Z_SPEED_INC         (7)
#define THRUST_SPEED_INC    (toFIXED(0.30))
#define FRICTION            (toFIXED(0.020))

#define MAX_SPEED_X         (toFIXED(2))
#define MIN_SPEED_X         (toFIXED(-2))
#define MAX_SPEED_Y         (toFIXED(2))
#define MIN_SPEED_Y         (toFIXED(-2))

// max number of objects
#define MAX_DISASTEROIDS        (50)
#define MAX_ALIEN_PROJECTILES   (50)
#define MAX_PROJECTILES         (50)
#define MAX_EXPLOSIONS          (50)
#define MAX_STARS               (100)
#define MAX_SHIP_DEBRIS         (48)
#define MAX_WAVE                (99)

// various timers (in number of frames)
#define GAME_OVER_TIMER         (3 * FPS) // how long to wait after all players are dead before ending game
#define PROJECTILE_TIMER        ((1 * FPS) + 8) // how many frames each projectile is alive
#define INVULNERABILITY_TIMER   (2 * FPS) // how long the player is invulnerable after spawning
#define DISASTEROID_SPAWN_TIMER (INVULNERABILITY_TIMER + 30) // how long to wait before spawning the next wave of disasteroids
#define EXPLOSION_TIMER         (2 * FPS) // how long the explosions last
#define SHIP_DEBRIS_TIMER       (4 * FPS) // how long ship debris last
#define RESPAWN_TIMER           (2 * FPS) // how long to wait before respawning a player after they die
#define STAR_STROBE_TIMER       (3 * FPS) // how long to strobe stars for a new wave
#define STAR_LIFE_TIMER         (60 * FPS) // Max each star is alive for. This value get's randomized

// projectiles
#define PROJECTILE_SPEED        (toFIXED(2))

// game object radiuses
#define ALIEN_SHIP_RADIUS       (6)
#define PLAYER_SHIP_RADIUS      (5)
#define PROJECTILE_RADIUS       (1)

// score
#define ALIEN_DESTROY_POINTS       (10) // points for destroying the alien ship
#define PVP_DESTROY_POINTS         (5)  // points for destroying opponent in vs mode
#define DISASTEROID_DESTROY_POINTS (1)  // points for destroying a destroid
