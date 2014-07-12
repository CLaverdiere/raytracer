#include "parser.h"

int main(int argc, const char *argv[])
{
  const char* in_file = "nff/balls2.nff";
  const char* out_file = "pics/sphere.ppm";

  // Scene* out_scene = Scene::gen_sample_scene(500, 500);
  // out_scene->trace_scene();
  // out_scene->export_scene(out_file);
  // delete out_scene;

  // Read scene from infile.
  Scene* in_scene = parse_nff_spheres(in_file);

  // Add lights to scene.
  Light l1(.9, vec(in_scene->pixels_width, in_scene->pixels_height, 0));
  std::vector<Light> lights;
  in_scene->lights.push_back(l1);

  // Trace scene.
  in_scene->trace_scene();

  // Export scene to ppm file.
  in_scene->export_scene(out_file);

  delete in_scene;

  return 0;
}
