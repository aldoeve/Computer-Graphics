//g++ IN.cpp -o OUT -lGL -lGLU -lglut
//------------------------------------------------------------------------------------
// Hello World!
//
// Use this program to test your OpenGL C/C++ setup. It should draw a multicolored
// triangle in a black window.
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// These preprocessor instructions will select and include the right header file(s)
// for your platform. Also, if you are on a Macintosh, they will suppress the
// annoying OpenGL deprecation warnings.
//------------------------------------------------------------------------------------

#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

//------------------------------------------------------------------------------------
// display()
//
// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted.
//------------------------------------------------------------------------------------

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque.
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer.

    // Draw a multicolored triangle.
    glBegin(GL_TRIANGLES);                // Each set of 3 vertices form a triangle.
       glColor3f(1.0f, 0.0f, 0.0f);       // Red
       glVertex2f(-0.5f, -0.5f);          // (x,y) coordinates of vertex
       glColor3f(0.0f, 1.0f, 0.0f);       // Green
       glVertex2f(0.5f, -0.5f);
       glColor3f(0.0f, 0.0f, 1.0f);       // Blue
       glVertex2f(0.0f, 0.5f);
    glEnd();

    glFlush();  // Render now
}

//------------------------------------------------------------------------------------
// main()
//
// Main function. GLUT runs as a console application starting at main().
//------------------------------------------------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);                 // Initialize GLUT.
    glutInitWindowSize(320, 320);          // Set the window's initial width & height.
    glutInitWindowPosition(50, 50);        // Position the window's initial top-left corner.
    glutCreateWindow("OpenGL Hello World");// Create a window with the given title.
    glutDisplayFunc(display);              // Register display callback handler for window re-paint.
    glutMainLoop();                        // Enter the infinitely event-processing loop.
    return 0;
}