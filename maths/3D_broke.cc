#include <stdio.h>
#include <esat/math.h>
#include <esat/draw.h>
#include <esat/window.h>
#include <esat/time.h>
#include <esat/input.h>
#include <math.h>

const int knPoints = 10;

esat::Vec4 g_star[knPoints * 2];

void InitStar() {
    float angle = 6.28f / (float) knPoints;

    for (int i = 0; i < knPoints; i++) {
        if (i % 2 == 0) {
            g_star[i] = { cosf(angle * i), sinf(angle * i), 0.4f, 1.0f }; // Front face 
            g_star[i + knPoints] = { cosf(angle * i), sinf(angle * i), -0.4f, 1.0f }; // Back face
        } else {
            g_star[i] = { cosf(angle * i) * 0.6f, sinf(angle * i) * 0.6f, 0.4f, 1.0f }; // Front face 
            g_star[i + knPoints] = { cosf(angle * i) * 0.6f, sinf(angle * i) * 0.6f, -0.4f, 1.0f }; // Back face
        }
    }
}

esat::Mat4 MatrizTransform() {

    esat::Mat4 m = esat::Mat4Identity();

    // rotar al bichito
    
    m = esat::Mat4Multiply(esat::Mat4RotateX(esat::Time() * 0.001f), m);
    m = esat::Mat4Multiply(esat::Mat4RotateY(esat::Time() * 0.001f), m);
    m = esat::Mat4Multiply(esat::Mat4RotateZ(esat::Time() * 0.001f), m);
    
    // Necesitamos transladar por el eje z (T(0, 0, Z))

    m = esat::Mat4Multiply(esat::Mat4Translate(0.0f, 0.0f, 8.0f), m);

    // Proyección

    m = esat::Mat4Multiply(esat::Mat4Projection(), m);

    // esacalamos con el eje z por 1

    m = esat::Mat4Multiply(esat::Mat4Scale(400.0f, 400.0f, 1.0f), m);

    // translacion a efectos por el eje z a 0

    m = esat::Mat4Multiply(esat::Mat4Translate(400.0f, 300.0f, 0.0f), m);

    return m;
}

esat::Mat4 DerivedTransform(esat::Mat4 base) {
    esat::Mat4 m = esat::Mat4Identity();

    m = esat::Mat4Multiply(esat::Mat4Scale(0.5f, 0.5f, 0.5f), m);
    m = esat::Mat4Multiply(esat::Mat4RotateZ(esat::Time() * 0.005f), m);
    m = esat::Mat4Multiply(esat::Mat4Translate(3.0f, 0.0f, 0.0f), m);
    m = esat::Mat4Multiply(esat::Mat4RotateZ(esat::Time() * 0.005f), m);
    m = esat::Mat4Multiply(base, m);

    return m;
}

void DrawMatriz(esat::Mat4 m) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    esat::Vec3 tr_star[knPoints * 2];

    for (int i = 0; i < knPoints * 2; i++) {

        // transformacion de vertices en algo temporal
        esat::Vec4 tmp = esat::Mat4TransformVec4(m, g_star[i]);

        // float r = 1.0f / tmp.w
        // we can use instead tmp.x * r and tmp.y * r
        tr_star[i].x = tmp.x / tmp.w;
        tr_star[i].y = tmp.y / tmp.w;
    }

    for (int i = 0; i < knPoints; i++) {
        esat::DrawLine(tr_star[i].x, tr_star[i].y, tr_star[(i +1) % knPoints].x, tr_star[(i +1) % knPoints].y);
        esat::DrawLine(tr_star[i].x, tr_star[i].y, tr_star[i + knPoints].x, tr_star[i + knPoints].y);
        esat::DrawLine(
            tr_star[i + knPoints].x, 
            tr_star[i + knPoints].y,
            tr_star[(i + 1) % knPoints + knPoints].x,
            tr_star[(i + 1) % knPoints + knPoints].y    
        );
    }
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);
    
    InitStar();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        esat::Mat4 matriz = MatrizTransform();
        DrawMatriz(matriz);
        esat::Mat4 d = DerivedTransform(matriz);
        DrawMatriz(d);
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}
