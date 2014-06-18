#include "scene.h"
#include <stdio.h>

Scene::Scene(int pixels_width, int pixels_height, int focal_length, vec camera, vec light, Raytracer* raytracer) :
  pixels_width(pixels_width),
  pixels_height(pixels_height),
  focal_length(focal_length),
  camera(camera),
  light(light),
  raytracer(raytracer)
{
  // Some real shit right here.
  pixels = new unsigned char** [pixels_height];
  for(int i=0; i<pixels_height; i++) {
    pixels[i] = new unsigned char* [pixels_width];
    for(int j=0; j<3; j++) {
      pixels[i][j] = new unsigned char[3];
    }
  }
};

Scene::~Scene() {
  for(int i=0; i<pixels_height; i++) {
    for(int j=0; j<3; j++) {
      delete pixels[i][j];
    }
    delete pixels[i];
  }
  delete pixels;
};

void Scene::export_scene(char* filename) {
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
  vec c1(0   , 0   , -focal_length*5   );
  vec c2(250 , -100, -focal_length*3.75);
  vec c3(100 , 75  , -focal_length*1.25);
  vec c4(-150, 25  , -focal_length*.9  );
  vec c5(-75 , 125 , -focal_length*.75 );

  // Sphere creation.
  Sphere* s1 = new Sphere(c1, (width+height) / 8);
  Sphere* s2 = new Sphere(c2, (width+height) / 13);
  Sphere* s3 = new Sphere(c3, (width+height) / 21);
  Sphere* s4 = new Sphere(c4, (width+height) / 34);
  Sphere* s5 = new Sphere(c5, (width+height) / 55);

  scene_objects.push_back(s1);
  scene_objects.push_back(s2);
  scene_objects.push_back(s3);
  scene_objects.push_back(s4);
  scene_objects.push_back(s5);

  vec camera(0, 0, 0);
  vec light(height*2, width*2, focal_length);
  Raytracer* raytracer = new Raytracer();

  scene = new Scene(500, 500, 250, camera, light, raytracer);
  scene->scene_objects = scene_objects;

  return scene;
};

void Scene::trace_scene() {
  for(int i=0; i<pixels_height; i++) {
    for(int j=0; j<pixels_width; j++) {
      float u = i - pixels_width/2;
      float v = j - pixels_height/2;

      vec e_to_ip(u, v, -focal_length);
      vec d = e_to_ip.unitlength();

      int color = raytracer->compute_pixel_value(d, light, scene_objects);
      pixels[i][j][0] = color;
      pixels[i][j][1] = color;
      pixels[i][j][2] = color;
    }
  }
};
