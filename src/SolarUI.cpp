/*
    SolarUI
    Lightweight UI framework for FreeGLUT/OpenGL

    Copyright (c) 2026 Ellie-Mae Dawson

    Licensed under the MIT License
*/

#include "SolarUI.h"

namespace SolarUI
{
    // **********************************************
    // *             CORE INPUT SYSTEM             *
    // **********************************************
    int Init()
    {
        MouseX = 0;
        MouseY = 0;
        MouseDown = false;
        MousePressed = false;

        return 1;
    }


    int Update()
    {
        static bool lastMouseDown = false;

        MousePressed = (MouseDown && !lastMouseDown);
        lastMouseDown = MouseDown;

        return 1;
    }


    int DrawFrame()
    {
        return 1;
    }


    // **********************************************
    // *                  LABEL                   *
    // **********************************************
    void Label::Draw()
    {
        glColor4f(1,1,1,1);
        glRasterPos2f(X, Y);

        const char* c = Text;
        while (*c)
        {
            glutBitmapCharacter(CurrentFont, *c);
            c++;
        }
    }


    // **********************************************
    // *                  BUTTON                  *
    // **********************************************
    void Button::Draw()
    {
        glColor4f(0.2f,0.2f,0.2f,1);

        glBegin(GL_QUADS);
            glVertex2f(X, Y);
            glVertex2f(X + W, Y);
            glVertex2f(X + W, Y + H);
            glVertex2f(X, Y + H);
        glEnd();

        glColor4f(1,1,1,1);
        glRasterPos2f(X + 10, Y + H * 0.6f);

        const char* c = Title.Text;
        while (*c)
        {
            glutBitmapCharacter(CurrentFont, *c);
            c++;
        }
    }


    bool Button::Contains(int mx, int my)
    {
        return mx >= X && mx <= X + W &&
               my >= Y && my <= Y + H;
    }


    bool Button::IsClicked()
    {
        return Contains(MouseX, MouseY) && MousePressed;
    }


    // **********************************************
    // *                  SLIDER                  *
    // **********************************************
    void Slider::Update()
    {
        if (MouseDown && Contains(MouseX, MouseY))
        {
            Value = (MouseX - X) / W;

            if (Value < 0) Value = 0;
            if (Value > 1) Value = 1;
        }
    }


    void Slider::Draw()
    {
        // track
        glColor4f(0.3f,0.3f,0.3f,1);

        glBegin(GL_QUADS);
            glVertex2f(X, Y + H/2 - 2);
            glVertex2f(X + W, Y + H/2 - 2);
            glVertex2f(X + W, Y + H/2 + 2);
            glVertex2f(X, Y + H/2 + 2);
        glEnd();

        // knob
        float k = X + Value * W;

        glColor4f(0.8f,0.8f,0.8f,1);

        glBegin(GL_QUADS);
            glVertex2f(k - 5, Y);
            glVertex2f(k + 5, Y);
            glVertex2f(k + 5, Y + H);
            glVertex2f(k - 5, Y + H);
        glEnd();

        // text
        glColor4f(1,1,1,1);
        glRasterPos2f(X, Y - 5);

        const char* c = Title.Text;
        while (*c)
        {
            glutBitmapCharacter(CurrentFont, *c);
            c++;
        }
    }


    bool Slider::Contains(int mx, int my)
    {
        return mx >= X && mx <= X + W &&
               my >= Y && my <= Y + H;
    }
}