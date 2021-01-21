#pragma once
#include "ray.h"
#include "vec3.h"

/**
 * @brief The camera class defines the renderer's view. It specifies from where the image is taken and into what direction. The camera class also defines the renderer's fov, aspect ratio and aperture/focus for depth of field calculations.
 *
 * The camera uses all this information to calculate the direction of the rays that are shot out.
*/
struct camera
{
	camera();
	camera(const vec3& lookFrom, const vec3& lookAt, const vec3& up, const real& pVFOV, const real& pAspect, const real& pAperture, const real& focus_dist);

	/**
	 * Calculate a ray based on where on the screen the ray is supposed to originate.
	 */
	[[nodiscard]] ray shoot(const real& s, const real& t) const;

	vec3 origin;

	//camera plane
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;

	vec3 u; //camera plane world right
	vec3 v; //camera plane world up
	vec3 w; //camera backwards direction

	real lens_radius; //aperture/2
};