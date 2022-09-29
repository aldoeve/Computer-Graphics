//--------------------------------------------------------------
//Developer------Aldo Vera-Espinoza
//Course---------CS3233
//Project--------Pentagonal Bipyramid
//Due Date-------September 30, 2022
//
//Draws a pentagonal bipyramid using OpenGL. 
//--------------------------------------------------------------

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#ifdef _WIN32
#include <GL/glut.h>
#elif __linux__
#include <GL/glut.h>
#elif __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif
using namespace std;

//This function generates the points for a pentagon and inserts them into a given array of arrays.
void generatePentagon(float point[][3], int startingIndex, float radius){
    float angleIncreament(360.0f/5.0f);
    angleIncreament *= M_PI / 180.0f;
    float angle(0.0f);
    for (int i(0); i < 5; ++i, ++startingIndex) {
        point[startingIndex][0] = (float)(radius * cos(angle));
        point[startingIndex][1] = (float)(radius * sin(angle));
        angle += angleIncreament;
    }
    return;
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

    float point[][3] = {
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}
    };
    generatePentagon(point, 0, 0.5f);
    glRotatef(50.0f, 1.0f, 1.0f, 0.0f);
    //glRotatef(50.0f, 1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3fv(point[0]);
    glVertex3fv(point[1]);
    glVertex3fv(point[2]);
    glVertex3fv(point[3]);
    glVertex3fv(point[4]);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3fv(point[0]);
    glVertex3fv(point[5]);
    glVertex3fv(point[4]);
    glVertex3fv(point[1]);
    glVertex3fv(point[5]);
    glVertex3fv(point[0]);
    glVertex3fv(point[2]);
    glVertex3fv(point[5]);
    glVertex3fv(point[1]);
    glVertex3fv(point[3]);
    glVertex3fv(point[5]);
    glVertex3fv(point[2]);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Bipyramid");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
