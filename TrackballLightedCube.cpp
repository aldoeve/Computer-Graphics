//--------------------------------------------------------------------------
// Developer -- Bryan Crawley, et al.
// Course ----- CS3233
// Project ---- Class demo
// Due date --- N/A
// 
// Draw a cube, and light it with one light source. Set reflectivity
// attributes for the faces of the cube. Use default attributes for the
// light source. Use the trackball feature of David Eck's camera API
// to enable the user to spin the cube with a mouse/trackball/etc.
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

#include <cstdio>
#include "camera.h"  // Eck's camera API. You also need to compile camera.cpp.

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

    //glMatrixMode(GL_PROJECTION);                    // Removed for Eck's camera.
    //glLoadIdentity();                               // Removed for Eck's camera.
    //glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f); // Removed for Eck's camera.
    //glMatrixMode(GL_MODELVIEW);                     // Removed for Eck's camera.
    cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // Eck camera; replaces 4 previous lines
    cameraApply();                                    // Eck camera; replaces 4 previous lines

    // Use these points for the vertices of the cube.
    int point[][3] = {
        {0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
        {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}
    };

    // Use this material for all the vertices of the cube. If we wanted
    // to, we could set the material for each vertex individually. We
    // don't want to for this application.
    float cube_color[] = { 0.7f, 0.0f, 0.7f, 1.0f };   // Go Bisons!
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    // Adjust the initial location and orientation of the cube. Translate it
    // so it is centered on the origin, and give it an attractive tilt.
    glTranslatef(-0.5f, -0.5f, -0.5f);
    glRotatef(50.0f, 1.0f, 1.0f, 1.0f);

    // Use GL_QUADS to draw the cube. Remember that quads are deprecated.
    // We could use triangles to draw each face of the cube if we wanted to.

    glBegin(GL_QUADS);

    glNormal3i(0,0,1);       // Front face
    glVertex3iv(point[3]);
    glVertex3iv(point[1]);
    glVertex3iv(point[5]);
    glVertex3iv(point[7]);

    glNormal3i(1,0,0);       // Right face
    glVertex3iv(point[7]);
    glVertex3iv(point[5]);
    glVertex3iv(point[4]);
    glVertex3iv(point[6]);

    glNormal3i(0,0,-1);      // Back face
    glVertex3iv(point[6]);
    glVertex3iv(point[4]);
    glVertex3iv(point[0]);
    glVertex3iv(point[2]);

    glNormal3i(-1,0,0);      // Left face
    glVertex3iv(point[2]);
    glVertex3iv(point[0]);
    glVertex3iv(point[1]);
    glVertex3iv(point[3]);

    glNormal3i(0,1,0);       // Top face
    glVertex3iv(point[2]);
    glVertex3iv(point[3]);
    glVertex3iv(point[7]);
    glVertex3iv(point[6]);

    glNormal3i(0,-1,0);      // Bottom face
    glVertex3iv(point[0]);
    glVertex3iv(point[4]);
    glVertex3iv(point[5]);
    glVertex3iv(point[1]);

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
