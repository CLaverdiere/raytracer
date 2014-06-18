#include <iostream>
#include "scene.h"

using namespace std;

int main(int argc, const char *argv[])
{
  Scene* scene = Scene::gen_sample_scene(250, 500, 500);
  scene->trace_scene();
  
  return 0;
}
