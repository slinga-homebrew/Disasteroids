#pragma once

typedef enum _ALIEN_SIZE
{
    ALIEN_SIZE_SMALL = 0,
    ALIEN_SIZE_LARGE = 1,
    ALIEN_SIZE_MAX = 2,
} ALIEN_SIZE;

// how the alien moves on the SSMTF screen
typedef enum _ALIEN_LOGIC
{
    ALIEN_SSMTF_LOGIC_0 = 0,
    ALIEN_SSMTF_LOGIC_1,
    ALIEN_SSMTF_LOGIC_2,
    ALIEN_SSMTF_LOGIC_3,
    ALIEN_SSMTF_LOGIC_4,
    ALIEN_GAMEPLAY_LOGIC_ENTER,
    ALIEN_GAMEPLAY_LOGIC_SHOOT,
    ALIEN_GAMEPLAY_LOGIC_LEAVE,
} ALIEN_LOGIC;

// alien
typedef struct _ALIEN
{
    GAME_OBJECT;

    ALIEN_SIZE size;

    ALIEN_LOGIC logic;

    int destroyFrames; // how many frames each piece is alive for

    bool isShooting;

    int frame;

} ALIEN, *PALIEN;

void initAlien(void);
void drawAlien(void);
void updateAlien(void);
void spawnAlien(void);
void destroyAlien(PALIEN alien);

void initSsmtfAlien(void);
void updateSsmtfAlien(void);
