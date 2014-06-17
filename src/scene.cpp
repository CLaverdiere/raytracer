#include "scene.h"
#include <stdio.h>

void Scene::export_scene(std::string filename) {
  FILE *f = fopen("filename", "wb");
  fprintf(f, "P6\n%d %d\n%d\n", pixels_width, pixels_height, 255);
  // fwrite(pixels, 1, pixels_height*pixels_width*3, f);
  fclose(f);
};

Scene* Scene::import_scene(std::string filename) {

};

std::vector<Surface*> Scene::gen_sample_scene_objects(int focal_length, int width, int height) {
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

  return scene_objects;
};
