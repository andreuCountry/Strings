#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 33;
float g_circle[knPoints * 2];

void DrawPoints() {

    int c = 0;
    for (int i = 0; i < knPoints; i++) {
        
    }

    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);
    esat::DrawSolidPath(g_circle, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);
    
    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
