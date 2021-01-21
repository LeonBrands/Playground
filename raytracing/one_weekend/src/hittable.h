#pragma once
#include "ray.h"
#include "ray_hit.h"

struct hittable
{
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, const real& t_min, const real& t_max, ray_hit& hit) const = 0;
};