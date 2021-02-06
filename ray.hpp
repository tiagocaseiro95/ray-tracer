#pragma once

#include "geometry.hpp"
#include "object.hpp"

class Ray {
  public:
    Ray(const Vec3f&, const Vec3f&);
    friend std::ostream& operator<<(std::ostream&, const Ray&);

  private:
    friend class Sphere;
    const Vec3f origin_;
    const Vec3f direction_;
};