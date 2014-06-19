#include <cmath>
#include <iostream>
#include <stdio.h>
#include "surfaces.h"
#include "util.h"

// TODO Separate these shapes into their own files.

// e: location vector of camera.
// d: direction unit-vector from camera to sphere.
float Sphere::get_discriminant(vec e, vec d) {
  return pow(d*(e-c), 2) - (d*d)*((e-c)*(e-c) - r*r);
}

vec* Sphere::get_intersection(vec e, vec d) {
  vec *ip = NULL;

  // Find discriminant.
  float disc = get_discriminant(e, d);
  if(disc < 0) return ip;

  // solution for parametric t.
  float t = std::min((-d*(e-c) + sqrt(disc)) / (d*d), (-d*(e-c) - sqrt(disc)) / (d*d));

  // intersection point vector.
  ip = new vec(d * t);

  return ip;
};

vec* Sphere::get_surface_normal(vec ip) {
  // TODO only compute some values once.
  // unit vector perpendicular to surface of sphere.
  // distance from center of sphere to intersection point.
  vec* norm = new vec((c - ip).unitlength());
  return norm;
};

bool Sphere::hit(vec e, vec d) {
  float disc = get_discriminant(e, d);

  // If Discriminant negative, no intersection.
  return disc > 0;
};

// Using Cramer's rule to solve linear system.
vec* Triangle::get_intersection(vec e, vec d) {
  vec* ip = NULL;

  float xa_m_xb = v1[0] - v1[1];
  float xa_m_xc = v1[0] - v1[2];
  float xa_m_xe = v1[0] - e[0];
  float ya_m_yb = v2[0] - v2[1];
  float ya_m_yc = v2[0] - v2[2];
  float ya_m_ye = v2[0] - e[1];
  float za_m_zb = v3[0] - v3[1];
  float za_m_zc = v3[0] - v3[2];
  float za_m_ze = v3[0] - e[2];

  // Compute a
  float matrix_a[] = { xa_m_xb, xa_m_xc, d[0],
                       ya_m_yb, ya_m_yc, d[1],
                       za_m_zb, za_m_zc, d[2] };

  float det_a = det3(matrix_a);

  // Compute t
  float matrix_t[] = { xa_m_xb, xa_m_xc, xa_m_xe,
                     ya_m_yb, ya_m_yc, ya_m_ye,
                     za_m_zb, za_m_zc, za_m_ze };

  float t = det3(matrix_t) / det_a;

  if(t < 0) return ip;

  // Compute gamma
  float matrix_gamma[] = { xa_m_xb, xa_m_xe, d[0],
                           ya_m_yb, ya_m_ye, d[1],
                           za_m_zb, za_m_ze, d[2] };

  float gamma = det3(matrix_gamma) / det_a;
  if(gamma < 0 || gamma > 1) return ip;

  // Compute beta
  float matrix_beta[] = { xa_m_xe, xa_m_xc, d[0],
                          ya_m_ye, ya_m_yc, d[1],
                          za_m_ze, za_m_zc, d[2] };

  float beta = det3(matrix_beta) / det_a;
  if(beta < 0 || beta > 1 - gamma) return ip;

  ip = new vec(e + t*d);
  std::cout << "triangle hit" << std::endl;
  return ip;
};

// The surface normal of a triangle is the cross product
// of any two sides.
// TODO only compute this once.
vec* Triangle::get_surface_normal(vec ip) {
  vec* norm = new vec((v2-v1) ^ (v3-v1));
  return norm;
};

// TODO implement.
bool Triangle::hit(vec e, vec d) {
  return false;
};
