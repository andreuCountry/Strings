#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <math.h>

float WindowX = 800, WindowY = 600;

const int kNPoints = 30;
float g_circle[kNPoints * 2];

int esat::main(int argc, char **argv) {

	esat::WindowInit(WindowX, WindowY);
	WindowSetMouseVisibility(true);


    float Angle = 6.28f / (float) kNPoints;
    for (int i = 0; i < kNPoints; ++i) {
        g_circle[i * 2] = cosf(Angle * i) * 180.0f + 400.0f;
        g_circle[i * 2 + 1] = sinf(Angle * i) * 180.0f + 300.0f; 
    }

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

            
    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::DrawSetStrokeColor(0,0,0,255);
        esat::DrawSetFillColor(255,255,0,255);
        esat::DrawSolidPath(g_circle, kNPoints);

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();

    return 0;
}