#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <esat/math.h>
#include <esat/time.h>
#include <math.h>

const int vertexs = 30;
esat::Vec3 g_circle[vertexs];

void InitCircle(int points) {
    float angle = 6.28f / (float) points;

    for (int i = 0; i < points; ++i) {
        g_circle[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

esat::Mat3 OrbitTransform(int i) {
    
    esat::Mat3 m = esat::Mat3Identity();

    m = esat::Mat3Multiply(esat::Mat3Scale(100.0f, 30.0f), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(6.28f / 3.0f * i), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);

    return m;
}

esat::Mat3 NeutronTransform(esat::Mat3 base, float speed) {
    esat::Mat3 m = esat::Mat3Identity();


    m = esat::Mat3Multiply(esat::Mat3Scale(1.0f / 100.0f * 10.0f, 1.0f / 30.0f * 10.0f), m);

    float angle = esat::Time() * 0.001f * speed;
    m = esat::Mat3Multiply(esat::Mat3Translate(cosf(angle), sinf(angle)), m);

    m = esat::Mat3Multiply(base, m);

    return m;
}

void DrawFigurita(esat::Mat3 m, int nPoints, esat::Vec3* points) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    esat::Vec2 damnPoints[100];

    for (int i = 0; i < nPoints; i++) {
        // Necesitamos esto para transformar los Mat3 en Vec3, para dibujar
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, points[i]);
        damnPoints[i] = {tmp.x, tmp.y};
    }
    esat::DrawSolidPath(&damnPoints[0].x, nPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitCircle(vertexs);
    float angle = 6.28f / vertexs;

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        for (int i = 0; i < 3; i++) {
            esat::Mat3 matriz = OrbitTransform(i);
            DrawFigurita(matriz, vertexs, g_circle);
            esat::Mat3 matriz2 = NeutronTransform(matriz, i+1);
            DrawFigurita(matriz2, vertexs, g_circle);
        }

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}