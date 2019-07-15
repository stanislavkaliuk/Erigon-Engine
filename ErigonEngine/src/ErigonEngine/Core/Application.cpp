#include "eepch.h"
#include "Application.h"
#include "ErigonEngine/Log/Log.h"
#include "ErigonEngine/Input/Input.h"
#include "ErigonEngine/Renderer/Renderer.h"

namespace ErigonEngine
{

#define BIND_EVENT(x) std::bind(&x, this,std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		EE_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<IWindow>(IWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));

		m_ImGuiLayer = new ImGUILayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[9]
		{
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


		BufferLayout inputBufferLayout = {
			{ShaderDataType::Float3, "a_Position"}
		};

		m_VertexBuffer->SetLayout(inputBufferLayout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indicies[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indicies, sizeof(indicies)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Square.reset(VertexArray::Create());

		float squareVert[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVert, sizeof(squareVert)));
		squareVB->SetLayout({ {ShaderDataType::Float3, "a_Position"} });
		m_Square->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
		m_Square->SetIndexBuffer(squareIB);

		std::string fragment = R"(
			#version 410
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		std::string vertex = R"(
			#version 410
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentBlue = R"(
			#version 410
			layout(location = 0) out vec4 color;
			void main()
			{
				color = vec4(0.8f,0.2f,0.4f,1.0f);
			}
		)";

		std::string vertexBlue = R"(
			#version 410
			layout(location = 0) in vec3 a_Position;
			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		m_ShaderBlue.reset(new Shader(vertexBlue, fragmentBlue));
		m_Shader.reset(new Shader(vertex, fragment));
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClosed));
		//EE_CORE_INFO(e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
			RenderCommand::Clear();

			Renderer::BeginScene();
			
			m_ShaderBlue->Bind();
			Renderer::Submit(m_Square);

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}