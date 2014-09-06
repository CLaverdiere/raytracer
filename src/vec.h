#ifndef _VEC_
#define _VEC_

#include <iostream>

class vec {
  public:
    double x, y, z;

    vec() : x(0), y(0), z(0) { };
    vec(double x, double y, double z) : x(x), y(y), z(z) { };

    // Vector properties
    vec unit(); // Unit vector
    double mag(); // Magnitude

    // Arithmetic vector operations with scalars.
    vec  operator +  (const double &other);
    vec& operator += (const double &other);

    vec  operator -  (const double &other);
    vec& operator -= (const double &other);

    vec  operator *  (const double &other);
    vec& operator *= (const double &other);

    vec  operator /  (const double &other);
    vec& operator /= (const double &other);

    // Vector operations.
    vec  operator +  (const vec &other);
    vec& operator += (const vec &other);

    vec  operator -  (const vec &other);
    vec& operator -= (const vec &other);

    // Negate vector components.
    vec operator - ();

    // Dot product
    double operator * (const vec &other);

    // Cross product
    vec operator ^ (const vec &other);
};

// Other combinations of arithmetic for convenience.
vec operator + (const double d, const vec &v);
vec operator - (const double d, const vec &v);
vec operator * (const double d, const vec &v);
vec operator / (const double d, const vec &v);

// Print a vector for debugging.
std::ostream &operator << (std::ostream &out, vec &v);

#endif
