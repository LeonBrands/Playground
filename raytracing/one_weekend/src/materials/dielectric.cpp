#include "dielectric.h"

#include "../random.h"

dielectric::dielectric(const real& pRefraction) : refraction_idx(pRefraction)
{
	
}

bool dielectric::scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const
{
	//The material makes no special changes to the ray's color
	attenuation = vec3(1, 1, 1);

	//Calculate the incoming direction and outgoing normal
	vec3 outward_normal;
	real ni_over_nt;
	real cosine;
	if (vec3::dot(ray_in.direction, hit.normal) > 0)
	{
		outward_normal = -hit.normal;
		ni_over_nt = refraction_idx;
		cosine = refraction_idx * vec3::dot(ray_in.direction, hit.normal) / ray_in.direction.length();
	}
	else
	{
		outward_normal = hit.normal;
		ni_over_nt = 1.0 / refraction_idx;
		cosine = -vec3::dot(ray_in.direction, hit.normal) / ray_in.direction.length();
	}

	//Calculate reflection probability upon refract
	vec3 refracted;
	real reflect_probability;
	if (refract(ray_in.direction, outward_normal, ni_over_nt, refracted))
	{
		reflect_probability = schlick(cosine);
	}
	else //Perfect reflection
	{
		reflect_probability = 1.0;
	}

	//Calculate a random (increasing depending on the value calculated by schlick) chance that the ray gets reflected 
	if (rand01() < reflect_probability)
	{
		const vec3 reflected = vec3::reflect(ray_in.direction, hit.normal);
		scattered = ray(hit.point, reflected);
	}
	else
	{
		scattered = ray(hit.point, refracted);
	}

	return true;
}

bool dielectric::refract(const vec3& v, const vec3& n, const real& ni_over_nt, vec3& refracted) const
{
	//Refraction as described by Snel's law:
	//n sin(theta) = n' sin(theta')
	//Where n is the refractive index (air = 1, glass = 1.3-1.7, diamond = 2.4)
	
	const vec3 uv = v.get_normalized();
	const real dt = vec3::dot(uv, n);
	const real discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);

	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	//Sometimes there is no solution to Snel's law, this happens when light is perfectly reflected
	//Thus, we return false and use a reflected ray instead
	return false;
}

real dielectric::schlick(const real& cosine) const
{
	//Polynomial approximation by Christophine Schlick
	real r0 = (1 - refraction_idx) / (1 + refraction_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow(1 - cosine, 5);
}
