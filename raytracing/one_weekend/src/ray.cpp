#include "ray.h"
#include "config.h"
#include "hittable.h"
#include "material.h"
#include "ray_hit.h"

ray::ray(const vec3& pOrigin, const vec3& pDirection): origin(pOrigin), direction(pDirection)
{
	
}

vec3 ray::point(const real& t) const
{
	return origin + t * direction;
}

vec3 ray::color(const hittable* world, const unsigned depth) const
{
	//Attempt to get a hit
	ray_hit hit;
	if (world->hit(*this, 0.0001, std::numeric_limits<real>::max(), hit))
	{
		ray scattered;
		vec3 attenuation;

		//Calculate a new ray from the hit object using the object's material's scatter function
		if (depth < NBOUNCES && hit.material->scatter(*this, hit, attenuation, scattered))
		{
			//Our resulting color is a combination of the material's attenuation (often color) and the surface's incoming light 
			return attenuation * scattered.color(world, depth + 1);
		}
		return vec3{};
	}

	//If getting a hit fails, this generates a basic skybox
	const vec3 unit_direction = direction.get_normalized();
	const real t = 0.5 * (unit_direction.y + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}