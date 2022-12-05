//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Conclusion Project
//Due Date--------December 5, 2022
//
//Draws a pentagonal bipyramid using OpenGL and 
//uses Eck's api to move the 3D shape.----------------------------------------
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
#include "stb_image.h"
#include <vector>

void init(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
}

void display(){
    static bool loadedData(false);
    static const int numOfTextures(7);
    static GLuint textureidList[numOfTextures];
    static std::vector<std::vector<int>> f;
    static std::vector<float> vt, vn, v;
    static std::vector<std::vector<int>> f;
    static std::vector<float> vt, vn, v;
    static std::vector<std::vector<int>> f;
    static std::vector<float> vt, vn, v;
    static std::vector<std::vector<int>> f;
    static std::vector<float> vt, vn, v;

    if(!loadedData){
        int imgWidth, imgHeight, bytesPerPixel;
        std::string textureNames[] ={ "this.jpg"};
        for(int i(0); i < numOfTextures; ++i){
            glBindTexture(GL_TEXTURE_2D, textureidList[i]);
            unsigned char* imgdata(stbi_load(textureNames[i].c_str(), &imgWidth, &imgHeight, &bytesPerPixel, 0));
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgdata);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        std::vector<int> size(2, 0);
        f.reserve(300); v.reserve(300);
        vt.reserve(300); vn.reserve(300);
        f.push_back(size);
        objReader(f, vt, v, vn, objfilename);
        loadedData = true;
    }

}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("So in conclusion...");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}