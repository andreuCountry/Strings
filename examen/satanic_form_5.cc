#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 49;
float g_circle[knPoints * 2];
esat::Vec2 g_circle_vec[49];
esat::Vec3 g_hexagon[6];

esat::Vec3 form[10] = {
    {0.0f, 0.0f, 1.0f},
    {0.45f, 0.0f, 1.0f},
    {0.8f, 0.35f, 1.0f},
    {0.9f, 0.35f, 1.0f},
    {1.0f, 0.25f, 1.0f},
    {1.0f, 0.35f, 1.0f},
    {0.9f, 0.45f, 1.0f},
    {0.8f, 0.45f, 1.0f},
    {0.45f, 0.1f, 1.0f}, 
    {0.0f, 0.1f, 1.0f}
};

esat::Vec3 form_neg[10] {
    {0.0f, 0.0f, 1.0f},
    {0.45f, 0.0f, 1.0f},
    {0.8f, -0.35f, 1.0f},
    {0.9f, -0.35f, 1.0f},
    {1.0f, -0.25f, 1.0f},
    {1.0f, -0.35f, 1.0f},
    {0.9f, -0.45f, 1.0f},
    {0.8f, -0.45f, 1.0f},
    {0.45f, -0.1f, 1.0f}, 
    {0.0f, -0.1f, 1.0f}
};

void DrawPoints() {

    float angle = 6.28f / (float) 49;
    float angle2 = 6.28f / (float) 7;

    for (int i = 0; i < 49; i++) {
        g_circle_vec[i] = {cosf(angle * i) * 40.0f + (float) esat::MousePositionX(), sinf(angle * i) * 40.0f + (float) esat::MousePositionY()};
    }

    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);
    esat::DrawSolidPath(&g_circle_vec[0].x, 49);
}

esat::Mat3 UpdateFigure(esat::Vec2 scale, float angle, esat::Vec2 translate, esat::Vec2 fixInit) {

    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(fixInit.x, fixInit.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);

    return m;
}

void DrawFigure(esat::Mat3 matriz) {
    esat::Vec2 form_vec[10];
    esat::Vec2 form_vec_neg[10];

    for (int i = 0; i < 10; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(matriz, form[i]);
        esat::Vec3 tmp2 = esat::Mat3TransformVec3(matriz, form_neg[i]);
        form_vec[i] = {tmp.x, tmp.y};
        form_vec_neg[i] = {tmp2.x, tmp2.y};
    }

    esat::DrawSetStrokeColor(0, 0, 0, 255);
    esat::DrawSetFillColor(255, 255, 0, 255);
    esat::DrawSolidPath(&form_vec[0].x, 10);
    esat::DrawSolidPath(&form_vec_neg[0].x, 10);
}

void InitHexagon() {
    float angle = 6.28f / (float) 6;

    for (int j = 0; j < 6; j++) {
        g_hexagon[j] = {cosf(angle * j), sinf(angle * j), 1.0f};
    }
}

void DrawHexagon(esat::Mat3 m) {
    esat::Vec2 g_hexagon_vec[6];

    for (int i = 0; i < 6; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_hexagon[i]);
        g_hexagon_vec[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(0, 0, 0, 255);
    esat::DrawSetFillColor(255, 255, 0, 255);
    esat::DrawSolidPath(&g_hexagon_vec[0].x, 6);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitHexagon();
    float angle = 6.28f / 7;
    
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        DrawPoints();

        for (int i = 0; i < 7; i++) {
            int divisor = 0;
            if (i == 0) {
                divisor = 0;
            } else {
                divisor = (7 * i);
            }
            esat::Mat3 matriz = UpdateFigure({100.0f, 100.0f}, angle * i, g_circle_vec[divisor], {0.0f, 0.0f});
            DrawFigure(matriz);

            esat::Mat3 matriz2 = UpdateFigure({5.0f, 5.0f}, angle * i, g_circle_vec[divisor], {40.0f, 100.0f});
            DrawHexagon(matriz2);   
        }
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
