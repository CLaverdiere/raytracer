// General algorithm for raytracing, from
//   Fundamentals of Computer Graphics, 3rd ed.
//   Peter Shirley, Steve Marschner.
//
// for each pixel:
//  compute viewing ray.
//  if ray hits an object with t ∈ [0,∞]:
//    compute n.
//    evalutate shading model and set pixel to that color.
//  else:
//    set pixel color to background color.

#include <algorithm>
#include <iostream>
#include "raytracer.h"

#define HEIGHT 500
#define WIDTH 500
#define SCALE 255

using namespace std;

Color Raytracer::compute_pixel_value(vec ray, vec camera, vector<vec> lights, std::vector<Surface*> surfaces) {
  Color color = {32, 67, 150};
  vec *ip, *n, ld;
  double lambert_shade;
  double diffuse_coef = SCALE;
  double light_intensity = 1;
  bool intersection = false;

  // Perspective view calculation.
  for(vector<Surface*>::iterator sit=surfaces.begin(); sit != surfaces.end(); ++sit) {
    Surface* s = *sit;
    ip = s->get_intersection(camera, ray);

    if(ip != NULL) {
      lambert_shade = 0;
      for(vector<vec>::iterator lit=lights.begin(); lit != lights.end(); ++lit) {
        vec light = *lit;
        n = s->get_surface_normal(*ip);
        ld = (*ip-light).unitlength(); // unit vector pointing towards light source.
        intersection = true; // discriminant negative ⇒ no intersection.
        lambert_shade += diffuse_coef * light_intensity * max(0.0, (*n)*ld);
      }
    }
  }


  // Evaluate Shading model.
  // Lambertian shading method.
  if(intersection) {
    color.r = min((unsigned int) lambert_shade, (unsigned int) SCALE);
    color.g = min((unsigned int) lambert_shade, (unsigned int) SCALE);
    color.b = min((unsigned int) lambert_shade, (unsigned int) SCALE);
  } else {
    color.r = 0;
    color.g = 0;
    color.b = 0;
  }

  delete ip, n;

  return color;
}
