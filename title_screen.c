#include <jo/jo.h>
#include "main.h"
#include "assets/assets.h"
#include "title_screen.h"
#include "objects/disasteroid.h"
#include "objects/ship.h"
#include "objects/star.h"

// globals for menu options
int g_TitleScreenChoice = 0;
int g_TitleTypeChoice = 0;
int g_TitleHudChoice = 0;
int g_TitleLivesChoice = 0;
int g_TitleScreenCursorColor = 0;
int g_TitleLives[]= {3, 6, 9, 12, 1};

typedef enum _MENU_OPTIONS
{
    TITLE_OPTION_GAME_TYPE = 0,
    TITLE_OPTION_GAME_LIVES = 1,
    TITLE_OPTION_GAME_HUD = 2,
    TITLE_OPTION_GAME_START = 3,
    TITLE_OPTION_MAX,
} MENU_OPTIONS;

static void drawTitleRectangle(void);
static void drawTitle(void);
static void drawOptions(void);
static void drawVersion(void);
static void drawMenuCursor(void);
static bool moreThanOnePlayer(void);

//
// Title screen callbacks
//

// initializations for title screen
void titleScreen_init(void)
{
    // random ship color for the cursor
    int index = jo_random(COUNTOF(g_Assets.randomizedColors)) - 1;
    g_TitleScreenCursorColor = g_Assets.randomizedColors[index];

    // starting selected option
    g_TitleScreenChoice = 0;

    g_Game.numLives = g_TitleLives[0];

    // reset the asteroids if needed
    initTitleScreenDisasteroids();

    initStars();
}

// handles input for the title screen
// only player one can control the title screen
void titleScreen_input(void)
{
    int titleScreenChoice = 0;

    if(g_Game.gameState != GAME_STATE_TITLE_SCREEN)
    {
        return;
    }

    titleScreenChoice = g_TitleScreenChoice;

    if (jo_is_pad1_key_pressed(JO_KEY_UP))
    {
        if(g_Game.input.pressedUp == false)
        {
            titleScreenChoice--;
        }
        g_Game.input.pressedUp = true;
    }
    else
    {
        g_Game.input.pressedUp = false;
    }

    if (jo_is_pad1_key_pressed(JO_KEY_DOWN))
    {
        if(g_Game.input.pressedDown == false)
        {
            titleScreenChoice++;
        }
        g_Game.input.pressedDown = true;
    }
    else
    {
        g_Game.input.pressedDown = false;
    }

    // keep title screen choice in range
    sanitizeValue(&titleScreenChoice, 0, TITLE_OPTION_MAX);

    g_TitleScreenChoice = titleScreenChoice;

    // select an option here
    if (jo_is_pad1_key_pressed(JO_KEY_START) ||
        jo_is_pad1_key_pressed(JO_KEY_A) ||
        jo_is_pad1_key_pressed(JO_KEY_C) ||
        jo_is_pad1_key_pressed(JO_KEY_RIGHT) ||
        jo_is_pad1_key_pressed(JO_KEY_LEFT))
    {
        if(g_Game.input.pressedStart == false)
        {
            switch(titleScreenChoice)
            {
                case TITLE_OPTION_GAME_TYPE:
                {
                    if(jo_is_pad1_key_pressed(JO_KEY_LEFT))
                    {
                        g_TitleTypeChoice--;
                    }
                    else
                    {
                        g_TitleTypeChoice++;
                    }

                    sanitizeValue(&g_TitleTypeChoice, 0, GAME_TYPE_MAX);

                    g_Game.gameType = g_TitleTypeChoice;
                    break;
                }
                case TITLE_OPTION_GAME_LIVES:
                {
                    if(jo_is_pad1_key_pressed(JO_KEY_LEFT))
                    {
                        g_TitleLivesChoice--;
                    }
                    else
                    {
                        g_TitleLivesChoice++;
                    }

                    sanitizeValue(&g_TitleLivesChoice, 0, COUNTOF(g_TitleLives));

                    g_Game.numLives = g_TitleLives[g_TitleLivesChoice];
                    break;
                }
                case TITLE_OPTION_GAME_HUD:
                {
                    if(jo_is_pad1_key_pressed(JO_KEY_LEFT))
                    {
                        g_TitleHudChoice--;
                    }
                    else
                    {
                        g_TitleHudChoice++;
                    }

                    sanitizeValue(&g_TitleHudChoice, 0,  COUNTOF(g_Assets.hudColors));

                    g_Game.hudColor = g_Assets.hudColors[g_TitleHudChoice];
                    break;
                }
                case TITLE_OPTION_GAME_START:
                {
                    if(jo_is_pad1_key_pressed(JO_KEY_RIGHT) ||
                       jo_is_pad1_key_pressed(JO_KEY_LEFT))
                    {
                        // ignore left\right on start
                        break;
                    }

                    // prevent game from starting if not enough players for GAME_TYPE_VERSUS
                    if(g_Game.gameType == GAME_TYPE_VERSUS)
                    {
                        bool allowVersus = false;

                        // make sure we have at least two players for versus mode
                        allowVersus = moreThanOnePlayer();
                        if(allowVersus == false)
                        {
                            // not enough players
                            jo_audio_play_sound(&g_Assets.popPCM);
                            break;
                        }

                        // enough players, fall through to game start
                    }

                    transitionState(GAME_STATE_GAMEPLAY);
                    break;
                }
            }
        }
        g_Game.input.pressedStart = true;
    }
    else
    {
        g_Game.input.pressedStart = false;
    }

    return;
}

// update callback for the title screens
void titleScreen_update(void)
{
    if(g_Game.gameState != GAME_STATE_TITLE_SCREEN)
    {
        return;
    }

    updateTitleScreenShips();
    updateTitleScreenDisasteroids();
    updateStars();

    return;
}

// draws the title screen
void titleScreen_draw(void)
{
    if(g_Game.gameState != GAME_STATE_TITLE_SCREEN)
    {
        return;
    }

    drawStars();
    drawOptions();
    drawVersion();
    drawMenuCursor();
    drawTitleScreenShips();
    drawTitleScreenDisasteroids();
    drawTitle();

    return;
}

// used for changing the HUD color
void incrementHudColor(void)
{
    g_TitleHudChoice++;

    if(g_TitleHudChoice < 0)
    {
        g_TitleHudChoice = COUNTOF(g_Assets.hudColors) - 1;
    }
    else if(g_TitleHudChoice > (int)(COUNTOF(g_Assets.hudColors) - 1))
    {
        g_TitleHudChoice = 0;
    }
    g_Game.hudColor = g_Assets.hudColors[g_TitleHudChoice];
}

//
// Title screen private functions
//

// returns true if there are two or more controllers connected
static bool moreThanOnePlayer(void)
{
    int count = 0;

    for(unsigned int i = 0; i < COUNTOF(g_Players); i++)
    {
        if(!jo_is_input_available(i))
        {
            // controller not connected
            continue;
        }

        count++;

        if(count >= 2)
        {
            // found at least two connected controllers
            return true;
        }
    }

    // didn't find two controllers
    return false;
}

//
// title screen draw functions
//

// draw a black rectangle under the title text
// this will mask the Disasteroids and make it easier to read the title text
static void drawTitleRectangle(void)
{
    jo_3d_mesh* mesh = g_Assets.rectangle;
    int xPos = 0;
    int yPos = -70;

    jo_3d_push_matrix();
    {
        jo_3d_camera_look_at(&g_Game.camera);
        jo_3d_set_mesh_color(mesh, JO_COLOR_Black);
        jo_3d_translate_matrix(xPos, yPos, 0);
        jo_3d_mesh_draw(mesh);
    }
    jo_3d_pop_matrix();
}

// "DISASTEROIDS" title text
static void drawTitle(void)
{
    int color = g_Game.hudColor;
    int xPos = -129;
    int yPos = -58;
    int letterSpacing = 22;
    int xScale = 4;
    int yScale = 6;

    // black rectangle under DISASTEROIDS title
    // used to mask out disasteroids
    drawTitleRectangle();

    //
    // DISASTEROIDS title
    //

    drawLetter('D', color, xPos + letterSpacing * 0, yPos, xScale, yScale);
    drawLetter('I', color, xPos + letterSpacing * 1, yPos, xScale, yScale);
    drawLetter('S', color, xPos + letterSpacing * 2, yPos, xScale, yScale);
    drawLetter('A', color, xPos + letterSpacing * 3, yPos, xScale, yScale);
    drawLetter('S', color, xPos + letterSpacing * 4, yPos, xScale, yScale);
    drawLetter('T', color, xPos + letterSpacing * 5, yPos, xScale, yScale);
    drawLetter('E', color, xPos + letterSpacing * 6, yPos, xScale, yScale);
    drawLetter('R', color, xPos + letterSpacing * 7, yPos, xScale, yScale);
    drawLetter('O', color, xPos + letterSpacing * 8, yPos, xScale, yScale);
    drawLetter('I', color, xPos + letterSpacing * 9, yPos, xScale, yScale);
    drawLetter('D', color, xPos + letterSpacing * 10, yPos, xScale, yScale);
    drawLetter('S', color, xPos + letterSpacing * 11, yPos, xScale, yScale);
}

// Options menu + values
static void drawOptions(void)
{
    int color = g_Game.hudColor;
    int xPos = 0;
    int yPos = 0;
    int letterSpacing = 11;
    int xScale = 2;
    int yScale = 2;
    char upperDigit = 0;
    char lowerDigit = 0;

    //
    // game mode (coop or vs)
    //

    xPos = 11;
    yPos = 0;

    drawLetter('M', color, xPos - letterSpacing * 4, yPos, xScale, yScale);
    drawLetter('O', color, xPos - letterSpacing * 3, yPos, xScale, yScale);
    drawLetter('D', color, xPos - letterSpacing * 2, yPos, xScale, yScale);
    drawLetter(':', color, xPos - letterSpacing * 1, yPos, xScale, yScale);

    if(g_Game.gameType == GAME_TYPE_COOP)
    {
        drawLetter('C', color, xPos - letterSpacing * 0, yPos, xScale, yScale);
        drawLetter('O', color, xPos - letterSpacing * -1, yPos, xScale, yScale);
    }
    else if(g_Game.gameType == GAME_TYPE_VERSUS)
    {
        drawLetter('V', color, xPos - letterSpacing * 0, yPos, xScale, yScale);
        drawLetter('S', color, xPos - letterSpacing * -1, yPos, xScale, yScale);
    }

    //
    // tries (num lives, 1,3,6,9,12)
    //

    yPos = 15;

    drawLetter('T', color, xPos - letterSpacing * 4, yPos, xScale, yScale);
    drawLetter('R', color, xPos - letterSpacing * 3, yPos, xScale, yScale);
    drawLetter('Y', color, xPos - letterSpacing * 2, yPos, xScale, yScale);
    drawLetter(':', color, xPos - letterSpacing * 1, yPos, xScale, yScale);

    // display the number of lives value
    upperDigit = (g_Game.numLives / 10) + '0';
    lowerDigit = (g_Game.numLives % 10) + '0';

    drawLetter(upperDigit, color, xPos - letterSpacing * 0, yPos, xScale, yScale);
    drawLetter(lowerDigit, color, xPos - letterSpacing * -1, yPos, xScale, yScale);

    //
    // HUD color
    //

    yPos = 30;

    drawLetter('H', color, xPos - letterSpacing * 4, yPos, xScale, yScale);
    drawLetter('U', color, xPos - letterSpacing * 3, yPos, xScale, yScale);
    drawLetter('D', color, xPos - letterSpacing * 2, yPos, xScale, yScale);
    drawLetter(':', color, xPos - letterSpacing * 1, yPos, xScale, yScale);

    // display the HUD value
    upperDigit = ((g_TitleHudChoice + 1) / 10) + '0';
    lowerDigit = ((g_TitleHudChoice + 1) % 10) + '0';

    drawLetter(upperDigit, color, xPos - letterSpacing * 0, yPos, xScale, yScale);
    drawLetter(lowerDigit, color, xPos - letterSpacing * -1, yPos, xScale, yScale);

    //
    // START
    //

    xPos += 6;
    yPos = 45;

    drawLetter('S', color, xPos - letterSpacing * 4, yPos, xScale, yScale);
    drawLetter('T', color, xPos - letterSpacing * 3, yPos, xScale, yScale);
    drawLetter('A', color, xPos - letterSpacing * 2, yPos, xScale, yScale);
    drawLetter('R', color, xPos - letterSpacing * 1, yPos, xScale, yScale);
    drawLetter('T', color, xPos - letterSpacing * 0, yPos, xScale, yScale);
    drawLetter('!', color, xPos - letterSpacing * -1, yPos, xScale, yScale);
}

// version text
static void drawVersion(void)
{
    int color = g_Game.hudColor;
    int xPos = 110;
    int yPos = 95;
    int letterSpacing = 6;
    int xScale = 1;
    int yScale = 1;

    // dynamically draw the game version
    for(unsigned int i = 0; i < sizeof(GAME_VERSION); i++)
    {
        drawLetter(GAME_VERSION[i], color, xPos + letterSpacing * i, yPos, xScale, yScale);
    }
}

// ship used as the menu cursor
static void drawMenuCursor(void)
{
    int color = g_TitleScreenCursorColor;
    jo_3d_mesh* mesh = g_Assets.cursorShip;
    int xPos = 0;
    int yPos = 0;
    int ang = 90; // face right

    xPos = -40;
    yPos = (g_TitleScreenChoice * 15) - 4; // vertical position varies based on selection

    jo_3d_push_matrix();
    {
        jo_3d_camera_look_at(&g_Game.camera);
        jo_3d_set_mesh_color(mesh, color);
        jo_3d_translate_matrix(xPos, yPos, 0);
        jo_3d_rotate_matrix(0, 0, ang);
        jo_3d_mesh_draw(mesh);
    }
    jo_3d_pop_matrix();
}
