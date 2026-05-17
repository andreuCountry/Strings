#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

float points[14] = {
    20.0f, 10.0f,
    15.0f, 0.0f,
    12.0f, 0.0f,
    20.0f, 16.0f,
    28.0f, 0.0f,
    25.0f, 0.0f,
    20.0f, 10.0f,
};

esat::Vec3 g_form[7];

void Homogeneixar(float points[]) {
    int c = 0;
    for (int i = 0; i < 7; i++) {
        g_form[i] = {points[c++] / 28.0f, points[c++] / 28.0f, 1.0f};
    }
}

esat::Mat3 UpdateMatriz(esat::Vec2 scale, float angle, float initialAngle, esat::Vec2 translate, esat::Vec2 initialPosFix) {
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);

    // primero lo centramos, y despues ya rotamos
    m = esat::Mat3Multiply(esat::Mat3Translate(initialPosFix.x, initialPosFix.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(initialAngle), m);

    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);

    return m;
}

void DrawPoints(esat::Mat3 m) {

    esat::Vec2 gformVec[7];
    for (int i = 0; i < 7; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_form[i]);

        gformVec[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);
    esat::DrawSolidPath(&gformVec[0].x, 7);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    Homogeneixar(points);
    float angle = 6.28f / (float) 7;
    float angle2 = 6.28f / (float) 5;
    
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        for (int i = 0; i < 7; i++) {
            esat::Mat3 matriz = UpdateMatriz({100.0f, 100.0f}, angle * i, -6.28f, {(float) esat::MousePositionX(), (float) esat::MousePositionY()}, {-70.0f, 150.0f});
            DrawPoints(matriz);
        }

        for (int i = 0; i < 5; i++) {
            esat::Mat3 matriz = UpdateMatriz({50.0f, 50.0f}, angle2 * i, 0.0f, {(float) esat::MousePositionX(), (float) esat::MousePositionY()}, {-35.0f, - 60.0f});
            DrawPoints(matriz);
        }
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
