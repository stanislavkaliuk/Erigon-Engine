#pragma once
#include <string>
#include <vector>

struct SceneItem
{
	std::string name;
	uint32_t gameObjectId;
	std::vector<uint32_t> componentIds;
};


class SceneData
{
public:
	void AddSceneItem(const SceneItem& item);
	void RemoveSceneItem(const SceneItem& item);
	void RemoveSceneItem(const uint32_t id);

private:
	std::vector<SceneItem> sceneItems;
};