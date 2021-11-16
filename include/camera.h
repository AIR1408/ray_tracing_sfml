#ifndef CAMERA_H
#define CAMERA_H

#include <linalg.h>
#include <structs.h>

typedef linalg::aliases::float3 float3;

class Camera{
public:
    Camera(float3 position, float3 up, float3 center, float fov, float aspect_ratio);    
    Ray getRay(float u, float v);

    float3 getPosition();
private:
    float fov;
    float3 position, up, fwd, right;
    Ray ray;
};

#endif