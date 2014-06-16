/* -*- c++ -*-
 * vec.h
 * CMSC 435/634, Spring 2012
 * Jacob Thompson <thompso1@umbc.edU>
 *
 * Three-dimensional vector class.
 */

#ifndef VEC_H
#define VEC_H

#include <iosfwd>

class vec
{
public:
   // default constructor
   vec () throw ();
  
   // constructor
   vec (const double x, const double y, const double z) throw ();

   // accessors
   double x () const throw ();
   double y () const throw ();
   double z () const throw ();
   double operator [] (unsigned i) const throw ();

   // mutators
   void x (const double x) throw ();
   void y (const double y) throw ();
   void z (const double z) throw ();

   // unary plus and negation
   vec operator + () const throw ();
   vec operator - () const throw ();

   // in-place addition and subtraction
   vec &operator += (const vec &that) throw ();
   vec &operator -= (const vec &that) throw ();

   // addition and subtraction
   vec operator + (const vec &that) const throw ();
   vec operator - (const vec &that) const throw ();

   // in-place scalar multiply
   vec &operator *= (const double s) throw ();

   // scalar multiply
   vec operator * (const double s) const throw ();

   // in-place scalar divide
   vec &operator /= (const double s) throw ();

   // scalar divide
   vec operator / (const double s) const throw ();

   // dot product
   double operator * (const vec &that) const throw ();

   // cross product
   vec operator ^ (const vec &that) const throw ();

   // in-place cross product
   vec &operator ^= (const vec &that) throw ();

   // length (magnitude, norm)
   double length () const throw ();

   // unit vector in direction of this vector (normalized)
   vec unitlength () const throw ();

   // in-place normalize
   vec &normalize () throw ();

private:
   double m_x, m_y, m_z;
};

// scalar multiplication, scalar on left side
vec operator * (const double s, const vec &v) throw ();

// output operator
std::ostream &operator << (std::ostream &sout, const vec &v);

// input operator
std::istream &operator >> (std::istream &sin, vec &v);

#endif
