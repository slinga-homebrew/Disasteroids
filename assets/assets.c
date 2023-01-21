#include "assets.h"
#include "font.h"

// priority queue to hold player colors
// needed to allow players to switch colors
// without colliding
typedef struct _PLAYER_COLORS
{
    int colors[MAX_PLAYERS + 1];
    int count;
    int capacity;

} PLAYER_COLORS, *PPLAYER_COLORS;

PLAYER_COLORS g_PlayerColors = {0};

static void initColors(void);
static void initPlayerColors(void);
static jo_3d_mesh* getMeshByCharacter(char letter);

// load the various polygons used by the ame
void loadPolygons(void)
{
    initColors();
    loadFont();
    loadShips();
    loadAlien();
    loadDisasteroids();
    loadStars();
}

// initialize colors
static void initColors(void)
{
    int colors[] =  {JO_COLOR_Green, JO_COLOR_White, JO_COLOR_Red,
                          JO_COLOR_Blue, JO_COLOR_Purple, JO_COLOR_Cyan,
                          JO_COLOR_Peach, JO_COLOR_Mint, JO_COLOR_Cream,
                          JO_COLOR_Brown, JO_COLOR_Yellow, JO_COLOR_Gold};

    memcpy(g_Assets.hudColors, colors, sizeof(colors));

    // randomize the order of player colors per boot
    memcpy(g_Assets.randomizedColors, colors, sizeof(colors));

    shuffleArray(g_Assets.randomizedColors, COUNTOF(g_Assets.randomizedColors));

    initPlayerColors();
}

// draws a single letter
void drawLetter(char letter, int color, int x, int y, int xScale, int yScale)
{
    jo_3d_mesh* mesh = NULL;

    mesh = getMeshByCharacter(letter);
    if(!mesh)
    {
        return;
    }

    jo_3d_push_matrix();
    {
        jo_3d_camera_look_at(&g_Game.camera);
        jo_3d_set_mesh_color(mesh, color);
        jo_3d_translate_matrix(x, y, 0);
        jo_3d_set_scale(xScale, yScale, 1);
        jo_3d_mesh_draw(mesh);
    }
    jo_3d_pop_matrix();

    return;
}

// retrieve the polygon mesh by character
static jo_3d_mesh* getMeshByCharacter(char letter)
{
    if(letter >= 'A' && letter <= 'Z')
    {
        return g_Assets.letters[LETTER_TO_INDEX(letter)];
    }
    else if(letter >= '0' && letter <= '9')
    {
        // TODO: make macro
        return g_Assets.digits[letter - '0'];
    }
    else if(letter == '.')
    {
        return g_Assets.period;
    }
    else if(letter == ':')
    {
        return g_Assets.semicolon;
    }

    return NULL;
}

//
// Player color management
//

// initialize the player color queue
static void initPlayerColors(void)
{
    memset(&g_PlayerColors, 0, sizeof(g_PlayerColors));

    g_PlayerColors.count = 0;
    g_PlayerColors.capacity = COUNTOF(g_PlayerColors.colors);

    for(unsigned int i = 0; i < COUNTOF(g_Assets.randomizedColors); i++)
    {
        pushPlayerColor(g_Assets.randomizedColors[i]);
    }

    return;
}

// add a color to the color queue
void pushPlayerColor(int color)
{
    if(g_PlayerColors.count + 1 <= g_PlayerColors.capacity)
    {
        g_PlayerColors.colors[g_PlayerColors.count] = color;
        g_PlayerColors.count++;
        return;
    }

    return;
}

// receive a color from the color queue
int popPlayerColor(void)
{
    int color = 0;

    if(g_PlayerColors.count > 0)
    {
        color = g_PlayerColors.colors[0];

        // move the rest of the colors up one
        memmove(g_PlayerColors.colors, g_PlayerColors.colors + 1, sizeof(g_PlayerColors.colors) - sizeof(g_PlayerColors.colors[0]));

        g_PlayerColors.count--;
    }

    return color;
}

// look up a player color by index
int getPlayerColorByIndex(int index)
{
    int color = 0;

    if(g_PlayerColors.count > index)
    {
        color = g_PlayerColors.colors[index];
    }

    return color;
}
