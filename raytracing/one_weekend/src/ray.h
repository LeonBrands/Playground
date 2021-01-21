#pragma once
#include "vec3.h"

struct ray
{
	explicit ray() = default;
	explicit ray(const vec3& pOrigin, const vec3& pDirection);

	[[nodiscard]] vec3 point(const real& t) const;

	vec3 origin{};
	vec3 direction{};
};