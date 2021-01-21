#pragma once
#include "ray.h"
#include "vec3.h"

#define PI 3.141592653589793238462643383279502884L

struct camera
{
public:
	camera();
	camera(const vec3& lookFrom, const vec3& lookAt, const vec3& up, const real& pVFOV, const real& pAspect, const real& pAperture, const real& focus_dist);

	[[nodiscard]] ray shoot(const real& s, const real& t) const;
	
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

	vec3 u, v, w;
	real lens_radius;
};