// General algorithm for raytracing, implemented from
//   Fundamentals of Computer Graphics, 3rd ed.
//
// for each pixel:
//  compute viewing ray.
//  if ray hits an object with t ∈ [0,∞]:
//    evalutate shading model and set pixel to that color.
//  else:
//    set pixel color to background color.
//
// Note: variable names are kept short to closer match the book's notation.

#include <algorithm>
#include <iostream>
#include "math.h"
#include "raytracer.h"

#define SCALE 255 // 8-bit RGB scale.
#define EPSILON_ADJUSTMENT 0.001 // Constant to avoid incorrect surface-ray intersections.
#define MAX_RECURSION_DEPTH 5

// TODO Passing way too many things here. Refactor this.
// Possibly merge the raytracer object entirely into a scene
//   class method.
Color Raytracer::compute_pixel_value(vec ray, vec eye, std::map<std::string,
    double> scene_attrs, std::map<std::string, bool> scene_flags,
    std::vector<Light> lights, std::vector<Surface*> scene_objects, Projection
    projection_type, Shading shading_method, int recursion_depth) {
  Color shade(scene_attrs["bg_r"],
              scene_attrs["bg_g"],
              scene_attrs["bg_b"]);
  bool intersection = false;
  double closest_hit_distance = 0;
  vec ip, closest_ip, n, ld, v, placeholder;
  Surface *s;
  Surface *closest_surface = scene_objects.at(0);

  // Closest object intersection calculations.
  for(std::vector<Surface*>::iterator sit=scene_objects.begin(); sit != scene_objects.end(); ++sit) {
    // (stores in ip) intersection point with surface.
    bool hit_surface = (*sit)->get_intersection(ip, eye, ray, 0);

    if(hit_surface) {
      intersection = true;
      if(closest_hit_distance == 0) { 
        closest_hit_distance = ip.mag(); 
      };

      if(ip.mag() <= closest_hit_distance) {
        closest_hit_distance = ip.mag();
        closest_surface = *sit;
        closest_ip = ip;
      }
    }
  }

  if(intersection) {
    ip = closest_ip;
    s = closest_surface;
    s->get_surface_normal(n, ip, eye); // (stores in n) unit vector for surface normal.

    if(!scene_flags["bg_blend_effect"]) {
      shade.x = 0; shade.y = 0; shade.z = 0;
    }

    // Lighting computations.
    for(std::vector<Light>::iterator lit=lights.begin(); lit != lights.end(); ++lit) {
      bool in_shadow = false;
      Light light = *lit;
      ld = (light.pos - ip).unit(); // unit vector pointing towards light source. // BUG: should be ip - light?
      v = -ray; // unit vector pointing towards camera.

      // Shadow computations.
      if(scene_flags["shadows_on"]) {
        for(std::vector<Surface*>::iterator sit_sc=scene_objects.begin(); sit_sc != scene_objects.end(); ++sit_sc) {
          Surface* s_sc = *sit_sc; // surface shadow-candidate.
          bool hit_surface = s_sc->get_intersection(placeholder, ip + eye, ld, EPSILON_ADJUSTMENT);
          if(hit_surface) {
            in_shadow = true;
            break;
          }
        }
      }

      // Shading computations.
      if(!in_shadow) {
        if(shading_method == Lambertian) {
          shade += s->attr.fill * (s->attr.kd * light.intensity * std::max(0.0, n*ld));
        } else if(shading_method == Blinn_Phong) {
          vec h = (v + ld).unit();
          double diffuse_comp = s->attr.kd * light.intensity * std::max(0.0, n*ld);
          double specular_comp = s->attr.ks * light.intensity * pow(std::max(0.0, n*h), s->attr.shine);
          shade += s->attr.fill * (diffuse_comp + specular_comp);
        } else { // No shading.
          shade = s->attr.fill;
        }
      }

      // Specular Reflection Recursion.
      if(recursion_depth < MAX_RECURSION_DEPTH && scene_flags["reflections_on"]) {
        vec mirror_ray = ray - 2*(ray*n)*n; // mirrored ray for reflection.
        vec eye_shifted = eye + ip + (mirror_ray * EPSILON_ADJUSTMENT);
        shade += s->attr.ks * this->compute_pixel_value(mirror_ray, eye_shifted,
            scene_attrs, scene_flags, lights, scene_objects,
            projection_type, shading_method, recursion_depth+1);
      } 
    }
  }

  // Scale color to RGB limit.
  // Only scale when not in reflection calculation.
  if(recursion_depth == 0) {
    shade.x = std::min((int) (shade.x * SCALE), SCALE);
    shade.y = std::min((int) (shade.y * SCALE), SCALE);
    shade.z = std::min((int) (shade.z * SCALE), SCALE);
  }

  return shade;
}
