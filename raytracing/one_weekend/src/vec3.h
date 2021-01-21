#pragma once
#include <iostream>

#include "real.h"

#define PI 3.141592653589793238462643383279502884L

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

	/**
	 * The length of the vector
	 * Uses sqrt and is thus a heavy calculation -> be mindful
	 */
	[[nodiscard]] real length() const;
	/**
	 * The squared length of the vector
	 * Useful in range comparisons, doesn't use sqrt
	 */
	[[nodiscard]] real squared_length() const;

	/**
	 * Rescales the vector so that length() == 1.
	 * Preserves its direction.
	 */
	void normalize();
	/**
	 * Returns a normalized copy of the vector.
	 */
	[[nodiscard]] vec3 get_normalized() const;

	/**
	 * Returns a normalized vector with a random direction.
	 */
	[[nodiscard]] static vec3 random_unit();

	/**
	 * Reflects the given vector using the normal.
	 * r = d - 2 * dot(d, n) * n
	 * Where n has to be a normalized vector.
	 */
	[[nodiscard]] static vec3 reflect(const vec3& vec, const vec3& normal);

	/**
	 * Calculate the dot product between vector a and b.
	 */
	static real dot(const vec3& a, const vec3& b);

	/**
	 * Calculate the cross product from vector a and b
	 */
	static vec3 cross(const vec3& a, const vec3& b);

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