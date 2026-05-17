#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 8;
esat::Vec2 g_octagon[8];

esat::Vec3 g_form[9] = {
    {1.0f, 0.0f, 1.0f},
    {1.0f, 3.0f, 1.0f},
    {3.0f, 7.0f, 1.0f},
    {1.0f, 7.0f, 1.0f},
    {0.0f, 5.0f, 1.0f},
    {-1.0f, 7.0f, 1.0f},
    {-3.0f, 7.0f, 1.0f},
    {-1.0f, 3.0f, 1.0f},
    {-1.0f, 0.0f, 1.0f}
};

void DrawOctagon() {
    int c = 0;
    float angle = 6.28f / (float) knPoints;

    for (int i = 0; i < knPoints; i++) {
        g_octagon[i] = {cosf(angle * i) * 100 + (float) esat::MousePositionX(), sinf(angle * i) * 100 + (float) esat::MousePositionY()};
    }

    esat::DrawSetStrokeColor(0, 0, 0, 255);
    esat::DrawSetFillColor(255, 255, 255, 0);
    esat::DrawSolidPath(&g_octagon[0].x, 8);

}

esat::Mat3 UpdateFigure(esat::Vec2 scale, float angle, esat::Vec2 translate) {
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(-1.57f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);

    return m;
}

void DrawFigure(esat::Mat3 m) {

    esat::Vec2 form_vec[9];

    for (int i = 0; i < 9; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_form[i]);
        form_vec[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(0, 0, 0, 255);
    esat::DrawSetFillColor(255, 255, 255, 0);
    esat::DrawSolidPath(&form_vec[0].x, 9);
}

void Homogeneixar(esat::Vec3* formVec) {
    
    for (int i = 0; i < 9; i++) {
        formVec[i] = {formVec[i].x / 7.0f, formVec[i].y / 7.0f, 1.0f};
    }
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    float angle = 6.28f / (float) knPoints;

    Homogeneixar(g_form);
    
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120, 120, 120);

        DrawOctagon();

        for (int i = 0; i < 8; i++) {
            esat::Mat3 matriz = UpdateFigure({100.0f, 100.0f}, angle * i, {g_octagon[i].x, g_octagon[i].y});
            DrawFigure(matriz);

            esat::Mat3 matriz2 = UpdateFigure({70.0f, 70.0f}, angle * i, {(float) esat::MousePositionX(), (float) esat::MousePositionY()});
            DrawFigure(matriz2);
        }

        esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
