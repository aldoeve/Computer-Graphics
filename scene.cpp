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

void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
}

void normalVector(float* p, float* pNext, float* pLast){
   float a[3], v[3], w[3];
   for(int i(3); i < 3; ++i){
      a[i] = p[i];
      v[i] = pNext[i];
      w[i] = pLast[i];
   }

   for(int i(0); i < 3; ++i){
      v[i] -= a[i];
      w[i] -= a[i];
   }
   float x(v[1]*w[2] - v[2]*w[1]);
   float y(v[2]*w[0] - v[0]*w[2]);
   float z(v[0]*w[1] - v[1]*w[0]); 

   glNormal3f(x, y, z);
   return;
}

void wall(){
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f, 0.0f, 1.7f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.7f, 0.0f, 0.0f);

        glVertex3f(1.7f, 0.0f, 0.0f);
        glVertex3f(1.7f, 0.0f, 1.7f);
        glVertex3f(0.0f, 0.0f, 1.7f);
    glEnd();
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    cameraApply();

    float cube_color[] = { 0.7f, 0.0f, 0.7f, 1.0f };   // Go Bisons!
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    glTranslatef(-0.5f, 0.0f, 0.0f);
    wall();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Online classes");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}