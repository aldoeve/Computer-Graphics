#ifndef SHAPES
#define SHAPES
//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Objects
//Due Date--------October 19, 2022
//
//Containes declarations of useful shapes for
//OpenGL to render.
//-----------------------------------------------

/*
Renders a singular flat wall. Takes an x and z to determine the
length and width of the shape. 
*/
void wall(float, float);

/*
Renders a cube using the wall implementation.
Takes a float to deterime side lenght of the
cube.
*/
void cube(float);

/*
Renders a cylinder with normal vectors at the edges. The
number passed to the function determines how many faces the
shape will be rendered with.
*/
void cylinder(const int);

#endif