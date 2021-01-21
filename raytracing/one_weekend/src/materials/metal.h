#pragma once
#include "../material.h"

struct metal : material
{
	explicit metal(const vec3& pAlbedo, const real& pFuzz = 1);
	bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const override;

	vec3 albedo;
	real fuzz = 1;
};
