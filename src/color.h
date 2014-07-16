#include "vec.h"
#include <vector>

// RGB values between 0 and 1.
typedef vec Color;

// Forward declaration of Surface.
class Surface;

// Randomly offset color's saturation.
Color offset_saturation_single(Color c);

// Randomly offset multiple colors' saturation.
void offset_saturation_multi(std::vector<Surface*> scene_objects);

// Randomly offset color's hue.
Color offset_hue_single(Color c);

// Randomly offset multiple colors' hues.
void offset_hue_multi(std::vector<Surface*> scene_objects);
