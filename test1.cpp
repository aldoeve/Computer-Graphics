//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Pentagonal Bipyramid
//Due Date--------October 10, 2022
//
//Draws a pentagonal bipyramid using OpenGL and 
//uses Eck's api to move the 3D shape.
//-----------------------------------------------

#ifdef _WIN32
   #include <GL/glut.h>
#elif __linux__
   #include <GL/glut.h>
#elif __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <OpenGL/gl.h>
   #include <GLUT/glut.h>
#endif
#include <cstdio>
#include "camera.h"
#define _USE_MATH_DEFINES
#include <math.h>

//This function generates the normal vector of given points and passes it to OpenGL
void normalVector(float* a, float* v, float* w){
    ;
}

//This function generates the vertices of a pentagonal pyramid for OpenGL to draw
void generatePyramid(float point[][3], bool colorSwitch = false){
   glBegin(GL_TRIANGLES);
      glVertex3fv(point[0]);
      glVertex3fv(point[5]);
      glVertex3fv(point[4]);

      glVertex3fv(point[4]);
      glVertex3fv(point[5]);
      glVertex3fv(point[3]);

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
}

//This function generates the points for a pentagon and inserts them into a given array of arrays.
void generatePentagon(float point[][3], int startingIndex, float radius){
   float angleIncreament(360.0f/5.0f);
   angleIncreament *= M_PI / 180.0f;
   float angle(0.0f);
   for (int i(0); i < 5; ++i, ++startingIndex) {
      point[startingIndex][0] = (float)(radius * cos(angle));
      point[startingIndex][2] = (float)(radius * sin(angle));
      angle += angleIncreament;
   }
   return;
}

void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
    return;
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    cameraApply();

    float point[][3] = {
      {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.7f, 0.0f}
    };
    generatePentagon(point, 0, 0.5f);

    float shapeColor[] = {0.1f, 0.7f, 0.3f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, shapeColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, shapeColor);
    glMaterialfv(GL_FRONT, GL_AMBIENT, shapeColor);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

    glRotatef(35.0f, 1.0f, 1.0f, 1.0f);
    generatePyramid(point);

    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Test 1 part 2");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
