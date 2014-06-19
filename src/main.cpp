#include <iostream>
#include "scene.h"

using namespace std;

int main(int argc, const char *argv[])
{
  const char* filename = "pics/sphere.ppm";
  Scene* scene = Scene::gen_sample_scene(250, 500, 500);
  scene->trace_scene();
  scene->export_scene(filename);
  delete scene;
  
  return 0;
}
