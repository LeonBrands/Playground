#pragma once
#include <iostream>

#include "real.h"

struct vec3
{
	explicit vec3() = default;
	explicit vec3(const real& pX, const real& pY, const real& pZ);

	const vec3& operator+() const;
	vec3 operator-() const;
	real& operator[](const unsigned int& i);
	real operator[](const unsigned int& i) const;

	vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);
	vec3& operator*=(const vec3& other);
	vec3& operator/=(const vec3& other);

	vec3& operator*=(const real& t);
	vec3& operator/=(const real& t);

	vec3 operator+(const vec3& other) const;
	vec3 operator-(const vec3& other) const;
	vec3 operator*(const vec3& other) const;
	vec3 operator/(const vec3& other) const;

	vec3 operator*(const real& t) const;
	vec3 operator/(const real& t) const;

	[[nodiscard]] real length() const;
	[[nodiscard]] real squared_length() const;
	void normalize();
	[[nodiscard]] vec3 get_normalized() const;

	[[nodiscard]] static vec3 random_unit();
	[[nodiscard]] static vec3 random_disk();

	[[nodiscard]] static vec3 reflect(const vec3& vec, const vec3& normal);
	
	[[nodiscard]] real dot(const vec3& other) const;
	static real dot(const vec3& a, const vec3& b);
	[[nodiscard]] vec3 cross(const vec3& other) const;

	real x = 0;
	real y = 0;
	real z = 0;
};

inline std::istream& operator>>(std::istream& is, vec3& t)
{
	is >> t.x >> t.y >> t.z;
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& t)
{
	os << t.x << " " << t.y << " " << t.z;
	return os;
}

inline vec3 operator*(const real& t, const vec3& v)
{
	return vec3{ v.x * t, v.y * t, v.z * t };
}