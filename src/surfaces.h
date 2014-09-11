#include "camera.h"
#include "color.h"
#include "vec.h"

// Attribute container for surfaces.
struct SurfaceAttr {
  Color fill;
  double kd, ks, shine, t, ior;

  SurfaceAttr();
  SurfaceAttr(Color fill, double kd, double ks, double shine, double t, double ior);
};


class Surface {
  public:
    SurfaceAttr attr; // Surface attributes.

    // Determines if our surface is hit by a unit vector d, from origin e.
    virtual bool hit(vec e, vec d) = 0;

    // Finds and stores if a unit vector d intersects our surface, from origin e, in interval [lower_t_bound, ∞].
    virtual bool get_intersection(vec &ip, vec e, vec d, float lower_t_bound) = 0;

    // Stores the surface normal defined at an intersection point ip.
    virtual void get_surface_normal(vec &norm, vec ip, vec eye) = 0;
};

class Sphere: public Surface {
  public:
    // A sphere is defined by a vector center c, and a radius r.
    vec c; // center
    double r; // radius

    Sphere(SurfaceAttr attr, vec c, double r);
    bool hit(vec e, vec d);
    bool get_intersection(vec &ip, vec e, vec d, float lower_t_bound);
    void get_surface_normal(vec &norm, vec ip, vec eye);

    // Finds the discriminant of a unit vector d to our sphere, from origin e.
    double get_discriminant(vec e, vec d);
};

std::ostream &operator << (std::ostream &out, Sphere& s);

class Triangle: public Surface {
  public:
    // A triangle is defined by three vertices.
    vec v1, v2, v3;

    Triangle(SurfaceAttr attr, vec v1, vec v2, vec v3);
    bool hit(vec e, vec d);
    bool get_intersection(vec &ip, vec e, vec d, float lower_t_bound);
    void get_surface_normal(vec &norm, vec ip, vec eye);
};

std::ostream &operator << (std::ostream &out, Triangle& t);

// NOT IN NFF SPEC.
class Plane: public Surface {
  public:
    // a plane is defined by a normal vector n to the plane, 
    //   and a point q on the plane.
    vec n, q;

    Plane(SurfaceAttr attr, vec n, vec q);
    bool hit(vec e, vec d);
    bool get_intersection(vec &ip, vec e, vec d, float lower_t_bound);
    void get_surface_normal(vec &norm, vec ip, vec eye);
};
