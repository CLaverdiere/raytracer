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

Color Raytracer::compute_pixel_value(vec ray, vec camera, vector<Light> lights, std::vector<Surface*> surfaces) {
  vec *ip = NULL, *n = NULL, ld;
  Color lambert_shade = {0, 0, 0};
  double light_intensity = 1;
  bool intersection = false;

  // Perspective view calculation.
  for(vector<Surface*>::iterator sit=surfaces.begin(); sit != surfaces.end(); ++sit) {
    Surface* s = *sit;
    ip = s->get_intersection(camera, ray);

    if(ip != NULL) {
      lambert_shade.r = 0;
      lambert_shade.g = 0;
      lambert_shade.b = 0;
      for(vector<Light>::iterator lit=lights.begin(); lit != lights.end(); ++lit) {
        Light light = *lit;
        n = s->get_surface_normal(*ip);
        ld = (*ip - light.pos).unitlength(); // unit vector pointing towards light source.
        intersection = true; // discriminant negative ⇒ no intersection.
        lambert_shade.r += s->dc.r * light.intensity * max(0.0, (*n)*ld);
        lambert_shade.g += s->dc.g * light.intensity * max(0.0, (*n)*ld);
        lambert_shade.b += s->dc.b * light.intensity * max(0.0, (*n)*ld);
      }
    }
  }

  // Evaluate Shading model.
  // Lambertian shading method.
  if(intersection) {
    lambert_shade.r = min((int) (lambert_shade.r * SCALE), SCALE);
    lambert_shade.g = min((int) (lambert_shade.g * SCALE), SCALE);
    lambert_shade.b = min((int) (lambert_shade.b * SCALE), SCALE);
  } 

  delete ip, n;

  return lambert_shade;
}
