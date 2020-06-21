#pragma once
#include "Scene.h"

namespace ErigonEngine
{
	class SceneManager
	{
	public:
		void SetCurrentScene(const Scene& scene);
		void SaveScene();
		void OpenScene();
	private:
		std::shared_ptr<Scene> currentScene;
	};
}