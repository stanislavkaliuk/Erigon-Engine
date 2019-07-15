#include "eepch.h"
#include "Application.h"
#include "ErigonEngine/Log/Log.h"
#include "ErigonEngine/Input/Input.h"
#include "ErigonEngine/Renderer/Buffer.h"
#include <glad/glad.h>

namespace ErigonEngine
{

#define BIND_EVENT(x) std::bind(&x, this,std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ErigonEngine::ShaderDataType::Float:  return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Float2: return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Float3: return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Float4: return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Mat3:   return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Mat4:   return GL_FLOAT;
			case ErigonEngine::ShaderDataType::Int:	   return GL_INT;
			case ErigonEngine::ShaderDataType::Int2:   return GL_INT;
			case ErigonEngine::ShaderDataType::Int3:   return GL_INT;
			case ErigonEngine::ShaderDataType::Int4:   return GL_INT;
			case ErigonEngine::ShaderDataType::Bool:   return GL_BOOL;
		}
	}
	Application::Application()
	{
		EE_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<IWindow>(IWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT(Application::OnEvent));

		m_ImGuiLayer = new ImGUILayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[9]
		{
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout inputBufferLayout = {
			{ShaderDataType::Float3, "a_Position"}
		};

		m_VertexBuffer->SetLayout(inputBufferLayout);

		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.Offset);
			index++;
		}

		uint32_t indicies[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indicies, sizeof(indicies)));

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
			glClearColor(0.1f, 0.1f, 0.1f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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