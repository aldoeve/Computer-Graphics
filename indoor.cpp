#ifdef _WIN32
   #include <GL/glut.h>
#elif __linux__
   #include <GL/glut.h>
#elif __APPLE__
   #define GL_SILENCE_DEPRECATION
   #include <OpenGL/gl.h>
   #include <GLUT/glut.h>
#endif
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    ///adjust
}

void display(){
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Computer Graphics with Dr.Crawley");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}