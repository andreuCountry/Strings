#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 10;
esat::Vec3 g_circle[knPoints];

void InitCircle() {
    float angle = 6.28f / (float) knPoints;

    for (int i = 0; i < knPoints; i++) {
        g_circle[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

esat::Mat3 UpdateCircle() {
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(200.0f, 200.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time() * 0.001f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);

    return m;
}

void DrawPoints(esat::Mat3 matriz) {

    esat::Vec2 vecSCircle[knPoints];
    for (int i = 0; i < knPoints; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(matriz, g_circle[i]);
        vecSCircle[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);
    esat::DrawSolidPath(&vecSCircle[0].x, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);
    
    InitCircle();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat3 matriz = UpdateCircle();
        DrawPoints(matriz);
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
