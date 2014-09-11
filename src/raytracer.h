#include "light.h"
#include <map>
#include "projection.h"
#include "shading.h"
#include "surfaces.h"
#include <string>
#include "vec.h"
#include <vector>

class Raytracer {
  public:
    Color compute_pixel_value(vec ray, vec eye, std::map<std::string, double>
        scene_attrs, std::map<std::string, bool> scene_flags,
        std::vector<Light> lights, std::vector<Surface*> scene_objects,
        Projection projection_type, Shading shading_method, int
        recursion_depth);
};
