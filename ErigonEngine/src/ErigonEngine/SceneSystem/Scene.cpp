#include "eepch.h"
#include "Scene.h"

namespace  ErigonEngine
{
    void Scene::Save()
    {
        for each (GameObject* gameObject in objects)
        {
            
        }
    }

    Ref<Scene> Scene::CreateScene()
    {
        return Ref<Scene>(new Scene());
    }

    Ref<Scene> Scene::OpenScene(const char* path)
    {
        return Ref<Scene>();
    }
}