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
#include "shapes.h"
#include "normalVectors.h"
#include <cstdio>
#include "camera.h"
#include <iostream>

void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    float point[] = {0.1f, 0.6f, -0.25f};
    glLightfv(GL_LIGHT0, GL_POSITION, point);
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    cameraApply();

    float cubeColor0[] = {0.9f, 0.8f, 0.0f, 0.3f};
    float cubeColor1[] = {0.0f, 0.4f, 0.4f, 1.0f};
    float cubeColor2[] = {0.7f, 0.4f, 0.1f, 1.0f};
    float moonColor[] = {0.96f, 0.93f, 0.84f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cubeColor1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cubeColor0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cubeColor0);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    glMaterialf(GL_BACK, GL_SHININESS, 10.0f);
    glMaterialfv(GL_BACK, GL_DIFFUSE, cubeColor2);
    glMaterialfv(GL_BACK, GL_SPECULAR, moonColor);
    glMaterialfv(GL_BACK, GL_AMBIENT, moonColor);

    //room walls
    glPushMatrix();
        glTranslatef(-0.85f, -0.85f, -0.85f);
        wall();
        glTranslatef(0.0f, 1.7f, 0.0f);
        glRotatef(270, 0.0f, 0.0f, 1.0f);
        wall();
        glTranslatef(0.0f, 0.0f, 1.7f);
        glRotatef(270, 1.0f, 0.0f, 0.0f);
        wall();
        
    //lightbulb string
        glTranslatef(0.0f, 1.0f, 1.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glScalef(0.01f, 0.01f, 0.2f);
        cylinder(50);
    glPopMatrix();
    
    //bulb
    float cube_color1[] = {0.9f, 0.8f, 0.0f, 0.3f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cube_color1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cube_color1);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, cube_color1);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0F);
    glPushMatrix();
        glTranslatef(0.08f, 0.56f, -0.22f);
        glRotatef(35, 1.0f, 0.0f, 0.0f);
        glScalef(0.07f, 0.07f, 0.07f);
        cube();
    glPopMatrix();

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