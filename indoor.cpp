//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Indoor
//Due Date--------October 19, 2022
//
//Renders an indoors scene of Dr.Crawley teaching
//his class using OpenGL.
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
#define STB_IMAGE_IMPLEMENTATION
#include "objects.h"
#include "stb_image.h"
#include "camera.h"
#include <string>

GLuint textureIdList[7];

void print(std::string a, int size, float* location){
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3fv(location);
    for (int i(0); i < size; i++) {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, a[i]);
    }
}

void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    float position[] = {0.4f, 0.0f, 0.4f, 1};
    float yellow[] = {0.9f, 0.8f, 0.0f, 0.1f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, yellow);
    glLightfv(GL_LIGHT1, GL_SPECULAR, yellow);
    glLightfv(GL_LIGHT1, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 90.0f);

    glutMouseFunc(trackballMouseFunction);
    glutMotionFunc(trackballMotionFunction);

    const int numOfTextures(7);
    int imgWidth, imgHeight, bytesPerPixel;
    std::string textureNames[] = {"floor.jpg", "wood.jpg", "plastic.jpg", "metal.jpg", "oak.jpg", "DrCrawley.jpg", "shape.jpg"};
    glGenTextures(numOfTextures, textureIdList);   
    for(int i(0); i < numOfTextures; ++i){
        glBindTexture(GL_TEXTURE_2D, textureIdList[i]);
        unsigned char* imgdata(stbi_load(textureNames[i].c_str(), &imgWidth, &imgHeight, &bytesPerPixel, 0));
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    cameraApply();

    float colors[][4] = {{1.0f, 1.0f, 1.0f, 1.0f}};
    float clear[] = {0.0f, 0.0f, 0.0f, 0.8f};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colors[0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colors[0]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, colors[0]);
    glMateriali(GL_FRONT, GL_SHININESS, 15);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, clear);
    
    double texels[][2] = {{0, 1}, {0, 0},
                          {1, 0}, {1, 1}};
    
    //floor
    glBindTexture(GL_TEXTURE_2D, textureIdList[0]);
    glPushMatrix();
        glTranslatef(-1.0f, -1.0f, -1.0f);
        wall(2.0f, 2.0f, texels);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, textureIdList[1]);
    //table
    glPushMatrix();
        glTranslatef(-0.5f, -0.72f, -0.8f);
        glScalef(1.0f, 1.0f, 0.8f);
        table(texels);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, textureIdList[5]);
    //professor
    glPushMatrix();
        glTranslatef(-0.15f, 0.0f, -0.8f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        wall(0.4f, 0.6f, texels);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, textureIdList[4]);
    //chairs
    glPushMatrix();
        glTranslatef(0.0f, -0.91f, 0.5f);
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        chair(texels);
        glRotatef(-35.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.8f, 0.0f, 0.0f);
        chair(texels);
        glRotatef(35.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(-0.2f, 0.0f, -0.5f);
        chair(texels);
        glTranslatef(-1.0f, 0.0f, -0.2f);
        glRotatef(10.0f, 0.0f, 1.0f, 0.0f);
        chair(texels);
        glTranslatef(-0.15f, 0.0f, 0.45f);
        chair(texels);
    glPopMatrix();

    //text bubble
    std::string upper ("------------------------");
    std::string speech("|Alright time for some computer graphics.|");
    std::string lower ("<-----------------------");
    float middle[] = {-0.15f, 0.1f, -0.8f};
    float top   [] = {-0.15f, 0.15f, -0.8f};
    float bottom[] = {-0.15f, 0.05f, -0.8f};
    print(speech, 43, middle);
    print(upper, 25, top);
    print(lower, 25, bottom);

    glBindTexture(GL_TEXTURE_2D, textureIdList[3]);
    //floor lamp
    glPushMatrix();
        glTranslatef(0.8f, 0.0f, -0.8f);
        glPushMatrix();
            glTranslatef(0.0f, -0.97f, 0.0f);
            glScalef(0.08f, 0.02f, 0.08f);
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            cylinder(30);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0f, -0.56f, 0.0f);
            glScalef(0.03f, 0.4f, 0.03f);
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            cylinder(35);
        glPopMatrix();
        glPushMatrix();
            float yellow[] = {0.9f, 0.8f, 0.0f, 1.0f};
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, yellow);
            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow);
            glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
            glTranslatef(0.0f, -0.1f, 0.0f);
            glScalef(0.2f, 0.1f, 0.2f);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            cylinder(20);
        glPopMatrix();
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