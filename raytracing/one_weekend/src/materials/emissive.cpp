#include "emissive.h"

emissive::emissive(const vec3& albedo, const real& intensity)
{
	color = albedo * intensity;
}

bool emissive::scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const
{
	scattered = ray{};
	attenuation = color;
	return false;
}