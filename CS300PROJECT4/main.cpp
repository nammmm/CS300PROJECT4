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

// Rotation of the object
static GLfloat rotate_x = 0.0, rotate_y = 0.0;

//Translation of the object
float trans_x = 0;
float trans_y = 0;
float trans_z = 0;

#define PI 3.14159

static GLfloat angle = -150;   /* in degrees */
static GLfloat angle2 = 30;   /* in degrees */

static int moving = 0, startx=0, starty=0;

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
    
    glTranslatef(trans_x, trans_y, trans_z);
    glRotatef(rotate_x, 1.0, 0.0, 0.0 );
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    
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

static void
mouse(int button, int state, int x, int y)
{
    /* Rotate the scene with the left mouse button. */
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}

/* ARGSUSED1 */
static void
motion(int x, int y)
{
    if (moving) {
        angle = (angle + (x - startx));
        angle2 = (angle2 + (y - starty));
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
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

// arrow keys that are used to control the rotation of the object
void specialKeys( int key, int x, int y )
{
    if (key == GLUT_KEY_RIGHT)
        rotate_x -= 5.0;
    else if (key == GLUT_KEY_LEFT)
        rotate_x -= -5.0;
    else if (key == GLUT_KEY_UP)
        rotate_y += 5.0;
    else if (key == GLUT_KEY_DOWN)
        rotate_y -= 5.0;
    
    glutPostRedisplay();
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
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}