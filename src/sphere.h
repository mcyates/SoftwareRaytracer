#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere() {}
    sphere(point3 cen, double r, shared_ptr<material> m)
        : center(cen), radius(r), matPtr(m){};

    virtual bool hit(
        const ray &r, double tMin, double tMax, hitRecord &rec) const override;

public:
    point3 center;
    double radius;
    shared_ptr<material> matPtr;
};
bool sphere::hit(const ray &r, double tMin, double tMax, hitRecord &rec) const
{
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto halfB = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = halfB * halfB - a * c;
    if (discriminant < 0)
        return false;
    auto sqrtd = sqrt(discriminant);

    // Find nearest root within acceptable range
    auto root = (-halfB - sqrtd) / a;
    if (root < tMin || tMax < root)
    {
        root = (-halfB + sqrtd) / a;
        if (root < tMin || tMax < root)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);
    rec.matPtr = matPtr;

    return true;
}

#endif