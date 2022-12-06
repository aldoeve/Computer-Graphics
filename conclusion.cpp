//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Conclusion Project
//Due Date--------December 5, 2022
//
//An outdoor scene of a dog watching a cow while
//a teapot cools down.
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
#include "stb_image.h"
#include "camera.h"
#include "objReader.h"
#include "objects.h"
#include <vector>

void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    //glutMouseFunc(trackballMouseFunction);
    //glutMotionFunc(trackballMotionFunction);
}

void objectToVector(std::vector<std::vector<int>>& f, std::vector<float>& vt, std::vector<float>& vn, std::vector<float>& v, std::string& filename){
    std::vector<int> size(2, 0);
    f.reserve(300); v.reserve(300);
    vt.reserve(300); vn.reserve(300);
    f.push_back(size);
    objReader(f, vt, v, vn, filename);
}

void objectDrawer(std::vector<std::vector<int>>& f, std::vector<float>& vt, std::vector<float>& vn, std::vector<float>& v, bool enableTextures){
    for(int i(1); i <= (int)(f[0][0]); ++i){
        if(f[i].size() == 9){
            glBegin(GL_TRIANGLES);
                for(short int j(0); j < 9; j += 3){
                    int vnLocation((f[i][j + 2] - 1) * 3);
                    int vtLocation((f[i][j + 1] - 1) * 3);
                    int vLocation((f[i][j] - 1) * 3);
                    if(vnLocation > 0) glNormal3f(vn[vnLocation], vn[vnLocation + 1], vn[vnLocation + 2]);
                    if(enableTextures && vtLocation > 0)
                      glTexCoord2f(vt[vtLocation], vt[vtLocation + 1]);
                    glVertex3f(v[vLocation], v[vLocation + 1], v[vLocation + 2]);
                }
            glEnd();
        }
        else if(f[i].size() > 9){
            glBegin(GL_QUADS);
                for(short int j(0); j < (int)(f[i].size()); j += 3){
                    int vnLocation((f[i][j + 2] - 1) *3);
                    int vtLocation((f[i][j + 1] - 1) * 3);
                    int vLocation((f[i][j] - 1) * 3);
                    if(vnLocation > 0) glNormal3f(vn[vnLocation], vn[vnLocation + 1], vn[vnLocation + 2]);
                    if(enableTextures && vtLocation > 0)
                      glTexCoord2f(vt[vtLocation], vt[vtLocation + 1]);
                    glVertex3f(v[vLocation], v[vLocation + 1], v[vLocation + 2]);
                }
            glEnd();
        }
    }
}

void timer(int unused){
    glutPostRedisplay();
    glutTimerFunc(17, timer, 0);
}

void display(){
    static double texels[][2] = {{0, 1}, {0, 0},
                          {1, 0}, {1, 1}};
    static bool loadedData(false);
    static const int numOfTextures(4);
    static GLuint textureidList[numOfTextures];
    static std::vector<std::vector<int>> f0;
    static std::vector<float> vt0, vn0, v0;
    static std::vector<std::vector<int>> f1;
    static std::vector<float> vt1, vn1, v1;
    static std::string objectfileNames[3] = {"cow.obj", "Lowpoly_tree_sample.obj", "dog.obj"};
    static std::vector<std::vector<int>> f2;
    static std::vector<float> vt2, vn2, v2;

    if(!loadedData){
        int imgWidth, imgHeight, bytesPerPixel;
        std::string textureNames[] ={ "marble.jpg", "grass.jpg", "cloud.jpg", "sun.jpg"};
        glGenTextures(numOfTextures, textureidList);
        for(int i(0); i < numOfTextures; ++i){
            glBindTexture(GL_TEXTURE_2D, textureidList[i]);
            unsigned char* imgdata(stbi_load(textureNames[i].c_str(), &imgWidth, &imgHeight, &bytesPerPixel, 0));
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        objectToVector(f0, vt0, vn0, v0, objectfileNames[0]);
        objectToVector(f1, vt1, vn1, v1, objectfileNames[1]);
        objectToVector(f2, vt2, vn2, v2, objectfileNames[2]);
        loadedData = true;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //cameraSetLimits(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); //here if the camera api is desired
    //cameraApply();
    glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -2.0f, 2.0f);
    glMatrixMode(GL_MODELVIEW);
    float colors[][4] = {{1.0f, 1.0f, 1.0f, 1.0f}};
    float clear[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colors[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, colors[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, colors[0]);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 15);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, clear);

    glRotatef(2.0, 0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glRotatef(30, 1.0f, 0.0f, 0.0f);
    //grass
    glBindTexture(GL_TEXTURE_2D, textureidList[1]);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTranslatef(-2.0f, -1.0f, -2.0f);
        wall(4, 4, texels);
    glPopMatrix();

    //sun
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textureidList[3]);
        glTranslatef(1.0f, 1.9f, 0.0f);
        cube(0.2, texels);
    glPopMatrix();

    //cloud
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textureidList[2]);
        glTranslatef(0.0f, 1.8f, 0.0f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        wall(0.5, 0.5, texels);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //cow
    glPushMatrix();
        glEnable(GL_CULL_FACE);
        glTranslatef(-1.0f, -1.0f, 0.4f);
        glScalef(0.8f, 0.8f, 0.8f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        objectDrawer(f0, vt0, vn0, v0, false);
        glDisable(GL_CULL_FACE);
    glPopMatrix();

    //dog
    glPushMatrix();
        glEnable(GL_CULL_FACE);
        glTranslatef(0.4f, -1.0f, 0.4f);
        glScalef(0.01f, 0.01f, 0.01f);
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        objectDrawer(f2, vt2, vn2, v2, false);
        glDisable(GL_CULL_FACE);
    glPopMatrix();

    //teapot
    glPushMatrix();
        glTranslatef(-0.52f, -0.6f, 0.8f);
        glutWireTeapot(0.1f);
    glPopMatrix();

    //outside table
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureidList[0]);
        glTranslatef(-0.8f, -0.72f, 0.5f);
        glScalef(0.5f, 1.0f, 0.8f);
        table(texels);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //pen
    glPushMatrix();
        float brown[] = {0.5f, 0.2f, 0.0f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, brown);
        glTranslatef(-0.3f, -1.0f, -0.4f);
        glScalef(1.0f, 6.0f, 1.0f);
        cube(0.1f, texels);
        glTranslated(1.3f, 0.0f, 0.0f);
        cube(0.1f, texels);
        glTranslatef(0.0f, 0.0f, -1.0f);
        cube(0.1f, texels);
        glTranslatef(-1.3f, 0.0f, 0.0f);
        cube(0.1f, texels);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.2f, -0.8f, -0.4f);
        glPushMatrix();
            glTranslatef(-0.1f, 0.0f, -0.9f);
            glScalef(1.0f, 3.0f, 10.0f);
            cube(0.1f, texels);
            glTranslatef(1.35f, 0.0f, 0.0f);
            cube(0.1f, texels);
        glPopMatrix();
        glPushMatrix();
            glScalef(12.0f, 3.0f, 1.0f);
            cube(0.1f, texels);
            glTranslatef(0.0f, 0.0f, -1.0f);
            cube(0.1f, texels);
        glPopMatrix();
    glPopMatrix();

    //tree
    glPushMatrix();
        float green[] = {0.5f, 0.9, 0.2, 0.0f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
        glEnable(GL_CULL_FACE);
        glTranslatef(-1.5f, -1.0f, -1.5f);
        glScalef(0.05f, 0.05f, 0.05f);
        objectDrawer(f1, vt1, vn1, v1, false);
        glDisable(GL_CULL_FACE);
    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("So in conclusion...");
    glutDisplayFunc(display);
    timer(0);
    init();
    glutMainLoop();
    return 0;
    //something intresting is that swaping buffers or culling faces seems to make certain things transparent just like
    //with the canon.obj
}