#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <math.h>

float WindowX = 800, WindowY = 600;

const int kNPoints = 30;
float g_circle[kNPoints * 2];

void InitCircle() {
    // 180 -> 3,141592...

    float Angle = 6.28f / (float) kNPoints;
    int c = 0;
    for (int i = 0; i < kNPoints; ++i) {
        g_circle[c++] = cosf(Angle * i) * 180.0f + 400.0f;
        g_circle[c++] = sinf(Angle * i) * 180.0f + 300.0f; 
    }
}


void DrawCircle() {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,255,0,255);
    esat::DrawSolidPath(g_circle, kNPoints);

}

int esat::main(int argc, char **argv) {

	esat::WindowInit(WindowX, WindowY);
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