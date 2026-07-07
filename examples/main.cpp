#include <GL/freeglut.h>
#include <iostream>
#include "../include/SolarUI.h"

SolarUI::Button* btn;
SolarUI::Slider* sld;
SolarUI::Label* lbl;
SolarUI::Checkbox* chk;
SolarUI::image* img;
SolarUI::inputBox* inpBox;
std::string inputMessage = "Type here...";

void MouseMove(int x, int y)
{
    float logicalX = 0.0f;
    float logicalY = 0.0f;
    SolarUI::ScreenToLogical(x, y, logicalX, logicalY);
    SolarUI::MouseX = logicalX;
    SolarUI::MouseY = logicalY;
}

void MouseButton(int button, int state, int x, int y)
{
    float logicalX = 0.0f;
    float logicalY = 0.0f;
    SolarUI::ScreenToLogical(x, y, logicalX, logicalY);

    SolarUI::MouseX = logicalX;
    SolarUI::MouseY = logicalY;

    if (button == GLUT_LEFT_BUTTON)
    {
        SolarUI::MouseDown = (state == GLUT_DOWN);
        if (SolarUI::MouseDown)
        {
            inpBox->OnClick();
        }
    }
}

void Keyboard(unsigned char key, int x, int y)
{
    inpBox->Update(key);
}

void Resize(int width, int height)
{
    SolarUI::UpdateViewport(width, height);
}

void Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    SolarUI::Update();
    sld->Update();
    chk->Update();

    if (btn->IsClicked())
    {
        std::cout << "Button clicked!\n";
    }

    if (inpBox->IsSubmitted())
    {
        inputMessage = inpBox->Input();
        std::cout << "Input submitted: " << inputMessage << "\n";
    }

    lbl->Text = chk->Checked ? "Checkbox: ON" : "Checkbox: OFF";

    SolarUI::SetFont(GLUT_BITMAP_HELVETICA_10);
    btn->Draw();

    SolarUI::SetFont(GLUT_BITMAP_TIMES_ROMAN_10);
    sld->Draw();

    SolarUI::SetFont(GLUT_BITMAP_HELVETICA_18);
    chk->Draw();
    lbl->Draw();
    img->Draw();
    inpBox->Draw();

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("SolarUI Test");

    SolarUI::Init();

    glutMouseFunc(MouseButton);
    glutReshapeFunc(Resize);
    glutPassiveMotionFunc(MouseMove);
    glutMotionFunc(MouseMove);
    glutKeyboardFunc(Keyboard);

    btn = new SolarUI::Button(50, 50, 150, 40, "Click Me");
    sld = new SolarUI::Slider(50, 120, 200, 20, "Volume");
    chk = new SolarUI::Checkbox(50, 180, 20, 20, "Enable feature");
    lbl = new SolarUI::Label("Checkbox: OFF", 50, 250);
    img = new SolarUI::image(500, 10, 128, 128, "examples/image.png");
    inpBox = new SolarUI::inputBox(50, 320, 300, 35);

    glutDisplayFunc(Render);
    glutMainLoop();

    return 0;
}