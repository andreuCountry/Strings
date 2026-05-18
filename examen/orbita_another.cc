#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 36;
esat::Vec3 g_orbit[knPoints];

void InitOrbit() {
    float angle = 6.28f / (float) knPoints;

    for (int i = 0; i < knPoints; i++) {
        g_orbit[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

esat::Mat3 UpdateFigure(esat::Vec2 scale, float angle, esat::Vec2 translate) {

    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);

    return m;
}

esat::Mat3 UpdateFigureHeredada(esat::Vec2 scale, float angle, esat::Vec2 translate, esat::Mat3 base) {
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);
    m = esat::Mat3Multiply(base, m);

    return m;
}

void DrawFigure(esat::Mat3 m) {

    esat::Vec2 orbit[36];

    for (int i = 0; i < knPoints; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_orbit[i]);

        orbit[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0, 0, 0, 0);
    esat::DrawSolidPath(&orbit[0].x, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitOrbit();
    float angle = 6.28f / (float) 3;
    
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);

        esat::Mat3 matriz = UpdateFigure({10.0f, 10.0f}, 0.0f, {400.0f, 300.0f});
        DrawFigure(matriz);

        for (int i = 0; i < 3; i++) {
            esat::Mat3 matriz2 = UpdateFigure({200.0f, 100.0f}, angle * i, {400.0f, 300.0f});
            DrawFigure(matriz2);

            esat::Mat3 neurons = UpdateFigureHeredada({0.1f, 0.2f}, 0.0f, {cosf(esat::Time() * 0.001f * (i + 1)), sinf(esat::Time() * 0.001f * (i + 1))}, matriz2);
            DrawFigure(neurons);
        }
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
