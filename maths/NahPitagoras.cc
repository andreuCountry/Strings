#include <stdio.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/math.h>
#include <stdio.h>
#include <math.h>

const int knPoints = 60;
float g_circle[knPoints*2];
const float hipo = 1.0f;
float ccontiguo = hipo, copuesto = 0;

esat::Vec2 g_pi_circle[knPoints];

// raiz quadrara sqrtf();

void InitCircle() {

    for (int i = 0; i < knPoints; i++) {

        if (knPoints < 15) {
            ccontiguo =- sqrtf((hipo*hipo) - (copuesto*copuesto));
            copuesto =+ sqrtf((hipo*hipo) - (ccontiguo*ccontiguo));
        } else if (knPoints >= 15 && knPoints < 30) {
            ccontiguo =+ sqrtf((hipo*hipo) - (copuesto*copuesto));
            copuesto =- sqrtf((hipo*hipo) - (ccontiguo*ccontiguo));
        } else if (knPoints >= 30 && knPoints < 45) {
            ccontiguo =+ sqrtf((hipo*hipo) - (copuesto*copuesto));
            copuesto =- sqrtf((hipo*hipo) - (ccontiguo*ccontiguo));
        } else if (knPoints >= 45 && knPoints < 60) {
            ccontiguo =- sqrtf((hipo*hipo) - (copuesto*copuesto));
            copuesto =+ sqrtf((hipo*hipo) - (ccontiguo*ccontiguo));
        }

        g_circle[i * 2] = ccontiguo * 180.0f + 400.0f;
        g_circle[i * 2 + 1] = copuesto * 180.0f + 300.0f;
    }

}

void InitPitagorialCircle() {
    float h = 1.0f;
    float co = h;
    int top_loop = knPoints >> 1;

    float diff = (h * 2.0) / (float) top_loop;

    for (int i = 0; i < top_loop; i++) {
        float cc = sqrtf(h * h - co * co);

        g_pi_circle[i].x = cc * 180.0f + 400.0f;
        g_pi_circle[i].y = co * 180.0f + 300.0f;

        g_pi_circle[i + top_loop].x = -cc * 180.0f + 400.0f;
        g_pi_circle[i + top_loop].y = -cc * 180.0f + 400.0f;

        co -= diff;
    }
}

void DrawCircle() {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);
    esat::DrawSolidPath(g_circle, knPoints);
}

void DrawPitiCircle() {
    esat::DrawSetStrokeColor(0,0,0,255);
    esat::DrawSetFillColor(255,0,0,255);
    esat::DrawSolidPath(g_pi_circle, knPoints);
}

int esat::main(int argc, char **argv) {

    esat::WindowInit(800, 600);
    WindowSetMouseVisibility(true);


    InitCircle();
    InitPitagorialCircle();

    while(esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)) {

    	esat::DrawBegin();
    	esat::DrawClear(120,120,120);

        DrawPitiCircle();
        
    	esat::DrawEnd();
        esat::WindowFrame();
        
    }

    esat::WindowDestroy();
    
    return 0;
}