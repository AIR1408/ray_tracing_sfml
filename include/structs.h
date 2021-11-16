#ifndef STRUCTS_H
#define STRUCTS_H

#include <linalg.h>

struct Light{
    Light() = default;
    Light(linalg::aliases::float3 pos, linalg::aliases::float3 clr) : 
        position(pos), color(clr){};
    linalg::aliases::float3 position;
    linalg::aliases::float3 color;

    linalg::aliases::float3 getDirection(linalg::aliases::float3 point);
    void applyTransform(const linalg::aliases::float4x4 &transform);
};

struct Ray{
    Ray() = default;
    Ray(linalg::aliases::float3 orig, linalg::aliases::float3 dir) :
        origin(orig), direction(dir){};
    linalg::aliases::float3 origin;
    linalg::aliases::float3 direction;
    linalg::aliases::float3 tail;
    linalg::aliases::float3 ambient;

    void applyTransform(const linalg::aliases::float4x4 &transform);
};


#endif