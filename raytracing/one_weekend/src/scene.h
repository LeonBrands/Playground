#pragma once
#include <vector>
#include <memory>

#include "hittable.h"

struct scene : hittable
{
	std::vector<std::unique_ptr<hittable>> objects;

	bool hit(const ray& r, const real& t_min, const real& t_max, ray_hit& hit) const override;
};