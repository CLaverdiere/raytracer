#include <ostream>

// RGB values between 0 and 1.
// TODO extend from vector.
typedef struct Color {
  double r, g, b;
  // std::ostream& operator<<(std::ostream& os, const Color& c);
} Color;
