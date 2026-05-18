#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 10;
esat::Vec3 g_star[knPoints];
esat::Vec3 g_orbits[36];

void InitPentagon() {

    float angle = 6.28f / (float) knPoints;
    for (int i = 0; i < knPoints; i++) {
        if (i % 2 == 0) {
            g_star[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
        } else {
            g_star[i] = {cosf(angle * i) * 0.5f, sinf(angle * i) * 0.5f, 1.0f};
        }
    }
}

void InitOrbits() {
    float angle = 6.28f / (float) 36;

    for (int i = 0; i < 36; i++) {
        g_orbits[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

void Serialize(esat::Mat3 m) {

    esat::Vec2 g_orbit[36];

    for (int i = 0; i < 36; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_orbits[i]);

        g_orbit[i] = {tmp.x, tmp.y};
    }
}

esat::Mat3 UpdateFigureHeredada(esat::Vec2 scale, float angle, esat::Mat3 base, int speed) {
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    float angle2 = esat::Time() * 0.001f * speed;
    m = esat::Mat3Multiply(esat::Mat3Translate(cosf(angle2), sinf(angle2)), m);
    m = esat::Mat3Multiply(base, m);

    return m;
}

esat::Mat3 UpdateFigure(esat::Vec2 scale, float angle, esat::Vec2 translate) {
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Rotate(esat::Time() * 0.001f), m);
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(translate.x, translate.y), m);

    return m;
}

void DrawStar(esat::Mat3 m) {

    esat::Vec2 star[10];

    for (int i = 0; i < knPoints; i++) {
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_star[i]);

        star[i] = {tmp.x, tmp.y};
    }

    esat::DrawSetStrokeColor(255, 255, 255);
    esat::DrawSetFillColor(0,0,0, 0);
    esat::DrawSolidPath(&star[0].x, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitPentagon();
    float angle = 6.28f / (float) 10;
    float angle2 = 6.28f / (float) 3;
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(0, 0, 0);

        esat::Mat3 matriz = UpdateFigure({10.0f, 10.0f}, 0.0f, {400.0f, 300.0f});
        DrawStar(matriz);

        for (int i = 0; i < 3; i++) {
            esat::Mat3 matrizBigger = UpdateFigure({150.0f, 50.0f}, angle2 * i, {400.0f, 300.0f});
            DrawStar(matrizBigger);

            esat::Mat3 matrizHeredar = UpdateFigure({100.0f - 20.0f * i, 100.0f + 20.0f * i}, 0.0f, {400.0f, 300.0f});
            Serialize(matrizHeredar);

            esat::Mat3 heredada = UpdateFigureHeredada({0.2f, 0.2f}, angle * i, matrizHeredar, i + 1);
            DrawStar(heredada);
        }
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
