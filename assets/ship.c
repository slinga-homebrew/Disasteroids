#include "ship.h"

static jo_3d_mesh* createTitleScreenShip(bool vs);
static jo_3d_mesh* createShip(void);
static jo_3d_mesh* createShipThrust(void);
static jo_3d_mesh* createShipProjectile(void);
static jo_3d_mesh* createShipDebrisSmall(void);
static jo_3d_mesh* createShipDebrisLarge(void);

// load the ship polygons
void loadShips(void)
{
    g_Assets.cursorShip = createShip();

    for(unsigned int i = 0; i < COUNTOF(g_Assets.ships); i++)
    {
        g_Assets.ships[i] = createShip();
        g_Assets.titleScreenShips[i] = createTitleScreenShip(FALSE);
        g_Assets.titleScreenShipsVs[i] = createTitleScreenShip(TRUE);

        g_Assets.shipThrusts[i] = createShipThrust();
        g_Assets.shipProjectiles[i] = createShipProjectile();

        g_Assets.shipDebris[SHIP_DEBRIS_SIZE_SMALL][i] = createShipDebrisSmall();
        g_Assets.shipDebris[SHIP_DEBRIS_SIZE_LARGE][i] = createShipDebrisLarge();
    }
}

static jo_3d_mesh* createShip(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, -4, -6, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, -6, 0, 4);
    QUAD_LINE_SEGMENT(mesh, -4, -6, 0, -4);
    QUAD_LINE_SEGMENT(mesh, 4, -6, 0, -4);

    return mesh;
}

static jo_3d_mesh* createShipThrust(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(2);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, -2, -5, 0, -9);
    QUAD_LINE_SEGMENT(mesh, 2, -5, 0, -9);

    return mesh;
}

static jo_3d_mesh* createShipProjectile(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((1) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((1) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((-1) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((-1) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \

    return mesh;
}

static jo_3d_mesh* createShipDebrisSmall(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, -2, 0, 2, 0);

    return mesh;
}

static jo_3d_mesh* createShipDebrisLarge(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, -5, 0, 5, 0);

    return mesh;
}

// the title screen ships are offset from the center
// this allows the mesh to rotate easily
// vs mode flag - whether or not theships face in or out
static jo_3d_mesh* createTitleScreenShip(bool vs)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;
    int xOff = 0;
    int yOff = 0;

    // in vs mode the ships face in
    if(vs == true)
    {
        yOff = 62;
    }
    else
    {
        yOff = -64;
    }

    QUAD_LINE_SEGMENT(mesh, -4 + xOff, -6 + yOff, 0 + xOff,  4 + yOff);
    QUAD_LINE_SEGMENT(mesh,  4 + xOff, -6 + yOff, 0 + xOff,  4 + yOff);
    QUAD_LINE_SEGMENT(mesh, -4 + xOff, -6 + yOff, 0 + xOff, -4 + yOff);
    QUAD_LINE_SEGMENT(mesh,  4 + xOff, -6 + yOff, 0 + xOff, -4 + yOff);

    return mesh;
}
