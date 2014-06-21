#include "raytracer.h"
#include <string>
#include <vector>

class Scene {
  public:
    unsigned char* pixels;
    int pixels_width, pixels_height, focal_length;
    std::vector<Surface*> scene_objects;
    Raytracer* raytracer;
    vec camera;
    std::vector<Light> lights;

    Scene(int pixels_width, int pixels_height, int focal_length, vec camera, std::vector<Light> lights, Raytracer* raytracer);
    ~Scene();
    void export_scene(const char* filename);
    Scene* import_scene(std::string filename);
    static Scene* gen_sample_scene(int focal_length, int width, int height);
    void trace_scene();
};
