#pragma once
#include "EECS_API.h"

namespace Erigon
{
	namespace ECS
	{
		class EECS_API Timer
		{
			using Elapsed = std::chrono::duration<float32, std::milli>;

		private:
			Elapsed elapsed;
		public:
			Timer();
			~Timer();

			void Tick(float ms);
			void Reset();
			inline TimeStamp GetTimeStamp() const
			{
				return TimeStamp(this->elapsed.count());
			}
		};
	}
}