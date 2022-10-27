//--------------------------------------------------------------------------
// Developer -- Bryan Crawley, et al.
// Course ----- CS3233
// Project ---- Class demo: Lighted and Textured Cube
// Due date --- N/A
// 
// Draw a cube, and light it with one light source. Set reflectivity
// attributes for the faces of the cube. Use default attributes for the
// light source.
// 
// This version of the lighted cube applies a texture image to one or
// more faces of the cube. I am experimenting a bit here, so you will
// need to read the code to see which faces are textured at the time I
// save it.
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

// This is Sean Barrett's image loader. See documentation in the code.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void init()
{
    glEnable(GL_LIGHTING);    // Enable lighting.
    glEnable(GL_LIGHT0);      // Turn on a light. Use default light attributes.
    glEnable(GL_NORMALIZE);   // OpenGL will make all normal vectors into unit normals

    // Load texture image; copy it into OpenGL; set min-filtering; enable texture.
    int imgWidth, imgHeight, bytesPerPixel;
    unsigned char* data = stbi_load("marble.jpg", &imgWidth, &imgHeight, &bytesPerPixel, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return;
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
    glMatrixMode(GL_MODELVIEW);

    // Use these points for the vertices of the cube.
    int point[][3] = {
        {0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
        {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}
    };

    // Use this material for all the vertices of the cube. If we wanted
    // to, we could set the material for each vertex individually. We
    // don't want to for this application.
    float cube_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // Go Bisons!
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    // Adjust the location and orientation of the cube. Translate it
    // so it is centered on the origin, and tilt it a bit.
    glTranslatef(-0.5f, -0.5f, -0.5f);
    glRotatef(50.0f, 1.0f, 1.0f, 1.0f);

    // Use GL_QUADS to draw the cube. Remember that quads are deprecated.
    // We could use triangles to draw each face of the cube if we wanted to.

    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glNormal3i(0, 0, 1);       // Front face

    glTexCoord2d(0.0, 0.5);
    glVertex3iv(point[3]);

    glTexCoord2d(0.0, 0.0);
    glVertex3iv(point[1]);

    glTexCoord2d(0.5, 0.0);
    glVertex3iv(point[5]);

    glTexCoord2d(0.5, 0.5);
    glVertex3iv(point[7]);

    glNormal3i(1, 0, 0);       // Right face
    glVertex3iv(point[7]);
    glVertex3iv(point[5]);
    glVertex3iv(point[4]);
    glVertex3iv(point[6]);

    glNormal3i(0, 0, -1);      // Back face
    glVertex3iv(point[6]);
    glVertex3iv(point[4]);
    glVertex3iv(point[0]);
    glVertex3iv(point[2]);

    glNormal3i(-1, 0, 0);      // Left face
    glTexCoord2d(0.0, 0.5);
    glVertex3iv(point[2]);
    glTexCoord2d(0.0, 0.0);
    glVertex3iv(point[0]);
    glTexCoord2d(0.5, 0.0);
    glVertex3iv(point[1]);
    glTexCoord2d(0.5, 0.5);
    glVertex3iv(point[3]);

    glNormal3i(0, 1, 0);       // Top face
    glVertex3iv(point[2]);
    glVertex3iv(point[3]);
    glVertex3iv(point[7]);
    glVertex3iv(point[6]);

    glNormal3i(0, -1, 0);      // Bottom face
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
    glutCreateWindow("Lighted Cube With Rotation");
    glutDisplayFunc(display);
    init();         // Various initializations; mostly lighting.
    glutMainLoop();
    return 0;
}
