#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <stdio.h>
#include <esat/math.h>
#include <esat/time.h>
#include <math.h>

float arrow[] = {
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, -3.0f,
    -1.0f, 0.0f
};

esat::Vec3 arrowVec[] = {
    {0.0f, 1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f},
    {0.0f, -3.0f, 1.0f},
    {-1.0f, 0.0f, 1.0f}
};

float square[] = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    1.0f, 1.0f,
    -1.0f, 1.0f,
    -1.0f, -1.0f
};

esat::Vec3 squareVec[] = {
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    {-1.0f, -1.0f, 1.0f}
};


/*esat::Vec3 g_figurita[6] {
    {0.0f, 2.0f, 1.0f},
    {-5.0f, -8.0f, 1.0f},
    {-8.0f, -8.0f, 1.0f},
    {0.0f, 8.0f, 1.0f},
    {8.0f, -8.0f, 1.0f},
    {5.0f, -8.0f, 1.0f}
};*/

//const float homogeneic = 8.0f;

esat::Mat3 UpdateFigurita(esat::Vec2 scale, float angle, esat::Vec2 whereMove, bool moveInitial, esat::Vec2 scaleRec) {
    
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Scale(scaleRec.x, scaleRec.y), m);
    if (moveInitial) {
        m = esat::Mat3Multiply(esat::Mat3Translate(-30.0f, 20.0f), m);
    }
    m = esat::Mat3Multiply(esat::Mat3Translate(whereMove.x, whereMove.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(angle), m);

    return m;
}

void DrawFigurita(esat::Mat3 m) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(120,120,120);

    float points[4 * 2];

    m = esat::Mat3Multiply(esat::Mat3Translate(400, 300), m);

    for (int i = 0; i < 4; i++) {
        // Necesitamos esto para transformar los Mat3 en Vec3, para dibujar
        
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, arrowVec[i]);
        points[i*2] = tmp.x;
        points[i*2+1] = tmp.y;
    }
    esat::DrawSolidPath(points, 4);
}

void DrawFigurita2(esat::Mat3 m, bool isRec, float angle) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(120,120,120);

    float points[5 * 2];

    m = esat::Mat3Multiply(esat::Mat3Translate(400, 300), m);

    for (int i = 0; i < 5; i++) {
        // Necesitamos esto para transformar los Mat3 en Vec3, para dibujar
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, squareVec[i]);
        points[i*2] = tmp.x;
        points[i*2+1] = tmp.y;
    }
    esat::DrawSolidPath(points, 5);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    float angle = 6.28f / 8;
    float angle2 = 6.28f / 4;
    float angle3 = 0.0f;

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        for (int i = 0; i < 8; i++) {
            if (i % 2 != 0) {
                esat::Mat3 matriz = UpdateFigurita({20.0f, 20.0f}, angle * i, {0.0f, -80.0f}, false, {1.0f, 1.0f});
                DrawFigurita(matriz);
            }
        }

        for (int j = 0; j < 1; j++) {
            esat::Mat3 matriz = UpdateFigurita({30.0f, 30.0f}, angle2 * j, {0.0f, 0.0f}, false, {1.0f, 1.0f});
            DrawFigurita2(matriz, false, 0.0f);
        }

        for (int k = 0; k < 5; k++) {
            esat::Mat3 matriz = UpdateFigurita({5.0f, 5.0f}, 0, {15.0f * k, 40.0f}, true, {1.0f, 1.0f});
            DrawFigurita(matriz);
        }

        for (int l = 0; l < 5; l++) {
            esat::Mat3 matriz = UpdateFigurita({5.0f, 5.0f}, 3.14f, {15.0f * l, 40.0f}, true, {1.0f, 1.0f});
            DrawFigurita(matriz);
        }

        for (int s = 0; s < 5; s++) {
            esat::Mat3 matriz = UpdateFigurita({5.0f, 5.0f}, 1.57f, {15.0f * s, 40.0f}, true, {1.0f, 1.0f});
            DrawFigurita(matriz);
        }

        for (int r = 0; r < 5; r++) {
            esat::Mat3 matriz = UpdateFigurita({5.0f, 5.0f}, 4.71f, {15.0f * r, 40.0f}, true, {1.0f, 1.0f});
            DrawFigurita(matriz);
        }

        for (int s = 0; s < 5; s++) {
            esat::Mat3 matriz = UpdateFigurita({5.0f, 5.0f}, 1.57f, {15.0f * s, 60.0f}, true, {1.0f, 2.0f});
            DrawFigurita2(matriz, true, 1.57f);
        }

        for (int r = 0; r < 5; r++) {
            esat::Mat3 matriz = UpdateFigurita({5.0f, 5.0f}, 4.71f, {15.0f * r, 60.0f}, true, {1.0f, 2.0f});
            DrawFigurita2(matriz, true, 4.71f);
        }

        for (int e = 0; e < 5; e++) {
            esat::Mat3 matriz = UpdateFigurita({5.0f, 5.0f}, angle3, {15.0f * e, 60.0f}, true, {1.0f, 2.0f});
            DrawFigurita2(matriz, true, angle3);
        }

        for (int e = 0; e < 5; e++) {
            esat::Mat3 matriz = UpdateFigurita({5.0f, 5.0f}, 3.14f, {15.0f * e, 60.0f}, true, {1.0f, 2.0f});
            DrawFigurita2(matriz, true, 3.14f);
        }

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}