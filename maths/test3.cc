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

/*
    Vamos a entender otra movida, ahora no nos vale con el g_circle y hacer movimiento giratorio
    Nos dan puntos recordamos, mente fría pipol, necesitamos entender que esos puntos son
    las coordenadas de nuestra figura, que no tiene porque tener unos puntos previos genericos alrededor
    de una esfera ni nada simplemente tenemos que saber que hay que "normalizar", siendo una cohesión de puntos
    entonces su HOMOGENEA siempre será 1.0f, porque son todo puntos, si fuesen vectores sería 0.0f
*/
esat::Vec3 g_figurita[6] {
    {0.0f, 2.0f, 1.0f}, // esta ultima es la goat, homogenea, se repite por cada par de puntos, por eso hacemos Vec3
    {-5.0f, -8.0f, 1.0f},
    {-8.0f, -8.0f, 1.0f},
    {0.0f, 8.0f, 1.0f},
    {8.0f, -8.0f, 1.0f},
    {5.0f, -8.0f, 1.0f}
};

const float homogeneic = 8.0f;

void Homogeneixar(int points, esat::Vec3 vector[], float goat) {
    for (int i = 0; i < points; ++i) {
        vector[i].x = vector[i].x / goat;
        vector[i].y = vector[i].y / goat;
    }
}

esat::Mat3 UpdateFigurita(esat::Vec2 scale, float rotateSpeed, esat::Vec2 whereMove, int numberFigures) {
    
    esat::Mat3 m = esat::Mat3Identity();
    m = esat::Mat3Multiply(esat::Mat3Scale(scale.x, scale.y), m);
    m = esat::Mat3Multiply(esat::Mat3Rotate(rotateSpeed), m);
    m = esat::Mat3Multiply(esat::Mat3Translate(whereMove.x, whereMove.y), m);

    return m;
}

void DrawFigurita(esat::Mat3 m, int numberOfFigures) {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);

    float points[6 * 2];

    m = esat::Mat3Multiply(esat::Mat3Translate(esat::MousePositionX(), esat::MousePositionY()), m);

    for (int i = 0; i < 6; i++) {
        // Necesitamos esto para transformar los Mat3 en Vec3, para dibujar
        esat::Vec3 tmp = esat::Mat3TransformVec3(m, g_figurita[i]);
        points[i*2] = tmp.x;
        points[i*2+1] = tmp.y;
    }
    esat::DrawSolidPath(points, 6);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);

    Homogeneixar(6, g_figurita, homogeneic);
    esat::Mat3 matriz = UpdateFigurita({20.0f, 20.0f}, 0.0f, {0.0f, 80.0f}, 6);

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        DrawFigurita(matriz, 6);

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}