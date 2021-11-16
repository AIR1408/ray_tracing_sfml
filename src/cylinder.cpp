#include <cylinder.h>

Cylinder::Cylinder(linalg::aliases::float3 color, float radius, linalg::aliases::float3 pa,
                   linalg::aliases::float3 pb) : Object(color)
{
    this->radius = radius;
    this->pa = pa;
    this->pb = pb;
}

float Cylinder::calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd)
{
    auto ba = pb - pa;
    auto oc = ro - pa;

    float baba = dot(ba, ba);
    float bard = dot(ba, rd);
    float baoc = dot(ba, oc);

    float k2 = baba - bard * bard;
    float k1 = baba * dot(oc, rd) - baoc * bard;
    float k0 = baba * dot(oc, oc) - baoc * baoc - radius * radius * baba;

    float h = k1 * k1 - k2 * k0;
    if (h < 0.0)
        return -1.0;
    h = sqrt(h);
    float t = (-k1 - h) / k2;

    // body
    float y = baoc + t * bard;
    if (y > 0.0 && y < baba){
        normal = (oc + t * rd - ba * y / baba) / radius;
        return t;
    }
    // caps
    auto sgn = [](float p){return p >= 0.f ? (p == 0.f? 0.f : 1.0f): -1.0f;};
    t = (((y < 0.0) ? 0.0 : baba) - baoc) / bard;
    if (abs(k1 + k2 * t) < h){
        normal = ba * sgn(y) / baba;
        return t;
    }

    return -1.0;
}