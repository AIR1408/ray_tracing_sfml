#ifndef CUBE_H
#define CUBE_H

#include <object.h> 

class Cube : public Object{
public:
    Cube(linalg::aliases::float3 color, float width);


private:
    float calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd);
    linalg::aliases::float3 sign(linalg::aliases::float3 vec);
    linalg::aliases::float3 step(linalg::aliases::float3 edge, linalg::aliases::float3 vec);

    float width, far;
};

#endif