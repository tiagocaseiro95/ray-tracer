#pragma once

#include <iostream>
#include <string>

#include "ray.hpp"

class Object {
  public:
    virtual ~Object()                   = default;
    virtual bool intersects(const Ray&) = 0;
    friend std::ostream& operator<<(std::ostream&, const Object&);

  protected:
    virtual std::string print() const = 0;
};

class Sphere : public Object {
  public:
    ~Sphere() = default;
    Sphere(const Vec3f& _center, float _radius) : Object(), center_{_center}, radius_{_radius} {}
    bool intersects(const Ray&) override;

  protected:
    std::string print() const override;

  private:
    Vec3f center_;
    float radius_;
};