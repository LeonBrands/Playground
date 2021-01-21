#include <fstream>
#include <progresscpp/ProgressBar.hpp>

#include "real.h"
#include "vec3.h"
#include "random.h"

#include "scene.h"
#include "camera.h"
#include "sphere.h"

#include "ray.h"
#include "material.h"
#include "materials/dielectric.h"
#include "materials/lambertian.h"
#include "materials/metal.h"

scene world;
const unsigned int nbounces = 50;

vec3 color(const ray& r, const hittable* object, const unsigned int depth)
{
	ray_hit hit;
	if (object->hit(r, 0.0001, std::numeric_limits<real>::max(), hit))
	{
		ray scattered;
		vec3 attenuation;

		if (depth < nbounces && hit.material->scatter(r, hit, attenuation, scattered))
		{
			return attenuation * color(scattered, object, depth + 1);
		}
		return vec3{};
	}

	const vec3 unit_direction = r.direction.get_normalized();
	const real t = 0.5 * (unit_direction.y + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

void generate_scene()
{
	world.objects.push_back(std::make_unique<sphere>(vec3{ 0, -1000, -1 }, 1000, std::make_unique<lambertian>(vec3{ 0.5, 0.5, 0.5 })));

	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			const real choose_mat = rand01();
			vec3 center{ a + 0.9 * rand01(), 0.2, b + 0.9 * rand01() };
			if ((center - vec3{ 4, 0.2, 0 }).length() > 0.9)
			{
				if (choose_mat < 0.6) //difuse
				{
					world.objects.push_back(std::make_unique<sphere>(center, 0.2, std::make_unique<lambertian>(vec3(rand01() * rand01(), rand01() * rand01(), rand01() * rand01()))));
				}
				else if (choose_mat < 0.8) //metal
				{
					world.objects.push_back(std::make_unique<sphere>(center, 0.2, std::make_unique<metal>(vec3{ 0.5 * (1 + rand01()), 0.5 * (1 + rand01()), 0.5 * (1 + rand01()) })));
				}
				else //glass
				{
					world.objects.push_back(std::make_unique<sphere>(center, 0.2, std::make_unique<dielectric>(1.5)));
				}
			}
		}
	}

	world.objects.push_back(std::make_unique<sphere>(vec3{ 0, 1, 0 }, 1.0, std::make_unique<dielectric>(1.5)));
	world.objects.push_back(std::make_unique<sphere>(vec3{ -4, 1, 0 }, 1.0, std::make_unique<lambertian>(vec3{ 0.4, 0.2, 0.1 })));
	world.objects.push_back(std::make_unique<sphere>(vec3{ 4, 1, 0 }, 1.0, std::make_unique<metal>(vec3{ 0.7, 0.6, 0.5 }, 0.0)));
}

int main(int argc, char** argv)
{
	std::cout << "Loading scene\n";
	generate_scene();

	std::cout << "Setting up render parameters\n";
	const int nx = 1920;
	const int ny = 1080;
	const int ns = 100;

	std::cout << "Creating camera\n";
	vec3 look_from{ 13, 2, 3 };
	vec3 look_at{ 0, 0, 0 };
	real dist_to_focus = 10.0;
	real aperture = 0.1;

	const camera cam{ look_from, look_at, vec3{ 0, 1, 0 }, 20, real(nx) / real(ny), aperture, dist_to_focus };

	std::cout << "Rendering started\n";
	progresscpp::ProgressBar progress{ ny, 70 };

	std::ofstream stream{ "test.ppm" };
	stream << "P3\n" << nx << " " << ny << "\n255\n";
	for (int y = ny - 1; y >= 0; y--)
	{
		for (int x = 0; x < nx; x++)
		{
			vec3 col{};

			for (int s = 0; s < ns; s++)
			{
				real u = real(x + rand01()) / real(nx);
				real v = real(y + rand01()) / real(ny);

				ray r = cam.shoot(u, v);
				col += color(r, &world, 0);
			}

			col /= ns;
			col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));
			col *= 255.99;
			stream << (int)col.x << " " << (int)col.y << " " << (int)col.z << "\n";
		}

		++progress;
		progress.display();
	}

	progress.done();
	stream.close();
	return 0;
}