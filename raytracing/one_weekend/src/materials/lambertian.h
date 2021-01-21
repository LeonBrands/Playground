#pragma once
#include "../material.h"

struct lambertian : material
{
	explicit lambertian(const vec3& pAlbedo);
	bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const override;

	vec3 albedo;
};