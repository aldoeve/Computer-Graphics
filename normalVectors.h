#ifndef NORMALVECTOR
#define NORMALVECTOR
//-----------------------------------------------
//Developer-------Aldo Vera-Espinoza
//Course----------CS3233
//Project---------Normalization
//Due Date--------October 18, 2022
//
//Computes a normal vecotor from the given points.
//-----------------------------------------------

void normalVector(float* p, float* pNext, float* pLast){
   float a[3], v[3], w[3];
   for(int i(0); i < 3; ++i){
      a[i] = p[i];
      v[i] = pNext[i];
      w[i] = pLast[i];
   }

   for(int i(0); i < 3; ++i){
      v[i] -= a[i];
      w[i] -= a[i];
   }
   float x(v[1]*w[2] - v[2]*w[1]);
   float y(v[2]*w[1] - v[0]*w[2]);
   float z(v[0]*w[1] - v[1]*w[0]); 

   //std::cout << x << '/' << y << '/' << z << std::endl;

   glNormal3f(x, y, z);
   return;
}
#endif