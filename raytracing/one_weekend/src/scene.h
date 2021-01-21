#pragma once
#include <vector>
#include <memory>

#include "hittable.h"

/**
 * Describes all the objects that exist in the scene, and a helper function to ray test against them
 */
struct scene : hittable
{
	std::vector<std::unique_ptr<hittable>> objects;

	/**
	 * @brief Test the given ray against all the objects in the scene to find a hit.
	 * @param r The ray to cast
	 * @param t_min The minimum distance the ray must've traveled
	 * @param t_max The maximum distance the ray can travel
	 * @param hit The resulting raycast hit information
	 * @return A boolean, true if a hit was detected, false if no hit was detected.
	*/
	bool hit(const ray& r, const real& t_min, const real& t_max, ray_hit& hit) const override;
};