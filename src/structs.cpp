#include <structs.h>

linalg::aliases::float3 Light::getDirection(linalg::aliases::float3 point){
    return linalg::normalize(point - position);
}

void Light::applyTransform(const linalg::aliases::float4x4 &transform){
    position = linalg::mul(transform, {position, 1.f}).xyz();
}

void Ray::applyTransform(const linalg::aliases::float4x4 &transform){
    origin = linalg::mul(transform, {origin, 1.f}).xyz();
    direction = linalg::mul(transform, {direction, 0.f}).xyz();    
}