/*
    SolarUI
    Lightweight UI framework for FreeGLUT/OpenGL

    Copyright (c) 2026 Ellie-Mae Dawson

    Licensed under the MIT License
*/

#include "SolarUI.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace
{
    bool LoadImageTexture(const std::string& path, GLuint& outTexture)
    {
        int width = 0;
        int height = 0;
        int channels = 0;

        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

        if (!data)
        {
            std::cerr << "Failed to load image: " << path << std::endl;
            return false;
        }

        glGenTextures(1, &outTexture);
        glBindTexture(GL_TEXTURE_2D, outTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
        return true;
    }
}

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

    void Checkbox::Update()
    {
        if (MousePressed && Contains(MouseX, MouseY))
        {
            Checked = !Checked;
        }
    }

    void Checkbox::Draw()
    {
        // box
        glColor4f(0.2f,0.2f,0.2f,1);

        glBegin(GL_QUADS);
            glVertex2f(X, Y);
            glVertex2f(X + W, Y);
            glVertex2f(X + W, Y + H);
            glVertex2f(X, Y + H);
        glEnd();

        // checkmark
        if (Checked)
        {
            glColor4f(0.8f,0.8f,0.8f,1);
            glLineWidth(2.0f);

            glBegin(GL_LINES);
                glVertex2f(X + 3, Y + H/2 + 2);
                glVertex2f(X + W/2 - 2, Y + H - 3);

                glVertex2f(X + W/2 - 2, Y + H - 3);
                glVertex2f(X + W - 3, Y + 3);
            glEnd();
            
            glLineWidth(1.0f);
        }

        // text
        glColor4f(1,1,1,1);
        glRasterPos2f(X + W + 5, Y + H * 0.6f);

        const char* c = Title.Text;
        while (*c)
        {
            glutBitmapCharacter(CurrentFont, *c);
            c++;
        }
    }

    bool Checkbox::Contains(int mx, int my)
    {
        return mx >= X && mx <= X + W &&
               my >= Y && my <= Y + H;
    }

    void image::LoadTexture()
    {
        if (TextureLoaded || FilePath.empty())
            return;

        if (LoadImageTexture(FilePath, TextureID))
        {
            TextureLoaded = true;
        }
        else
        {
            TextureID = 0;
            TextureLoaded = true;
        }
    }

    void image::Draw()
    {
        LoadTexture();

        if (TextureID == 0)
            return;

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, TextureID);

        glColor4f(1, 1, 1, 1);

        glBegin(GL_QUADS);
            glTexCoord2f(1, 1); glVertex2f(X, Y);
            glTexCoord2f(0, 1); glVertex2f(X - W, Y);
            glTexCoord2f(0, 0); glVertex2f(X - W, Y - H);
            glTexCoord2f(1, 0); glVertex2f(X, Y - H);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }
}