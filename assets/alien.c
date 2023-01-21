#include "ship.h"

static jo_3d_mesh* createAlien(void);

// load the alien polygon
void loadAlien(void)
{
    g_Assets.alien = createAlien();
}

static jo_3d_mesh* createAlien(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(10);
    int verticeIndex = 0;

    int xOffset = 3;
    jo_fixed yOffset = -toFIXED(1.5);


    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(0-xOffset), toFIXED(0) - yOffset, toFIXED(5-xOffset), toFIXED(0) - yOffset);
    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(-1-xOffset), toFIXED(1) - yOffset, toFIXED(6-xOffset), toFIXED(1) - yOffset);
    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(0-xOffset), toFIXED(0) - yOffset, toFIXED(-1-xOffset), toFIXED(1) - yOffset);
    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(5-xOffset), toFIXED(0) - yOffset, toFIXED(6-xOffset), toFIXED(1) - yOffset);

    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(-1-xOffset), toFIXED(1) - yOffset, toFIXED(1-xOffset), toFIXED(2) - yOffset);
    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(6-xOffset), toFIXED(1) - yOffset, toFIXED(4-xOffset), toFIXED(2) - yOffset);

    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(1-xOffset), toFIXED(2) - yOffset, toFIXED(4-xOffset), toFIXED(2) - yOffset);
    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(2-xOffset), toFIXED(3) - yOffset, toFIXED(3-xOffset), toFIXED(3) - yOffset);
    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(1-xOffset), toFIXED(2) - yOffset, toFIXED(2-xOffset), toFIXED(3) - yOffset);
    QUAD_LINE_SEGMENT_FIXED(mesh, toFIXED(4-xOffset), toFIXED(2) - yOffset, toFIXED(3-xOffset), toFIXED(3) - yOffset);

    return mesh;
}
