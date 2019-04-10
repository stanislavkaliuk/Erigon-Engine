#include <ErigonEngine.h>

class Sandbox : public ErigonEngine::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};


ErigonEngine::Application* ErigonEngine::CreateApplication()
{
	return new Sandbox();
}