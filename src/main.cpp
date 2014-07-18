#include "parser.h"

// TODO: Bug with non-square image dimensions. Produces garbage.
// TODO: Fix memory leaks.

int main(int argc, const char *argv[])
{
  const char* in_file = "nff/balls2.nff";
  const char* out_file = "pics/sphere.ppm";

  // Read scene attributes from infile.
  std::map<std::string, double> scene_attrs = parse_nff_attrs(in_file);

  // TODO Add extra environment variables not specified by nff spec.
  //  ie: shadows_enabled, reflection_enabled, etc.
  Projection projection_type = Parallel;
  Shading shading_method = Blinn_Phong;

  // Read scene objects from infile.
  std::vector<Surface*> scene_objects = parse_nff_objects(in_file, scene_attrs);

  // Modify objects' color in subtle ways.
  // offset_saturation_multi(scene_objects); 
  // offset_hue_multi(scene_objects);

  // Add lights to scene.
  Light l1(.9, vec(scene_attrs["resx"], scene_attrs["resy"], 500));
  Light l2(.6, vec(0, 0, 500));
  Light l3(.7, -2*vec(-scene_attrs["resx"], -scene_attrs["resy"], 0));
  std::vector<Light> lights;
  lights.push_back(l1);
  lights.push_back(l2);
  // lights.push_back(l3);

  // Create scene
  Scene* in_scene = new Scene(scene_attrs, lights, scene_objects, projection_type, shading_method);

  // Trace scene.
  in_scene->trace_scene();

  // Export scene to ppm file.
  in_scene->export_scene(out_file);

  delete in_scene;

  return 0;
}
