#include "camera.h"
#include "color.h"
#include "vec.h"

class Surface {
  public:
    Color dc; // default color

    // Determines if our surface is hit by a unit vector d, from origin e.
    virtual bool hit(vec e, vec d) = 0;

    // Finds if a unit vector d intersects our surface, from origin e, in interval [lower_t_bound, ∞].
    virtual vec* get_intersection(vec e, vec d, float lower_t_bound) = 0;

    // Returns the surface normal defined at an intersection point ip.
    virtual vec* get_surface_normal(vec ip, Camera* camera) = 0;
};

class Sphere: public Surface {
  public:
    vec c; // center
    double r; // radius

    Sphere(Color dc, vec c, double r);
    bool hit(vec e, vec d);
    vec* get_intersection(vec e, vec d, float lower_t_bound);
    vec* get_surface_normal(vec ip, Camera* camera);

    // Finds the discriminant of a unit vector d to our sphere, from origin e.
    double get_discriminant(vec e, vec d);

    friend std::ostream& operator<<(std::ostream& os, const Sphere& s);
};

class Triangle: public Surface {
  public:
    vec v1, v2, v3; // three verticies

    Triangle(Color dc, vec v1, vec v2, vec v3);
    bool hit(vec e, vec d);
    vec* get_intersection(vec e, vec d);
    vec* get_surface_normal(vec ip, Camera* camera);
};
