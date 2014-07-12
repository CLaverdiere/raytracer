#include "parser.h"

// TODO implement most view attributes.

Scene* parse_nff_spheres(const char* filename) {
  std::ifstream fi;
  fi.open(filename);

  // Identifier storage.
  std::string in;

  // Parse background colors.
  double bgr, bgg, bgb;
  fi >> in; // b
  fi >> bgr;
  fi >> bgg;
  fi >> bgb;

  // std::cout << bgr << " " << bgg << " " << bgb << std::endl;

  // Parse View attributes.
  double fromx, fromy, fromz;
  fi >> in; // v
  fi >> in; // from
  fi >> fromx;
  fi >> fromy;
  fi >> fromz;

  vec from(fromx, fromy, fromz);
  // std::cout << from.x() << " " << from.y() << " " << from.z() << std::endl;

  double atx, aty, atz;
  fi >> in; // at
  fi >> atx;
  fi >> aty;
  fi >> atz;

  vec at(atx, aty, atz);
  // std::cout << at.x() << " " << at.y() << " " << at.z() << std::endl;

  double upx, upy, upz;
  fi >> in; // up
  fi >> upx;
  fi >> upy;
  fi >> upz;

  vec up(upx, upy, upz);
  // std::cout << up.x() << " " << up.y() << " " << up.z() << std::endl;

  double angle;
  fi >> in; // angle
  fi >> angle;

  // std::cout << angle << std::endl;

  double hither;
  fi >> in; // hither
  fi >> hither;

  // std::cout << hither << std::endl;

  double resx, resy;
  fi >> in; // hither
  fi >> resx;
  fi >> resy;

  // std::cout << resx << " " << resy << std::endl;

  // Parse Fill attributes.
  double r, g, b, kd, ks, shine, t, ior;
  fi >> in;    // f
  fi >> r;     // red
  fi >> g;     // green
  fi >> b;     // blue
  fi >> kd;    // diffuse component
  fi >> ks;    // specular
  fi >> shine; // phong cosine power
  fi >> t;     // transmittance
  fi >> ior;   // index of refraction

  // std::cout << r << " " << g << " " << b << " " << kd << " " << ks << " " <<
  //             shine << " " << t << " " << ior << " " << std::endl;

  // Parse Spheres
  double cx, cy, cz, rad, 
         minx=0, miny=0, maxx=0, maxy=0; // used for image view.
  std::vector<Surface*> scene_objects;
  std::vector<double> img_dims;

  while(!fi.eof()) {
    fi >> in; // s
    fi >> cx; // centerx
    fi >> cy; // centery
    fi >> cz; // centerz
    fi >> rad; // radius

    if(cx < minx) minx = cx;
    if(cx > maxx) maxx = cx;
    if(cy < miny) miny = cy;
    if(cy > maxy) maxy = cy;

    if(fi.eof()) break;
    Color col = {r*kd, g*kd, b*kd};
    scene_objects.push_back(new Sphere(col, vec(cx, cy, cz), rad));
    // std::cout << cx << " " << cy << " " << cz << " " << rad << std::endl;
  }

  img_dims.push_back(minx);
  img_dims.push_back(maxx);
  img_dims.push_back(miny);
  img_dims.push_back(maxy);

  fi.close();

  // TODO angle, hither

  // Read parsed attributes into Scene object.
  Projection projection_type = Parallel;
  vec to = at - from;
  std::vector<Light> lights;
  Color bg_col = {bgr, bgg, bgb};
  Camera* camera = new Camera(from, at);
  Raytracer* raytracer = new Raytracer();
  Scene* parsed_scene = new Scene(resx, resy, img_dims, projection_type,
      camera, lights, bg_col, scene_objects, raytracer);

  return parsed_scene;
}
