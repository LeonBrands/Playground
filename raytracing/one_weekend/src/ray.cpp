#include "ray.h"

ray::ray(const vec3& pOrigin, const vec3& pDirection): origin(pOrigin), direction(pDirection)
{
	
}

vec3 ray::point(const real& t) const
{
	return origin + t * direction;
}