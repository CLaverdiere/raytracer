#include "vec.h"

class Camera {
  public:
    // The camera's position is the camera's 3d coordinates.
    // The 'at' vector is the direction it's pointing in.
    // The 'up' vector specifies the vector towards the top of the camera.
    // The 'right' vector is calculated directly from 'at' and 'up'.
    vec pos, at, up, right;

    Camera(vec pos, vec at, vec up) : pos(pos), at(at), up(up) { right = at ^ up; };
};
