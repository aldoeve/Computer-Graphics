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


int main(){
    ;
}