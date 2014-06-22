#include "color.h"

std::ostream& operator<<(std::ostream& os, const Color& c) {
  os << c.r << " " << c.g << " " << c.b;
  return os;
};
