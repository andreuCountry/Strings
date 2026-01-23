#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <math.h>

const int knPoints = 30;
float g_circle[knPoints*2];

void InitCircle() {
    float angle_a = 0.0f;
    float angle_b = 6.28f / (float) knPoints;
    float sin_a = sinf(angle_a);
    float sin_b = sinf(angle_b);
    float cos_a = cosf(angle_a);
    float cos_b = cosf(angle_b);

    for (int i = 0; i < knPoints; ++i) {
        float sin_a_b = sin_a * cos_b + cos_a * sin_b;
        float cos_a_b = cos_a * cos_b - sin_a * sin_b;

        g_circle[i * 2] = cos_a_b * 180.0f + 400.0f;
        g_circle[i * 2 + 1] = sin_a_b * 180.0f + 300.0f;

        sin_a = sin_a_b;
        cos_a = cos_a_b;
    }
}

void DrawCircle() {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);
    esat::DrawSolidPath(g_circle, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);


    InitCircle();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        DrawCircle();
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}