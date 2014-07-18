#include <cmath>
#include <iostream>
#include <stdio.h>
#include "surfaces.h"
#include "util.h"

// TODO Separate these shapes into their own files.

Sphere::Sphere(Color dc, vec c, double r) : c(c), r(r) { 
  this->dc = dc;
};

// e: location vector of camera.
// d: direction unit-vector from camera to sphere.
double Sphere::get_discriminant(vec e, vec d) {
  return pow(d*(e-c), 2) - (d*d)*((e-c)*(e-c) - r*r);
}

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

void Sphere::get_surface_normal(vec &norm, vec ip, Camera* camera) {
  // Distance from center of sphere to intersection point.
  vec to_c = c - camera->pos;

  norm = (ip - to_c).unitlength(); // WANT ip - (sphere center - camera)
};

bool Sphere::hit(vec e, vec d) {
  double disc = get_discriminant(e, d);

  // If Discriminant negative, no intersection.
  return disc > 0;
};

std::ostream& operator<<(std::ostream& os, const Sphere& s) {
  os << "x=" << s.c.x() << " y=" << s.c.y() << " z=" << s.c.z() << " r=" << s.r;
  return os;
}

Triangle::Triangle(Color dc, vec v1, vec v2, vec v3) : v1(v1), v2(v2), v3(v3) { 
  this->dc = dc;
};

// Using Cramer's rule to solve linear system.
bool Triangle::get_intersection(vec &ip, vec e, vec d) {
  double xa_m_xb = v1[0] - v1[1];
  double xa_m_xc = v1[0] - v1[2];
  double xa_m_xe = v1[0] - e[0];
  double ya_m_yb = v2[0] - v2[1];
  double ya_m_yc = v2[0] - v2[2];
  double ya_m_ye = v2[0] - e[1];
  double za_m_zb = v3[0] - v3[1];
  double za_m_zc = v3[0] - v3[2];
  double za_m_ze = v3[0] - e[2];

  // Compute a
  double matrix_a[] = { xa_m_xb, xa_m_xc, d[0],
                       ya_m_yb, ya_m_yc, d[1],
                       za_m_zb, za_m_zc, d[2] };

  double det_a = det3(matrix_a);

  // Compute t
  double matrix_t[] = { xa_m_xb, xa_m_xc, xa_m_xe,
                     ya_m_yb, ya_m_yc, ya_m_ye,
                     za_m_zb, za_m_zc, za_m_ze };

  double t = det3(matrix_t) / det_a;

  if(t < 0) return false;

  // Compute gamma
  double matrix_gamma[] = { xa_m_xb, xa_m_xe, d[0],
                           ya_m_yb, ya_m_ye, d[1],
                           za_m_zb, za_m_ze, d[2] };

  double gamma = det3(matrix_gamma) / det_a;
  if(gamma < 0 || gamma > 1) return false;

  // Compute beta
  double matrix_beta[] = { xa_m_xe, xa_m_xc, d[0],
                          ya_m_ye, ya_m_yc, d[1],
                          za_m_ze, za_m_zc, d[2] };

  double beta = det3(matrix_beta) / det_a;
  if(beta < 0 || beta > 1 - gamma) return false;

  ip = e + t*d;
  std::cout << "triangle hit" << std::endl;
  return true;
};

// The surface normal of a triangle is the cross product
// of any two sides.
// TODO only compute this once.
void Triangle::get_surface_normal(vec &norm, vec ip, Camera* camera) {
  norm = (v2-v1) ^ (v3-v1);
};

// TODO implement.
bool Triangle::hit(vec e, vec d) {
  return false;
};
