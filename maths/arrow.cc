#include <stdio.h>
#include <math.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/math.h>
#include "library.h"



void DrawLineTop(KOBE::Vec2 initialPoint) {
    float positionX = (float) esat::MousePositionX();
    float positionY = (float) esat::MousePositionY();

    KOBE::Vec2 pointToGo = KOBE::InitializeVec2(positionX, positionY);
    KOBE::Vec2 vector = KOBE::VMinusV2(pointToGo, initialPoint);

    float lengthVector = KOBE::Vec2Length(vector);

    KOBE::Vec2 normalizedVector = KOBE::Vec2Normalize(vector);

    KOBE::Vec2 vectorScalable = KOBE::VMultpV2(normalizedVector, lengthVector * 0.75);
    vectorScalable = KOBE::VPlusV2(vectorScalable, initialPoint);


    KOBE::Vec2 vectorPerp = KOBE::VMultpV2(normalizedVector, lengthVector * 0.25);

    // next step

    KOBE::Vec2 vperp1 = KOBE::PerpendicularVec2Metod1(vectorPerp);
    KOBE::Vec2 vperp2 = KOBE::PerpendicularVec2Metod2(vectorPerp);
    vperp1 = KOBE::VPlusV2(vperp1, vectorScalable);
    vperp2 = KOBE::VPlusV2(vperp2, vectorScalable);

    KOBE::Vec2Print(vperp1);

    esat::DrawLine(initialPoint.x, initialPoint.y, vectorScalable.x, vectorScalable.y);
    esat::DrawLine(vectorScalable.x, vectorScalable.y, vperp1.x, vperp1.y);
    esat::DrawLine(vectorScalable.x, vectorScalable.y, vperp2.x, vperp2.y);
    esat::DrawLine(vperp1.x, vperp1.y, positionX, positionY);
    esat::DrawLine(vperp2.x, vperp2.y, positionX, positionY);
}

int esat::main(int argc, char** argv) {
    KOBE::Vec2 v = { 2.0f, 1.0f };
    /*
        m1 = 1.0f 0.0f
            2.0f 1.0f
    */
    KOBE::Mat2 m1 = { 1.0f, 2.0f, 0.0f, 1.0f };
    /*
        m2 = 2.0f 3.0f
            0.0f 2.0f
    */
    KOBE::Mat2 m2 = { 2.0f, 0.0f, 3.0f, 2.0f };

    /*
        v1 = m1 * v
        1.0f 0.0f  *  2.0f
        2.0f 1.0f     1.0f
    */
    KOBE::Vec2 v1 = KOBE::Vec2MultMat2Vec2(m1, v);
    /*
        v2 = m2 * v
        2.0f 3.0f  *  2.0f
        0.0f 2.0f     1.0f
    */
    KOBE::Vec2 v2 = KOBE::Vec2MultMat2Vec2(m2, v);

    //KOBE::Vec2Print(v1);
    //KOBE::Vec2Print(v2);

    printf("Length vector: [%f]  [%f], %f \n", v.x, v.y, KOBE::Vec2Length(v));

    KOBE::Vec2 v3 = KOBE::InitializeVec2(1, 1);
    printf("[X]: %f [Y]: %f", v3.x, v3.y);


    // example library
    esat::WindowInit(800, 600);
    esat::WindowSetMouseVisibility(true);

    KOBE::Vec2 initialPoint = KOBE::InitializeVec2(800/2, 600/2);

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        DrawLineTop(initialPoint);

    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();

  return 0;
}
