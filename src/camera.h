#include "vec.h"

class Camera {
  public:
    // Supplied vectors:
    //   pos: camera's position is the camera's 3d coordinates.
    //   at: the point we're looking at.
    //   up: specifies the vector towards the top of the camera. First basis vector.

    // Basis vectors:
    //   b_w: the (negative) direction vector towards the point we're looking at.
    //   b_u: the vector orthogonal to up and b_w.
    //   b_v: the vector orthogonal to b_w and b_u.
    vec pos, at, up;
    vec b_w, b_u, b_v;

    Camera(vec pos, vec at, vec up);
};
