/* -*- c++ -*-
 * vec.cpp
 * CMSC 435/634, Spring 2012
 * Jacob Thompson <thompso1@umbc.edu>
 *
 * Three-dimensional vector class.
 */

#include "vec.h"
#include <cmath>
#include <iostream>

using namespace std;

// default constructor
vec::vec () throw ()
   : m_x (0.0), m_y (0.0), m_z (0.0)
{
}

// constructor
vec::vec (const double x, const double y, const double z) throw ()
   : m_x (x), m_y (y), m_z (z)
{
}

// x accessor
double vec::x () const throw ()
{
   return m_x;
}

// y accessor
double vec::y () const throw ()
{
   return m_y;
}

// z accessor
double vec::z () const throw ()
{
   return m_z;
}

// access ith component
double vec::operator [] (unsigned i) const throw ()
{
   switch (i)
   {
      case 0:
	 return m_x;
      case 1:
	 return m_y;
      case 2:
	 return m_z;
   }
   return NAN;
}

// x mutator
void vec::x (const double x) throw ()
{
   m_x = x;
}

// y mutator
void vec::y (const double y) throw ()
{
   m_y = y;
}

// z mutator
void vec::z (const double z) throw ()
{
   m_z = z;
}

// unary plus
vec vec::operator + () const throw ()
{
   return *this;
}

// negation
vec vec::operator - () const throw ()
{
   return vec (-m_x, -m_y, -m_z);
}

// in-place addition
vec &vec::operator += (const vec &that) throw ()
{
   m_x += that.m_x;
   m_y += that.m_y;
   m_z += that.m_z;
   return *this;
}

// in-place subtraction
vec &vec::operator -= (const vec &that) throw ()
{
   m_x -= that.m_x;
   m_y -= that.m_y;
   m_z -= that.m_z;
   return *this;
}

// addition
vec vec::operator + (const vec &that) const throw ()
{
   vec v (*this);
   return v += that;
}

// subtraction
vec vec::operator - (const vec &that) const throw ()
{
   vec v (*this);
   return v -= that;
}

// in-place scalar multiply
vec &vec::operator *= (const double s) throw ()
{
   m_x *= s;
   m_y *= s;
   m_z *= s;
   return *this;
}

// scalar multiply
vec vec::operator * (const double s) const throw ()
{
   vec v (*this);
   return v *= s;
}

// in-place scalar divide
vec &vec::operator /= (const double s) throw ()
{
   m_x /= s;
   m_y /= s;
   m_z /= s;
   return *this;
}

// scalar divide
vec vec::operator / (const double s) const throw ()
{
   vec v (*this);
   return v /= s;
}

// dot product
double vec::operator * (const vec &that) const throw ()
{
   return m_x * that.m_x + m_y * that.m_y + m_z * that.m_z;
}

// cross product
vec vec::operator ^ (const vec &that) const throw ()
{
   return vec (m_y * that.m_z - m_z * that.m_y,
	       m_z * that.m_x - m_x * that.m_z,
	       m_x * that.m_y - m_y * that.m_x);
}

// in-place cross product
vec &vec::operator ^= (const vec &that) throw ()
{
   return *this = *this ^ that;
}

// length (magnitude, norm) of vector
double vec::length () const throw ()
{
   return sqrt (*this * *this);
}

// unit vector in direction of this vector (normalized)
vec vec::unitlength () const throw ()
{
   return *this / this->length();
}

// in-place normalize
vec &vec::normalize () throw ()
{
   return *this /= this->length();
}

// scalar multiplication, scalar on left side
vec operator * (const double s, const vec &v) throw ()
{
   return v * s;
}

// output operator
ostream &operator << (ostream &sout, const vec &v)
{
   sout << v.x () << ' ' << v.y () << ' ' << v.z ();
   return sout;
}

// input operator
std::istream &operator >> (std::istream &sin, vec &v)
{
   double x, y, z;
   sin >> x;
   sin >> y;
   sin >> z;
   v.x (x);
   v.y (y);
   v.z (z);
   return sin;
}
