#include <fstream>
#include <progresscpp/ProgressBar.hpp>

#include "real.h"
#include "vec3.h"
#include "random.h"

#include "config.h"

#include "scene.h"
#include "camera.h"
#include "hittables/sphere.h"

#include "ray.h"
#include "materials/dielectric.h"
#include "materials/emissive.h"
#include "materials/lambertian.h"
#include "materials/metal.h"

scene generate_scene()
{
	auto world = scene{};
	
	//"ground" sphere
	world.objects.push_back(std::make_unique<sphere>(vec3{ 0, -1000, -1 }, 1000, std::make_unique<lambertian>(vec3{ 0.5, 0.5, 0.5 })));

	const int spawn_range = 11;
	const real spawn_radius = 0.2;
	for (int a = -spawn_range; a < spawn_range; a++)
	{
		for (int b = -spawn_range; b < spawn_range; b++)
		{
			const real choose_mat = rand01();
			vec3 center{ a + 0.9 * rand01(), 0.2, b + 0.9 * rand01() };
			if ((center - vec3{ 4, 0.2, 0 }).length() > 0.9)
			{
				if (choose_mat < 0.6) //difuse
				{
					world.objects.push_back(std::make_unique<sphere>(center, spawn_radius, std::make_unique<lambertian>(vec3(rand01() * rand01(), rand01() * rand01(), rand01() * rand01()))));
				}
				else if (choose_mat < 0.8) //metal
				{
					world.objects.push_back(std::make_unique<sphere>(center, spawn_radius, std::make_unique<metal>(vec3{ 0.5 * (1 + rand01()), 0.5 * (1 + rand01()), 0.5 * (1 + rand01()) })));
				}
				else if (choose_mat < 0.9)
				{
					world.objects.push_back(std::make_unique<sphere>(center + vec3(0, 0.3, 0), 0.2, std::make_unique<emissive>(vec3{ 1, 1, 1 }, 5)));
				}
				else //glass
				{
					world.objects.push_back(std::make_unique<sphere>(center, spawn_radius, std::make_unique<dielectric>(1.5)));
				}
			}
		}
	}

	//A few bigger manual central pieces
	world.objects.push_back(std::make_unique<sphere>(vec3{ 0, 1, 0 }, 1.0, std::make_unique<dielectric>(1.5)));
	world.objects.push_back(std::make_unique<sphere>(vec3{ -4, 1, 0 }, 1.0, std::make_unique<lambertian>(vec3{ 0.4, 0.2, 0.1 })));
	world.objects.push_back(std::make_unique<sphere>(vec3{ 4, 1, 0 }, 1.0, std::make_unique<metal>(vec3{ 0.7, 0.6, 0.5 }, 0.0)));

	return world;
}

int main(int argc, char** argv)
{
	scene world = generate_scene();
	const camera cam{ LOOK_FROM, LOOK_AT, CAM_UP, VFOV, real(NX) / real(NY), APERTURE , DIST_TO_FOCUS };

	progresscpp::ProgressBar progress{ NY, 70 };

	std::ofstream stream{ "output.ppm" };
	stream << "P3\n" << NX << " " << NY << "\n255\n";
	for (int y = NY - 1; y >= 0; y--) //inverse Y
	{
		for (int x = 0; x < NX; x++)
		{
			//Calculate the average color across a number (NS) of random samples within the pixel's area
			vec3 col{};
			for (int s = 0; s < NS; s++)
			{
				//Generate ray with random offset
				real u = real(x + rand01()) / real(NX);
				real v = real(y + rand01()) / real(NY);

				ray r = cam.shoot(u, v);
				col += r.color(&world, 0);
			}

			//Average
			col /= NS;
			//Gamma correction
			col = vec3(sqrt(col.x), sqrt(col.y), sqrt(col.z));

			//Convert to 256 based integer colors and write to stream
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