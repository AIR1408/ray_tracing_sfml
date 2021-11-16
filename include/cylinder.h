#ifndef CYLINDER_H
#define CYLINDER_H

#include <object.h>

class Cylinder : public Object{
public:
    Cylinder(linalg::aliases::float3 color, float radius, linalg::aliases::float3 pa,
        linalg::aliases::float3 pb);

private:
    float calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd);
    
    float radius;
    linalg::aliases::float3 pa, pb;
};

#endif