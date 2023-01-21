#include "ship.h"

static jo_3d_mesh* createStar(void);

// loads the star polygon
void loadStars(void)
{
    for(unsigned int i = 0; i < COUNTOF(g_Assets.stars); i++)
    {
        g_Assets.stars[i] = createStar();
    }
}

static jo_3d_mesh* createStar(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);

    return mesh;
}
