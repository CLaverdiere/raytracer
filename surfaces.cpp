#include <cmath>
#include <iostream>
#include <stdio.h>
#include "surfaces.h"

// e: location vector of camera.
// d: direction unit-vector from camera to sphere.
float Sphere::get_discriminant(vec e, vec d) {
  return pow(d*(e-c), 2) - (d*d)*((e-c)*(e-c) - r*r);
}

vec Sphere::get_intersection(vec e, vec d) {
  float disc = get_discriminant(e, d);

  // solution for parametric t.
  float t = std::min((-d*(e-c) + sqrt(disc)) / (d*d), (-d*(e-c) - sqrt(disc)) / (d*d)); 

  // intersection point vector.
  vec ip = d * t; 

  return ip;
}

vec Sphere::get_surface_normal(vec ip) {
  // unit vector perpendicular to surface of sphere.
  return (c - ip).unitlength();
}

bool Sphere::hit(vec e, vec d) {
  float disc = get_discriminant(e, d);

  // If Discriminant negative, no intersection.
  return disc > 0;
};
