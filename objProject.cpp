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

std::vector<std::vector<int>> f;
std::vector<float> vt, vn, v;
unsigned max;

void init(const std::string & filename){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);

    std::vector<int> size(1, 0);
    f.reserve(300) ; v.reserve(300);
    vt.reserve(300); vn.reserve(300);
    f.push_back(size);
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
    glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, -50.0f, 50.0f);
    glMatrixMode(GL_MODELVIEW);

    //assuming faces with more than three vertices will be rendered using depricated quads.
    //faces with 3 vertices will be rendered using triangles.
    //any face less than three vertices will be discarded as errors.
    for(int i(1); i <= (int)(f[0][0]); ++i){
        if(f[i].size() == 9){
            glBegin(GL_TRIANGLES);
            //v vt vn
                for(short int j(0); j < 9; j += 3){
                    int vnLocation((f[i][j + 2] - 1) *3);
                    int vLocation((f[i][j] - 1) * 3); 
                    int vtLocation((f[i][j + 1] - 1) * 2);
                    glNormal3f(vn[vnLocation], vn[vnLocation + 1], vn[vnLocation + 2]);
                    glTexCoord2f(vt[vtLocation], vt[vtLocation + 1]);
                    glVertex3f(v[vLocation], v[vLocation + 1], v[vLocation + 2]);
                }
            glEnd();
        }
        else if(f[i].size() > 9){
            glBegin(GL_QUADS);
                for(short int j(0); j < (int)(f[i].size()); j += 3){
                    int vnLocation((f[i][j + 2] - 1) *3);
                    int vLocation((f[i][j] - 1) * 3); 
                    int vtLocation((f[i][j + 1] - 1) * 2);
                    glNormal3f(vn[vnLocation], vn[vnLocation + 1], vn[vnLocation + 2]);
                    glTexCoord2f(vt[vtLocation], vt[vtLocation + 1]);
                    glVertex3f(v[vLocation], v[vLocation + 1], v[vLocation + 2]);
                }
            glEnd();
        }
    }

    glutSwapBuffers();
}

int main(int argc, char** argv){
    char texture;
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    std::cout << "Do you want to use a texture?(y/n): ";
    std::cin >> texture;

    init(filename);
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
    