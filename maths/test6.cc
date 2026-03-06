#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <esat/math.h>
#include <esat/time.h>
#include <math.h>

const int vertexs = 5;
esat::Vec3 g_circle[vertexs];

void InitCircle(int points) {
    float angle = 6.28f / (float) points;

    for (int i = 0; i < points; ++i) {
        g_circle[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

esat::Mat3 UpdateFigurita(esat::Vec2 scale, float angle, esat::Vec2 whereMove) {
    
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(whereMove.x, whereMove.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);

    return m;
}

esat::Mat3 DerivedTransform(esat::Mat3 base, int contador) {
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(0.5f, 0.5f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(3.1415f), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(1.5f, 0.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(6.28f / (float) vertexs * contador), m);

    m = esat::Mat3Multiply(base, m);
    return m;
}

void DrawFigurita(esat::Mat3 m, int numberOfFigures) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    float points[vertexs * 2];

    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);

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
    float angle = 6.28f / vertexs;

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat3 matriz = UpdateFigurita({50.0f, 50.0f}, angle, {0.0f, 0.0f});
        DrawFigurita(matriz, vertexs);
        
        for (int i = 0; i < 5; i++) {
            esat::Mat3 matriz2 = DerivedTransform(matriz, i);
            DrawFigurita(matriz2, vertexs);
        }

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}