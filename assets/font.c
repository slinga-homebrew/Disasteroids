#include "assets.h"
#include "font.h"

static void loadAlphabet(void);
static void loadDigits(void);
static void loadSpecialCharacters(void);

// capital letters
static jo_3d_mesh* createA(void);
static jo_3d_mesh* createC(void);
static jo_3d_mesh* createD(void);
static jo_3d_mesh* createE(void);
static jo_3d_mesh* createF(void);
static jo_3d_mesh* createG(void);
static jo_3d_mesh* createH(void);
static jo_3d_mesh* createI(void);
static jo_3d_mesh* createK(void);
static jo_3d_mesh* createL(void);
static jo_3d_mesh* createM(void);
static jo_3d_mesh* createN(void);
static jo_3d_mesh* createO(void);
static jo_3d_mesh* createP(void);
static jo_3d_mesh* createQ(void);
static jo_3d_mesh* createR(void);
static jo_3d_mesh* createS(void);
static jo_3d_mesh* createT(void);
static jo_3d_mesh* createU(void);
static jo_3d_mesh* createV(void);
static jo_3d_mesh* createW(void);
static jo_3d_mesh* createY(void);

// digits 0-9
static jo_3d_mesh* create0(void);
static jo_3d_mesh* create1(void);
static jo_3d_mesh* create2(void);
static jo_3d_mesh* create3(void);
static jo_3d_mesh* create4(void);
static jo_3d_mesh* create5(void);
static jo_3d_mesh* create6(void);
static jo_3d_mesh* create7(void);
static jo_3d_mesh* create8(void);
static jo_3d_mesh* create9(void);

// special characters
static jo_3d_mesh* createPeriod(void);
static jo_3d_mesh* createSemicolon(void);
static jo_3d_mesh* createHorizontalLine(void);
static jo_3d_mesh* createVerticalLine(void);
static jo_3d_mesh* createRectangle(void);

// load the font polygons
void loadFont(void)
{
    loadAlphabet();
    loadDigits();
    loadSpecialCharacters();
}

// letters
void loadAlphabet(void)
{
    g_Assets.letters[LETTER_TO_INDEX('A')] = createA();
    g_Assets.letters[LETTER_TO_INDEX('C')] = createC();
    g_Assets.letters[LETTER_TO_INDEX('D')] = createD();
    g_Assets.letters[LETTER_TO_INDEX('E')] = createE();
    g_Assets.letters[LETTER_TO_INDEX('F')] = createF();
    g_Assets.letters[LETTER_TO_INDEX('G')] = createG();
    g_Assets.letters[LETTER_TO_INDEX('H')] = createH();
    g_Assets.letters[LETTER_TO_INDEX('I')] = createI();
    g_Assets.letters[LETTER_TO_INDEX('K')] = createK();
    g_Assets.letters[LETTER_TO_INDEX('L')] = createL();
    g_Assets.letters[LETTER_TO_INDEX('M')] = createM();
    g_Assets.letters[LETTER_TO_INDEX('N')] = createN();
    g_Assets.letters[LETTER_TO_INDEX('O')] = createO();
    g_Assets.letters[LETTER_TO_INDEX('P')] = createP();
    g_Assets.letters[LETTER_TO_INDEX('Q')] = createQ();
    g_Assets.letters[LETTER_TO_INDEX('R')] = createR();
    g_Assets.letters[LETTER_TO_INDEX('S')] = createS();
    g_Assets.letters[LETTER_TO_INDEX('T')] = createT();
    g_Assets.letters[LETTER_TO_INDEX('U')] = createU();
    g_Assets.letters[LETTER_TO_INDEX('V')] = createV();
    g_Assets.letters[LETTER_TO_INDEX('W')] = createW();
    g_Assets.letters[LETTER_TO_INDEX('Y')] = createY();
}

// digits
void loadDigits(void)
{
    g_Assets.digits[0] = create0();
    g_Assets.digits[1] = create1();
    g_Assets.digits[2] = create2();
    g_Assets.digits[3] = create3();
    g_Assets.digits[4] = create4();
    g_Assets.digits[5] = create5();
    g_Assets.digits[6] = create6();
    g_Assets.digits[7] = create7();
    g_Assets.digits[8] = create8();
    g_Assets.digits[9] = create9();
}

// special characters
void loadSpecialCharacters(void)
{
    g_Assets.period = createPeriod();
    g_Assets.semicolon = createSemicolon();
    g_Assets.horizontalLine = createHorizontalLine();
    g_Assets.verticalLine = createVerticalLine();
    g_Assets.rectangle = createRectangle();
}

//
// Letters
//

static jo_3d_mesh* createA(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);

    return mesh;
}

static jo_3d_mesh* createC(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(3);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);

    return mesh;
}

static jo_3d_mesh* createD(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 1, 0, 1, 4);

    return mesh;
}

static jo_3d_mesh* createE(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);

    return mesh;
}

static jo_3d_mesh* createF(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(3);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);

    return mesh;
}

static jo_3d_mesh* createG(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(5);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 2, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 2);

    return mesh;
}

static jo_3d_mesh* createH(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(3);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);

    return mesh;
}

static jo_3d_mesh* createI(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(3);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 2, 0, 2, 4);

    return mesh;
}

static jo_3d_mesh* createK(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 3, 4, 3, 2);

    return mesh;
}

static jo_3d_mesh* createL(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(2);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);

    return mesh;
}

static jo_3d_mesh* createM(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 2, 2, 2, 4)

    return mesh;
}

static jo_3d_mesh* createN(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(3);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);

    return mesh;
}

static jo_3d_mesh* createO(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);

    return mesh;
}

static jo_3d_mesh* createP(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 4, 2, 4, 4);

    return mesh;
}

static jo_3d_mesh* createQ(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(5);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 2, 0, 2, 2);

    return mesh;
}

static jo_3d_mesh* createR(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(5);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 3, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 3, 2, 3, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 2, 4, 0);

    return mesh;
}

static jo_3d_mesh* createS(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(5);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 2, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 4, 2, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);

    return mesh;
}

static jo_3d_mesh* createT(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(2);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 2, 0, 2, 4);

    return mesh;
}

static jo_3d_mesh* createU(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(3);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);

    return mesh;
}

static jo_3d_mesh* createV(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(7);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 1, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 1, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 1, 1, 1);
    QUAD_LINE_SEGMENT(mesh, 4, 1, 3, 1);
    QUAD_LINE_SEGMENT(mesh, 1, 0, 1, 1);
    QUAD_LINE_SEGMENT(mesh, 3, 0, 3, 1);
    QUAD_LINE_SEGMENT(mesh, 1, 0, 3, 0);

    return mesh;
}

static jo_3d_mesh* createW(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 4, 0, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 2, 3, 2, 0)

    return mesh;
}

static jo_3d_mesh* createY(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 4, 0, 2);
    QUAD_LINE_SEGMENT(mesh, 4, 4, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 2, 0, 2, 2);

    return mesh;
}

//
// Digits
//

static jo_3d_mesh* create0(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    /*
    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    */

    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((0) * WIDTH_UNIT), jo_int2fixed((-4) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((4) * WIDTH_UNIT), jo_int2fixed((-4) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((4) * WIDTH_UNIT), jo_int2fixed((0) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);

    return mesh;
}

static jo_3d_mesh* create1(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 2, 0, 2, 4);

    return mesh;
}

static jo_3d_mesh* create2(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(5);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 2);
    QUAD_LINE_SEGMENT(mesh, 4, 2, 4, 4);

    return mesh;
}

static jo_3d_mesh* create3(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);

    return mesh;
}

static jo_3d_mesh* create4(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(3);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);

    return mesh;
}

static jo_3d_mesh* create5(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(5);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 2, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 4, 2, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);

    return mesh;
}

static jo_3d_mesh* create6(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 2);

    return mesh;
}

static jo_3d_mesh* create7(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(2);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);

    return mesh;
}

static jo_3d_mesh* create8(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(5);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 0, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 0, 4, 0);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);

    return mesh;
}

static jo_3d_mesh* create9(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, 2, 0, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 4, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 4, 0, 4, 4);
    QUAD_LINE_SEGMENT(mesh, 0, 2, 4, 2);

    return mesh;
}

//
// Special characters and shapes
//

static jo_3d_mesh* createPeriod(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(4);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 1, 0, 3, 0);
    QUAD_LINE_SEGMENT(mesh, 1, 0, 1, 1);
    QUAD_LINE_SEGMENT(mesh, 1, 1, 3, 1);
    QUAD_LINE_SEGMENT(mesh, 3, 0, 3, 1);

    return mesh;
}

static jo_3d_mesh* createSemicolon(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(8);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 1, 0, 3, 0);
    QUAD_LINE_SEGMENT(mesh, 1, 0, 1, 1);
    QUAD_LINE_SEGMENT(mesh, 1, 1, 3, 1);
    QUAD_LINE_SEGMENT(mesh, 3, 0, 3, 1);
    QUAD_LINE_SEGMENT(mesh, 1, 3, 3, 3);
    QUAD_LINE_SEGMENT(mesh, 1, 3, 1, 4);
    QUAD_LINE_SEGMENT(mesh, 1, 4, 3, 4);
    QUAD_LINE_SEGMENT(mesh, 3, 3, 3, 4);

    return mesh;
}

static jo_3d_mesh* createHorizontalLine(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, -106, 0, 104, 0);

    return mesh;
}

static jo_3d_mesh* createVerticalLine(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    QUAD_LINE_SEGMENT(mesh, 0, -100, 0, 100);

    return mesh;
}

static jo_3d_mesh* createRectangle(void)
{
    jo_3d_mesh* mesh = jo_3d_create_mesh(1);
    int verticeIndex = 0;

    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((-132) * WIDTH_UNIT), jo_int2fixed((-15) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((-132) * WIDTH_UNIT), jo_int2fixed((15) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((132) * WIDTH_UNIT), jo_int2fixed((15) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);
    jo_3d_set_mesh_vertice(mesh, jo_int2fixed((132) * WIDTH_UNIT), jo_int2fixed((-15) * HEIGHT_UNIT), jo_int2fixed(0), verticeIndex++);

    return mesh;
}
