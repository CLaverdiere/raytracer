#include "camera.h"
#include "vec.h"

// Normalize basis vectors in constructor.
Camera::Camera(vec pos, vec at, vec up) { 
  this->pos = pos;
  this->at = at;
  this->at_d = at - pos;
  this->at_u = this->at_d.unit();
  this->up = up.unit();
  this->right = (this->at_u ^ this->up).unit(); 
};
