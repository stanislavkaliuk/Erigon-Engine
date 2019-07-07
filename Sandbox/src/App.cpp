#include <ErigonEngine.h>


class ExampleLayer : public ErigonEngine::Layer
{
public: 
	ExampleLayer() : Layer("Example"){}
	void OnUpdate() override
	{
		if (ErigonEngine::Input::IsKeyPressed(EE_KEY_TAB))
		{
			EE_INFO("Example layer: Tab pressed (poll)");
		}
	}

	void OnEvent(ErigonEngine::Event& event) override
	{
		//EE_TRACE(event.ToString());
		if (event.GetEventType() == ErigonEngine::EventType::KeyPressed)
		{
			ErigonEngine::KeyPressedEvent& e = (ErigonEngine::KeyPressedEvent&) event;
			if (ErigonEngine::Input::IsKeyPressed(EE_KEY_TAB))
			{
				EE_INFO("Example layer: Tab pressed (poll)");
			}
			EE_TRACE("{0}", (char)e.GetKeyCode());
		}
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