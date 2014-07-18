#include <fstream>
#include <iostream>
#include "scene.h"
#include "stdlib.h"

// The nff file has multiple sections, which multiple methods access. We want
//   to keep the position of the location in the file where we leave off in each
//   method. This is file_pos in the following calls.

// Parsing assumes file is in correct format, for the sake of compactness.
std::map<std::string, double> parse_nff_attrs(const char* filename, int &file_pos);
std::vector<Surface*> parse_nff_objects(const char* filename, std::map<std::string, double> scene_attrs, int &file_pos);
