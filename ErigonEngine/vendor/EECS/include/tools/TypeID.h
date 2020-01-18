#pragma once

#include "../EECS_API.h"

namespace Erigon
{
	namespace ECS
	{
		template<class T>
		class EECS_API TypeID
		{
			static typeID count;
		public:
			template<class U>
			static const typeID Get()
			{
				static const typeID STATIC_TYPE_ID{ count++ };
				return STATIC_TYPE_ID;
			}

			static const typeID Get()
			{
				return count;
			}
		};
	}
}