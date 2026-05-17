#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 5;
esat::Vec3 g_pentagon[knPoints];

// la hago global para dibujar en los indices las arrow
esat::Vec2 pentagon[5];

esat::Vec3 pointsArrow[16] = {
    {0.0f, 0.4f, 1.0f},
    {0.65f, 0.4f, 1.0f},
    {0.65f, 0.25f, 1.0f},
    {1.0f, 0.5f, 1.0f},
    {0.65f, 0.75f, 1.0f},
    {0.65f, 0.6f, 1.0f},
    {0.0f, 0.6f, 1.0f},
    {0.0f, 0.4f, 1.0f},
};

esat::Mat3 UpdateFigure(esat::Vec2 scale, float angle, esat::Vec2 translate, esat::Vec2 fixTranslate) {
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(fixTranslate.x, fixTranslate.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);

    return m;
}

void DrawPoints(esat::Mat3 m) {

    for (int i = 0; i < 5; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_pentagon[i]);
        pentagon[i] = {tmp.x, tmp.y};

    }

    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);
    esat::DrawSolidPath(&pentagon[0].x, knPoints);
}

void DrawArrows(esat::Mat3 mA) {
    
    esat::Vec2 arrow[8];

    int c = 0;

    for (int i = 0; i < 8; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(mA, pointsArrow[i]);
        arrow[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(0, 0, 0, 255);
    esat::DrawSetFillColor(255, 0, 0, 255);
    esat::DrawSolidPath(&arrow[0].x, 8);
}

void InitPentagon() {
    
    float angle = 6.28f / (float) 5;
    for (int i = 0; i < 5; i++) {
        g_pentagon[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    } 
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitPentagon();
    
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat3 matriz = UpdateFigure({100.0f, 100.0f}, esat::Time() * 0.001f, {(float) esat::MousePositionX(), (float) esat::MousePositionY()}, {0.0f, 0.0f});
        DrawPoints(matriz);

        for (int i = 0; i < 5; i++) {
            float rotation = esat::Time() * 0.001f;

            if (i == 2) {
                rotation = 0.0f;
            }
            esat::Mat3 arrowMatriz = UpdateFigure({25.0f, 25.0f}, rotation * i, pentagon[i], {0.0f, -10.0f});
            DrawArrows(arrowMatriz);
        }

        

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
