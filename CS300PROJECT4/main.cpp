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
#include <vector>

//----------------------
// Function prototypes
//----------------------
void init(void);
void display(void);
void reshape(int w, int h);
void idle(void);
void keyboard (unsigned char key, int x, int y);
void arrowkeys(int key, int x, int y);
void constructTerrainGrid();
void constructTriangles();
void surfaceNormal();
//----------------------
// Global variables
//----------------------
const GLfloat PI = 3.1415926535f;
const GLint win_width = 500;                    // window dimensions
const GLint win_height = 500;
FractalTerrain terrain = FractalTerrain(5, 0.6);

int lod = 5;
int steps = 1 << lod;
vector<Triangle> triangles(steps * steps * 2);
vector<vector<Triple>> map(steps+1);
vector<vector<RGB>> colors(steps+1);

// Normal and lighting
double ambient = .4;
double diffuse = 4.0;
vector< vector<Triple> > normals(steps+1);
const GLfloat sun[] = { -1.2f, -1.3f, -1.4f, 1.0 };
const GLfloat pos[] = { 0.0, 1, 0, 0};
const GLfloat pos2[] = { 1.0, 0, 0, 0};
const GLfloat pos3[] = { 0.0, 0, 1, 0};
const GLfloat pos4[] = { -1.0, 0, 0, 0};
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f};

// Rotation of the object
static GLfloat rotate_x = 0.0, rotate_y = 0.0;
float trans_x = 0;
float trans_y = 0;
float trans_z = 0;

//Translation of the object
static GLfloat angle = -150;   /* in degrees */
static GLfloat angle2 = 30;   /* in degrees */
static int moving = 0, startx=0, starty=0;

void constructTerrainGrid()
{
    double exaggeration = .7;
    
    for (int i = 0; i < steps + 1; i++)
        map[i].resize(steps + 1);

    for (int i = 0; i < steps + 1; i++)
        colors[i].resize(steps+1);
    for (int i = 0; i <= steps; i++) {
        for (int j = 0; j <= steps; ++ j) {
            double x = 1.0 * i / steps, z = 1.0 * j / steps;
            double altitude = terrain.getAltitude (x, z);
            //cout << i << ' '<< j << ' '<< altitude<< '\n';
            map[i][j] = Triple(x, altitude * exaggeration, z);
            colors[i][j] = terrain.getColor(x, z);
            
        }
    }
}

void constructTriangles()
{
    int numTriangles = (steps * steps * 2);
    triangles.resize(numTriangles);
    cout << "Num of Triangles: " << numTriangles << '\n';
    int triangle = 0;
    for (int i = 0; i < steps; i++) {
        for (int j = 0; j < steps; j++) {
            triangles[triangle ++] = Triangle (i, j, i + 1, j, i, j + 1);
            triangles[triangle ++] = Triangle (i + 1, j, i + 1, j + 1, i, j + 1);
        }
    }
}

void surfaceNormal()
{
    // Initialize every vector on every vertex to be (0,0,0)
    for (int i = 0; i < steps+1; i++)
        normals[i].resize(steps+1);
    for (int i = 0; i < steps+1; i++)
        for (int j = 0; j < steps+1; j++)
        {
            normals[i][j] = Triple(0.0, 0.0, 0.0);
        }
    /* compute triangle normals and vertex averaged normals */
    for (int i = 0; i < triangles.size(); i++)
    {
        Triple v0 = map[triangles[i].getVertex(0).at(0)][triangles[i].getVertex(0).at(2)],
        v1 = map[triangles[i].getVertex(1).at(0)][triangles[i].getVertex(1).at(2)],
        v2 = map[triangles[i].getVertex(2).at(0)][triangles[i].getVertex(2).at(2)];
        Triple normal = v0.subtract (v1).cross (v2.subtract (v1)).normalize ();
        //cout << "Num " << i << ' '<< normal.getX() << ' '<< normal.getHeight() << ' '<< normal.getZ() << '\n';
        triangles[i].setNormal(normal);
        for (int j = 0; j < 3; j++) {
            normals[triangles[i].getVertex(j).at(0)][triangles[i].getVertex(j).at(2)] = normals[triangles[i].getVertex(j).at(0)][triangles[i].getVertex(j).at(2)].add(normal);
        }
    }
    /* compute vertex colors and triangle average colors */
    Triple sunVect = Triple(sun[0], sun[1], sun[2]);
    for (int i = 0; i < triangles.size(); i++) {
        RGB avg = RGB (0.0, 0.0, 0.0);
        vector<RGB> c(3);
        for (int j = 0; j < 3; j++) {
            int k = triangles[i].getVertex(j).at(0), l = triangles[i].getVertex(j).at(2);
            Triple vertex = map[k][l];
            RGB color = colors[k][l];
            //cout << "Original Color: "<< k << ' '<< l << ' '<<color.getRed() << ' '<< color.getGreen()<<' '<< color.getBlue() << '\n';
            Triple normal = normals[k][l].normalize();
            Triple light = vertex.subtract(sunVect);
            double distance2 = light.length2();
            double dot = light.normalize().dot(normal);
            double lighting;
            if (dot < 0.0)
                lighting = ambient;
            else
                lighting = ambient - diffuse * dot/distance2;
            cout << "lighting " << lighting << '\n';
            color = color.scale(lighting);
            //cout << "After lighting Color: "<< color.getRed() << ' '<< color.getGreen()<<' '<< color.getBlue() << '\n';
            c[j] = color;
            avg = avg.add(color);
        }
        triangles[i].setColor(c);
        triangles[i].getAvgColor() = avg.scale(1.0 / 3.0);
    }
}

// Initialize OpenGL graphics
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);                  // Black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (-10.0, 10.0, -10.0,
             10.0, -10.0, 10.0);
    
    // Initialize the light.
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
    glLightfv(GL_LIGHT1, GL_POSITION, pos2);
    
    glLightfv(GL_LIGHT2, GL_POSITION, pos3);
    
    glLightfv(GL_LIGHT3, GL_POSITION, pos4);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    constructTerrainGrid();
    constructTriangles();
    surfaceNormal();
//    for (int i = 0; i < steps+1; i++)
//        for (int j = 0; j < steps+1; j++)
//            cout << normals[i][j].getX() << ' '<< normals[i][j].getHeight()<<' '<< normals[i][j].getZ() << ' '<<normals[i][j].normalize().length2()<<'\n';
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
    
    glPushMatrix();
    glTranslatef(-0.5, 0, -0.5);
    Triangle buf = Triangle();
    vector<double> vertex;
    glBegin(GL_TRIANGLES);
    int num = 0;
    while (num < steps*steps*2)
    {
        buf = triangles[num];
        vertex = buf.getVertex(0);
        vertex[1] = map[vertex[0]][vertex[2]].getHeight();
        //cout << vertex[0] << ' '<< vertex[1] << ' '<< vertex[2] << '\n';
        //glColor3f((float)colors[vertex[0]][vertex[2]].getRed(), (float)colors[vertex[0]][vertex[2]].getGreen(), (float)colors[vertex[0]][vertex[2]].getBlue());
        //cout << buf.getColor().at(0).getRed() << ' '<< buf.getColor().at(0).getGreen() << ' ' << buf.getColor().at(0).getBlue()<< '\n';
        glColor3f(buf.getColor().at(0).getRed(), buf.getColor().at(0).getGreen(), buf.getColor().at(0).getBlue());
        glVertex3f(vertex[0]/steps, vertex[1], vertex[2]/steps);
            
        vertex = buf.getVertex(1);
        vertex[1] = map[vertex[0]][vertex[2]].getHeight();
        //cout << vertex[0] << ' '<< vertex[1] << ' '<< vertex[2] << '\n';
        
        //glColor3f(colors[vertex[0]][vertex[2]].getRed(), colors[vertex[0]][vertex[2]].getGreen(), colors[vertex[0]][vertex[2]].getBlue());
        glColor3f(buf.getColor().at(1).getRed(), buf.getColor().at(1).getGreen(), buf.getColor().at(1).getBlue());
        glVertex3f(vertex[0]/steps, vertex[1], vertex[2]/steps);
            
        vertex = buf.getVertex(2);
        vertex[1] = map[vertex[0]][vertex[2]].getHeight();
        //cout << vertex[0] << ' '<< vertex[1] << ' '<< vertex[2] << '\n';
        //glColor3f(colors[vertex[0]][vertex[2]].getRed(), colors[vertex[0]][vertex[2]].getGreen(), colors[vertex[0]][vertex[2]].getBlue());
        glColor3f(buf.getColor().at(2).getRed(), buf.getColor().at(2).getGreen(), buf.getColor().at(2).getBlue());
        glVertex3f(vertex[0]/steps, vertex[1], vertex[2]/steps);
        num ++;
    }
    glEnd();
    glPopMatrix();
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
        glOrtho (-2.0, 2.0, -2.0*(GLfloat)h/(GLfloat)w,
                 2.0*(GLfloat)h/(GLfloat)w, -2.0, 2.0);
    else
        glOrtho (-2.0*(GLfloat)w/(GLfloat)h,
                 2.0*(GLfloat)w/(GLfloat)h, -2.0, 2.0, -2.0, 2.0);
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