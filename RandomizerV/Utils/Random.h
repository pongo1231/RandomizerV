#pragma once

#include <random>
#include <time.h>

namespace Random
{
	inline int GetRandomInt(int lower, int upper)
	{
		static std::random_device random_device;
		static std::mt19937 random(random_device());

		std::uniform_int_distribution<> distr(lower, upper);
		return distr(random);
	}
};