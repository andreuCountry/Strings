#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <esat/math.h>
#include <esat/time.h>
#include <math.h>
#include "Library.h"

const int vertexs = 5;
esat::Vec3 g_circle[vertexs];

void InitCircle(int points) {
    float angle = 6.28f / (float) points;

    for (int i = 0; i < points; ++i) {
        g_circle[i] = {cosf(angle * i) * 50, sinf(angle * i) * 50, 1.0f};
    }
}

bool CalculateCollision(esat::Mat3 matriz, esat::Vec3 point1, esat::Vec3 point2) {

    for (int i = 0; i < 5; i++) {
        
        esat::Vec3 vectorPrimate;
        if (i != 5) {
            vectorPrimate = {
                g_circle[i + 1].x - g_circle[i].x,
                g_circle[i + 1].y - g_circle[i].y,
                1.0f
            };
        }
        
        vectorPrimate = KOBE::Vec3Normalize(vectorPrimate);

        esat::Vec3 normal = KOBE::PerpendicularVec3Method1(vectorPrimate);

        float dotProduct = KOBE::Vec3DocProduct(vectorPrimate, normal);

        printf("[%f] \n", dotProduct);
    }

    return true;
}

esat::Mat3 UpdateFigurita(esat::Vec2 scale, esat::Vec2 whereMove) {
    
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Translate(whereMove.x, whereMove.y), m);

    return m;
}

void DrawFigurita(esat::Mat3 m, int numberOfFigures) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    float points[vertexs * 2];

    m = esat::Mat3Multiply(esat::Mat3Translate(400, 300), m);

    for (int i = 0; i < vertexs; i++) {
        // Necesitamos esto para transformar los Mat3 en Vec3, para dibujar
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_circle[i]);
        points[i*2] = tmp.x;
        points[i*2+1] = tmp.y;
    }
    esat::DrawSolidPath(points, 5);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitCircle(vertexs);

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat3 matriz = UpdateFigurita({1.0f, 1.0f}, {0.0f, 0.0f});

        // debug
        bool isValid = CalculateCollision();
        DrawFigurita(matriz, vertexs);
    

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}