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
#include "math.h"
#include "raytracer.h"

#define SCALE 255 // RGB scale ends at 255.
#define SHADOW_ADJUSTMENT 0.001 // Constant to avoid incorrect shadow intersections.

Color Raytracer::compute_pixel_value(vec ray, std::map<std::string, double> scene_attrs,
    Camera* camera, std::vector<Light> lights, std::vector<Surface*> scene_objects,
    Projection projection_type, Shading shading_method) {
  Color shade(scene_attrs.at("bg_r")*SCALE,
              scene_attrs.at("bg_g")*SCALE,
              scene_attrs.at("bg_b")*SCALE);
  bool intersection = false;
  double closest_hit_distance = 0;

  for(std::vector<Surface*>::iterator sit=scene_objects.begin(); sit != scene_objects.end(); ++sit) {
    vec ip, n, ld, v, placeholder;
    Surface* s = *sit;
    bool hit_surface = s->get_intersection(ip, camera->pos, ray, 0);

    if(hit_surface) {
      if(closest_hit_distance == 0) { closest_hit_distance = ip.length(); };

      if(ip.length() <= closest_hit_distance) {
        closest_hit_distance = ip.length();
        shade.x(0); shade.y(0); shade.z(0);
        for(std::vector<Light>::iterator lit=lights.begin(); lit != lights.end(); ++lit) {
          bool in_shadow = false;
          Light light = *lit;
          s->get_surface_normal(n, ip, camera); // unit vector for surface normal.
          ld = (light.pos - ip).unitlength(); // unit vector pointing towards light source. // BUG: should be ip - light?
          v = -ray; // unit vector pointing towards camera.
          intersection = true; // discriminant negative ⇒ no intersection.

          // Shadow computations.
          for(std::vector<Surface*>::iterator sit_sc=scene_objects.begin(); sit_sc != scene_objects.end(); ++sit_sc) {
            Surface* s_sc = *sit_sc; // surface shadow-candidate.
            if(s_sc->get_intersection(placeholder, ip + camera->pos, ld, 0)) {
              in_shadow = true;
              break;
            }
          }

          // Shading computations.
          if(!in_shadow) {
            if(shading_method == Lambertian) {
              shade += s->dc * light.intensity * std::max(0.0, n*ld);
            } else if(shading_method == Blinn_Phong) {
              vec h = (v + ld);
              shade += s->dc * light.intensity * (scene_attrs.at("kd") * (std::max(0.0, n*ld))
                + scene_attrs.at("ks") * pow(std::max(0.0, n*h), scene_attrs.at("shine")));
            } else { // No shading.
              shade = s->dc;
            }
          }
        }
      }
    }
  }

  // Evaluate Shading model.
  // Lambertian shading method.
  if(intersection) {
    shade.x(std::min((int) (shade.x() * SCALE), SCALE));
    shade.y(std::min((int) (shade.y() * SCALE), SCALE));
    shade.z(std::min((int) (shade.z() * SCALE), SCALE));
  }

  return shade;
}
