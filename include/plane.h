#ifndef PLANE_H
#define PLANE_H

#include <object.h> 

class Plane : public Object{
public:
    Plane(linalg::aliases::float3 color, linalg::aliases::float3 plane_normal);


private:
    float calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd);
    linalg::aliases::float4 p;
};

#endif