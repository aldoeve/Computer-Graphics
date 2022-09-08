#ifndef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif
#include <cmath>

void drawCircle(int NumofTriangles, float radius, float x, float y){
    float twicepi = 2.0f * M_PI;
    for(int i(0); i <= NumofTriangles; ++i){
        glVertex2f(x + (radius * cos(i * twicepi / NumofTriangles)), y + ((radius + 0.05) * sin(i * twicepi / NumofTriangles)));
    }
}

void display(){
    glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);   //ground and sky
        glColor3f(0.01f, 0.2f, 0.01f);
        glVertex2f(-1.0, -1.0f);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, -1.0f);
        glColor3f(0.0f, 1.0f, 0.5f);
        glVertex2f(1.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);   //body of house
        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex2f(-0.6f, -0.4f);
        glVertex2f(-0.6f, 0.3f);
        glVertex2f(0.6f, 0.3f);
        glVertex2f(0.6f, -0.4f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN); //sun
        float x(0.90);
        float y(0.85);
        glColor3f(0.9f, 0.9f, 0.0f);
        glVertex2f(x, y);
        drawCircle(30, 0.1f, x, y);
    glEnd();


    glBegin(GL_TRIANGLE_STRIP); //roof
        glColor3f(0.6f, 0.6f, 0.6f);
        glVertex2f(-0.7f, 0.3f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(-0.5f, 0.3f);
    glEnd();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glBegin(GL_TRIANGLE_FAN); //clouds
        x = -0.3;
        y = 0.75;
        glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
        glVertex2f(x, y);
        drawCircle(20, 0.1f, x, y);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        x = -0.25;
        y = 0.85;
        glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
        glVertex2f(x, y);
        drawCircle(20, 0.1f, x, y);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
        x = -0.4;
        y = 0.85;
        glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
        glVertex2f(x, y);
        drawCircle(20, 0.1f, x, y);
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