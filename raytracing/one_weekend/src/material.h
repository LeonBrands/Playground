#pragma once
#include "ray.h"
#include "hittable.h"

/**
 * Base class for materials.
 * A material defines how an object interacts with rays through its scatter function.
 */
struct material
{
	virtual ~material() = default;

	/**
	 * @brief The scatter function defines how the object interacts with rays. It takes a given ray and scattes the ray in whichever way it desires.
	 * @param ray_in The incoming ray.
	 * @param hit The hit information, important for e.g. the hit's normal or the hit's point.
	 * @param attenuation The function sets this value to whatever the material's natural color/output is.
	 * @param scattered The scattered/outgoing ray calculated by this function.
	 * @return Returns true if the ray scatters further, returns false if nothing happens.
	*/
	virtual bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const = 0;
};