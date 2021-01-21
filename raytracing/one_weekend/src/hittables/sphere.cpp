#include "sphere.h"

sphere::sphere(const vec3& pCenter, const real& pRadius, std::unique_ptr<material> pMaterial) : center(pCenter), radius(pRadius), mat(std::move(pMaterial))
{

}

bool sphere::hit(const ray& r, const real& t_min, const real& t_max, ray_hit& hit) const
{
	//R: radius
	//Equation to check if position P is exactly on a sphere is P.x*P.x + P.y*P.y + P.z*P.z = R * R
	//If sphere is centered at center C, the equation becomes (P.x-C.x)*(P.x-C.x) + (P.y-C.y)*(P.y-C.y) + (P.z-C.z)*(P.z-C.z) = R * R
	//This is equivalent to dot(P - C, P - C) = R * R

	//To find if the ray hits the sphere, we can describe P as a function of t, thus:
	//dot(P(t) - C, P(t) - C) = R * R
	//P is a function that calculates any point along the ray for t (where O is the ray's origin and D is the ray's direction):
	//P(t) = O + t * D
	//Thus after expanding P(t), the formula becomes:
	//dot((O + t*D - C), (O + t*D - C)) = R * R
	//t^​2 * dot(D, D) + t * 2 * dot(D, O-C) + dot(O-C, O-C) - R * R = 0

	//This is a quadratic equation and thus can be solved by calculating the discriminant (b^2 - 4ac)
	//If the discriminant is more than 0 then the ray passes through the sphere twice

	const vec3 oc = r.origin - center; //pre-calculate O - C since it's a recurring calculations

	const real a = vec3::dot(r.direction, r.direction); //a = dot(D, D)
	const real b = vec3::dot(oc, r.direction); //b = 2 * dot(D, O-C)
	const real c = vec3::dot(oc, oc) - radius * radius; //c = dot(O-C, O-C) - R * R

	const real discriminant = b * b - a * c;

	//no hit
	if (discriminant <= 0)
	{
		hit.t = -1.0;
		return false;
	}

	//The quadratic equation has 2 possible points that it can resolve
	//Since t_min and t_max might invalidate either, it's important to check both
	
	real temp = (-b - sqrt(b * b - a * c)) / a;
	if (temp < t_max && temp > t_min)
	{
		hit.t = temp;
		hit.point = r.point(hit.t);
		hit.normal = (hit.point - center) / radius;
		hit.material = mat.get();
		return true;
	}
	temp = (-b + sqrt(b * b - a * c)) / a;
	if (temp < t_max && temp > t_min)
	{
		hit.t = temp;
		hit.point = r.point(hit.t);
		hit.normal = (hit.point - center) / radius;
		hit.material = mat.get();
		return true;
	}

	hit.t = -1.0;
	return false;
}