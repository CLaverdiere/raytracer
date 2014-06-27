#include "light.h"
#include "surfaces.h"
#include <vector>
#include "vec.h"

class Raytracer {
  public:
    Color compute_pixel_value(vec ray, Camera* camera, std::vector<Light> lights, Color bg_col, std::vector<Surface*> surfaces);
};
