#include "camera.h"
#include "color.h"
#include "vec.h"

// TODO find how to avoid redeclaring the virtual methods in derived classes.

class Surface {
  public:
    Color dc; // default color

    // Determines if our surface is hit by a unit vector d, from origin e.
    virtual bool hit(vec e, vec d) = 0;

    // Finds and stores if a unit vector d intersects our surface, from origin e, in interval [lower_t_bound, ∞].
    virtual bool get_intersection(vec &ip, vec e, vec d, float lower_t_bound) = 0;

    // Stores the surface normal defined at an intersection point ip.
    virtual void get_surface_normal(vec &norm, vec ip, Camera* camera) = 0;
};

class Sphere: public Surface {
  public:
    // A sphere is defined by a vector center c, and a radius r.
    vec c; // center
    double r; // radius

    Sphere(Color dc, vec c, double r);
    bool hit(vec e, vec d);
    bool get_intersection(vec &ip, vec e, vec d, float lower_t_bound);
    void get_surface_normal(vec &norm, vec ip, Camera* camera);

    // Finds the discriminant of a unit vector d to our sphere, from origin e.
    double get_discriminant(vec e, vec d);

    // friend std::ostream& operator<<(std::ostream& os, const Sphere& s);
};

class Triangle: public Surface {
  public:
    // A triangle is defined by three vertices.
    vec v1, v2, v3;

    Triangle(Color dc, vec v1, vec v2, vec v3);
    bool hit(vec e, vec d);
    bool get_intersection(vec &ip, vec e, vec d, float lower_t_bound);
    void get_surface_normal(vec &norm, vec ip, Camera* camera);
};

class Plane: public Surface {
  public:
    // a plane is defined by a normal vector n to the plane, 
    //   and a point q on the plane.
    vec n, q;

    Plane(Color dc, vec n, vec q);
    bool hit(vec e, vec d);
    bool get_intersection(vec &ip, vec e, vec d, float lower_t_bound);
    void get_surface_normal(vec &norm, vec ip, Camera* camera);
};
