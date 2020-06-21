#include "eepch.h"
#include "SceneManager.h"

void ErigonEngine::SceneManager::SetCurrentScene(const Scene& scene)
{
	currentScene = std::make_shared<Scene>(scene);
}

void ErigonEngine::SceneManager::SaveScene()
{
	currentScene->Save();
}

void ErigonEngine::SceneManager::OpenScene()
{
	
}
