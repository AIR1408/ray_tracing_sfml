#include <triangle.h>

Triangle::Triangle(linalg::aliases::float3 color,
    linalg::aliases::float3 v0, linalg::aliases::float3 v1, linalg::aliases::float3 v2) : 
        Object(color)
{
    this->v0 = v0, this->v1 = v1, this->v2 = v2;
}

float Triangle::calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd){
    linalg::aliases::float3 v1v0 = v1 - v0, v2v0 = v2 - v0, rov0 = ro - v0,
                            n = cross(v1v0, v2v0), q = cross(rov0, rd);
    float d = 1.0 / dot(rd, n), u = d * dot(-q, v2v0), v = d * dot(q, v1v0), t = d * dot(-n, rov0);
    if (u < 0.0 || u > 1.0 || v < 0.0 || (u + v) > 1.0) return -1.f;
    normal = linalg::normalize(n);
    return t;
}