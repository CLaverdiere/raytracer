#include "parser.h"

void parse_nff_file(const char* filename, std::map<std::string, double>
                    &scene_attrs, std::vector<Surface*> &scene_objects) {
  std::ifstream fi;
  fi.open(filename);

  Color fill_col;

  // Identifier storage.
  std::string in;

  // Parsing loop.
  while(!fi.eof()) {
    fi >> in; // Read in the next character.
    if(fi.eof()) { break; }

    if(in == "b") { // Background color
      std::cout << "Parsing b" << std::endl;
      fi >> scene_attrs["bg_r"];
      fi >> scene_attrs["bg_g"];
      fi >> scene_attrs["bg_b"];

    } else if(in == "c") { // Cone or cylinder primitive.
      // NOT IMPLEMENTED.
      std::cout << "Parsing c" << std::endl;
      fi >> in; fi >> in; fi >> in; fi >> in; // base vector, radius.
      fi >> in; fi >> in; fi >> in; fi >> in; // apex vector, radius.

    } else if(in == "f") { // Object material properties.
      std::cout << "Parsing f" << std::endl;
      fi >> scene_attrs["fill_r"]; // red
      fi >> scene_attrs["fill_g"]; // green
      fi >> scene_attrs["fill_b"]; // blue
      fi >> scene_attrs["kd"];     // diffuse component
      fi >> scene_attrs["ks"];     // specular
      fi >> scene_attrs["shine"];  // phong cosine power
      fi >> scene_attrs["t"];      // transmittance
      fi >> scene_attrs["ior"];    // index of refraction
      fill_col = Color(scene_attrs.at("fill_r"), 
                       scene_attrs.at("fill_g"), 
                       scene_attrs.at("fill_b"));

    } else if(in == "l") { // Positional light location.
      std::cout << "Parsing l" << std::endl;
      // TODO NOT IMPLEMENTED.
      fi >> in; fi >> in; fi >> in; 

    } else if(in == "p") { // Polygon primitive.
      std::cout << "Parsing p" << std::endl;
      // TODO NOT IMPLEMENTED FOR ANY POLYGON, ONLY TRIANGLES.
      double v1x, v1y, v1z,
             v2x, v2y, v2z,
             v3x, v3y, v3z;
      fi >> in; // Number of verts.
      fi >> v1x; fi >> v1y; fi >> v1z;
      fi >> v2x; fi >> v2y; fi >> v2z;
      fi >> v3x; fi >> v3y; fi >> v3z;
      
      scene_objects.push_back(new Triangle(fill_col, 
                                 vec(v1x, v1y, v1z), 
                                 vec(v2x, v2y, v2z), 
                                 vec(v3x, v3y, v3z)));

    } else if(in == "pp") { // Polygonal patch primitive.
      std::cout << "Parsing pp" << std::endl;
      // TODO NOT IMPLEMENTED.

    } else if(in == "s") { // Sphere primitive.
      std::cout << "Parsing s" << std::endl;
      double cx, cy, cz, rad;
      fi >> cx;  // centerx
      fi >> cy;  // centery
      fi >> cz;  // centerz
      fi >> rad; // radius
      scene_objects.push_back(new Sphere(fill_col, vec(cx, cy, cz), rad));

    } else if(in == "v") { // Viewing vectors and angles.
      std::cout << "Parsing v" << std::endl;

      // Assuming that these are always in the same order.
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

    } else {
      std::cout << "WARNING: Unsupported nff character: " << in << ". Moving on." << std::endl;
    }
  }

  fi.close();
}
