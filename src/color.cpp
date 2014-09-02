#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include "surfaces.h"
#include <time.h>

Color offset_saturation_single(Color c) {
  srand(time(NULL));
  double r = (rand() % 10) / 10.0;

  c *= r;
  return c;
}

void offset_saturation_multi(std::vector<Surface*> scene_objects) {
  srand(time(NULL));
  for(std::vector<Surface*>::iterator it = scene_objects.begin(); it != scene_objects.end(); ++it) {
    double r = (rand() % 10) / 10.0;
    Surface* s = *it;

    s->dc *= r;
  }
}

Color offset_hue_single(Color c) {
  srand(time(NULL));
  double rr = (rand() % 10) / 10.0;
  double rg = (rand() % 10) / 10.0;
  double rb = (rand() % 10) / 10.0;

  c.x = c.x * rr;
  c.y = c.y * rg;
  c.z = c.z * rb;

  return c;
}

void offset_hue_multi(std::vector<Surface*> scene_objects) {
  srand(time(NULL));
  for(std::vector<Surface*>::iterator it = scene_objects.begin(); it != scene_objects.end(); ++it) {
    double rr = (rand() % 10) / 10.0;
    double rg = (rand() % 10) / 10.0;
    double rb = (rand() % 10) / 10.0;
    Surface* s = *it;

    s->dc.x = s->dc.x * rr;
    s->dc.y = s->dc.y * rg;
    s->dc.z = s->dc.z * rb;
  }
}
