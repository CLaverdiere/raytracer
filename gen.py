# Generate raytracer nff files.

from itertools import product
import random
import math

class Sphere:
    def __init__(self, pos=(0,0,0), rad=0, col=(0,0,0)):
        self.pos = pos
        self.rad = rad
        self.col = col

        self.x = pos[0]
        self.y = pos[1]
        self.z = pos[2]

        self.cx = col[0]
        self.cy = col[1]
        self.cz = col[2]

    def __str__(self):
        s = "f {} {} {} 0.5 0.5 100 0 1\n".format(self.cx, self.cy, self.cz)
        s += "s {} {} {} {}".format(round(self.x, 3), round(self.y, 3), round(self.z, 3), rad)
        return s


# Settings
walls_on = False
rad = 0.3

base_str = """
b 0.05 0.05 0.05
v
from 10 -10 10
at 0 0 0
up 0 0 1
angle 45
hither 0.01
resolution 512 512
l 3 3 3
l -3 -3 2
l 5 -5 7
"""

walls = """
f 1.0 0.7 0.3 0.8 0 40 0 1
p 4
5 5 -0.5
-5 5 -0.5
-5 -5 -0.5
5 -5 -0.5
p 4
5 5 -0.5
5 5 4.5
-5 5 4.5
-5 5 -0.5
p 4
-5 5 -0.5
-5 5 4.5
-5 -5 4.5
-5 -5 -0.5
"""

# Functions to create sphere locations.
# If prefixed by gen, it is parametric in nature, and n spheres can be
#   generated by calling next(generator_function).
# If prefixed by make, it just returns sphere locations in a list.

# Random sphere paths with path weight
def gen_sphere_paths():
    ds = rad * 2
    chance = .3
    pos = [0, 0, 0]
    path_index = 0
    path_dir = 1
    while True:
        col = random.sample([i / 10. for i in range(1, 9)], 3)
        if(random.uniform(0, 1) < chance):
            path_index = random.choice([x for x in range(3) if x is not path_index])
            path_dir = random.choice([1, -1])
        pos[path_index] += ds * path_dir
        yield Sphere(pos, rad, col)

# Random sphere blob
def gen_sphere_blob():
    ds = rad * 2
    pos = [0, 0, 0]
    while True:
        col = random.sample([i / 10. for i in range(1, 9)], 3)
        pos[random.randrange(0, 3)] += random.choice([1,-1]) * ds
        yield Sphere(pos, rad, col)

# Spiral
def gen_sphere_spiral():
    pos = [0,0,0]
    angle = 0
    da = .1
    dr = 1
    for i in range(550):
        col = random.sample([i / 10. for i in range(1, 9)], 3)
        pos[0] = dr * rad * math.cos(angle)
        pos[1] = dr * rad * math.sin(angle)
        # pos[2] += rad * .3
        angle += da
        dr += .05
        yield Sphere(pos, rad, col)

# Vertical lattice
def make_sphere_lattice():
    spheres = []
    cart = list(product([1,-1], repeat=2))
    for z in range(5):
        for c in cart:
            col = random.sample([i / 10. for i in range(1, 9)], 3)
            pos = [c[0], c[1], z]
            spheres.append(Sphere(pos, rad, col))
    return spheres

# 3d curve eqn: (sinx * siny) / (x*y)
def make_single_mountain():
    spheres = []
    for x in range(-50, 50, 5):
        for y in range(-50, 50, 5):
            if(x != 0 and y != 0):
                col = random.sample([i / 10. for i in range(1, 9)], 3)
                sx = x / 10.
                sy = y / 10.
                z = 4 * (math.sin(sx) * math.sin(sy)) / (sx * sy)
                pos = [sx, sy, z]
                spheres.append(Sphere(pos, rad, col))
    return spheres

# 3d curve eqn: (sinx + siny)
def make_multi_mountain():
    spheres = []
    for x in range(-50, 50, 5):
        for y in range(-50, 50, 5):
            col = random.sample([i / 10. for i in range(1, 9)], 3)
            sx = x / 10.
            sy = y / 10.
            z = math.sin(sx) + math.sin(sy)
            pos = [sx, sy, z]
            spheres.append(Sphere(pos, rad, col))
    return spheres

def main():
    # View parameters
    print(base_str)
    if walls_on:
        print walls

    # Sphere creator (parametric)
    # object_gen = gen_sphere_spiral()
    # for i in range(500):
    #     print(next(object_gen))

    # Sphere creator (non-parametric)
    objects = make_multi_mountain()
    for o in objects:
        print o

if __name__ == "__main__":
    main()