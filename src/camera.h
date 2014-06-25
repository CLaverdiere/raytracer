#include "vec.h"

class Camera {
  public:
    vec pos, center;

    Camera(vec pos, vec center) : pos(pos), center(center) { };
};
