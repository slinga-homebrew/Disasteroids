#pragma once

#include <jo/jo.h>
#include "../main.h"
#include "../objects/disasteroid.h"
#include "../objects/explosion.h"
#include "audio.h"
#include "alien.h"
#include "disasteroid.h"
#include "font.h"
#include "ship.h"
#include "star.h"

#define MAX_LETTERS (26)
#define MAX_DIGITS  (10)

// random variations within each asteroid size
#define NUM_DISASTEROID_VARIATIONS (16)

#define LETTER_TO_INDEX(chr) (chr - 'A')

// additional colors, not defined by Jo Engine
#define JO_COLOR_Gold   (0x825D)
#define JO_COLOR_Brown  (0x9997)
#define JO_COLOR_Mint   (0xAAA8)
#define JO_COLOR_Cream  (0xBFFD)
#define JO_COLOR_Peach  (0xC153)

// macro to make a polyine using quads
#define QUAD_LINE_SEGMENT(mesh, x1, y1, x2, y2) { \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((x1) * WIDTH_UNIT), jo_int2fixed((-y1) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((x1) * WIDTH_UNIT), jo_int2fixed((-y1) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((x2) * WIDTH_UNIT), jo_int2fixed((-y2) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((x2) * WIDTH_UNIT), jo_int2fixed((-y2) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
}

#define QUAD_LINE_SEGMENT_FIXED(mesh, x1, y1, x2, y2) { \
    jo_3d_set_mesh_vertice(mesh, ((x1) * WIDTH_UNIT), ((-y1) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, ((x1) * WIDTH_UNIT), ((-y1) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, ((x2) * WIDTH_UNIT), ((-y2) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, ((x2) * WIDTH_UNIT), ((-y2) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
}

// holds sprite and audio assets
typedef struct _assets
{
    // ships
    jo_3d_mesh* cursorShip;
    jo_3d_mesh* ships[MAX_PLAYERS];
    jo_3d_mesh* shipThrusts[MAX_PLAYERS];
    jo_3d_mesh* shipProjectiles[MAX_PLAYERS];
    jo_3d_mesh* shipDebris[SHIP_DEBRIS_SIZE_MAX][MAX_PLAYERS];
    jo_3d_mesh* titleScreenShips[MAX_PLAYERS];
    jo_3d_mesh* titleScreenShipsVs[MAX_PLAYERS];

    // disasteroids
    jo_3d_mesh* disasteroids[DIASTEROID_SIZE_MAX][NUM_DISASTEROID_VARIATIONS];
    jo_3d_mesh* explosion;

    // alien
    jo_3d_mesh* alien;

    // background stars
    jo_3d_mesh* stars[MAX_PLAYERS];

    //
    // font
    //

    // capital letters A-Z
    // letters that I didn't implement are NULL...
    jo_3d_mesh* letters[MAX_LETTERS];

    // digits 0-9
    jo_3d_mesh* digits[MAX_DIGITS];

    // special characters
    jo_3d_mesh* period;
    jo_3d_mesh* semicolon;
    jo_3d_mesh* horizontalLine;
    jo_3d_mesh* verticalLine;
    jo_3d_mesh* rectangle;

    // don't randomize HUD colors
    unsigned int hudColors[MAX_PLAYERS];

    // randomized colors per boot
    unsigned int randomizedColors[MAX_PLAYERS];

    // audio assets
    jo_sound popPCM;

} ASSETS, *PASSETS;

// initialize polygon assets
void loadPolygons(void);

// draw letter at position
void drawLetter(char letter, int color, int x, int y, int xScale, int yScale);

// manage player colors
int popPlayerColor(void);
void pushPlayerColor(int color);
int getPlayerColorByIndex(int index);

extern ASSETS g_Assets;
