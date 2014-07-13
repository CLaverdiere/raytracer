#include "parser.h"

int main(int argc, const char *argv[])
{
  const char* in_file = "nff/balls_single.nff";
  const char* out_file = "pics/sphere.ppm";

  // Scene* out_scene = Scene::gen_sample_scene(500, 500);
  // out_scene->trace_scene();
  // out_scene->export_scene(out_file);
  // delete out_scene;

  // Read scene attributes from infile.
  std::map<std::string, double> scene_attrs = parse_nff_attrs(in_file);

  // TODO Add extra environment variables not specified by nff spec.
  Projection projection_type = Parallel;
  Shading shading_method = Blinn_Phong;

  // Read scene objects from infile.
  std::vector<Surface*> scene_objects = parse_nff_objects(in_file, scene_attrs);

  // Add lights to scene.
  Light l1(.9, vec(scene_attrs["resx"], scene_attrs["resy"], 0));
  std::vector<Light> lights;
  lights.push_back(l1);

  // Create scene
  Scene* in_scene = new Scene(scene_attrs, lights, scene_objects, projection_type, shading_method);

  // Trace scene.
  in_scene->trace_scene();

  // Export scene to ppm file.
  in_scene->export_scene(out_file);

  delete in_scene;

  return 0;
}
