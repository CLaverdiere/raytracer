#include "raytracer.h"
#include <string>
#include "surfaces.h"
#include <vector>

class Scene {
  public:
    int pixels_width, pixels_height;
    unsigned char pixels[pixels_height][pixels_width][3];
    std::vector<Surface*> scene_objects;
    Raytracer raytracer;
    vec camera;
    vec light;  // TODO Should really be a container of vectors.

    void export_scene(std::string filename);
    Scene* import_scene(std::string filename);
    static std::vector<Surface*> gen_sample_scene_objects(int focal_length, int width, int height);
};
