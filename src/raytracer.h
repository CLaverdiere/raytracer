#include "surfaces.h"
#include <vector>
#include "vec.h"

typedef struct Color {
  unsigned char r, g, b;
} Color;

class Raytracer {
  public:
    Color compute_pixel_value(vec ray, vec camera, vec light, std::vector<Surface*> surfaces);
};
