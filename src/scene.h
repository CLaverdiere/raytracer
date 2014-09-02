#include "raytracer.h"

class Scene {
  public:
    // TODO refactor this typedef into definitions for brevity.
    // typedef std::map<std::string, double> scene_map;
    unsigned char* pixels;
    Camera* camera;
    Color bg_col;
    std::map<std::string, double> scene_attrs;
    std::map<std::string, bool> scene_flags;
    std::vector<Surface*> scene_objects;
    std::vector<Light> lights;
    Projection projection_type;
    Raytracer* raytracer;
    Shading shading_method;

    Scene(std::map<std::string, double> scene_attrs, 
        std::map<std::string, bool> scene_flags, 
        std::vector<Light> lights, std::vector<Surface*>
        scene_objects, Projection projection_type, Shading shading_method);
    ~Scene();
    void export_scene(const char* filename, std::string filetype);
    void trace_scene();
};
