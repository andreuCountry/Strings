#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <math.h>

float WindowX = 800, WindowY = 600;

const int TrianglePoints = 3, CubePoints = 4, PentaPoints = 5;
float triangle[TrianglePoints * 2], Cube[CubePoints * 2], Penta[PentaPoints * 2];

// Parametrizar
void InitCube() {
    // 180 -> 3,141592...

    float Angle = 6.28f / (float) CubePoints;

    float Offset = 3.14f / 4;
    
    int c = 0;
    for (int i = 0; i < CubePoints; ++i) {
        Cube[c++] = cosf(Angle * i + Offset) * 100.0f + 500.0f;
        Cube[c++] = sinf(Angle * i + Offset) * 100.0f + 200.0f; 
    }
}

void InitTriangle() {
    // 180 -> 3,141592...

    float Angle = 6.28f / (float) TrianglePoints;

    float Offset = 3.14f / 2;

    int c = 0;
    for (int i = 0; i < TrianglePoints; ++i) {
        triangle[c++] = cosf(Angle * i - Offset) * 100.0f + 200.0f;
        triangle[c++] = sinf(Angle * i - Offset) * 100.0f + 100.0f; 
    }
}

void DrawCube() {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,255,0,255);
    esat::DrawSolidPath(Cube, CubePoints);

}

void DrawTriangle() {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,255,0,255);
    esat::DrawSolidPath(triangle, TrianglePoints);

}

int esat::main(int argc, char **argv) {

	esat::WindowInit(WindowX, WindowY);
	WindowSetMouseVisibility(true);

    InitCube();
    InitTriangle();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        DrawCube();
        DrawTriangle();
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();

    return 0;
}