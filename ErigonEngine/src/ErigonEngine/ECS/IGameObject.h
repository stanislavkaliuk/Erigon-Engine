#pragma once
#include "ErigonEngine/Serialization/ISerializable.h"

namespace ErigonEngine
{
	class IGameObject : public ISerializable
	{
	protected:
		virtual void Serialize() = 0;
	};
}