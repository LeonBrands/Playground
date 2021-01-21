#pragma once
#include "../material.h"

struct dielectric : material
{
	explicit dielectric(const real& pRefraction);
	
	bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const override;
	static bool refract(const vec3& v, const vec3& n, const real& ni_over_nt, vec3& refracted);
	static real schlick(const real& cosine, const real& refraction_idx);

	real refraction_idx;
};