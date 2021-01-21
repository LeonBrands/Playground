#pragma once
#include "../real.h"
#include "../vec3.h"
#include "../ray.h"
#include "../material.h"
#include "../hittable.h"

/**
 * @brief A simple spherical raycast hittable object defined by a center and a radius.
*/
struct sphere : hittable
{
	sphere() = default;
	sphere(const vec3& pCenter, const real& pRadius, std::unique_ptr<material> pMaterial);
	
	bool hit(const ray& r, const real& t_min, const real& t_max, ray_hit& hit) const override;
	
	vec3 center{};
	real radius{};

	std::unique_ptr<material> mat;
};