#include <object.h>

Object::Object(linalg::aliases::float3 color){
    this->color = color;
    reflection_intensity = 0.f;
    transform = linalg::identity;    
}

float Object::getIntersectonWith(Ray ray){
    ray.applyTransform(transform);
    float rv = calcIntersection(ray.origin, ray.direction);
    if (rv > 0)
        normal = linalg::normalize(linalg::mul(linalg::transpose(transform), {normal, 0.f}).xyz());
    return rv;
}

linalg::aliases::float3 Object::getPhongColor(Ray ray, Light light){
    light.applyTransform(transform);

    auto ld = -light.getDirection(ray.tail);
    
    float cosA = linalg::dot(ld, normal);
    auto reflect = 2 * normal * cosA - ld,
        diff_color = color * linalg::max(cosA, 0) * light.color / 255,
        spec_color = light.color * pow2pow(linalg::max(linalg::dot(reflect, -ray.direction), 0), 4);
    return linalg::min(25 + diff_color + spec_color, 255);
}

void Object::applyTransform(linalg::aliases::float4x4 mat){
    transform = linalg::mul(transform, linalg::inverse(mat));
}

linalg::aliases::float4x4 Object::getTransform() const { 
    return transform;
}

void Object::setReflectionIntensity(float r){
    reflection_intensity = r;
}

float Object::getReflectionIntensity() const {
    return reflection_intensity;
}

linalg::aliases::float3 Object::getNormal() const {
    return normal;
}

// Returns x^(2^y)
float Object::pow2pow(float x, int y) const {
    for (int i = 0; i < y; ++i)
        x *= x;
    return x;
}