#pragma once
#include "real.h"
#include "vec3.h"

struct material;

/**
 * Ray cast hit information
 */
struct ray_hit
{
	real t = -1.0; //The distance along the ray
	vec3 point{}; //The point in 3D space where the ray hit
	vec3 normal{}; //The surface normal of the hit

	material* material; //A pointer to the object's material
};