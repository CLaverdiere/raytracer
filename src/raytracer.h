#include "surfaces.h"
#include <vector>
#include "vec.h"

class Raytracer {
  public:
    int compute_pixel_value(vec ray, vec light, std::vector<Surface*> surfaces);
};
