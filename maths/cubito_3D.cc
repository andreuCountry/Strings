#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 8;


esat::Vec3 g_cube = {

};

esat::Mat4 MatrizTransform() {

    esat::Vec2 centralPoint = {(float) esat::MousePositionX(), (float) esat::MousePositionY()};

    esat::Mat4 m = esat::Mat4Identity();

    

    // Necesitamos transladar por el eje z (T(0, 0, Z))


    // Proyección


    // esacalamos con el eje z por 1


    // translacion a efectos por el eje z a 0


    return m;
}

void InitMatriz() {
    float angle = 6.28f / (float) knPoints;
    for (int i = 0; i < knPoints; ++i) {
        g_cube[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

void DrawMatriz(esat::Mat3 m) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    esat::Vec2 tr_cube[knPoints];

    for (int i = 0; i < knPoints; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_cube[i]);
        tr_cube[i] = {tmp.x, tmp.y};

        esat::DrawLine(&tr_cube[i].x, &tr_cube[i].y, &tr_cube[i+1].x, &tr_cube[i+1].y);
    }
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);
    

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat3 matriz = UpdateCircle();
        DrawMatriz(matriz);
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}