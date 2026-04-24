#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 8;

esat::Vec4 g_cube[knPoints];

int edges[12][2] = {
    {0,1},
    {1,2},
    {2,3},
    {3,0},
    {4,5},
    {5,6},
    {6,7},
    {7,4},
    {0,4},
    {1,5},
    {2,6},
    {3,7}
};

void InitVec() {
    g_cube[0] = {-1.0f, -1.0f, -1.0f, 1.0f};
    g_cube[1] = {-1.0f, 1.0f, -1.0f, 1.0f};
    g_cube[2] = {1.0f, 1.0f, -1.0f, 1.0f};
    g_cube[3] = {1.0f, -1.0f, -1.0f, 1.0f};
    g_cube[4] = {-1.0f, -1.0f, 1.0f, 1.0f};
    g_cube[5] = {-1.0f, 1.0f, 1.0f, 1.0f};
    g_cube[6] = {1.0f, 1.0f, 1.0f, 1.0f};
    g_cube[7] = {1.0f, -1.0f, 1.0f, 1.0f};
}

float angle = 0.0f;

esat::Mat4 MatrizTransform() {

    esat::Mat4 m = esat::Mat4Identity();

    angle++;


    // rotar al bichito

    m = esat::Mat4Multiply(esat::Mat4RotateX(esat::Time() * 0.001f), m);
    m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time() * 0.001f), m);
    m = esat::Mat4Multiply(esat::Mat4RotateZ(esat::Time() * 0.001f), m);

    // Necesitamos transladar por el eje z (T(0, 0, Z))

    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, 3.0f), m);

    // Proyección

    m = esat::Mat4Multiply(esat::Mat4Projection(), m);

    // esacalamos con el eje z por 1

    m = esat::Mat4Multiply(esat::Mat4Scale(200.0f, 200.0f, 1.0f), m);

    // translacion a efectos por el eje z a 0

    m = esat::Mat4Multiply(esat::Mat4Translate(400.0f, 300.0f, 0.0f), m);

    return m;
}

void DrawMatriz(esat::Mat4 m) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    esat::Vec3 tr_cube[knPoints];

    for (int i = 0; i < knPoints; i++) {

        // transformacion de vertices en algo temporal
        esat::Vec4 tmp = esat::Mat4TransformVec4(m, g_cube[i]);

        tr_cube[i].x = tmp.x / tmp.w;
        tr_cube[i].y = tmp.y / tmp.w;
    }

    for (int i = 0; i < 12; i++) {
        esat::DrawLine(tr_cube[edges[i][0]].x, tr_cube[edges[i][0]].y,tr_cube[edges[i][1]].x, tr_cube[edges[i][1]].y);
    }
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);
    
    InitVec();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat4 matriz = MatrizTransform();
        DrawMatriz(matriz);
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
