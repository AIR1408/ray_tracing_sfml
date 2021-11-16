#include <sphere.h>

Sphere::Sphere(linalg::aliases::float3 color, float radius):
        Object(color){
    this->radius = radius;
}

float Sphere::calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd){
    float b = linalg::dot(ro, rd), c = linalg::dot(ro, ro) - radius * radius, h = b * b - c;
    if (h < 0.0) return -1.f;
    h = sqrt(h);
    float near = -b - h;
    far = -b + h, normal = linalg::normalize(ro + rd * near);
    return near;
}