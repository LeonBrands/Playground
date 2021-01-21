#pragma once
#include "ray.h"
#include "ray_hit.h"

/**
 * @brief The base class for all objects that can be hit by a ray.
*/
struct hittable
{
	virtual ~hittable() = default;

	/**
	 * @brief Test the given ray against this object to see if it hits.
	 * @param r The ray to test.
	 * @param t_min The minimum distance the ray must travel. If the ray hits before t_min then it won't apply.
	 * @param t_max The maximum distance the ray can travel. If the ray hits beyond t_max then it won't apply.
	 * @param hit The resulting hit information.
	 * @return Returns true if the hittable was hit by the ray, false if that isn't the case.
	*/
	virtual bool hit(const ray& r, const real& t_min, const real& t_max, ray_hit& hit) const = 0;
};