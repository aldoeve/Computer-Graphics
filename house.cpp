#ifndef _WIN32
    #include <GL/glut.h>
#elif
    #include <GL/glut.h>
#elif
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif

void display(){
    glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.5f);
        glVertex2f(-1.0, -1.0f);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, -1.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(720, 480);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("My House");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}