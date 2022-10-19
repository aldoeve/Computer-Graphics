//--------------------------------------------------------------------------------------
//Made by Aldo Vera-Espinoza
//Course: CS3233
//Date: September 19, 2022
//The code takes a point inputed by the user and 
//returns the point contrived from the selected
//transform.
//--------------------------------------------------------------------------------------
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

//The function does matrix multiplication between a 3x3 and a 3x1 matrices.
void matrixMult(double matrix[3][3], vector<double> & point){
    vector<double> temp = {0, 0, 0};
    for (int i(0); i < 3; ++i){
        for (int j(0); j < 3; ++j){
            temp[i] += matrix[i][j] * point[j];
        }
    }
    point[0] = temp[0];
    point[1] = temp[1];
}


void translate(double matrix[3][3], vector<double> & point){
    double x, y;
    cout << "Enter a x and y to translate the point by in the form x y:";
    cin >> x >> y;
    matrix[0][2] = x;
    matrix[1][2] = y;
    matrixMult(matrix, point);
}

void scale(double matrix[3][3], vector<double> & point){
    double x, y;
    cout << "Enter a x and y to scale the point by in the form x y:";
    cin >> x >> y;
    matrix[0][0] = x;
    matrix[1][1] = y;
    matrixMult(matrix, point);
}

void rotate(double matrix[3][3], vector<double> & point){
    double x;
    cout << "Enter a degree to rotate the point by in the form x y:";
    cin >> x;
    matrix[0][0] = cos(x);
    matrix[0][1] = -1 * (sin(x));
    matrix[1][0] = sin(x);
    matrix[1][1] = cos(x);
    matrixMult(matrix, point);
}

int main(){
    double x, y;
    cout << "Enter the point the the form x y:";
    cin >> x >> y;
    cout << "Enter 0 to exit the program. The matrix is constantly popped after each transform." << endl;
    cout << "Enter the transforms to apply to the point. 1 is translation, 2 is scaling, and 3 is rotation." << endl;
    cout << "The program will only carry out one transform at a time."  << endl;

    double matrix[3][3] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    vector<double> point = {x, y, 1};

    int transform(-1);
    while (cin >> transform && transform != 0 && transform < 3){
        if (transform == 1) translate(matrix, point);
        else if (transform == 2) scale(matrix, point);
        else rotate(matrix, point);
        cout << "The point is now at (" << point[0] << ", "<< point[1] << ")." << endl;
        cout << "Enter another transform or 0 to end the program." << endl;
    }
    return 0;
}