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
#include "raytracer.h"

#define HEIGHT 500
#define WIDTH 500
#define SCALE 255

using namespace std;

Color Raytracer::compute_pixel_value(vec ray, vec camera, vec light, std::vector<Surface*> surfaces) {
  Color color = {32, 67, 150};
  vec *ip, *n, ld;
  bool intersection = false;

  // Perspective view calculation.
  for(vector<Surface*>::iterator it=surfaces.begin(); it != surfaces.end(); ++it) {
    Surface* s = *it;
    ip = s->get_intersection(camera, ray);

    if(ip != NULL) {
      n = s->get_surface_normal(*ip);
      ld = (*ip-light).unitlength(); // unit vector pointing towards light source.
      intersection = true; // discriminant negative ⇒ no intersection.
    }
  }

  // Evaluate Shading model.
  // Lambertian shading method.
  if(intersection) {
    float diffuse_coef = SCALE;
    float light_intensity = 1;
    float lambert_shade = diffuse_coef * light_intensity * max(0.0, (*n)*ld);
    color.r = (unsigned int) lambert_shade;
    color.g = (unsigned int) lambert_shade;
    color.b = (unsigned int) lambert_shade;
  } else {
    color.r = 0;
    color.g = 0;
    color.b = 0;
  }

  delete ip, n;

  return color;
}
