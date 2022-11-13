#ifndef OBJECT_READER
#define OBJECT_READER
#include <vector>
#include <iostream>
//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Obj file reader
//Due Date--------November XX, 2022
//
//Containes declarations useful to reading an 
//Obj file for OpenGL programs to read.
//-----------------------------------------------

//The function takes three vector containers and fills them with the proper information
//from the given obj file.
void objReader(std::vector<float> &, std::vector<float> &, std::vector<float> &, std::vector<float> &, const std::string &);

#endif