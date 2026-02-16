#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <math.h>
#include "Library.h"

const int knPoints = 3;
float ship[knPoints*2];

struct Ship {
    KOBE::Vec2 pos;
    float scale;
    float angle;
    KOBE::Vec2 speed;
};



void InitShip() {
    float angle_a = 0.0f;
    float angle_b = 6.28f / (float) knPoints;
    float sin_a = sinf(angle_a);
    float sin_b = sinf(angle_b);
    float cos_a = cosf(angle_a);
    float cos_b = cosf(angle_b);

    for (int i = 0; i < knPoints; ++i) {
        float sin_a_b = sin_a * cos_b + cos_a * sin_b;
        float cos_a_b = cos_a * cos_b - sin_a * sin_b;

        ship[i * 2] = cos_a_b * 20.0f + 400.0f;
        ship[i * 2 + 1] = sin_a_b * 20.0f + 300.0f;

        sin_a = sin_a_b;
        cos_a = cos_a_b;
    }
}

void InitShipVec() {
    KOBE::Vec2 iniPos = {800 / 2, 600 / 2};

    float initialAngle = 0.0f;
    float finalAngle = 6.28;


}

void CalculeShip() {
    float angle_a = 0.0f;
    float angle_b = 6.28f / (float) knPoints;
    float sin_a = sinf(angle_a);
    float sin_b = sinf(angle_b);
    float cos_a = cosf(angle_a);
    float cos_b = cosf(angle_b);

    for (int i = 0; i < knPoints; ++i) {
        float sin_a_b = sin_a * cos_b + cos_a * sin_b;
        float cos_a_b = cos_a * cos_b - sin_a * sin_b;

        float scale = 1;

        if (i != 0) {
            scale *= 1.5f;
        }
        ship[i * 2] = cos_a_b * 20.0f * scale + 400.0f;
        ship[i * 2 + 1] = sin_a_b * 20.0f * scale + 300.0f;

        sin_a = sin_a_b;
        cos_a = cos_a_b;
    }
}

void DrawShip() { 
    CalculeShip();
    esat::DrawSetStrokeColor(255, 255, 255, 255);
    esat::DrawSetFillColor(0,0,0,255);
    esat::DrawSolidPath(ship, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitShip();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(0, 0, 0);

        DrawShip();
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}