#include "camera.h"
#include "vec.h"

// Normalize basis vectors in constructor.
Camera::Camera(vec pos, vec at, vec up) { 
  this->pos = pos;
  this->at = at;
  this->up = up.unit();
  this->b_w = (pos - at).unit();
  this->b_u = (up ^ b_w).unit();
  this->b_v = (b_w ^ b_u).unit();
};
