#pragma once
#include "../material.h"

/**
 * @brief A material of which rays can move through. The scatter ray may change direction depending on the refraction index.
*/
struct dielectric : material
{
	explicit dielectric(const real& pRefraction);
	
	bool scatter(const ray& ray_in, const ray_hit& hit, vec3& attenuation, ray& scattered) const override;

	/**
	 * @brief Refracts the given vector using the refraction index
	 * @param v The ray direction
	 * @param n The normal of the surface
	 * @param ni_over_nt The refraction index, adjusted for refractions against/through the surface
	 * @param refracted The resulting refracted direction
	 * @return Returns false if the refraction can't be resolved in which case it is actually a perfect reflection
	*/
	[[nodiscard]] bool refract(const vec3& v, const vec3& n, const real& ni_over_nt, vec3& refracted) const;
	/**
	 * @brief Approximates the chance that a ray reflects instead of refracts. This chance becomes increasingly higher towards sharper angles.
	 * @param cosine The angle at which the ray hit the surface
	 * @return Returns the chance that a ray reflects.
	*/
	[[nodiscard]] real schlick(const real& cosine) const;

	real refraction_idx;
};