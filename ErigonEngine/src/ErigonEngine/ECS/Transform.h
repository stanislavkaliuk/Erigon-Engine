#pragma once
#include "ErigonEngine/Tools/Vector3.h"
#include "IComponent.h"
#include <EECS.h>

namespace ErigonEngine
{
	class Transform : public Erigon::ECS::Component<Transform>, IComponent
	{
	public:
		Transform() : position(Vector3::Zero()), scale(Vector3::One()) {}
		Transform(const Vector3& pos, const Vector3& scale) : position(pos), scale(scale) {}
		virtual ~Transform() {}

		void Serialize(YAML::Node* node) override;
		void Serialize(YAML::Emitter* emitter) override;
		void Deserialize(const YAML::Node& node) override;

	public:
		Vector3 position;
		Vector3 scale;
	};
}