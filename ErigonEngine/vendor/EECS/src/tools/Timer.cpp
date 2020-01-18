#include "tools/Timer.h"

namespace Erigon
{
	namespace ECS
	{
		Timer::Timer() :elapsed(0) {}
		Timer::~Timer() {}

		void Timer::Tick(float ms)
		{
			this->elapsed += std::chrono::duration<float, std::ratio<1, 1000>>(ms);
		}

		void Timer::Reset()
		{
			this->elapsed = Elapsed::zero();
		}
	}
}