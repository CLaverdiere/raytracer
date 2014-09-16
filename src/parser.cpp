#include "parser.h"
#include <string.h>

// TODO Object material properties should be unique to each object.

void parse_nff_file(const char* filename, std::map<std::string, double>
    &scene_attrs, std::vector<Surface*> &scene_objects, std::vector<Light> &lights) {
  std::ifstream ifs;
  std::istream* fi;

  // Keep global set of surface attributes for object creation.
  SurfaceAttr attr;

  // Use stdin if filename is empty.
  if(strcmp(filename, "")) {
    fi = &ifs;
    ifs.open(filename);
  } else {
    fi = &std::cin;
  }

  // Identifier storage.
  std::string in;

  // Parsing loop.
  while(!fi->eof()) {
    *(fi) >> in; // Read in the next character.
    if(fi->eof()) { break; }

    if(in == "#") { // Comment.
      std::getline(*fi, in);
    
    } else if(in == "b") { // Background color
      (*fi) >> scene_attrs["bg_r"];
      (*fi) >> scene_attrs["bg_g"];
      (*fi) >> scene_attrs["bg_b"];

    } else if(in == "c") { // Cone or cylinder primitive.
      // PARSED, BUT NOT IMPLEMENTED.
      (*fi) >> in; (*fi) >> in; (*fi) >> in; (*fi) >> in; // base vector, radius.
      (*fi) >> in; (*fi) >> in; (*fi) >> in; (*fi) >> in; // apex vector, radius.

    } else if(in == "f") { // Object material properties.
      double tempr, tempg, tempb;
      (*fi) >> tempr; // red
      (*fi) >> tempg; // green
      (*fi) >> tempb; // blue
      attr.fill = Color(tempr, tempg, tempb);

      (*fi) >> attr.kd;     // diffuse component
      (*fi) >> attr.ks;     // specular
      (*fi) >> attr.shine;  // phong cosine power
      (*fi) >> attr.t;      // transmittance
      (*fi) >> attr.ior;    // index of refraction

    } else if(in == "l") { // Positional light location.
      // Optional RGB light component not implemented.
      double lx, ly, lz;
      (*fi) >> lx; (*fi) >> ly; (*fi) >> lz;
      lights.push_back(Light(scene_attrs["light_intensity"], vec(lx, ly, lz)));
      scene_attrs["num_lights"] += 1;

    } else if(in == "p") { // Polygon primitive.
      // For an n sided polygon, split it into triangles.
      double vx, vy, vz;
      int num_verts;
      vec verts[3];

      (*fi) >> num_verts;

      // First, read in a three vertices.
      // The first vertex will always stay in our vertex list.
      // Then, for each vertex after the third
      //   Push the 3rd vector into slot 2.
      //   Read the new vector into the vacant 3rd slot.
      // Add that new triangle to our object collection. Repeat.
      // This process is messy, but is unfortuneately how NFF outputs its vertices.
      (*fi) >> vx; (*fi) >> vy; (*fi) >> vz;
      verts[0] = vec(vx, vy, vz);
      (*fi) >> vx; (*fi) >> vy; (*fi) >> vz;
      verts[1] = vec(vx, vy, vz);
      (*fi) >> vx; (*fi) >> vy; (*fi) >> vz;
      verts[2] = vec(vx, vy, vz);
      scene_objects.push_back(new Triangle(attr, verts[0], verts[1], verts[2]));

      for(int i=0; i < num_verts-3; i++) {
        (*fi) >> vx; (*fi) >> vy; (*fi) >> vz;
        
        verts[1] = verts[2];
        verts[2] = vec(vx, vy, vz);

        scene_objects.push_back(new Triangle(attr, verts[0], verts[1], verts[2]));
      }

      scene_attrs["num_triangles"] += num_verts - 2;

    } else if(in == "pp") { // Polygonal patch primitive.
      // Same process as polygon. I throw away the normals.
      double vx, vy, vz;
      int num_verts;
      vec verts[3];

      (*fi) >> num_verts;

      (*fi) >> vx; (*fi) >> vy; (*fi) >> vz;
      (*fi) >> in; (*fi) >> in; (*fi) >> in;
      verts[0] = vec(vx, vy, vz);
      (*fi) >> vx; (*fi) >> vy; (*fi) >> vz;
      (*fi) >> in; (*fi) >> in; (*fi) >> in;
      verts[1] = vec(vx, vy, vz);
      (*fi) >> vx; (*fi) >> vy; (*fi) >> vz;
      (*fi) >> in; (*fi) >> in; (*fi) >> in;
      verts[2] = vec(vx, vy, vz);
      scene_objects.push_back(new Triangle(attr, verts[0], verts[1], verts[2]));

      for(int i=0; i < num_verts-3; i++) {
        (*fi) >> vx; (*fi) >> vy; (*fi) >> vz;
        
        verts[1] = verts[2];
        verts[2] = vec(vx, vy, vz);

        scene_objects.push_back(new Triangle(attr, verts[0], verts[1], verts[2]));
      }

      scene_attrs["num_triangles"] += num_verts - 2;

    } else if(in == "s") { // Sphere primitive.
      double cx, cy, cz, rad;
      (*fi) >> cx;  // centerx
      (*fi) >> cy;  // centery
      (*fi) >> cz;  // centerz
      (*fi) >> rad; // radius
      scene_objects.push_back(new Sphere(attr, vec(cx, cy, cz), rad));
      scene_attrs["num_spheres"] += 1;

    } else if(in == "v") { // Viewing vectors and angles.

      // Assuming that these are always in the same order.
      (*fi) >> in; // from
      (*fi) >> scene_attrs["from_x"];
      (*fi) >> scene_attrs["from_y"];
      (*fi) >> scene_attrs["from_z"];

      (*fi) >> in; // at
      (*fi) >> scene_attrs["atx"];
      (*fi) >> scene_attrs["aty"];
      (*fi) >> scene_attrs["atz"];

      (*fi) >> in; // up
      (*fi) >> scene_attrs["upx"];
      (*fi) >> scene_attrs["upy"];
      (*fi) >> scene_attrs["upz"];

      (*fi) >> in; // angle
      (*fi) >> scene_attrs["angle"];

      (*fi) >> in; // hither
      (*fi) >> scene_attrs["hither"];

      (*fi) >> in; // resolution
      (*fi) >> scene_attrs["resx"];
      (*fi) >> scene_attrs["resy"];

    } else {
      std::cout << "WARNING: Unsupported nff character: " << in << ". Moving on." << std::endl;
    }
  }
}
