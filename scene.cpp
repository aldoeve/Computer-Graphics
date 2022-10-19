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

void normalVector(float* p, float* pNext, float* pLast){
   float a[3], v[3], w[3];
   for(int i(0); i < 3; ++i){
      a[i] = p[i];
      v[i] = pNext[i];
      w[i] = pLast[i];
   }

   for(int i(0); i < 3; ++i){
      v[i] -= a[i];
      w[i] -= a[i];
   }
   float x(v[1]*w[2] - v[2]*w[1]);
   float y(v[2]*w[1] - v[0]*w[2]);
   float z(v[0]*w[1] - v[1]*w[0]); 

   std::cout << x << '/' << y << '/' << z << std::endl;

   glNormal3f(x, y, z);
   return;
}

void wall(){
    glBegin(GL_TRIANGLES);
        float points[][3] = {
            {0.0f, 0.0f, 1.7f}, {0.0f, 0.0f, 0.0f}, {1.7f, 0.0f, 0.0f},
            {1.7f, 0.0f, 1.7f}
        };

        glNormal3f(0, 1, 0);
        glVertex3fv(points[0]);
        glVertex3fv(points[1]);
        glVertex3fv(points[2]);

        glVertex3fv(points[2]);
        glVertex3fv(points[3]);
        glVertex3fv(points[0]);
    glEnd();
}

void cylinder(const int sides){
    float point[sides * 2][3];
    double radians, degrees;
    for(int pt(0); pt < sides; ++pt){
        degrees = pt * 360 / sides;
        radians = degrees * M_PI / 180;
        point[pt][0] = point[pt + sides][0] = cos(radians);
        point[pt][1] = point[pt + sides][1] = sin(radians);
        point[pt][2] = 1;
        point[pt + sides][2] = -1;
    }

    float purple[] = {0.7f, 0.0f, 0.7f, 1.0f};
    float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, purple);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT, purple);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

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

void cube(){
    glPushMatrix();
        glRotatef(-90, 0.0f, 0.0f, -1.0f);
        wall();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 1.7f, 0.0f);
        wall();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.7f, 1.7f, 0.0f);
        glRotatef(90, 0.0f, 0.0f, -1.0f);
        wall();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, 1.7f);
        glRotatef(180, 1.0f, 0.0f, 0.0f);
        wall();
    glPopMatrix();
    glPushMatrix();
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        wall();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0f, 1.7f, 1.7f);
        glRotatef(-270, 1.0f, 0.0f, 0.0f);
        wall();
    glPopMatrix();
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