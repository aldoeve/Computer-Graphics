//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Objects
//Due Date--------October 19, 2022
//
//Containes declarations of useful shapes for
//OpenGL to render.
//-----------------------------------------------
#ifndef SHAPES
#define SHAPES

/*
Renders a singular flat wall. Takes an x and z to determine the
length and width of the shape. The last parameter is the texel
coordinates to use and is an array of 6 points. 
*/
void wall(float, float, double (*)[2]);

/*
Renders a cube using the wall implementation.
Takes a float to deterime side length of the
cube.The last parameter is an array of the texel points.
*/
void cube(float, double (*)[2]);

/*
Renders a cylinder with normal vectors at the edges. The
number passed to the function determines how many faces the
shape will be rendered with.
*/
void cylinder(const int);

#endif