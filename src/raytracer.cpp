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

#include <algorithm>
#include <stdio.h>
#include "surfaces.h"
#include <vector>

#define HEIGHT 500
#define WIDTH 500
#define SCALE 255

using namespace std;

int main(int argc, const char *argv[])
{
  unsigned char pixels[HEIGHT][WIDTH][3];
  int focal_length = (WIDTH+HEIGHT) / 2;

  vec e(0, 0, 0); // camera
  vec li(-WIDTH, HEIGHT, -focal_length*.75); // light source
  float l = e.x() - WIDTH/2;
  float r = e.x() + WIDTH/2;
  float b = e.y() - HEIGHT/2;
  float t = e.y() + HEIGHT/2;
  float nx = WIDTH;
  float ny = HEIGHT;

  // Sphere centers.
  vec c1(0   , 0   , -focal_length*5   );
  vec c2(250 , -100, -focal_length*3.75);
  vec c3(100 , 75  , -focal_length*1.25);
  vec c4(-150, 25  , -focal_length*.9  );
  vec c5(-75 , 125 , -focal_length*.75 );

  // Sphere creation.
  Sphere* s1 = new Sphere(c1, (WIDTH+HEIGHT) / 8);
  Sphere* s2 = new Sphere(c2, (WIDTH+HEIGHT) / 13);
  Sphere* s3 = new Sphere(c3, (WIDTH+HEIGHT) / 21);
  Sphere* s4 = new Sphere(c4, (WIDTH+HEIGHT) / 34);
  Sphere* s5 = new Sphere(c5, (WIDTH+HEIGHT) / 55);

  // All objects in the scene.
  std::vector<Surface*> scene;
  scene.push_back(s1);
  scene.push_back(s2);
  scene.push_back(s3);
  scene.push_back(s4);
  scene.push_back(s5);

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

      // For each object in our scene, check ray intersection.
      for(int k=0; k<5; k++) {
        Surface *s = scene[k];
        disc = s->get_discriminant(e, d);

        if(disc > 0) {
          // printf("Hit: %f %f\n", disc, t);
          ip = s->get_intersection(e, d);
          n = s->get_surface_normal(ip);
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
          // printf("  lambert: %f %f\n", n*ld, lambert_shade);
      } else {
        for(int k=0; k<3; k++) {
          pixels[j][i][k] = 0;
        }
      }
    }
  }

  FILE *f = fopen("pics/sphere.ppm", "wb");
  fprintf(f, "P6\n%d %d\n%d\n", WIDTH, HEIGHT, SCALE);
  fwrite(pixels, 1, HEIGHT*WIDTH*3, f);
  fclose(f);

  return 0;
}
