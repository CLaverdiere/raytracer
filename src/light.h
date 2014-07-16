#include "vec.h"

class Light {
  public:
    double intensity;
    vec pos;

    Light(double intensity, vec pos) : intensity(intensity), pos(pos) { };
};
