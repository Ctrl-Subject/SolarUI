/*
    SolarUI
    Lightweight UI framework for FreeGLUT/OpenGL

    Copyright (c) 2026 Ellie-Mae Dawson

    Licensed under the MIT License
*/
#ifndef SOLAR_UI_H
#define SOLAR_UI_H

#include <GL/freeglut.h>

namespace SolarUI
{
    // **********************************************
    // *              GLOBAL INPUT STATE            *
    // **********************************************
    inline float MouseX = 0.0f;
    inline float MouseY = 0.0f;

    inline bool MouseDown = false;
    inline bool MousePressed = false;


    // **********************************************
    // *              GLOBAL FONT SYSTEM            *
    // **********************************************

    inline void* CurrentFont = GLUT_BITMAP_HELVETICA_18;

    inline void SetFont(void* font)
    {
        CurrentFont = font;
    }


    // **********************************************
    // *              CORE FUNCTIONS               *
    // **********************************************
    int Init();
    int Update();
    int DrawFrame();


    // **********************************************
    // *                   LABEL                   *
    // **********************************************
    struct Label
    {
        const char* Text;
        float X, Y;

        Label(const char* text = "", float x = 0, float y = 0)
            : Text(text), X(x), Y(y) {}

        void Draw();
    };


    // **********************************************
    // *                  BUTTON                   *
    // **********************************************
    struct Button
    {
        float X, Y, W, H;
        Label Title;

        Button(float x, float y, float w, float h, const char* text)
            : X(x), Y(y), W(w), H(h), Title(text, x, y) {}

        void Draw();
        bool Contains(int mx, int my);
        bool IsClicked();
    };


    // **********************************************
    // *                  SLIDER                   *
    // **********************************************
    struct Slider
    {
        float X, Y, W, H;
        float Value;

        Label Title;

        Slider(float x, float y, float w, float h, const char* text)
            : X(x), Y(y), W(w), H(h),
              Value(0.5f),
              Title(text, x, y) {}

        void Draw();
        void Update();
        bool Contains(int mx, int my);
    };
}

#endif