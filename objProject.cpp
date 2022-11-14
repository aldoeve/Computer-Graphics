#ifdef _WIN32
    #include <GL/glut.h>
#elif __linux__
    #include <GL/glut.h>
#elif __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#endif
#include "objReader.h"

std::vector<std::vector<float>> f;
std::vector<float> vt, vn, v;
float numOfFaces(0);

void init(const std::string & filename){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);

    std::vector<float> size(1, 0);
    vt.push_back(0); vn.push_back(0); 
    v.push_back(0) ; f.push_back(size);
    objReader(f, vt, v, vn, filename);
}

void timer(int unused){
    glutPostRedisplay();
    glutTimerFunc(17, timer, 0);
}

void display(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}

int main(int argc, char** argv){
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    init(filename);
        std::cout << f[1][0] << '\n';
        std::cout << f[1][1] << '\n';
        std::cout << f[1][2] << '\n';
        std::cout << f[1][4] << '\n';
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Test 2");
    glutDisplayFunc(display);
    timer(0);
    glutMainLoop();
    return 0;
}
    