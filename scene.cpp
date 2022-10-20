//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Lighted Scene
//Due Date--------October 19, 2022
//
//Draws a scene of what some students would have
//been like when zoom classes were prevalent.
//-----------------------------------------------

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
    float point[] = {0.1f, 0.6f, -0.25f, 1};
    float point2[] = {-2.0f, 2.0f, -0.01f, 1};
    float moon[] = {0.8f, 0.8f, 0.8f, 0.1f};
    float moonBlue[] = {0.7f, 0.9f, 1.0f, 0.1f};
    float white[] = {0.0f, 0.0f, 0.0f};
    float greenish[] = {0.7f, 0.8f, 0.6f};
    float brown[] = {0.7f, 0.4f, 0.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, greenish);
    glLightfv(GL_LIGHT0, GL_AMBIENT, brown);
    glLightfv(GL_LIGHT0, GL_POSITION, point);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, moon);
    glLightfv(GL_LIGHT1, GL_SPECULAR, moon);
    glLightfv(GL_LIGHT1, GL_AMBIENT, moonBlue);
    glLightfv(GL_LIGHT1, GL_POSITION, point2);

    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    cameraApply();

    float cubeColor0[] = {0.7f, 0.4f, 0.0f, 0.3f};
    float cubeColor1[] = {0.0f, 0.4f, 0.4f, 1.0f};
    float moonColor[] = {0.96f, 0.93f, 0.84f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cubeColor1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cubeColor0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cubeColor0);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);
    glMaterialf(GL_BACK, GL_SHININESS, 50.0f);
    glMaterialfv(GL_BACK, GL_DIFFUSE, moonColor);
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
        glPushMatrix();
            glTranslatef(0.0f, 1.7f, 0.0f);
            glRotatef(270, 0.0f, 0.0f, 1.0f);
            wall();
        glPopMatrix();
        
    //lightbulb string
        float purple[] = {0.7f, 0.0f, 0.7f, 1.0f};
        float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, purple);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white);
        glMaterialfv(GL_FRONT, GL_AMBIENT, purple);
        glMateriali(GL_FRONT, GL_SHININESS, 128);
        glTranslatef(0.14f, 1.0f, 1.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        glScalef(0.01f, 0.01f, 0.2f);
        cylinder(50);
    glPopMatrix();
    
    //bulb
    float lightbulb[] = {0.9f, 0.8f, 0.0f, 0.5f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightbulb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lightbulb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightbulb);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0F);
    glPushMatrix();
        glTranslatef(0.08f, 0.56f, -0.22f);
        glRotatef(35, 1.0f, 0.0f, 0.0f);
        glScalef(0.07f, 0.07f, 0.07f);
        cube();
    glPopMatrix();

    //TV
    glPushMatrix();
        float black[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glMaterialfv(GL_FRONT, GL_SPECULAR, lightbulb);
        glMaterialfv(GL_FRONT, GL_AMBIENT, black);
        glMateriali(GL_FRONT, GL_SHININESS, 60);
        glTranslatef(-0.84f, 0.1f, -0.49f);
        glScalef(0.025f, 0.3f, 0.6f);
        cube();
    glPopMatrix();

    //moon
    glPushMatrix();
        float moon[] = {0.8f, 0.8f, 0.8f, 0.5f};
        float moonBlue[] = {0.7f, 0.9f, 1.0f, 0.5f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moonBlue);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0F);
        glTranslatef(-2.0f, 2.0f, 0.0f);
        glScalef(0.3f, 0.3f, 0.04f);
        cylinder(50);
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Intro to programming 2020");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}