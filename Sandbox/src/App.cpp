#include "Engine2D.h"
#include <ErigonEngine/Core/EntryPoint.h>

class Sandbox : public ErigonEngine::Application
{
public:
	Sandbox()
	{
		mainLayer = new Engine2D();
		PushLayer(mainLayer);
	}
	~Sandbox()
	{
		PopLayer(mainLayer);
		delete mainLayer;
	}
private:
	Engine2D* mainLayer;
};

ErigonEngine::Application* ErigonEngine::CreateApplication()
{
	return new Sandbox();
}