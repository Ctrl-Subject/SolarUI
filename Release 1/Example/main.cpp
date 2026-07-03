#include <GL/freeglut.h>
#include <iostream>
#include "SolarUI.h"

SolarUI::Button* btn;
SolarUI::Slider* sld;
SolarUI::Label* lbl;   // ✅ ADDED

// **********************************************
// *              INPUT CALLBACKS               *
// **********************************************

void MouseMove(int x, int y)
{
    SolarUI::MouseX = (float)x;
    SolarUI::MouseY = (float)y;
}

void MouseButton(int button, int state, int x, int y)
{
    SolarUI::MouseX = (float)x;
    SolarUI::MouseY = (float)y;

    if (button == GLUT_LEFT_BUTTON)
    {
        SolarUI::MouseDown = (state == GLUT_DOWN);
    }
}

// **********************************************
// *                 RENDER LOOP                *
// **********************************************
void Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // update input state
    SolarUI::Update();

    // slider logic must update BEFORE draw
    sld->Update();

    // button click
    if (btn->IsClicked())
    {
        std::cout << "Button clicked!\n";
    }

    // draw UI

    SolarUI::SetFont(GLUT_BITMAP_HELVETICA_10);
    btn->Draw();

    SolarUI::SetFont(GLUT_BITMAP_TIMES_ROMAN_10);
    sld->Draw();

    // ✅ LABEL ADDED
    SolarUI::SetFont(GLUT_BITMAP_HELVETICA_18);
    lbl->Draw();

    glutSwapBuffers();
    glutPostRedisplay();
}

// **********************************************
// *                   MAIN                     *
// **********************************************
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("SolarUI Test");

    // 2D setup
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 600, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // init UI system
    SolarUI::Init();

    // input callbacks
    glutMouseFunc(MouseButton);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MouseMove);

    // create UI elements
    btn = new SolarUI::Button(50, 50, 150, 40, "Click Me");
    sld = new SolarUI::Slider(50, 120, 200, 20, "Volume");

    // ✅ LABEL CREATED
    lbl = new SolarUI::Label("Hello this is a Label!!!", 50, 200);

    // render loop
    glutDisplayFunc(Render);

    glutMainLoop();
    return 0;
}