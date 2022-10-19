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
      point[startingIndex][2] = (float)(radius * sin(angle));
      angle += angleIncreament;
   }
   return;
}

//This function generates the vertices of a pentagonal pyramid for OpenGL to draw
void generatePyramid(float point[][3], bool colorSwitch = false){
   float color[][3] = {
         {0.9f, 0.5f, 0.0f}, {0.22f, 1.0f, 0.07f}, {0.3f, 0.3f, 1.0f},
         {0.68f, 0.13f, 1.0f}, {1.0f, 0.94f, 0.12f}
      };
   if (colorSwitch){
      color[0][0] = 0.7f; color[0][1] = 1.0f; color[0][2] = 0.8f;
      color[1][0] = 1.0f; color[1][1] = 0.5f; color[1][2] = 0.9f;
      color[2][0] = 0.4f; color[2][1] = 0.0f; color[2][2] = 0.1f;
      color[3][0] = 0.3f; color[3][1] = 1.0f; color[3][2] = 1.0f;
      color[4][0] = 0.6f; color[4][1] = 0.5f; color[4][2] = 0.5f;
   }

   glBegin(GL_TRIANGLES);
      glColor3fv(color[0]);
      glVertex3fv(point[0]);
      glVertex3fv(point[5]);
      glVertex3fv(point[4]);

      glColor3fv(color[1]);
      glVertex3fv(point[4]);
      glVertex3fv(point[5]);
      glVertex3fv(point[3]);

      glColor3fv(color[2]);
      glVertex3fv(point[1]);
      glVertex3fv(point[5]);
      glVertex3fv(point[0]);

      glColor3fv(color[3]);
      glVertex3fv(point[2]);
      glVertex3fv(point[5]);
      glVertex3fv(point[1]);

      glColor3fv(color[4]);
      glVertex3fv(point[3]);
      glVertex3fv(point[5]);
      glVertex3fv(point[2]);
   glEnd();
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
      {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.7f, 0.0f}
   };
   generatePentagon(point, 0, 0.5f);
   glRotatef(35.0f, 1.0f, 1.0f, 1.0f);
   
   //Top half base used to guide where the sides would be placed
   glBegin(GL_TRIANGLE_FAN);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3fv(point[0]);
      glVertex3fv(point[1]);
      glVertex3fv(point[2]);
      glVertex3fv(point[3]);
      glVertex3fv(point[4]);
   glEnd();

   //Top half of the shape
   generatePyramid(point);

   glLoadIdentity();
   glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
   glRotatef(35.0f, 1.0f, 1.0f, 1.0f);
   glRotatef(180.0f, 1.0f, 0.0f, 0.0f);

   //bottom half of the shape
   generatePyramid(point, true);

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
