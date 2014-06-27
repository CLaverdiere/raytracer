#include "scene.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

Scene::Scene(int pixels_width, int pixels_height, std::vector<double> img_dims,
    Camera* camera, std::vector<Light> lights, Color bg_col,
    std::vector<Surface*> scene_objects, Raytracer* raytracer) :
  pixels_width(pixels_width),
  pixels_height(pixels_height),
  img_dims(img_dims),
  camera(camera),
  lights(lights),
  bg_col(bg_col),
  scene_objects(scene_objects),
  raytracer(raytracer)
{
  pixels = new unsigned char [pixels_height*pixels_width*3];
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
  fprintf(f, "P6\n%d %d\n%d\n", pixels_width, pixels_height, 255);
  fwrite(pixels, 1, pixels_height*pixels_width*3, f);
  fclose(f);
};

Scene* Scene::import_scene(std::string filename) {
  // TODO: Read in nff file.
};

Scene* Scene::gen_sample_scene(int width, int height) {
  Scene* scene;
  std::vector<Surface*> scene_objects;

  // Sphere centers.
  vec c1(0, 0, 4);

  // Sphere creation.
  Color col1 = {.1, .3, .8};
  Sphere* s1 = new Sphere(col1, c1, 3);

  // Triangle creation.
  // vec v1(0, -150, -focal_length);
  // vec v2(-100, 100, -focal_length);
  // vec v3(100, 100, -focal_length);
  // Triangle* t1 = new Triangle(v1, v2, v3);

  // Add spheres to scene
  scene_objects.push_back(s1);

  // Add triangles to scene
  // scene_objects.push_back(t1);

  Light l1(.9, vec(-width, -height, -200));
  std::vector<Light> lights;
  lights.push_back(l1);

  vec from(0, 0, 0);
  vec at(0, 0, 50);
  Camera* camera = new Camera(from, at);
  Raytracer* raytracer = new Raytracer();

  std::vector<double> img_dims;
  img_dims.push_back(-500);
  img_dims.push_back(-500);
  img_dims.push_back(500);
  img_dims.push_back(500);

  Color bg_col = {0, 0, 0};

  scene = new Scene(500, 500, img_dims, camera, lights, bg_col, scene_objects, raytracer);

  return scene;
};

void Scene::trace_scene() {
  for(int i=0; i<pixels_height; i++) {
    for(int j=0; j<pixels_width; j++) {
      double l = img_dims.at(0) * 2,
             r = img_dims.at(1) * 2,
             b = img_dims.at(2) * 2,
             t = img_dims.at(3) * 2;
      double u = l + ((r - l) * (j + 0.5) / pixels_height);
      double v = b + ((t - b) * (i + 0.5) / pixels_width);

      // std::cout << l << std::endl <<  r << std::endl << b << std::endl << t << std::endl << std::endl; 

      vec e_to_ip(camera->center.x() - u, camera->center.y() - v, (camera->center - camera->pos).z()); // BUG: centers?
      vec d = e_to_ip.unitlength();

      Color color = raytracer->compute_pixel_value(d, camera, lights, bg_col, scene_objects);
      pixels[(i*pixels_height+j)*3] = (unsigned int) color.r;
      pixels[(i*pixels_height+j)*3+1] = (unsigned int) color.g;
      pixels[(i*pixels_height+j)*3+2] = (unsigned int) color.b;
    }
  }
};
