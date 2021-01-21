#pragma once
#include "real.h"
#include "vec3.h"

struct material;

struct ray_hit
{
	real t = -1.0;
	vec3 point{};
	vec3 normal{};

	material* material;
};