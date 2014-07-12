#include "light.h"
#include "shading.h"
#include "surfaces.h"
#include <vector>
#include "vec.h"

class Raytracer {
  public:
    Color compute_pixel_value(vec ray, Camera* camera, std::vector<Light>
        lights, Color bg_col, double ks, double shine, Shading shading_method, std::vector<Surface*> surfaces);
};
