#include "ISystem.h"

namespace Erigon
{
	namespace ECS
	{
		ISystem::ISystem(SystemPriority priority, float32 updateInterval_ms) : priority(priority), updateInterval(updateInterval_ms), enabled(true) {}
		ISystem::~ISystem() {}
	}
}