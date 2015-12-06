/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Name: Nan Jiang, Pratistha Bhandari, Xiangyu Li
 * Assignment: Project 4
 * Title: ---
 * Course: CS 300
 * Semester: Fall 2015
 * Instructor: D. Byrnes
 * Date: ---
 * Sources consulted: Lecture notes, course book, and stack overflow.
 * Program description: ---
 * Instructions: ---
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <cmath>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include "FractalTerrain.h"
#include "Triple.h"
#include "RGB.h"
#include "Triangle.h"
#include <iostream>

//----------------------
// Function prototypes
//----------------------
void init(void);
void display(void);
void reshape(int w, int h);
void idle(void);
void keyboard (unsigned char key, int x, int y);
void arrowkeys(int key, int x, int y);

//----------------------
// Global variables
//----------------------
const GLint win_width = 500;                    // window dimensions
const GLint win_height = 500;
FractalTerrain terrain = FractalTerrain(5, 0.5);

// Initialize OpenGL graphics
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);                  // Black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-12.0, 12.0, -12.0,
             12.0, -12.0, 12.0);
    
    
    
    glShadeModel (GL_SMOOTH);                           // OpenGL shade model is set to GL_SMOOTH
    glEnable(GL_DEPTH_TEST);
}

// Display
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    int counter = 0;
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
        {
            glVertex3f(i, (float)terrain.getAltitude(i, j), j);
            counter++;
        }
    
    glEnd();
    std::cout << counter;
    glutSwapBuffers();
}

// Reshape
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho (-12.0, 12.0, -12.0*(GLfloat)h/(GLfloat)w,
                 12.0*(GLfloat)h/(GLfloat)w, -12.0, 12.0);
    else
        glOrtho (-12.0*(GLfloat)w/(GLfloat)h,
                 12.0*(GLfloat)w/(GLfloat)h, -12.0, 12.0, -12.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor (0.0, 0.0, 0.0, 0.0);
}

// Idle
void idle(void)
{
    // Add code
    glutPostRedisplay();
}

// Keyboard
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

// Special keys
void arrowkeys(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_RIGHT:
            break;
        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (win_width, win_height);         // 500 x 500 pixel window
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Project 4");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowkeys);
    glutMainLoop();
    return 0;
}