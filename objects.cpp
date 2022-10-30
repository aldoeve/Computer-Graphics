//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Objects
//Due Date--------October 19, 2022
//
//Containes implementations of useful shapes for
//OpenGL to render.
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
#ifndef SHAPE_IMPLEMENTATION
#define SHAPE_IMPLEMENTATION
#include "objects.h"
#define USE_MATH_DEFINES
#include <math.h>
#define PI 3.14159265359

void wall(float x, float z, double texels[4][2]){
    glBegin(GL_TRIANGLES);
        float points[][3] = {
            {0.0f, 0.0f, z}, {0.0f, 0.0f, 0.0f}, {x, 0.0f, 0.0f},
            {x, 0.0f, z}
        };

        glNormal3f(0, 1, 0);
        glTexCoord2dv(texels[0]);
        glVertex3fv(points[0]);
        glTexCoord2dv(texels[1]);
        glVertex3fv(points[1]);
        glTexCoord2dv(texels[2]);
        glVertex3fv(points[2]);

        glVertex3fv(points[2]);
        glTexCoord2dv(texels[3]);
        glVertex3fv(points[3]);
        glTexCoord2dv(texels[0]);
        glVertex3fv(points[0]);
    glEnd();
}

void cube(float sideLength, double texels[4][2]){
    glPushMatrix();
        glRotatef(-90, 0.0f, 0.0f, -1.0f);
        wall(sideLength, sideLength, texels);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, sideLength, 0.0f);
        wall(sideLength, sideLength, texels);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(sideLength, sideLength, 0.0f);
        glRotatef(90, 0.0f, 0.0f, -1.0f);
        wall(sideLength, sideLength, texels);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, sideLength);
        glRotatef(180, 1.0f, 0.0f, 0.0f);
        wall(sideLength, sideLength, texels);
    glPopMatrix();
    glPushMatrix();
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        wall(sideLength, sideLength, texels);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, sideLength, sideLength);
        glRotatef(-270, 1.0f, 0.0f, 0.0f);
        wall(sideLength, sideLength, texels);
    glPopMatrix();
}

void cylinder(const int sides){
    float point[sides * 2][3];
    double radians, degrees;
    for(int pt(0); pt < sides; ++pt){
        degrees = pt * 360 / sides;
        radians = degrees * PI / 180;
        point[pt][0] = point[pt + sides][0] = cos(radians);
        point[pt][1] = point[pt + sides][1] = sin(radians);
        point[pt][2] = 1;
        point[pt + sides][2] = -1;
    }

    glBegin(GL_TRIANGLE_FAN);
    glNormal3i(0,0,1);
    for(int pt(0); pt < sides; ++pt){
        glVertex3fv(point[pt]);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3i(0,0,-1);
    for(int pt(sides - 1); pt >= 0; --pt){
        glVertex3fv(point[pt + sides]);
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_STRIP);
    for (int i(0); i <= sides; ++i){
        glNormal3f(point[i % sides][0], point[i % sides][1], 0.0f);
        glVertex3fv(point[i % sides]);
        glVertex3fv(point[i % sides + sides]);
    }
    glEnd();
}

void table(double texels[4][2]){
    glPushMatrix();
            glScalef(1.0f, 0.05f, 0.6f);
            cube(1, texels);
        glPopMatrix();
        glPushMatrix();
            glScalef(1.0f, 2.7f, 1.0f);
            glTranslatef(0.0f, -0.1f, 0.0f);
            cube(0.1, texels);
            glTranslatef(0.0f, 0.0f, 0.5f);
            cube(0.1, texels);
            glTranslatef(0.9f, 0.0f, 0.0f);
            cube(0.1, texels);
            glTranslatef(0.0f, 0.0f, -0.5f);
            cube(0.1, texels);
        glPopMatrix();
}

#endif