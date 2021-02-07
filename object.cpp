#include "object.hpp"

#include <cmath>
#include <sstream>

#include "ray.hpp"

Object::Object(const Vec3f& _color) : color_{_color} {}

Sphere::Sphere(const Vec3f& _center, float _radius, const Vec3f& _color)
  : Object(_color), center_{_center}, radius_{_radius} {}

bool Sphere::intersects(const Ray& ray) {
    auto l   = center_ - ray.origin_;
    auto tca = l.dotProduct(ray.direction_);

    if (tca < 0)
        return false;

    auto d = std::sqrt(l.dotProduct(l) - tca * tca);

    if (d > radius_)
        return false;

    auto thc = std::sqrt(radius_ * radius_ + d * d);
    auto t0  = tca - thc;
    auto t1  = tca + thc;

    return true;
}

std::string Sphere::print() const {
    auto os = std::ostringstream();

    os << "[Center: " << center_ << " Radius: " << radius_ << "]";

    return os.str();
}

std::ostream& operator<<(std::ostream& os, const Object& object) {
    return os << object.print();
}
