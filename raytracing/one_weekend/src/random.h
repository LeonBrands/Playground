#pragma once
#include <random>

#include "real.h"

[[nodiscard]] static real rand01()
{
	std::random_device rd;
	std::mt19937 m(rd());
	const std::uniform_real_distribution<real> distribution(0.0, 1.0);
	return distribution(m);
}