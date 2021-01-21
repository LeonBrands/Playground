#pragma once
#include "../material.h"

/**
 * @brief A standard diffuse material, scatters rays outwards based on the normal with a random direction creating an always rough material
*/
struct lambertian : material
{
	explicit lambertian(const vec3& pAlbedo);
	bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const override;

	vec3 albedo;
};