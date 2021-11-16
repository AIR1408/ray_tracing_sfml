#include <camera.h>

Camera::Camera(float3 position, float3 up, float3 center, float fov, float aspect_ratio){
    this->position = position, this->fwd = linalg::normalize(center - position),
    this->up = linalg::normalize(up - dot(up, fwd) / dot(fwd, fwd) * fwd) * tanf(fov / 2),
    this->right = linalg::normalize(cross(fwd, up)) * tanf(fov / 2) * aspect_ratio;
    ray.origin = position;
}

Ray Camera::getRay(float u, float v){
    ray.direction = linalg::normalize(u * right + v * up + fwd);
    return ray;
}

float3 Camera::getPosition(){
    return position;
}