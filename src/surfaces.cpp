#include <cmath>
#include <iostream>
#include <stdio.h>
#include "surfaces.h"
#include "util.h"

// TODO Separate these shapes into their own files.

SurfaceAttr::SurfaceAttr() :
  fill(Color(0,0,0)), kd(0), ks(0), shine(0), t(0), ior(0) { };

SurfaceAttr::SurfaceAttr(Color fill, double kd, double ks, double shine, double t, double ior) :
  fill(fill), kd(kd), ks(ks), shine(shine), t(t), ior(ior) { };


Sphere::Sphere(SurfaceAttr attr, vec c, double r) : c(c), r(r) { 
  this->attr = attr;
};

// e: location vector of camera.
// d: direction unit-vector from camera to sphere.
double Sphere::get_discriminant(vec e, vec d) {
  return pow(d*(e-c), 2) - (d*d)*((e-c)*(e-c) - r*r);
};

bool Sphere::hit(vec e, vec d) {
  double disc = get_discriminant(e, d);

  // If Discriminant negative, no intersection.
  return disc > 0;
};

bool Sphere::get_intersection(vec &ip, vec e, vec d, float lower_t_bound) {
  // TODO Investigate boost::optional.
  // This function should be able to return either a vector, or fail to return one.
  // This way, we could return a vector copy, and not have to deal with passing
  //   references back and forth.
  // Similar to 'Maybe' in Haskell.

  // Find discriminant.
  double disc = get_discriminant(e, d);

  if(disc < 0) return false;

  // solution for parametric t.
  double t = std::min((-d*(e-c) + sqrt(disc)) / (d*d), (-d*(e-c) - sqrt(disc)) / (d*d));

  // intersection point vector.
  if(t > lower_t_bound) {
    ip = d * t;
    return true;
  }

  return false;
};

void Sphere::get_surface_normal(vec &norm, vec ip, vec eye) {
  // Distance from center of sphere to intersection point.
  vec to_c = c - eye;

  norm = (ip - to_c).unit(); // WANT ip - (sphere center - camera)
};

std::ostream &operator << (std::ostream &out, Sphere &s) {
  out << "SPHERE: c=" << s.c << " r=" << s.r;
  return out;
}

Triangle::Triangle(SurfaceAttr attr, vec v1, vec v2, vec v3) : v1(v1), v2(v2), v3(v3) { 
  this->norm = ((v2-v1) ^ (v3-v1)).unit();
  this->attr = attr;
};

// TODO implement.
bool Triangle::hit(vec e, vec d) {
  return false;
};

// Using Cramer's rule to solve linear system.
// We solve by storing determinants used multiple times, for speed.
bool Triangle::get_intersection(vec &ip, vec e, vec d, float lower_t_bound) {
  double xa_m_xb = v1.x - v2.x;
  double xa_m_xc = v1.x - v3.x;
  double xa_m_xe = v1.x - e.x;
  double ya_m_yb = v1.y - v2.y;
  double ya_m_yc = v1.y - v3.y;
  double ya_m_ye = v1.y - e.y;
  double za_m_zb = v1.z - v2.z;
  double za_m_zc = v1.z - v3.z;
  double za_m_ze = v1.z - e.z;

  // Store determinants.
  double ei_m_hf = ya_m_yc*d.z - d.y*za_m_zc;
  double gf_m_di = d.x*za_m_zc - xa_m_xc*d.z;
  double dh_m_eg = xa_m_xc*d.y - ya_m_yc*d.x;
  double ak_m_jb = xa_m_xb*ya_m_ye - xa_m_xe*ya_m_yb;
  double jc_m_al = xa_m_xe*za_m_zb - xa_m_xb*za_m_ze;
  double bl_m_kc = ya_m_yb*za_m_ze - ya_m_ye*za_m_zb;
  double M = xa_m_xb * ei_m_hf + ya_m_yb * gf_m_di + za_m_zb * dh_m_eg;

  // Compute a
  // double matrix_a[] = { xa_m_xb, xa_m_xc, d.x,
  //                       ya_m_yb, ya_m_yc, d.y,
  //                       za_m_zb, za_m_zc, d.z };

  // double det_a = det3(matrix_a);

  // Compute t
  // double matrix_t[] = { xa_m_xb, xa_m_xc, xa_m_xe,
  //                       ya_m_yb, ya_m_yc, ya_m_ye,
  //                       za_m_zb, za_m_zc, za_m_ze };

  // double t = det3(matrix_t) / det_a;
  double t = -1 * (za_m_zc * ak_m_jb + ya_m_yc * jc_m_al + xa_m_xc * bl_m_kc) / M;

  if(t < lower_t_bound) { return false; }

  // Compute gamma
  // double matrix_gamma[] = { xa_m_xb, xa_m_xe, d.x,
  //                           ya_m_yb, ya_m_ye, d.y,
  //                           za_m_zb, za_m_ze, d.z };

  // double gamma = det3(matrix_gamma) / det_a;
  double gamma = (d.z * ak_m_jb + d.y * jc_m_al + d.x * bl_m_kc) / M;

  if(gamma < 0 || gamma > 1) { return false; }

  // Compute beta
  // double matrix_beta[] = { xa_m_xe, xa_m_xc, d.x,
  //                          ya_m_ye, ya_m_yc, d.y,
  //                          za_m_ze, za_m_zc, d.z };

  // double beta = det3(matrix_beta) / det_a;
  double beta = (xa_m_xe * ei_m_hf + ya_m_ye * gf_m_di + za_m_ze * dh_m_eg) / M;

  if(beta < 0 || beta > 1 - gamma) { return false; }

  ip = d * t; // add e?
  return true;
};

// The surface normal of a triangle is the cross product
// of any two sides, and is precomputed in the constructor.
void Triangle::get_surface_normal(vec &norm, vec ip, vec eye) {
  norm = this->norm;
};

std::ostream &operator << (std::ostream &out, Triangle &t) {
  out << "TRIANGLE: v1=" << t.v1 << " v2=" << t.v2 << " v3=" << t.v3;
  return out;
}

Plane::Plane(SurfaceAttr attr, vec n, vec q) : n(n), q(q) {
  this->attr = attr;
};

// TODO implement.
bool Plane::hit(vec e, vec d) {
  return false;
};

// FIXME This doesn't work fully yet.
bool Plane::get_intersection(vec &ip, vec e, vec d, float lower_t_bound) {
  float t = (n * (q - e)) / (n * d);

  // intersection point vector.
  if(t > lower_t_bound) {
    ip = d * t;
    return true;
  }

  return false;
};

void Plane::get_surface_normal(vec &norm, vec ip, vec eye) {
  norm = n.unit();
};
