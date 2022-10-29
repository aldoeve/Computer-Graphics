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
#include "objects.h"
#include "stb_image.h"
#include "camera.h"

void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);

    long int imgWidth, imgHeight, bytesPerPixel;
    unsigned char* imgdata(stbi_load("floor.jpg", &imgWidth, &imgHeight, &bytesPerPixel, 0));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    cameraApply();

    float colors[][4] = {{1.0f, 1.0f, 1.0f, 1.0f}};

    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[0]);
    glMateriali(GL_FRONT, GL_SHININESS, 15);
    
    double texels[][2] = {{-1, 1}, {-1, -1},
                          {1, -1}, {1, 1}};
    
    glPushMatrix();
    glTranslatef(-1.0f, -1.0f, -1.0f);
    wall(2.0f, 2.0f, texels);
    glPopMatrix();

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