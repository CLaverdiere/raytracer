#include "projection.h"
#include "raytracer.h"
#include <string>
#include <vector>

class Scene {
  public:
    unsigned char* pixels;
    int pixels_width, pixels_height;
    std::vector<double> img_dims;
    Projection projection_type;
    std::vector<Surface*> scene_objects;
    Camera* camera;
    std::vector<Light> lights;
    Color bg_col;
    Raytracer* raytracer;

    Scene(int pixels_width, int pixels_height, std::vector<double> img_dims,
        Projection projection_type, Camera* camera, std::vector<Light> lights,
        Color bg_col, std::vector<Surface*> scene_objects, Raytracer*
        raytracer);
    ~Scene();
    void export_scene(const char* filename);
    Scene* import_scene(std::string filename);
    static Scene* gen_sample_scene(int width, int height);
    void trace_scene();
};
