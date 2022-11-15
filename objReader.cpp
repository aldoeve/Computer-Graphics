//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Obj file reader
//Due Date--------November XX, 2022
//
//Reads an obj file for OpenGL to use.
//-----------------------------------------------
#ifndef OBJECT_READER_IMPLEMENTATION
#define OBJECT_READER_IMPLEMENTATION
#include "objReader.h"
#include <fstream>
#include <sstream>

void objReader(std::vector<std::vector<int>> & faces, std::vector<float> & texels, std::vector<float> & vertices, std::vector<float> & normals, const std::string & filename){
    std::ifstream objectFile(filename);
    std::string temp;
    char trash;

    while(getline(objectFile, temp)){
        const std::string data(temp);
        if(data[0] == 'v'){
            std::istringstream values(temp);
            if(data[1] == 'n'){
                values >> trash >> trash;
                while(values >> temp) normals.push_back(std::stof(temp));
            }
            else if(data[1] == 't'){
                values >> trash >> trash;
                while(values >> temp) texels.push_back(std::stof(temp));
            }
            else{
                values >> trash;
                while(values >> temp) vertices.push_back(std::stof(temp));
            }
        }
        else if(data[0] == 'f'){
            ++faces[0][0]; 
            std::istringstream values(temp);
            values >> trash;
            std::vector<int> oneFace;
            while(values >> temp){
                std::string separatedValue;
                for(int i(0); temp[i] != '\0'; ++i){
                    if(temp[i] == '/'){
                        float valueToStore(-1);
                        if(!separatedValue.empty()) valueToStore = (std::stoi(separatedValue));
                        oneFace.push_back(valueToStore);
                        separatedValue.erase();
                    }
                    else{separatedValue += temp[i];}
                }
                float valueToStore(-1);
                if(!separatedValue.empty()) valueToStore = (std::stoi(separatedValue));
                oneFace.push_back(valueToStore);
            }
            faces.push_back(oneFace);
        }
    }
    objectFile.close();
}
#endif   