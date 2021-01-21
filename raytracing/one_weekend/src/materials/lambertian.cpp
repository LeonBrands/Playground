#include "lambertian.h"

lambertian::lambertian(const vec3& pAlbedo) : albedo(pAlbedo)
{
	
}

bool lambertian::scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const
{
	const vec3 target = hit.point + hit.normal + vec3::random_unit();
	scattered = ray(hit.point, target - hit.point);
	attenuation = albedo;
	return true;
}