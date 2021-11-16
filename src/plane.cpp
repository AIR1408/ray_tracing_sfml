#include <plane.h>

Plane::Plane(linalg::aliases::float3 color, linalg::aliases::float3 plane_normal) : 
        Object(color){
    this->normal = linalg::normalize(plane_normal);
    this->p = {normal, 0};
}

float Plane::calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd){
    return -(dot(ro, p.xyz()) + p.w) / dot(rd, p.xyz());
}

