#pragma once
#include "Vector3.h"
#include <EECS.h>

namespace ErigonEngine
{
	class Transform : public Erigon::ECS::Component<Transform>
	{
	public:
		Transform() : position(Vector3::Zero()), scale(Vector3::One()) {}
		Transform(const Vector3& pos, const Vector3& scale) : position(pos), scale(scale) {}
		virtual ~Transform() {}

	public:
		Vector3 position;
		Vector3 scale;
	};
}