#include <ErigonEngine.h>


class ExampleLayer : public ErigonEngine::Layer
{
public: 
	ExampleLayer() : Layer("Example"){}
	void OnUpdate() override
	{
		EE_INFO("Example layer::Update");
	}

	void OnEvent(ErigonEngine::Event& event) override
	{
		EE_TRACE(event.ToString());
	}
};


class Sandbox : public ErigonEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ErigonEngine::ImGUILayer());
	}
	~Sandbox()
	{

	}
};


ErigonEngine::Application* ErigonEngine::CreateApplication()
{
	return new Sandbox();
}