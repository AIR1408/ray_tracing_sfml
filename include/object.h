#ifndef OBJECT_H
#define OBJECT_H

#include <linalg.h>
#include <structs.h>

class Object{
public:
    Object(linalg::aliases::float3 color);

    linalg::aliases::float3 getPhongColor(Ray ray, Light light);
    
    float getIntersectonWith(Ray ray);

    void applyTransform(linalg::aliases::float4x4 mat);
    linalg::aliases::float4x4 getTransform() const;

    void setReflectionIntensity(float r);
    float getReflectionIntensity() const;

    linalg::aliases::float3 getNormal() const;
protected:
    float reflection_intensity;
    linalg::aliases::float3 color, normal;
    linalg::aliases::float4x4 transform;

    virtual float calcIntersection(linalg::aliases::float3 ro, linalg::aliases::float3 rd) = 0;
private:
    void appTransform(Ray &ray, Light &light);
    float fast_pow(float x, int y) const;
};

#endif