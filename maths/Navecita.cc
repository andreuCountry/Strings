#include <stdio.h>
#include <math.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/math.h>
#include "library.h"

struct {
    KOBE::Vec2 position;
    float angle;
    float scale[3];
    KOBE::Vec2 speed;
};

const int knPoints = 3;
KOBE::Vec2 triangle;

void CalculateVectors() {

}

void InitPitagorialTriangle() {
    float h = 1.0f;
    float co = h;
    int top_loop = knPoints >> 1;

    float diff = (h * 2.0) / (float) top_loop;

    for (int i = 0; i < top_loop; i++) {
        float cc = sqrtf(h * h - co * co);

        triangle[i].x = cc * 180.0f + 400.0f;
        triangle[i].y = co * 180.0f + 300.0f;

        triangle[i + top_loop].x = -cc * 180.0f + 400.0f;
        triangle[i + top_loop].y = -cc * 180.0f + 400.0f;

        co -= diff;
    }
}

int esat::main(int argc, char** argv) {

    // example library
    esat::WindowInit(800, 600);
    esat::WindowSetMouseVisibility(true);

    KOBE::Vec2 initialPoint = KOBE::InitializeVec2(800, 600);

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();

  return 0;
}