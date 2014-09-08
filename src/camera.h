#include "vec.h"

class Camera {
  public:
    // The camera's position is the camera's 3d coordinates.
    // The 'at' vector is the point we're looking at.
    // The 'at_d' vector is the direction vector towards the point we're looking at.
    // The 'at_u' vector is the unit vector for at_d, to form a basis vector.
    // The 'up' vector specifies the vector towards the top of the camera.
    // The 'right' vector is calculated directly from 'at' and 'up'.
    vec pos, at, at_d, at_u, up, right;

    Camera(vec pos, vec at, vec up);
};
