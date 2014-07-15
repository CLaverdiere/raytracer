#include <iostream>
#include "scene.h"
#include <stdio.h>
#include <stdlib.h>

Scene::Scene(std::map<std::string, double> scene_attrs, std::vector<Light> lights, std::vector<Surface*> scene_objects, Projection projection_type, Shading shading_method) :
  lights(lights),
  projection_type(projection_type),
  scene_attrs(scene_attrs),
  scene_objects(scene_objects),
  shading_method(shading_method)
{
  vec from(scene_attrs["from_x"], scene_attrs["from_y"], scene_attrs["from_z"]);
  vec at(scene_attrs["atx"], scene_attrs["aty"], scene_attrs["atz"]);
  vec up(scene_attrs["upx"], scene_attrs["upy"], scene_attrs["upz"]);

  camera = new Camera(from, at);
  pixels = new unsigned char [(int) scene_attrs.at("resx") * (int) scene_attrs.at("resy") * 3];
  raytracer = new Raytracer();
};

Scene::~Scene() {
  delete[] pixels;
  delete raytracer;
  delete camera;
  for(std::vector<Surface*>::iterator it = scene_objects.begin(); it != scene_objects.end(); ++it) {
    delete *it;
  }
};

void Scene::export_scene(const char* filename) {
  FILE *f = fopen(filename, "wb");
  fprintf(f, "P6\n%d %d\n%d\n", (int) scene_attrs["resx"], (int) scene_attrs["resy"], 255);
  fwrite(pixels, 1, scene_attrs["resy"]*scene_attrs["resx"]*3, f);
  fclose(f);
};

void Scene::trace_scene() {
  for(int i=0; i<scene_attrs["resy"]; i++) {
    for(int j=0; j<scene_attrs["resx"]; j++) {
      double l = -1, r = 1, b = -1, t = 1;
      double u = l + ((r - l) * (j + 0.5) / scene_attrs["resy"]);
      double v = b + ((t - b) * (i + 0.5) / scene_attrs["resx"]);

      Camera camera_shifted = *camera;
      Color color;
      vec d;

      if(projection_type == Perspective) {
        vec e_to_p(u - camera->center.x(), 
                   v - camera->center.y(), 
                   (camera->center - camera->pos).z());
        d = e_to_p.unitlength();
        color = raytracer->compute_pixel_value(d, scene_attrs, camera, lights,
            scene_objects, projection_type, shading_method);
      } else { // parallel projection by default.
        d = (camera->center - camera->pos).unitlength();
        camera_shifted.pos.x(camera_shifted.pos.x() + u);
        camera_shifted.pos.y(camera_shifted.pos.y() + v);
        color = raytracer->compute_pixel_value(d, scene_attrs, &camera_shifted,
            lights, scene_objects, projection_type, shading_method);
      }

      pixels[(i*(int)scene_attrs["resy"]+j)*3] = (unsigned int) color.r;
      pixels[(i*(int)scene_attrs["resy"]+j)*3+1] = (unsigned int) color.g;
      pixels[(i*(int)scene_attrs["resy"]+j)*3+2] = (unsigned int) color.b;
    }
  }
};
