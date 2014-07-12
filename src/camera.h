#include "vec.h"

class Camera {
  public:
    // The camera's position is the camera's coordinates in space.
    // A camera's center is the unit vector of the direction it's pointing in.
    vec pos, center;

    Camera(vec pos, vec center) : pos(pos), center(center) { };
};
