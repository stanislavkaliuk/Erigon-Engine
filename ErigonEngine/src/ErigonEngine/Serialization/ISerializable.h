#pragma once
#include <yaml-cpp/yaml.h>

namespace ErigonEngine
{
	class ISerializable
	{
	public:
		virtual void Serialize(YAML::Node* node) = 0;
		virtual void Serialize(YAML::Emitter* emitter) = 0;
		virtual void Deserialize(const YAML::Node& node) = 0;
	};
}