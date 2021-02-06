#pragma once

#include <iostream>
#include <string>

#include "geometry.hpp"

class Ray;

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
    Sphere(const Vec3f&, float);
    bool intersects(const Ray&) override;

  protected:
    std::string print() const override;

  private:
    Vec3f center_;
    float radius_;
};