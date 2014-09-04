#include <algorithm>
#include "parser.h"
#include "string.h"

// TODO: Bug with non-square image dimensions. Produces garbage.
// TODO: Implement ambient shading.
// TODO: Implement configuration file for scene attributes.
// TODO: Get rid of this "if quiet" nonsense.

int main(int argc, const char *argv[])
{
  // Parse command line flags.
  // -l : loading bar. Display a loading bar while raytracing happens.
  // -q : quiet. No stdout output.
  // -v : verbose. Prints option information at the start of the program.
  bool loading_bar = std::find(argv, argv+argc, (std::string) "-l") != argv+argc ? true : false;
  bool quiet       = std::find(argv, argv+argc, (std::string) "-q") != argv+argc ? true : false;
  bool verbose     = std::find(argv, argv+argc, (std::string) "-v") != argv+argc ? true : false;

  // Greeting.
  if(!quiet) {
    std::cout << std::endl;
    std::cout << "Raytracer program for CMSC 435 at UMBC" << std::endl;
    std::cout << "Chris Laverdiere 2014" << std::endl << std::endl;
  }

  // Parse input filename as final command line argument.
  const char* in_file;
  if(argc > 1) {
    in_file = *(argv+(argc-1));
    if(strstr(in_file, "nff")) {
      if(!quiet) {
        std::cout << "Reading " << in_file << std::endl;
      }
    } else {
      in_file = "nff/trace.nff";
      if(!quiet) {
        std::cout << "WARNING: No nff input file found. Using " << in_file << " as default." << std::endl;
      }
    }
  }

  // Global scene flags.
  bool bg_blend_effect = false;
  bool random_hue = false;
  bool random_saturation = false;
  bool reflections_on = false;
  bool shadows_on = false;

  // Global scene flags map.
  std::map<std::string, bool> scene_flags;
  scene_flags["bg_blend_effect"] = bg_blend_effect;
  scene_flags["loading_bar"] = loading_bar;
  scene_flags["random_hue"] = random_hue;
  scene_flags["random_saturation"] = random_saturation;
  scene_flags["reflections_on"] = reflections_on;
  scene_flags["quiet"] = quiet;
  scene_flags["shadows_on"] = shadows_on;
  scene_flags["verbose"] = verbose;

  // Extra scene settings not specified in NFF spec.
  Projection projection_type = Parallel;
  // Shading shading_method = None;
  Shading shading_method = Blinn_Phong;

  // Default output filename.
  const char* out_file = "pics/trace.pam";

  // Read scene attributes, objects from infile.
  std::map<std::string, double> scene_attrs;
  std::vector<Surface*> scene_objects;
  std::vector<Light> lights;
  parse_nff_file(in_file, scene_attrs, scene_objects, lights);

  // Object saturation modification.
  if(scene_flags["random_saturation"]) {
    offset_saturation_multi(scene_objects);
  }

  // Object hue modification.
  if(scene_flags["random_hue"]) {
    offset_hue_multi(scene_objects);
  }

  // Scene lighting.
  // Light l1(.9, vec(scene_attrs["resx"], scene_attrs["resy"], 200));
  // Light l2(.3, vec(0, 0, 500));
  // Light l3(.7, -2*vec(-scene_attrs["resx"], -scene_attrs["resy"], 0));
  // std::vector<Light> lights;
  // lights.push_back(l1);
  // lights.push_back(l2);
  // lights.push_back(l3);

  // Extra program output.
  if(!quiet) {
    std::cout << "Program Settings:" << std::endl;
    std::cout << "Shading Method: " << ShadingNames[shading_method] << std::endl;
    std::cout << "Projection Type: " << ProjectionNames[projection_type] << std::endl;
    std::cout << "Reflections: " << std::boolalpha << reflections_on << std::endl;
    std::cout << "Shadows: " << std::boolalpha << shadows_on << std::endl;
    std::cout << std::endl;
  }

  // Create scene
  if(!quiet) { std::cout << "Parsing scene from " << in_file << std::endl; }
  Scene* in_scene = new Scene(scene_attrs, scene_flags, lights, scene_objects, projection_type, shading_method);

  // Trace scene.
  if(!quiet) { std::cout << "Tracing scene" << std::endl; }
  in_scene->trace_scene();

  // Export scene to ppm file.
  if(!quiet) { std::cout << "Exporting image to " << out_file << std::endl; }
  in_scene->export_scene(out_file, "pam");

  delete in_scene;

  return 0;
}
