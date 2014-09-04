#include "parser.h"

void parse_nff_file(const char* filename, std::map<std::string, double>
    &scene_attrs, std::vector<Surface*> &scene_objects, std::vector<Light> &lights) {
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
      fi >> scene_attrs["bg_r"];
      fi >> scene_attrs["bg_g"];
      fi >> scene_attrs["bg_b"];

    } else if(in == "c") { // Cone or cylinder primitive.
      // PARSED, BUT NOT IMPLEMENTED.
      fi >> in; fi >> in; fi >> in; fi >> in; // base vector, radius.
      fi >> in; fi >> in; fi >> in; fi >> in; // apex vector, radius.

    } else if(in == "f") { // Object material properties.
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
      // Optional RGB light component not implemented.
      double lx, ly, lz;
      fi >> lx; fi >> ly; fi >> lz;
      lights.push_back(Light(scene_attrs["light_intensity"], vec(lx, ly, lz)));

    } else if(in == "p") { // Polygon primitive.
      // For an n sided polygon, split it into triangles.
      double vx, vy, vz;
      int num_verts;
      vec verts[3];

      fi >> num_verts;

      // First, read in a single vertex.
      // Store this in an array of three vectors, representing a triangle.
      // This overwrites the oldest vector with the newest one parsed, or a new vector if empty.
      // Add that new triangle to our object collection. Repeat.
      for(int i=0; i < num_verts; i++) {
        fi >> vx; fi >> vy; fi >> vz;
        
        verts[i % 3] = vec(vx, vy, vz);

        if(i >= 2) { // We have at least three vertices parsed to form a triangle.
          scene_objects.push_back(new Triangle(fill_col, verts[0], verts[1], verts[2]));
        }
      }

    } else if(in == "pp") { // Polygonal patch primitive.
      // PARSED, BUT NOT IMPLEMENTED.
      int num_verts;
      double vx, vy, vz,
             nx, ny, nz;
      fi >> num_verts;
      for(int i=0; i < num_verts; i++) {
        fi >> vx; fi >> vy; fi >> vz;
        fi >> nx; fi >> ny; fi >> nz;
      }

    } else if(in == "s") { // Sphere primitive.
      double cx, cy, cz, rad;
      fi >> cx;  // centerx
      fi >> cy;  // centery
      fi >> cz;  // centerz
      fi >> rad; // radius
      scene_objects.push_back(new Sphere(fill_col, vec(cx, cy, cz), rad));

    } else if(in == "v") { // Viewing vectors and angles.

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
