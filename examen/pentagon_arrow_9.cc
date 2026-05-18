#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 5;
esat::Vec3 g_pentagon[knPoints];
esat::Vec3 g_arrow[8] = {
    {0.0f, 0.4f, 1.0f},
    {0.65f, 0.4f, 1.0f},
    {0.65f, 0.25f, 1.0f},
    {1.0f, 0.5f, 1.0f},
    {0.65f, 0.75f, 1.0f},
    {0.65f, 0.6f, 1.0f},
    {0.0f, 0.6f, 1.0f},
    {0.0f, 0.4f, 1.0f}
};

esat::Vec2 pentagon[5];

void InitPentagon() {

    float angle = 6.28f / (float) knPoints;

    for (int i = 0; i < 5; i++) {
        g_pentagon[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

esat::Mat3 UpdateFigure(esat::Vec2 scale, float angle, esat::Vec2 translate, esat::Vec2 fixTranslate) {
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(fixTranslate.x, fixTranslate.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);

    return m;
}

void DrawPentagon(esat::Mat3 m) {


    for (int i = 0; i < knPoints; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_pentagon[i]);

        pentagon[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0, 0, 0, 0);
    esat::DrawSolidPath(&pentagon[0].x, knPoints);
}

void DrawArrow(esat::Mat3 m) {
    esat::Vec2 arrow[8];

    for (int i = 0; i < 8; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_arrow[i]);

        arrow[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0, 0, 0, 0);
    esat::DrawSolidPath(&arrow[0].x, 8);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitPentagon();
    
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);

        esat::Mat3 pentagonMatriz = UpdateFigure({80.0f, 80.0f}, esat::Time() * 0.001f, {400.0f, 300.0f}, {1.0f, 1.0f});
        DrawPentagon(pentagonMatriz);

        for (int i = 0; i < 5; i++) {
            esat::Mat3 arrowM = UpdateFigure({20.0f, 20.0f}, esat::Time() * 0.001f * (i + 1), pentagon[i], {0.0f, -10.0f});
            DrawArrow(arrowM);
        }
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
