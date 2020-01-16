#pragma once
#include "EECS_API.h"
#include "ISystem.h"
#include "tools/TypeID.h"

namespace Erigon
{
	namespace ECS
	{
		template<class T>
		class System : public ISystem
		{
			friend class SystemManager;

		private:
			SystemManager* systemManager;

		public:
			static const SystemTypeID SYSTEM_TYPE_ID;

		protected:
			System() {}

		public:
			virtual ~System() {}
			virtual inline const SystemTypeID GetSystemTypeID() const override { return SYSTEM_TYPE_ID; }

			template<class... Dependencies>
			void AddDependencies(Dependencies&&... dependencies)
			{
				this->systemManager->AddSystemDependency(this, std::forward<Dependencies>(dependencies)...);
			}

			virtual void PreUpdate(float32 deltaTime) override {}
			virtual void Update(float32 deltaTime) override {}
			virtual void PostUpdate(float32 deltaTime) override {}
		};

		template<class T>
		const SystemTypeID System<T>::SYSTEM_TYPE_ID = TypeID<ISystem>::Get<T>();
	}
}