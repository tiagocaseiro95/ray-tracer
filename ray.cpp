#include "ray.hpp"

Ray::Ray(const Vec3f& _origin, const Vec3f& _direction)
  : origin_{_origin}, direction_{_direction} {}

std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    return os << "[Origin: " << ray.origin_ << " Direction: " << ray.direction_ << "]";
}