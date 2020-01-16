#include "Engine2D.h"
#include <ErigonEngine/Core/EntryPoint.h>

class Sandbox : public ErigonEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new Engine2D());
	}
	~Sandbox()
	{

	}
};

ErigonEngine::Application* ErigonEngine::CreateApplication()
{
	return new Sandbox();
}