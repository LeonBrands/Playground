#pragma once
#include "vec3.h"

struct hittable;

/**
 * The core concept of the ray tracer.
 * Rays describe a line in 3D space with an origin (starting point) and a direction.
*/
struct ray
{
	explicit ray() = default;
	explicit ray(const vec3& pOrigin, const vec3& pDirection);

	/**
	 * Calculate the point along the ray at distance t.
	 */
	[[nodiscard]] vec3 point(const real& t) const;

	/**
	 * Cast ray and get its resulting color.
	 *
	 * This function runs recursively until depth == NBOUNCES or until the ray hits no target.
	 */
	[[nodiscard]] vec3 color(const hittable* world, unsigned int depth) const;
	
	vec3 origin{};
	vec3 direction{};
};