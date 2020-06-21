#pragma once
#include <vector>
#include <EECS_Controller.hpp>
#include "ErigonEngine/ECS/Enitites/GameObject.h"
#include "ErigonEngine/Serialization/ISerializable.h"

namespace ErigonEngine 
{
	class Scene : public ISerializable
	{
	public:
		void Add(GameObject* object) { objects.push_back(object); };
		void Remove(GameObject* object) { objects.erase(std::find(objects.begin(), objects.end(), object)); };
		std::vector <GameObject*> GetAllObjects() {
			return objects;
		}

		void Save();
		static Ref<Scene> CreateScene();
		static Ref<Scene> OpenScene(const char* path);
	protected:
		virtual void Serialize(YAML::Node* node) override {};
		virtual void Serialize(YAML::Emitter* emitter) override {};
		virtual void Deserialize(const YAML::Node& node) override {};
	private:
		std::vector<GameObject*> objects;
	};
}
