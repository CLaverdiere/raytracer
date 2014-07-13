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

#define SCALE 255

Color Raytracer::compute_pixel_value(vec ray, std::map<std::string, double> scene_attrs, 
    Camera* camera, std::vector<Light> lights, std::vector<Surface*> scene_objects, 
    Projection projection_type, Shading shading_method) {
  vec *ip = NULL, *n = NULL, ld, v;
  Color shade = {scene_attrs.at("bg_r")*SCALE, 
                 scene_attrs.at("bg_g")*SCALE, 
                 scene_attrs.at("bg_b")*SCALE};
  bool intersection = false;
  double closest_hit_distance = 0;

  // Perspective view calculation.
  for(std::vector<Surface*>::iterator sit=scene_objects.begin(); sit != scene_objects.end(); ++sit) {
    Surface* s = *sit;
    ip = s->get_intersection(camera->pos, ray);

    if(ip != NULL) {
      if(closest_hit_distance == 0) { closest_hit_distance = ip->length(); };

      if(ip->length() <= closest_hit_distance) {
        closest_hit_distance = ip->length();
        shade.r = shade.g = shade.b = 0;
        for(std::vector<Light>::iterator lit=lights.begin(); lit != lights.end(); ++lit) {
          Light light = *lit;
          n = s->get_surface_normal(*ip, camera);
          ld = (light.pos - *ip).unitlength(); // unit vector pointing towards light source. // BUG: should be ip - light?
          v = -ray; // unit vector pointing towards camera.
          intersection = true; // discriminant negative ⇒ no intersection.
          if(shading_method == Lambertian) {
            shade.r += s->dc.r * light.intensity * std::max(0.0, (*n)*ld);
            shade.g += s->dc.g * light.intensity * std::max(0.0, (*n)*ld);
            shade.b += s->dc.b * light.intensity * std::max(0.0, (*n)*ld);
          } else { // default is Blinn-Phong
            vec h = (v + ld);
            // TODO de-uglify this.
            shade.r += s->dc.r * light.intensity * (scene_attrs.at("kd") * (std::max(0.0, (*n)*ld)) 
              + scene_attrs.at("ks") * pow(std::max(0.0, (*n)*h), scene_attrs.at("shine")));
            shade.g += s->dc.g * light.intensity * (scene_attrs.at("kd") * (std::max(0.0, (*n)*ld)) 
              + scene_attrs.at("ks") * pow(std::max(0.0, (*n)*h), scene_attrs.at("shine")));
            shade.b += s->dc.b * light.intensity * (scene_attrs.at("kd") * (std::max(0.0, (*n)*ld)) 
              + scene_attrs.at("ks") * pow(std::max(0.0, (*n)*h), scene_attrs.at("shine")));
          }
        }
      }
    }
  }

  // Evaluate Shading model.
  // Lambertian shading method.
  if(intersection) {
    shade.r = std::min((int) (shade.r * SCALE), SCALE);
    shade.g = std::min((int) (shade.g * SCALE), SCALE);
    shade.b = std::min((int) (shade.b * SCALE), SCALE);
    // std::cout << shade.r << " " << shade.g << " " << shade.b << std::endl;
  }

  delete ip, n;

  return shade;
}
