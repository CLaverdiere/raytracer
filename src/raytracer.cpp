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

#define SCALE 255

Color Raytracer::compute_pixel_value(vec ray, Camera* camera, std::vector<Light> lights, std::vector<Surface*> surfaces) {
  vec *ip = NULL, *n = NULL, ld;
  Color lambert_shade = {0, 0, 0};
  bool intersection = false;

  // Perspective view calculation.
  for(std::vector<Surface*>::iterator sit=surfaces.begin(); sit != surfaces.end(); ++sit) {
    Surface* s = *sit;
    ip = s->get_intersection(camera->pos, ray);

    if(ip != NULL) {
      lambert_shade.r = lambert_shade.g = lambert_shade.b = 0;
      for(std::vector<Light>::iterator lit=lights.begin(); lit != lights.end(); ++lit) {
        Light light = *lit;
        n = s->get_surface_normal(*ip, camera);
        ld = (light.pos - *ip).unitlength(); // unit vector pointing towards light source. // BUG: should be ip - light?
        intersection = true; // discriminant negative ⇒ no intersection.
        lambert_shade.r += s->dc.r * light.intensity * std::max(0.0, (*n)*ld);
        lambert_shade.g += s->dc.g * light.intensity * std::max(0.0, (*n)*ld);
        lambert_shade.b += s->dc.b * light.intensity * std::max(0.0, (*n)*ld);
      }
    }
  }

  // Evaluate Shading model.
  // Lambertian shading method.
  if(intersection) {
    lambert_shade.r = std::min((int) (lambert_shade.r * SCALE), SCALE);
    lambert_shade.g = std::min((int) (lambert_shade.g * SCALE), SCALE);
    lambert_shade.b = std::min((int) (lambert_shade.b * SCALE), SCALE);
    // std::cout << lambert_shade.r << " " << lambert_shade.g << " " << lambert_shade.b << std::endl;
  }

  delete ip, n;

  return lambert_shade;
}
