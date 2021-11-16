#include <cube.h>

Cube::Cube(linalg::aliases::float3 color, float width) : 
        Object(color){
    this->width = width;
}

float Cube::calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd){
    auto eps = [](float p){return p == 0 ? MAXFLOAT: 1 / p;};
    linalg::aliases::float3 m = {eps(rd.x), eps(rd.y), eps(rd.z)},
        n = m * ro, k = linalg::abs(m) * width, t1 = -n - k, t2 = -n + k;
	float near = linalg::maxelem(t1);
	far = linalg::minelem(t2);
    if (near > far || far < 0.0f) return -1.f;
    normal = -sign(rd) * step({t1.y, t1.z, t1.x}, t1) * step({t1.z, t1.x, t1.y}, t1);
    return near;
}

linalg::aliases::float3 Cube::sign(linalg::aliases::float3 vec){
    auto sgn = [](float p){return p >= 0.f ? (p == 0.f? 0.f : 1.0f): -1.0f;};
    return linalg::aliases::float3{sgn(vec.x), sgn(vec.y), sgn(vec.z)};
}

linalg::aliases::float3 Cube::step(linalg::aliases::float3 edge, linalg::aliases::float3 vec){
    auto stp = [](float x, float y){return y < x ? 0.0f : 1.0f;};
    return linalg::aliases::float3{stp(edge.x, vec.x), stp(edge.y, vec.y), stp(edge.z, vec.z)};
}

