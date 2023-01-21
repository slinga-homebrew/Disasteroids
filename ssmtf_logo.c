#include <jo/jo.h>
#include "assets/assets.h"
#include "main.h"
#include "ssmtf_logo.h"
#include "objects/alien.h"
#include "objects/projectile.h"

#define SSMTF_LOGO_TIMER (10 * FPS)

int g_ssmtfFrame = 0;

static void drawSsmtfLogo(void);

//
// SSMTF logo callbacks
//

// initializations for SSMTF screen
void ssmtfLogo_init(void)
{
    g_ssmtfFrame = 0;

    initSsmtfAlien();
    initAlienProjectiles();
}

// allow player one to hit a key to skip
void ssmtfLogo_input(void)
{
    if(g_Game.gameState != GAME_STATE_SSMTF_LOGO)
    {
        return;
    }

    //
    // skip the logo if player 1 hits start, a, b, c
    //

    // payer 1 hit start, a, b, c
    if(jo_is_pad1_key_pressed(JO_KEY_A) ||
       jo_is_pad1_key_pressed(JO_KEY_B) ||
       jo_is_pad1_key_pressed(JO_KEY_C) ||
       jo_is_pad1_key_pressed(JO_KEY_START))
    {
        if(g_Game.input.pressedStart == false &&
           g_Game.input.pressedAC == false &&
           g_Game.input.pressedB == false)
        {
            g_Game.input.pressedStart = true;
            g_Game.input.pressedAC = true;
            g_Game.input.pressedB = true;

            // skip to the title screen
            transitionState(GAME_STATE_TITLE_SCREEN);
            return;
        }
    }
    else
    {
        g_Game.input.pressedStart = false;
        g_Game.input.pressedAC = false;
        g_Game.input.pressedB = false;
    }

    return;
}

// update callback routine for SSMTF logo
void ssmtfLogo_update(void)
{
    if(g_Game.gameState != GAME_STATE_SSMTF_LOGO)
    {
        return;
    }

    g_ssmtfFrame++;

    // check if the the timer has expired
    if(g_ssmtfFrame >= SSMTF_LOGO_TIMER)
    {
        transitionState(GAME_STATE_TITLE_SCREEN);
        return;
    }

    updateSsmtfAlien();
    updateAlienProjectiles();

    return;
}

// draws the Sega Saturn Multiplayer Task Force logo and alien
void ssmtfLogo_draw(void)
{
    if(g_Game.gameState != GAME_STATE_SSMTF_LOGO)
    {
        return;
    }

    drawSsmtfLogo();
    drawAlien();
    drawAlienProjectiles();
}

//
// Private SSMTF functions
//

// draws the screen text
static void drawSsmtfLogo(void)
{
    int color = g_Game.hudColor;
    int xPos = 0;
    int yPos = 0;
    int letterSpacing = 12;
    int xScale = 2;
    int yScale = 3;

    //
    // THE SEGA SATURN
    //

    xPos = -90;
    yPos = -32;

    drawLetter('T', color, xPos + letterSpacing * 0, yPos, xScale, yScale);
    drawLetter('H', color, xPos + letterSpacing * 1, yPos, xScale, yScale);
    drawLetter('E', color, xPos + letterSpacing * 2, yPos, xScale, yScale);

    drawLetter('S', color, xPos + letterSpacing * 4, yPos, xScale, yScale);
    drawLetter('E', color, xPos + letterSpacing * 5, yPos, xScale, yScale);
    drawLetter('G', color, xPos + letterSpacing * 6, yPos, xScale, yScale);
    drawLetter('A', color, xPos + letterSpacing * 7, yPos, xScale, yScale);

    drawLetter('S', color, xPos + letterSpacing * 9, yPos, xScale, yScale);
    drawLetter('A', color, xPos + letterSpacing * 10, yPos, xScale, yScale);
    drawLetter('T', color, xPos + letterSpacing * 11, yPos, xScale, yScale);
    drawLetter('U', color, xPos + letterSpacing * 12, yPos, xScale, yScale);
    drawLetter('R', color, xPos + letterSpacing * 13, yPos, xScale, yScale);
    drawLetter('N', color, xPos + letterSpacing * 14, yPos, xScale, yScale);

    //
    // MULTIPLAYER TASK FORCE
    //

    xPos = -132;
    yPos = 0;

    drawLetter('M', color, xPos + letterSpacing * 0, yPos, xScale, yScale);
    drawLetter('U', color, xPos + letterSpacing * 1, yPos, xScale, yScale);
    drawLetter('L', color, xPos + letterSpacing * 2, yPos, xScale, yScale);
    drawLetter('T', color, xPos + letterSpacing * 3, yPos, xScale, yScale);
    drawLetter('I', color, xPos + letterSpacing * 4, yPos, xScale, yScale);
    drawLetter('P', color, xPos + letterSpacing * 5, yPos, xScale, yScale);
    drawLetter('L', color, xPos + letterSpacing * 6, yPos, xScale, yScale);
    drawLetter('A', color, xPos + letterSpacing * 7, yPos, xScale, yScale);
    drawLetter('Y', color, xPos + letterSpacing * 8, yPos, xScale, yScale);
    drawLetter('E', color, xPos + letterSpacing * 9, yPos, xScale, yScale);
    drawLetter('R', color, xPos + letterSpacing * 10, yPos, xScale, yScale);

    drawLetter('T', color, xPos + letterSpacing * 12, yPos, xScale, yScale);
    drawLetter('A', color, xPos + letterSpacing * 13, yPos, xScale, yScale);
    drawLetter('S', color, xPos + letterSpacing * 14, yPos, xScale, yScale);
    drawLetter('K', color, xPos + letterSpacing * 15, yPos, xScale, yScale);

    drawLetter('F', color, xPos + letterSpacing * 17, yPos, xScale, yScale);
    drawLetter('O', color, xPos + letterSpacing * 18, yPos, xScale, yScale);
    drawLetter('R', color, xPos + letterSpacing * 19, yPos, xScale, yScale);
    drawLetter('C', color, xPos + letterSpacing * 20, yPos, xScale, yScale);
    drawLetter('E', color, xPos + letterSpacing * 21, yPos, xScale, yScale);

    //
    // PROUDLY PRESENTS
    //

    xPos = -96;
    yPos = 32;

    drawLetter('P', color, xPos + letterSpacing * 0, yPos, xScale, yScale);
    drawLetter('R', color, xPos + letterSpacing * 1, yPos, xScale, yScale);
    drawLetter('O', color, xPos + letterSpacing * 2, yPos, xScale, yScale);
    drawLetter('U', color, xPos + letterSpacing * 3, yPos, xScale, yScale);
    drawLetter('D', color, xPos + letterSpacing * 4, yPos, xScale, yScale);
    drawLetter('L', color, xPos + letterSpacing * 5, yPos, xScale, yScale);
    drawLetter('Y', color, xPos + letterSpacing * 6, yPos, xScale, yScale);

    drawLetter('P', color, xPos + letterSpacing * 8, yPos, xScale, yScale);
    drawLetter('R', color, xPos + letterSpacing * 9, yPos, xScale, yScale);
    drawLetter('E', color, xPos + letterSpacing * 10, yPos, xScale, yScale);
    drawLetter('S', color, xPos + letterSpacing * 11, yPos, xScale, yScale);
    drawLetter('E', color, xPos + letterSpacing * 12, yPos, xScale, yScale);
    drawLetter('N', color, xPos + letterSpacing * 13, yPos, xScale, yScale);
    drawLetter('T', color, xPos + letterSpacing * 14, yPos, xScale, yScale);
    drawLetter('S', color, xPos + letterSpacing * 15, yPos, xScale, yScale);
}
