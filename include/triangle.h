#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <object.h> 

class Triangle : public Object{
public:
    Triangle(linalg::aliases::float3 color, linalg::aliases::float3 v0,
        linalg::aliases::float3 v1, linalg::aliases::float3 v2);

private:
    float calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd);
    linalg::aliases::float3 v0, v1, v2;
};

#endif