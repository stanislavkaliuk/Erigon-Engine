#include "tools/TypeID.h"

namespace Erigon
{
	namespace ECS
	{
		class IEntity;
		class IComponent;
		class ISystem;

		uint64 TypeID<IEntity>::count = 0u;
		uint64 TypeID<IComponent>::count = 0u;
		uint64 TypeID<ISystem>::count = 0u;

		template class TypeID<IEntity>;
		template class TypeID<IComponent>;
		template class TypeID<ISystem>;
	}
}