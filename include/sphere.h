#ifndef SPHERE_H
#define SPHERE_H

#include <object.h>

class Sphere : public Object{
public:
    Sphere(linalg::aliases::float3 color, float radius);

private:
    float radius, far;
    float calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd);
};

#endif