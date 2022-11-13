#ifndef OBJECT_READER_IMPLEMENTATION
#define OBJECT_READER_IMPLEMENTATION
#include "objReader.h"
#include <fstream>
//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Obj file reader
//Due Date--------November XX, 2022
//
//Reads an obj file for OpenGL to use.
//-----------------------------------------------

void objReader(std::vector<float> & faces, std::vector<float> & texels, std::vector<float> & vertices, std::vector<float> & normals, const std::string & filename){
    std::ifstream objectFile(filename);
    std::string temp;
    int v(0), vt(0), f(0), vn(0);

    while(std::getline(objectFile, temp)){
        if(temp[0] == 'v'){
            if(temp[1] == 'n'){
                ++vn;
            }
            if(temp[1] == 't'){
                ++vt;
            }
            else{
                ++v;
            }
        }
        else if(temp[0] == 'f'){
            ++f;
        }
    }
    std::cout << v << '\n' << vt << '\n' << f << '\n' << vn << '\n';
    objectFile.close();
}

#endif   