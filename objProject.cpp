#include "objReader.h"
#include <fstream>
#include <sstream>


int main(){
    std::vector<std::vector<float>> a;
    std::vector<float> b;
    std::vector<float> c;
    std::vector<float> d;
    objReader(a, b, c, d, "Lowpoly_tree_sample.obj");
}
    