// General algorithm for raytracing, from
//   Fundamentals of Computer Graphics, 3rd ed.
//   Peter Shirley, Steve Marschner.
//
// for each pixel:
//  compute viewing ray.
//  if ray hits an object with t ∈ [0,∞]:
//    compute n.
//    evalutate shading model and set pixel to that color.
//  else:
//    set pixel color to background color.
//
//  Implement a Surface class once Sphere is working.

#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

#define HEIGHT 500
#define WIDTH 500
#define SCALE 255

using namespace std;

typedef struct Point3 {
  float x, y, z;
} Point3;

typedef struct Sphere {
  vec center;
  float radius;
} Sphere;

typedef struct Ray {
  vec origin;
  vec dir;
} Ray;

int main(int argc, const char *argv[])
{
  unsigned char pixels[HEIGHT][WIDTH][3];
  int focal_length = (WIDTH+HEIGHT) / 2;

  vec e(0, 0, 0); // camera
  vec li(WIDTH/2, HEIGHT/2, -focal_length/2); // light source
  float l = e.x() - WIDTH/2;
  float r = e.x() + WIDTH/2;
  float b = e.y() - HEIGHT/2;
  float t = e.y() + HEIGHT/2;
  float nx = WIDTH;
  float ny = HEIGHT;

  Sphere spheres[5] = { 
    {{0   , 0   , -focal_length*3    } , (WIDTH+HEIGHT) / 8  } ,
    {{50  , -100, -focal_length*1.75 } , (WIDTH+HEIGHT) / 12 } ,
    {{100 , 75  , -focal_length*1.25 } , (WIDTH+HEIGHT) / 16 } ,
    {{-150, 25  , -focal_length*.9   } , (WIDTH+HEIGHT) / 24 } ,
    {{-75 , 125 , -focal_length*.75  } , (WIDTH+HEIGHT) / 32 }
  };

  // Using a Perspective View.
  for(int i=0; i<HEIGHT; i++) {
    for(int j=0; j<WIDTH; j++) {
      float u, v, t, disc;
      vec n, ip, ld;
      bool intersection = false;

      // Compute viewing ray.
      // float u = (l + (r-l) * (i + .5)) / nx;
      // float v = (b + (t-b) * (j + .5)) / ny;
      u = i - WIDTH/2;
      v = j - HEIGHT/2;

      vec e_to_ip(u, v, -focal_length);
      vec d = e_to_ip.unitlength();

      // Check ray intersection.
      for(int s=0; s<5; s++) {
        vec c = spheres[s].center;
        float rad = spheres[s].radius;

        // float vd = 1; // unit vector pointing towards camera.

        // If Discriminant negative, no intersection.
        disc = pow(d*(e-c), 2) - (d*d)*((e-c)*(e-c) - rad*rad);
        if(disc > 0) {
          // printf("Hit: %f %f\n", disc, t);
          t = min((-d*(e-c) + sqrt(disc)) / (d*d), (-d*(e-c) - sqrt(disc)) / (d*d)); // solution for parametric t.
          ip = d * t; // intersection point vector.
          n = (c-ip).unitlength();  // unit vector perpendicular to surface of sphere.
          ld = (ip-li).unitlength(); // unit vector pointing towards light source.
          intersection = true; // discriminant negative ⇒ no intersection.
        } 
      }

      // Evaluate Shading model.
      // Lambertian shading method.
      if(intersection) {
        float diffuse_coef = SCALE;
        float light_intensity = 1;
        float lambert_shade = diffuse_coef * light_intensity * max(0.0, n*ld);
        for(int k=0; k<3; k++)
          pixels[j][i][k] = (int) lambert_shade;
          // printf("  u, v: %f %f\n", u, v);
          // printf("  d. x, y, z: %f %f %f\n", d.x(), d.y(), d.z());
          // printf("  n. %f %f %f  l. %f %f %f\n", n.x(), n.y(), n.z(), ld.x(), ld.y(), ld.z());
          printf("  lambert: %f %f\n", n*ld, lambert_shade);
      } else {
        for(int k=0; k<3; k++) {
          pixels[j][i][k] = 0;
        }
      }
    }
  }

  FILE *f = fopen("sphere.ppm", "wb");
  fprintf(f, "P6\n%d %d\n%d\n", WIDTH, HEIGHT, SCALE);
  fwrite(pixels, 1, HEIGHT*WIDTH*3, f);
  fclose(f);

  return 0;
}
