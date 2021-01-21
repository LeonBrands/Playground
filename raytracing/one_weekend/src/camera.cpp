#include "camera.h"
#include <cmath>

#include "random.h"

vec3 random_unit_in_disk()
{
	vec3 p;
	do
	{
		p = 2.0 * vec3(rand01(), rand01(), 0) - vec3(1, 1, 0);
	} while (vec3::dot(p, p) >= 1.0);
	return p;
}

camera::camera()
{
	lower_left_corner = vec3{ -2, -1, -1 };
	horizontal = vec3{ 4, 0, 0 };
	vertical = vec3{ 0, 2, 0 };
	origin = vec3{ 0, 0, 0 };
	lens_radius = 0;
}

camera::camera(const vec3& lookFrom, const vec3& lookAt, const vec3& up, const real& pVFOV, const real& pAspect,
	const real& pAperture, const real& focus_dist)
{
	lens_radius = pAperture / 2.0;
	
	//Calculate directional vectors based on the look position/direction
	w = (lookFrom - lookAt).get_normalized();
	u = vec3::cross(up, w).get_normalized();
	v = vec3::cross(w, u);

	origin = lookFrom;

	//Calculate camera plane, adjust for FOV and focus
	const real theta = pVFOV * PI / 180.0;
	const real half_height = tan(theta / 2.0);
	const real half_width = pAspect * half_height;

	lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
	horizontal = 2 * half_width * focus_dist * u;
	vertical = 2 * half_height * focus_dist * v;
}

ray camera::shoot(const real& s, const real& t) const
{
	const vec3 rd = lens_radius * random_unit_in_disk(); //Calculate a random offset based on the lens_radius
	const vec3 offset = u * rd.x + v * rd.y;
	return ray{ origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset };
}