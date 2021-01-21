#include "scene.h"

bool scene::hit(const ray& r, const real& t_min, const real& t_max, ray_hit& hit) const
{
	ray_hit temp;
	bool result = false;

	real closest = t_max;
	for (const auto& object : objects)
	{
		if (object->hit(r, t_min, closest, temp))
		{
			result = true;
			closest = temp.t;
			hit = temp;
		}
	}

	return result;
}