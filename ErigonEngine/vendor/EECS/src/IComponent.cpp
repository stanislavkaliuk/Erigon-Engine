#include "IComponent.h"

namespace Erigon
{
	namespace ECS
	{
		IComponent::IComponent() : owner(INVALID_ENTITY_ID), enabled(true) {}
		IComponent::~IComponent() {}
	}
}