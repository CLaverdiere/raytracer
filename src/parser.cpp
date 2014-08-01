#include "parser.h"

// TODO implement most view attributes.

// Parse our file for scene attributes.
std::map<std::string, double> parse_nff_attrs(const char* filename, int &file_pos) {
  std::map<std::string, double> scene_attrs;
  std::ifstream fi;

  fi.open(filename);

  // Identifier storage.
  std::string in;

  // Parse background colors.
  fi >> in; // b
  fi >> scene_attrs["bg_r"];
  fi >> scene_attrs["bg_g"];
  fi >> scene_attrs["bg_b"];

  // Parse View attributes.
  fi >> in; // v
  fi >> in; // from
  fi >> scene_attrs["from_x"];
  fi >> scene_attrs["from_y"];
  fi >> scene_attrs["from_z"];

  fi >> in; // at
  fi >> scene_attrs["atx"];
  fi >> scene_attrs["aty"];
  fi >> scene_attrs["atz"];

  fi >> in; // up
  fi >> scene_attrs["upx"];
  fi >> scene_attrs["upy"];
  fi >> scene_attrs["upz"];

  fi >> in; // angle
  fi >> scene_attrs["angle"];

  fi >> in; // hither
  fi >> scene_attrs["hither"];

  fi >> in; // resolution
  fi >> scene_attrs["resx"];
  fi >> scene_attrs["resy"];

  // Parse Fill attributes.
  fi >> in;    // f
  fi >> scene_attrs["fill_r"]; // red
  fi >> scene_attrs["fill_g"]; // green
  fi >> scene_attrs["fill_b"]; // blue
  fi >> scene_attrs["kd"];     // diffuse component
  fi >> scene_attrs["ks"];     // specular
  fi >> scene_attrs["shine"];  // phong cosine power
  fi >> scene_attrs["t"];      // transmittance
  fi >> scene_attrs["ior"];    // index of refraction

  // Store position in file before closing.
  file_pos = fi.tellg();

  fi.close();

  return scene_attrs;
};

// Parse our file for all objects.
// Returns a vector containing all scene objects.
// Currently only works for spheres.
// TODO: account for other object types.
std::vector<Surface*> parse_nff_objects(const char* filename, std::map<std::string, double> scene_attrs, int &file_pos) {
  std::ifstream fi;
  fi.open(filename);

  // Identifier storage.
  std::string in;

  // Single object color.
  Color col(scene_attrs.at("fill_r"), 
            scene_attrs.at("fill_g"), 
            scene_attrs.at("fill_b"));

  // Jump to the point in the file where spheres are declared.
  fi.seekg(file_pos);

  // Parse Objects
  std::vector<Surface*> scene_objects;

  while(!fi.eof()) {

    fi >> in; // Object identifier

    if(in == "s") { // sphere
      double cx, cy, cz, rad;
      fi >> cx;  // centerx
      fi >> cy;  // centery
      fi >> cz;  // centerz
      fi >> rad; // radius

      scene_objects.push_back(new Sphere(col, vec(cx, cy, cz), rad));
    } else if(in == "p") { // plane
      double nx, ny, nz, qx, qy, qz;
      fi >> nx;  // centerx
      fi >> ny;  // centery
      fi >> nz;  // centerz
      fi >> qx;  // centerx
      fi >> qy;  // centery
      fi >> qz;  // centerz

      scene_objects.push_back(new Plane(col, vec(nx, ny, nz), vec(qx, qy, qz)));
    }

    if(fi.eof()) break;
  }

  fi.close();
  return scene_objects;
};
