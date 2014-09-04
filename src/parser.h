#include <fstream>
#include <iostream>
#include "scene.h"
#include "stdlib.h"

// Parsing assumes file is in correct format, for the sake of compactness.
void parse_nff_file(const char* filename, std::map<std::string, double>
    &scene_attrs, std::vector<Surface*> &scene_objects, std::vector<Light> &lights);
