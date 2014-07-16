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
    Color compute_pixel_value(vec ray, std::map<std::string, double> scene_attrs, 
        Camera* camera, std::vector<Light> lights, std::vector<Surface*> scene_objects, 
        Projection projection_type, Shading shading_method);
};
