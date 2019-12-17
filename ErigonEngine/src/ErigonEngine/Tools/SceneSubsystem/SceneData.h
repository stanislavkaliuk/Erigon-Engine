#pragma once
#include <string>
#include <vector>
#include <map>
#include <variant>
namespace ErigonEngine
{
	namespace SceneManagement
	{
		struct GameObjectItem
		{
			std::string name;
			uint32_t gameObjectId;
			std::vector<ComponentItem> componentItems;
		};

		template<class... Types>
		class ComponentParam
		{
		public:
			std::string name;
			Types value;
		};

		using FloatMap = std::map<std::string, float>;
		using IntMap = std::map<std::string, uint32_t>;
		using ComponentParamVector = std::vector<ComponentParam<std::variant<int, std::string, FloatMap, IntMap>>>;

		struct ComponentItem
		{
			std::string name;
			uint32_t componentId;
			ComponentParamVector componentParams;
		};

		class SceneData
		{
		public:
			SceneData(const std::string& filePath);
			void AddSceneItem(const GameObjectItem& item);
			void RemoveSceneItem(const GameObjectItem& item);
			void RemoveSceneItem(const uint32_t id);
			void Save(const std::string& filePath);

			GameObjectItem* GetGameObjectItem(int index)
			{
				if (index < sceneItems.size())
				{
					return &sceneItems[index];
				}

				return nullptr;
			}

			ComponentItem* GetComponentItem(const GameObjectItem& gameobjectItem, std::string& componentName)
			{
				for (auto component : gameobjectItem.componentItems)
				{
					if (component.name == componentName)
					{
						return &component;
					}
				}

				return nullptr;
			}

		private:
			std::vector<GameObjectItem> sceneItems;
		};
	}
}