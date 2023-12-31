#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "rtweekend.h"

class material;

struct hitRecord
{
    point3 p;
    vec3 normal;
    shared_ptr<material> matPtr;
    double t;
    bool frontFace;

    inline void setFaceNormal(const ray &r, const vec3 &outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittable
{
public:
    virtual bool hit(const ray &r, double tMin, double tMax, hitRecord &rec) const = 0;
};

#endif