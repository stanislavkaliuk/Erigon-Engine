#pragma once
#include "EECS_API.h"
#include "tools/Handle.h"

namespace Erigon
{
	namespace ECS
	{
		using EntityTypeID = typeID;
		using EntityID = Handle64;

		static const EntityID INVALID_ENTITY_ID = Handle64::INVALID_HANDLE;

		class EECS_API IEntity
		{
			friend class EntityManager;
		private:
			ComponentManager* componentManager;
		protected:
			EntityID entityID;
			bool isActive;

		public:
			IEntity();
			virtual ~IEntity();

			template<class T>
			T* GetComponent() const
			{
				return this->componentManager->GetComponent<T>(this->entityID);
			}

			template<class T, class ...P>
			T* AddComponent(P&& ... param)
			{
				return this->componentManager->AddComponent<T>(this - entityID, std::forward<P>(param)...);
			}

			template<class T>
			void RemoveComponent()
			{
				this->componentManager->RemoveComponent<T>(this->entityID);
			}

			template<class T>
			std::map<typeID, T*> GetAllComponents()
			{
				this->componentManager->GetAllComponents<T>(this->entityID);
			}

			inline bool operator==(const IEntity& other) const { return this->entityID == other.entityID; }
			inline bool operator!=(const IEntity& other) const { return this->entityID != other.entityID; }
			inline bool operator==(const IEntity* other) const { return this->entityID == other->entityID; }
			inline bool operator!=(const IEntity* other) const { return this->entityID != other->entityID; }

			virtual const EntityTypeID GetEntityTypeID() const = 0;

			inline const EntityID GetEntityID() const { return this->entityID; }

			void SetActive(bool active);

			inline bool IsActive() const { return this->isActive; }

			virtual void OnEnable() {}
			virtual void OnDisable() {}
		};
	}
}