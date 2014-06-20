#include "util.h"

// For a matrix [ a b ]
//              [ c d ],
// the determinant is (ad - bc)
double det2(double* a) {
  return a[0]*a[3] - a[1]*a[2];
}

// For a matrix [ a b c ]
//              [ d e f ]
//              [ g h i ],
// the determinant is:   a*det(e,f,h,i)
//                     - b*det(d,f,g,i) 
//                     + c*det(d,e,g,h)
double det3(double* a) {
  double x[] = { a[4], a[5], a[7], a[8] };
  double y[] = { a[3], a[5], a[6], a[8] };
  double z[] = { a[3], a[4], a[6], a[7] };
  return a[0]*det2(x) - a[1]*det2(y) + a[2]*det2(z);
}
