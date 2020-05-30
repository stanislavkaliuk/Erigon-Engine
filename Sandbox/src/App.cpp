#include "Engine2D.h"
#include <ErigonEngine/Core/EntryPoint.h>
#include "EditorLayer.h"

class Sandbox : public ErigonEngine::Application
{
public:
	Sandbox()
	{
		mainLayer = new Engine2D();
		editorLayer = new EditorLayer();
		PushLayer(mainLayer);
		PushOverlay(editorLayer);
	}
	~Sandbox()
	{
		PopOverlay(editorLayer);
		PopLayer(mainLayer);
		delete editorLayer;
		delete mainLayer;
	}
private:
	Engine2D* mainLayer;
	EditorLayer* editorLayer;
};

ErigonEngine::Application* ErigonEngine::CreateApplication()
{
	return new Sandbox();
}