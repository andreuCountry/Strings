#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <esat/math.h>
#include <esat/time.h>
#include <math.h>

const int knPoints = 12;
esat::Vec3 g_circle[knPoints];

void InitCircle() {
    float angle = 6.28f / (float) knPoints;
    for (int i = 0; i < knPoints; ++i) {
        g_circle[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

esat::Mat3 UpdateCircle() {
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(180.0f, 180.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time() * 0.001f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(200.0f, 300.0f), m);

    return m;
}

void DrawCircle(esat::Mat3 m) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    esat::Vec2 tr_circle[knPoints];

    for (int i = 0; i < knPoints; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_circle[i]);
        tr_circle[i] = {tmp.x, tmp.y};
    }
    esat::DrawSolidPath(&tr_circle[0].x, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitCircle();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat3 matriz = UpdateCircle();
        DrawCircle(matriz);
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}