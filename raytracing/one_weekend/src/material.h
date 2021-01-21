#pragma once
#include "ray.h"
#include "hittable.h"

struct material
{
	virtual ~material() = default;
	virtual bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const = 0;
};