#include <cmath>
#include "vec.h"

// Vector properties
// Unit vector
vec vec::unit() {
  return *this / this->mag();
}

// Magnitude
double vec::mag() {
  return sqrt(x*x + y*y + z*z);
}


// Arithmetic vector operations with scalars.
vec vec::operator + (const double &other) {
  return vec(x+other, y+other, z+other);
}

vec operator + (const double d, const vec &v) {
  return vec(v.x + d, v.y + d, v.z + d);
}

vec& vec::operator += (const double &other) {
  x += other; y += other; z += other;
  return *this;
}

vec vec::operator - (const double &other) {
  return vec(x-other, y-other, z-other);
}

vec operator - (const double d, const vec &v) {
  return vec(v.x - d, v.y - d, v.z - d);
}

vec& vec::operator -= (const double &other) {
  x -= other; y -= other; z -= other;
  return *this;
}

vec vec::operator * (const double &other) {
  return vec(x*other, y*other, z*other);
}

vec operator * (const double d, const vec &v) {
  return vec(v.x * d, v.y * d, v.z * d);
}

vec& vec::operator *= (const double &other) {
  x *= other; y *= other; z *= other;
  return *this;
}

vec vec::operator / (const double &other) {
  return vec(x/other, y/other, z/other);
}

vec operator / (const double d, const vec &v) {
  return vec(v.x / d, v.y / d, v.z / d);
}

vec& vec::operator /= (const double &other) {
  x /= other; y /= other; z /= other;
  return *this;
}


// Vector operations.
vec vec::operator + (const vec &other) {
  return vec(x+other.x, y+other.y, z+other.z);
}

vec& vec::operator += (const vec &other) {
  x += other.x; y += other.y; z += other.z;
  return *this;
}

vec vec::operator - (const vec &other) {
  return vec(x-other.x, y-other.y, z-other.z);
}

vec& vec::operator -= (const vec &other) {
  x -= other.x; y -= other.y; z -= other.z;
  return *this;
}

// Negate all values.
vec vec::operator - () {
  return vec(-x, -y, -z);
}

// Dot product
double vec::operator * (const vec &other) {
  return x*other.x + y*other.y + z*other.z;
}

// Cross product
vec vec::operator ^ (const vec &other) {
  return vec(y*other.z - z*other.y, -1 * (x*other.z - z*other.x), x*other.y - y*other.x);
}


// Print a vector for debugging.
std::ostream &operator << (std::ostream &out, vec &v) {
  out << "<" << v.x << ", " << v.y << ", " << v.z << ">";
  return out;
}
