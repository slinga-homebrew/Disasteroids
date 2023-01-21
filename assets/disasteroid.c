#include "disasteroid.h"

static jo_3d_mesh* createDisasteroid(DISASTEROID_SIZE size);
static jo_3d_mesh* createExplosion(void);
static void createDisasteroidVertex(jo_fixed* x, jo_fixed* y, int radius, int variance, int angle);

// load the disasteroid polygons
void loadDisasteroids(void)
{
    // small, medium, and large disasteroids
    for(unsigned int i = 0; i < COUNTOF(g_Assets.disasteroids[DISASTEROID_SIZE_SMALL]); i++)
    {
        g_Assets.disasteroids[DISASTEROID_SIZE_SMALL][i] = createDisasteroid(DISASTEROID_SIZE_SMALL);
        g_Assets.disasteroids[DISASTEROID_SIZE_MEDIUM][i] = createDisasteroid(DISASTEROID_SIZE_MEDIUM);
        g_Assets.disasteroids[DISASTEROID_SIZE_LARGE][i] = createDisasteroid(DISASTEROID_SIZE_LARGE);
    }

    g_Assets.explosion = createExplosion();
}

// get the radius of a disasteroid
int getDisasteroidRadiusSize(DISASTEROID_SIZE size)
{
    int radius = 0;

    switch(size)
    {
        case DISASTEROID_SIZE_SMALL:
        {
            radius = DISASTEROID_RADIUS_SIZE_SMALL;
            break;
        }
        case DISASTEROID_SIZE_MEDIUM:
        {
            radius = DISASTEROID_RADIUS_SIZE_MEDIUM;
            break;
        }
        case DISASTEROID_SIZE_LARGE:
        {
            radius = DISASTEROID_RADIUS_SIZE_LARGE;
            break;
        }
        default:
            break;
    }

    return radius;
}

// create randomized disasteroid based on size
static jo_3d_mesh* createDisasteroid(DISASTEROID_SIZE size)
{
    jo_fixed x[8] = {0};
    jo_fixed y[8] = {0};
    jo_3d_mesh* mesh = jo_3d_create_mesh(8);
    int verticeIndex = 0;
    int radius = 0;
    int randomization = 2;

    // lookup radius size
    radius = getDisasteroidRadiusSize(size);

    for(unsigned int i = 0; i < COUNTOF(x); i++)
    {
        createDisasteroidVertex(&x[i], &y[i], toFIXED(radius), randomization, i*45);
    }

    QUAD_LINE_SEGMENT_FIXED(mesh, x[0], y[0], x[1], y[1]);
    QUAD_LINE_SEGMENT_FIXED(mesh, x[1], y[1], x[2], y[2]);
    QUAD_LINE_SEGMENT_FIXED(mesh, x[2], y[2], x[3], y[3]);
    QUAD_LINE_SEGMENT_FIXED(mesh, x[3], y[3], x[4], y[4]);
    QUAD_LINE_SEGMENT_FIXED(mesh, x[4], y[4], x[5], y[5]);
    QUAD_LINE_SEGMENT_FIXED(mesh, x[5], y[5], x[6], y[6]);
    QUAD_LINE_SEGMENT_FIXED(mesh, x[6], y[6], x[7], y[7]);
    QUAD_LINE_SEGMENT_FIXED(mesh, x[7], y[7], x[0], y[0]);

    return mesh;
}

static void createDisasteroidVertex(jo_fixed* x, jo_fixed* y, jo_fixed radius, int variance, int rot)
{
    jo_fixed var = toFIXED(jo_random(variance));
    var |= jo_random(0xFFFF);

    *x = jo_fixed_mult(radius + var, slCos(rot * 182));
    *y = jo_fixed_mult(radius + var, slSin(rot * 182));
}

static jo_3d_mesh* createExplosion(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++); \

    return mesh;
}
