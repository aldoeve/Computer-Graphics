//--------------------------------------------------------------
//Developer------Aldo Vera-Espinoza
//Course---------CS3233
//Project--------Pentagonal Bipyramid
//Due Date-------September 30, 2022
//
//Draws a pentagonal bipyramid using OpenGL. 
//--------------------------------------------------------------

#include<iostream>
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

void display(){
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);

   float point[][3] = {
      //{0.5f, 0.0f, 0.0f}, {0.155f, 0.476f, 0.0f}, {-0.405f, 0.294f, 0.0f},
      //{-0.405f, -0.294f, 0.0f}, {0.155f, -0.476f, 0.0f}

   }; 
   generatePentagon(point, 0, 0.5f);

   //base of the "top" half
   glBegin(GL_TRIANGLE_FAN);
      glColor3f(0.0f, 0.0f, 1.0f);
      glVertex3fv(point[0]);
      glVertex3fv(point[1]);
      glVertex3fv(point[2]);
      glVertex3fv(point[3]);
      glVertex3fv(point[4]);
   glEnd();

   glFlush();
}

//This function generates the points for a pentagon and inserts them into a given array of arrays.
void generatePentagon(float* point[], int startingIndex, float radius){
   float angleIncreament(360.0f);
   float angle(0.0f);
   for(int i(0); i < 5; ++i, ++startingIndex){
      point[startingIndex][0] = radius * cos(angle);
      point[startingIndex][1] = radius * sin(angle);
      angle += angleIncreament;
   }
   return;  
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitWindowSize(640, 640);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("Bipyramid");
   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}