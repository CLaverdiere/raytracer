#include "parser.h"

using namespace std;

int main(int argc, const char *argv[])
{
  const char* out_file = "pics/sphere.ppm";
  const char* in_file = "nff/balls1.nff";

  Scene* out_scene = Scene::gen_sample_scene(250, 500, 500);
  out_scene->trace_scene();
  out_scene->export_scene(out_file);
  delete out_scene;

  Scene* in_scene = parse_nff_spheres(in_file);
  return 0;
}
