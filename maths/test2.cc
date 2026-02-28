#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <esat/math.h>
#include <esat/time.h>
#include <math.h>

/*
    Vamos a entender ciertas cosas, si hay puntos, en mas de una figura isometrica
    lo que hace es que esos puntos esten en el drawSolidPath en mas de crearlos dinamicamente
    por eso los escalamos y transladamos mas fácilmente, que recorrer y asingar dentro del array
    los puntos por uno mismo
*/
const int vertexPoints1 = 12, vertexPoints2 = 10, vertexPoints3 = 15, vertexPoints4 = 20;

esat::Vec3 g_circle1[vertexPoints1], g_circle2[vertexPoints2], g_circle3[vertexPoints3], g_circle4[vertexPoints4];

void InitCircle(int points, esat::Vec3 vector[]) {
    float angle = 6.28f / (float) points;
    for (int i = 0; i < points; ++i) {
        vector[i] = {cosf(angle * i), sinf(angle * i), 1.0f};
    }
}

esat::Mat3 UpdateCircle(esat::Vec2 scale, float rotateSpeed, esat::Vec2 whereMove) {
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(rotateSpeed), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(whereMove.x, whereMove.y), m);

    return m;
}

void DrawCircle(esat::Mat3 m, esat::Vec2 pointsFlex[]) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    for (int i = 0; i < vertexPoints1; i++) {
        // Necesitamos esto para transformar los Mat3 en Vec3, para dibujar
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_circle1[i]);
        pointsFlex[i] = {tmp.x, tmp.y};
    }
    esat::DrawSolidPath(&pointsFlex[0].x, vertexPoints1);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    InitCircle(vertexPoints1, g_circle1);
    InitCircle(vertexPoints2, g_circle2);
    InitCircle(vertexPoints3, g_circle3);
    InitCircle(vertexPoints4, g_circle4);

    esat::Vec2 pointsFlex1[vertexPoints1];
    esat::Vec2 pointsFlex2[vertexPoints2];
    esat::Vec2 pointsFlex3[vertexPoints3];
    esat::Vec2 pointsFlex4[vertexPoints4];

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat3 matriz = UpdateCircle({40.0f, 40.0f}, esat::Time() * 0.001f, {40.0f, 40.0f});
        DrawCircle(matriz, pointsFlex1);

        esat::Mat3 matriz2 = UpdateCircle({80.0f, 80.0f}, esat::Time(), {100.0f, 500.0f});
        DrawCircle(matriz2, pointsFlex2);

        esat::Mat3 matriz3 = UpdateCircle({80.0f, 80.0f}, esat::Time() * 0.001f, {400.0f, 200.0f});
        DrawCircle(matriz3,pointsFlex3);
        
        esat::Mat3 matriz4 = UpdateCircle({20.0f, 20.0f}, esat::Time(), {600.0f, 400.0f});
        DrawCircle(matriz4, pointsFlex4);

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}