//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Obj file reader
//Due Date--------November 16, 2022
//
//Containes declarations useful to reading an 
//Obj file for OpenGL programs to read.
//-----------------------------------------------
#ifndef OBJECT_READER
#define OBJECT_READER
#include <vector>
#include <iostream>

//The function takes four vector containers and fills them with the proper information from the given obj file.
//Note that the number of faces and the max dimension size will be stored in the first vector for the first parameter.
void objReader(std::vector<std::vector<int>> &, std::vector<float> &, std::vector<float> &, std::vector<float> &, const std::string &);

#endif