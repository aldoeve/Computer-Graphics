
//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Test 2
//Due Date--------November 16, 2022
//
//Uses data from an obj file to draw the object
//using OpenGL.
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
#include "objReader.h"

//I understand Global variables are not preferable
std::vector<std::vector<int>> f;
std::vector<float> vt, vn, v;

void init(const std::string & objfilename){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);

    std::vector<int> size(2, 0);
    f.reserve(300) ; v.reserve(300);
    vt.reserve(300); vn.reserve(300);
    f.push_back(size);
    objReader(f, vt, v, vn, objfilename);
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
    glOrtho(-1.0f * f[0][1] - 5.0f, f[0][1] + 5.0f, -1.0f * f[0][1] - 5.0f, f[0][1] + 5.0f, -1.0f * f[0][1] - 5.0f, f[0][1] + 5.0f);
    glMatrixMode(GL_MODELVIEW);

    float cube_color[] = { 0.7f, 0.0f, 0.7f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_color);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_color);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0F);

    glRotatef(2.0, 0.0f, 1.0f, 0.0f);

    //assuming faces with more than three vertices will be rendered using depricated quads.
    //faces with 3 vertices will be rendered using triangles.
    //any face less than three vertices will be discarded as errors.
    //while texture vetices are read in as per the test requirements, they are not utilized.
    //If any information is not present in the faces such as no given normal vector, the previous one will be utilized.
    for(int i(1); i <= (int)(f[0][0]); ++i){
        if(f[i].size() == 9){
            glBegin(GL_TRIANGLES);
                for(short int j(0); j < 9; j += 3){
                    int vnLocation((f[i][j + 2] - 1) * 3);
                    //int vtLocation((f[i][j + 1] - 1) * 3);
                    int vLocation((f[i][j] - 1) * 3);
                    if(vnLocation > 0) glNormal3f(vn[vnLocation], vn[vnLocation + 1], vn[vnLocation + 2]);
                    //if(vtLocation > 0)
                    //  glTexCoord2f(vt[vtLocation], vt[vtLocation + 1]);
                    glVertex3f(v[vLocation], v[vLocation + 1], v[vLocation + 2]);
                }
            glEnd();
        }
        else if(f[i].size() > 9){
            glBegin(GL_QUADS);
                for(short int j(0); j < (int)(f[i].size()); j += 3){
                    int vnLocation((f[i][j + 2] - 1) *3);
                    //int vtLocation((f[i][j + 1] - 1) * 3);
                    int vLocation((f[i][j] - 1) * 3);
                    if(vnLocation > 0) glNormal3f(vn[vnLocation], vn[vnLocation + 1], vn[vnLocation + 2]);
                    //if(vtLocation > 0)
                    //  glTexCoord2f(vt[vtLocation], vt[vtLocation + 1]);
                    glVertex3f(v[vLocation], v[vLocation + 1], v[vLocation + 2]);
                }
            glEnd();
        }
    }

    glutSwapBuffers();
}

int main(int argc, char** argv){
    std::string objFileName;
    std::string textureFileName;
    std::cout << "Enter filename: ";
    std::cin  >> objFileName;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Test 2");
    glutDisplayFunc(display);
    init(objFileName);
    timer(0);
    glutMainLoop();
    return 0;
}
    