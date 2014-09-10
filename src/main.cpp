#include <algorithm>
#include <string>
#include "parser.h"
#include "string.h"

// TODO: Bug with non-square image dimensions. Produces garbage.
// TODO: Implement ambient shading.
// TODO: Implement configuration file for scene attributes.
// TODO: Get rid of this "if quiet" nonsense.

int main(int argc, const char *argv[])
{
  // Global scene settings. Edit these to change scene settings.
  bool bg_blend_effect = false;
  bool random_hue = false;
  bool random_saturation = false;
  bool reflections_on = false;
  bool shadows_on = false;
  double light_intensity = .71;
  Projection projection_type = Perspective;
  Shading shading_method = Blinn_Phong;

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
  std::string in_file;
  if(argc > 1) {
    in_file = *(argv+(argc-1));
    if(in_file.find("nff") != std::string::npos) {
      if(!quiet) {
        std::cout << "Reading " << in_file << std::endl << std::endl;
      }
    } else {
      in_file = "";
      if(!quiet) {
        std::cout << "WARNING: No nff input file found. Using stdin as default." << std::endl;
      }
    }
  }

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

  // Create output filename.
  std::string out_file = in_file;

  // Format output filename.
  if(out_file != "") {
    // output filename: 'nff/name.nff' -> 'pics/name.nff'
    int index = out_file.find("nff");
    out_file.replace(index, 3, "pics");

    // output filename: 'pics/name.nff' -> 'pics/name.pam'
    index = out_file.find("nff");
    out_file.replace(index, 3, "pam");
  } else {
    out_file = "pics/trace.pam";
    std::cout << "WARNING: Using default output filename: trace.pam." << std::endl;
  }

  // Read scene attributes, objects from infile.
  std::map<std::string, double> scene_attrs;
  std::vector<Surface*> scene_objects;
  std::vector<Light> lights;

  scene_attrs["light_intensity"] = light_intensity;
  parse_nff_file(in_file.c_str(), scene_attrs, scene_objects, lights);

  // Object saturation modification.
  if(scene_flags["random_saturation"]) {
    offset_saturation_multi(scene_objects);
  }

  // Object hue modification.
  if(scene_flags["random_hue"]) {
    offset_hue_multi(scene_objects);
  }

  // Extra program output.
  if(!quiet) {
    std::cout << "Program Settings:" << std::endl;
    std::cout << "Shading Method: " << ShadingNames[shading_method] << std::endl;
    std::cout << "Projection Type: " << ProjectionNames[projection_type] << std::endl;
    std::cout << "Reflections: " << std::boolalpha << reflections_on << std::endl;
    std::cout << "Shadows: " << std::boolalpha << shadows_on << std::endl;
    std::cout << std::endl;
  }

  // Helpful warnings.
  if(!quiet) {
    if (lights.size() == 0) {
      std::cout << "WARNING: No lights specified in scene." << std::endl;
    }
    if (scene_objects.size() == 0) {
      std::cout << "WARNING: No objects specified in scene." << std::endl;
    }
  }

  // Create scene
  Scene* in_scene = new Scene(scene_attrs, scene_flags, lights, scene_objects, projection_type, shading_method);

  // Trace scene.
  if(!quiet) { std::cout << "Tracing scene" << std::endl; }
  in_scene->trace_scene();

  // Export scene to ppm file.
  if(!quiet) { std::cout << "Exporting image to " << out_file << std::endl; }
  in_scene->export_scene(out_file.c_str(), "pam");

  delete in_scene;

  return 0;
}
