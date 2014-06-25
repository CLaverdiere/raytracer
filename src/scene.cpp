#include "scene.h"
#include <stdio.h>
#include <stdlib.h>

Scene::Scene(int pixels_width, int pixels_height, int focal_length, Camera* camera, std::vector<Light> lights, std::vector<Surface*> scene_objects, Raytracer* raytracer) :
  pixels_width(pixels_width),
  pixels_height(pixels_height),
  focal_length(focal_length),
  camera(camera),
  lights(lights),
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

Scene* Scene::gen_sample_scene(int focal_length, int width, int height) {
  Scene* scene;
  std::vector<Surface*> scene_objects;

  // Sphere centers.
  vec c1(0   , 0   , -focal_length*4   );

  // Sphere creation.
  Color col1 = {.1, .3, .8};
  Sphere* s1 = new Sphere(col1, c1, (width+height) / 2);

  // Triangle creation.
  // vec v1(0, -150, -focal_length);
  // vec v2(-100, 100, -focal_length);
  // vec v3(100, 100, -focal_length);
  // Triangle* t1 = new Triangle(v1, v2, v3);

  // Add spheres to scene
  scene_objects.push_back(s1);

  // Add triangles to scene
  // scene_objects.push_back(t1);


  Light l1(.9, vec(-width, -height, 0));
  std::vector<Light> lights;
  lights.push_back(l1);

  vec from(0, 0, 0);
  vec at(0, 0, -focal_length);
  Camera* camera = new Camera(from, at);
  Raytracer* raytracer = new Raytracer();

  scene = new Scene(500, 500, 250, camera, lights, scene_objects, raytracer);

  return scene;
};

void Scene::trace_scene() {
  for(int i=0; i<pixels_height; i++) {
    for(int j=0; j<pixels_width; j++) {
      double u = j - pixels_height/2;
      double v = i - pixels_width/2;

      vec e_to_ip(u, v, -focal_length);
      vec d = e_to_ip.unitlength();

      Color color = raytracer->compute_pixel_value(d, camera, lights, scene_objects);
      pixels[(i*pixels_height+j)*3] = (unsigned int) color.r;
      pixels[(i*pixels_height+j)*3+1] = (unsigned int) color.g;
      pixels[(i*pixels_height+j)*3+2] = (unsigned int) color.b;
    }
  }
};
