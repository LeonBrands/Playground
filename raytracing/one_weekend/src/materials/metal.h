#pragma once
#include "../material.h"

/**
 * @brief A metal-like material with strong reflections that can be modified to make the metal look "rough" through the fuzz parameter.
*/
struct metal : material
{
	explicit metal(const vec3& pAlbedo, const real& pFuzz = 1);
	bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const override;

	vec3 albedo;
	real fuzz = 1;
};
