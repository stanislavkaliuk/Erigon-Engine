#pragma once

#include <cstdlib>
#include <ctime>

namespace ErigonEngine
{
	struct SystemRandom
	{
		SystemRandom()
		{
			srand((unsigned int)time(NULL));
		}

		template<typename T>

		static T Range(const T min, const T max)
		{
			return (T)((double)rand() / RAND_MAX * (max - min) + min);
		}

		static SystemRandom Random;
	};
}