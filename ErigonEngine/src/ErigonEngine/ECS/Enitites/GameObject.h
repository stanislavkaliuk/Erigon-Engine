#pragma once
#include "ErigonEngine/Serialization/ISerializable.h"
#include "ErigonEngine/ECS/ECSController.h"
#include <EECS_Controller.hpp>
#include <any>

namespace ErigonEngine
{
	class GameObject : public ISerializable
	{
	public:
		GameObject() {}
		GameObject(::ECS::Entity entity, std::initializer_list<std::any> components);
		~GameObject() = default;
	protected:
		virtual void Serialize(YAML::Node* node) override {};
		virtual void Serialize(YAML::Emitter* emitter) override {};
		virtual void Deserialize(const YAML::Node& node) override {};
	private:
	private:
		::ECS::Entity connectedEntity;
		std::list<std::any> connectedComponents;
	};
}