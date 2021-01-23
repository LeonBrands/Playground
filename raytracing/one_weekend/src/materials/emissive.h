#pragma once
#include "../material.h"

/**
 * Emissive materials don't scatter rays but instead return a color value.
 */
struct emissive : material
{
	emissive(const vec3& albedo, const real& intensity);
	bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const override;

	vec3 color;
};