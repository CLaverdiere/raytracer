#include <fstream>
#include <iostream>
#include "scene.h"
#include "stdlib.h"

// Parsing assumes file is in correct format, for the sake of compactness.
std::map<std::string, double> parse_nff_attrs(const char* filename);
std::vector<Surface*> parse_nff_objects(const char* filename, std::map<std::string, double> scene_attrs);
