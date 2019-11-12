#include "IEntity.h"

namespace Erigon
{
	namespace ECS
	{
		IEntity::IEntity() :isActive(true) {}
		IEntity::~IEntity() {}

		void IEntity::SetActive(bool active)
		{
			if (this->isActive == active)
			{
				return;
			}

			if (!active)
			{
				this->OnDisable();
			}
			else
			{
				this->OnEnable();
			}
			this->isActive = true;
		}
	}
}