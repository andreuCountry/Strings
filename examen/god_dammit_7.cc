#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 36;
esat::Vec3 g_circle[knPoints];

void InitCircle() {

    float angle = 6.28f / (float) knPoints;

    for (int i = 0; i < 36; i++) {
        g_circle[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

esat::Mat3 UpdateFigure(esat::Vec2 scale, float angle, esat::Vec2 translate) {

    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);


    return m;
}

esat::Mat3 UpdateFigureNeuron(esat::Vec2 scale, esat::Mat3 base, int speed) {
    
    esat::Mat3 m = esat::Mat3Identity();
    float angle = esat::Time() * 0.001f * speed;
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(cosf(angle), sinf(angle)), m);

    // hereda aqui
    m = esat::Mat3Multiply(base, m);

    return m;
}

void DrawFigure(esat::Mat3 m) {

    esat::Vec2 circle_vec[36];

    for (int i = 0; i < 36; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_circle[i]);

        circle_vec[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0,0,0,0);
    esat::DrawSolidPath(&circle_vec[0].x, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitCircle();
    float angle = 6.28f / (float) knPoints;

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(0,0,0);

        for (int i = 0; i < 3; i++) {
            esat::Vec2 scale = {120 + 20.0f * i, 80.0f - 30.0f * i};
            if (i % 2 == 0) {
                scale = {120.0f - 30.0f * i, 80.0f + 20.0f * i};
            }
            esat::Mat3 initialMatriz = UpdateFigure(scale, angle * i, {400.0f, 300.0f});
            DrawFigure(initialMatriz);


            esat::Mat3 matrizNeuron = UpdateFigureNeuron({0.1f, 0.1f}, initialMatriz, i + 1);
            DrawFigure(matrizNeuron);
        }

        esat::Mat3 matriz = UpdateFigure({10.0f, 10.0f}, 0.0f, {400.0f, 300.0f});
        DrawFigure(matriz);

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
