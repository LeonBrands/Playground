#include "vec3.h"
#include "random.h"

#include <cmath>

vec3::vec3(const real& pX, const real& pY, const real& pZ) : x(pX), y(pY), z(pZ)
{

}

const vec3& vec3::operator+() const
{
	return *this;
}

vec3 vec3::operator-() const
{
	return vec3{ -x, -y, -z };
}

real& vec3::operator[](const unsigned& i)
{
	switch (i)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: throw;
	}
}

real vec3::operator[](const unsigned& i) const
{
	switch (i)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: throw;
	}
}

vec3& vec3::operator+=(const vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

vec3& vec3::operator-=(const vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

vec3& vec3::operator*=(const vec3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

vec3& vec3::operator/=(const vec3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.y;
	return *this;
}

vec3& vec3::operator*=(const real& t)
{
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

vec3& vec3::operator/=(const real& t)
{
	x /= t;
	y /= t;
	z /= t;
	return *this;
}

vec3 vec3::operator+(const vec3& other) const
{
	return vec3{ x + other.x, y + other.y, z + other.z };
}

vec3 vec3::operator-(const vec3& other) const
{
	return vec3{ x - other.x, y - other.y, z - other.z };
}

vec3 vec3::operator*(const vec3& other) const
{
	return vec3{ x * other.x, y * other.y, z * other.z };
}

vec3 vec3::operator/(const vec3& other) const
{
	return vec3{ x / other.x, y / other.y, z / other.y };
}

vec3 vec3::operator*(const real& t) const
{
	return vec3{ x * t, y * t, z * t };
}

vec3 vec3::operator/(const real& t) const
{
	return vec3{ x / t, y / t, z / t };
}

real vec3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

real vec3::squared_length() const
{
	return x * x + y * y + z * z;
}

void vec3::normalize()
{
	operator/=(length());
}

vec3 vec3::get_normalized() const
{
	vec3 vec = *this;
	vec.normalize();
	return vec;
}

vec3 vec3::random_unit()
{
	return vec3{ 2 * rand01() - 1, 2 * rand01() - 1, 2 * rand01() - 1 }.get_normalized();
}

vec3 vec3::reflect(const vec3& vec, const vec3& normal)
{
	return vec - 2 * dot(vec, normal) * normal;
}

real vec3::dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3::cross(const vec3& a, const vec3& b)
{
	return vec3{ (a.y * b.z - a.z * b.y),
				 (-(a.x * b.z - a.z * b.x)),
				 (a.x * b.y - a.y * b.x) };
}
