//--------------------------------------------------------------------------
// Developer -- Bryan Crawley, et al.
// Course ----- CS3233
// Project ---- Class demo
// Due date --- N/A
// 
// Draw a lighted cylinder, and enable rotating it with Eck's
// trackball.
//--------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

#include <iostream>
using namespace std;

#include <cmath>
#include "camera.h"
//#include "normalizer.h"

const double PI = 3.141592653589793;

void init()
{
    glEnable(GL_LIGHTING);    // Enable lighting.
    glEnable(GL_LIGHT0);      // Turn on a light. Use default light attributes.
    glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals
    glutMouseFunc(trackballMouseFunction);      // Use Eck's mouse function.
    glutMotionFunc(trackballMotionFunction);    // Use Eck's motion function.
    return;
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    cameraSetLimits(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0); // Eck camera
    cameraApply();                                    // Eck camera

    // Use these points for the vertices.
    const int faces = 10;
    float point[faces*2][3];

    // Create a vertex list.
    for (int pt = 0; pt<faces; pt++) {
        double degrees, radians;
        degrees = pt * 360/faces;
        radians = degrees * PI / 180;
        point[pt][0] = point[pt+faces][0] = cos(radians);  // x
        point[pt][1] = point[pt+faces][1] = sin(radians);  // y
        point[pt][2] = 1;  // z
        point[pt+faces][2] = -1;  // z
    }

    // Use this material for all the vertices of the bipyramid. I'm
    // experimenting here. We may not use all these colors.
    float purple[] = { 0.7f, 0.0f, 0.7f, 1.0f };
    float gold[] = { 1.0f, 0.7f, 0.0f, 1.0f };
    float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, purple);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT, purple);
    glMateriali(GL_FRONT, GL_SHININESS, 128);

    // Draw the near end of the cylinder.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3i(0,0,1);
    for (int pt = 0; pt < faces; pt++) {
        glVertex3fv(point[pt]);
    }
    glEnd();
    
    // Draw the far end of the cylinder.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3i(0,0,-1);
    for (int pt = faces-1; pt>=0; pt--) {
        glVertex3fv(point[pt+faces]);
    }
    glEnd();
    
    // Draw sides of the cylinder.
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= faces; i++) {
        glNormal3f(point[i%faces][0], point[i%faces][1], 0.0f);
        glVertex3fv(point[i%faces]);
        glVertex3fv(point[i%faces + faces]);
    }
    glEnd();
    
    glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Lighted Cube With Mouse Rotation");
    glutDisplayFunc(display);
    init();         // Various initializations; mostly lighting.
    glutMainLoop();
    return 0;
}
