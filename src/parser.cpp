#include "parser.h"

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

  Color c = {bgr, bgg, bgb};
  std::cout << c.r << " " << c.g << " " << c.b << std::endl;

  // Parse View attributes.
  double fromx, fromy, fromz;
  fi >> in; // v
  fi >> in; // from
  fi >> fromx;
  fi >> fromy;
  fi >> fromz;

  vec from(fromx, fromy, fromz);
  std::cout << from.x() << " " << from.y() << " " << from.z() << std::endl;

  double atx, aty, atz;
  fi >> in; // at
  fi >> atx;
  fi >> aty;
  fi >> atz;

  vec at(atx, aty, atz);
  std::cout << at.x() << " " << at.y() << " " << at.z() << std::endl;

  double upx, upy, upz;
  fi >> in; // up
  fi >> upx;
  fi >> upy;
  fi >> upz;

  vec up(upx, upy, upz);
  std::cout << up.x() << " " << up.y() << " " << up.z() << std::endl;

  double angle;
  fi >> in; // angle
  fi >> angle;

  std::cout << angle << std::endl;

  double hither;
  fi >> in; // hither
  fi >> hither;

  std::cout << hither << std::endl;

  double resx, resy;
  fi >> in; // hither
  fi >> resx;
  fi >> resy;

  std::cout << resx << " " << resy << std::endl;

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

  std::cout << r << " " << g << " " << b << " " << kd << " " << ks << " " <<
              shine << " " << t << " " << ior << " " << std::endl;

  // Parse Spheres
  double cx, cy, cz, rad;

  while(!fi.eof()) {
    fi >> in; // s
    fi >> cx; // centerx
    fi >> cy; // centery
    fi >> cz; // centerz
    fi >> rad; // radius

    if(fi.eof()) exit(1);
    std::cout << cx << " " << cy << " " << cz << " " << rad << std::endl;
  }

  fi.close();
}
