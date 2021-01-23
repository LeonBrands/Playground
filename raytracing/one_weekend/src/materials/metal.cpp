#include "metal.h"

metal::metal(const vec3& pAlbedo, const real& pFuzz) : albedo(pAlbedo)
{
	if (pFuzz < 1) fuzz = pFuzz;
	else fuzz = 1;
}

bool metal::scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const
{
	const vec3 reflected = vec3::reflect(ray_in.direction.get_normalized(), hit.normal);
	scattered = ray(hit.point, reflected + fuzz * vec3::random_unit()); //Adjust direction of refracted rays randomly scaled by fuzz
	const bool scatters = vec3::dot(scattered.direction, hit.normal) > 0;

	if (scatters)
		attenuation = albedo;

	return scatters;
}