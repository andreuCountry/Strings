#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 10;
esat::Vec4 g_star[knPoints * 2];

void InitStar() {
    float angle = 6.28f / (float) knPoints;

    for (int i = 0; i < knPoints; i++) {
        if (i % 2 == 0) {
            g_star[i] = {cosf(angle * i), sinf(angle * i), 0.4f, 1.0f};
            g_star[i + knPoints] = {cosf(angle * i), sinf(angle * i), -0.4f, 1.0f};
        } else {
            g_star[i] = {cosf(angle * i) * 0.5f, sinf(angle * i) * 0.5f, 0.4f, 1.0f};
            g_star[i + knPoints] = {cosf(angle * i) * 0.5f, sinf(angle * i) * 0.5f, -0.4f, 1.0f};
        }
    }
}

esat::Mat4 UpdateFigure(esat::Vec2 scale, float angle, esat::Vec2 translate) {
    esat::Mat4 m = esat::Mat4Identity();

    m = esat::Mat4Multiply(esat::Mat4RotateX(angle), m);
    //m = esat::Mat4Multiply(esat::Mat4RotateY(angle), m);
    //m = esat::Mat4Multiply(esat::Mat4RotateZ(angle), m);
    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, 4.0f), m);
    m = esat::Mat4Multiply(esat::Mat4Projection(), m);
    m = esat::Mat4Multiply(esat::Mat4Scale(scale.x, scale.y, 1.0f), m);
    m = esat::Mat4Multiply(esat::Mat4Translate(translate.x, translate.y, 0.0f), m);

    return m;
}

esat::Mat4 DerivadaFigure(esat::Vec2 scale, float angle, esat::Vec2 translate, esat::Mat4 base) {
    esat::Mat4 m = esat::Mat4Identity();

    m = esat::Mat4Multiply(esat::Mat4Scale(scale.x, scale.y, 1.0f), m);
    m = esat::Mat4Multiply(esat::Mat4RotateX(angle), m);
    m = esat::Mat4Multiply(esat::Mat4Translate(translate.x, translate.y, 1.0f), m);
    m = esat::Mat4Multiply(esat::Mat4RotateX(angle), m);
    m = esat::Mat4Multiply(base, m);

    return m;
}

void DrawFigure(esat::Mat4 m) {

    esat::Vec3 star[knPoints * 2];

    for (int i = 0; i < knPoints * 2; i++) {
        esat::Vec4 tmp = esat::Mat4TransformVec4(m, g_star[i]);
        
        star[i].x = tmp.x / tmp.w;
        star[i].y = tmp.y / tmp.w;
    }

    esat::DrawSetStrokeColor(255,255,255);
    esat::DrawSetFillColor(0, 0, 0);
    
    for (int j = 0; j < knPoints; j++) {
        esat::DrawLine(star[j].x, star[j].y, star[(j +1) % knPoints].x, star[(j +1) % knPoints].y);
        esat::DrawLine(star[j].x, star[j].y, star[j+knPoints].x, star[j+knPoints].y);
        esat::DrawLine(
            star[j+knPoints].x,
            star[j+knPoints].y,
            star[(j+1) % knPoints + knPoints].x,
            star[(j+1) % knPoints + knPoints].y
        );
    }
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);
    
    InitStar();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(0, 0, 0);

        esat::Mat4 m = UpdateFigure({150.0f, 150.0f}, esat::Time() * 0.001f, {400.0f, 300.0f});
        DrawFigure(m);

        esat::Mat4 mDerivada = DerivadaFigure({0.3f, 0.3f}, esat::Time() * 0.005f, {0.0f, 2.0f}, m);
        DrawFigure(mDerivada);
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
