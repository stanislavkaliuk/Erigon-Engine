#include <ErigonEngine.h>
#include "imgui/imgui.h"

class ExampleLayer : public ErigonEngine::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0.0f,0.0f,0.0f), m_CameraRotation(0.0f)
	{
		m_VertexArray.reset(ErigonEngine::VertexArray::Create());

		float vertices[9]
		{
		   -0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		std::shared_ptr<ErigonEngine::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(ErigonEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		ErigonEngine::BufferLayout inputBufferLayout = {
			{ErigonEngine::ShaderDataType::Float3, "a_Position"}
		};
		m_VertexBuffer->SetLayout(inputBufferLayout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indicies[3] = { 0, 1, 2 };
		std::shared_ptr<ErigonEngine::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(ErigonEngine::IndexBuffer::Create(indicies, sizeof(indicies)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_Square.reset(ErigonEngine::VertexArray::Create());

		float squareVert[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<ErigonEngine::VertexBuffer> squareVB;
		squareVB.reset(ErigonEngine::VertexBuffer::Create(squareVert, sizeof(squareVert)));
		squareVB->SetLayout({ {ErigonEngine::ShaderDataType::Float3, "a_Position"} });
		m_Square->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<ErigonEngine::IndexBuffer> squareIB;
		squareIB.reset(ErigonEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
		m_Square->SetIndexBuffer(squareIB);


		std::string vertex = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragment = R"(
			#version 410
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";


		std::string vertexBlue = R"(
			#version 410
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_ShaderBlue.reset(ErigonEngine::Shader::Create(vertexBlue, fragmentBlue));
		m_Shader.reset(ErigonEngine::Shader::Create(vertex, fragment));
	}

	void OnUpdate(ErigonEngine::Timestep deltaTime) override
	{
		EE_TRACE("Delta time: {0} ({1}ms)", deltaTime.GetSeconds(), deltaTime.GetMilliseconds());
		CheckKeyPress(deltaTime);

		ErigonEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		ErigonEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		ErigonEngine::Renderer::BeginScene(m_Camera);

		ErigonEngine::Renderer::Submit(m_ShaderBlue, m_Square);

		ErigonEngine::Renderer::Submit(m_Shader, m_VertexArray);

		ErigonEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(ErigonEngine::Event& event) override
	{
		ErigonEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<ErigonEngine::KeyPressedEvent>(EE_BIND_EVENT(ExampleLayer::OnKeyPressedEvent));
	}

	void CheckKeyPress(float deltaTime)
	{
		if (ErigonEngine::Input::IsKeyPressed(EE_KEY_A))
		{
			m_CameraPosition.x -= m_CameraSpeed * deltaTime;
		}

		if (ErigonEngine::Input::IsKeyPressed(EE_KEY_D))
		{
			m_CameraPosition.x += m_CameraSpeed * deltaTime;
		}

		if (ErigonEngine::Input::IsKeyPressed(EE_KEY_W))
		{
			m_CameraPosition.y += m_CameraSpeed * deltaTime;
		}

		if (ErigonEngine::Input::IsKeyPressed(EE_KEY_S))
		{
			m_CameraPosition.y -= m_CameraSpeed * deltaTime;
		}

		if (ErigonEngine::Input::IsKeyPressed(EE_KEY_R))
		{
			m_CameraRotation += m_CameraRotationSpeed * deltaTime;
		}
		if (ErigonEngine::Input::IsKeyPressed(EE_KEY_T))
		{
			m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
		}
	}

	bool OnKeyPressedEvent(ErigonEngine::KeyPressedEvent& event)
	{
		/*
		if (event.GetKeyCode() == EE_KEY_A)
		{
			m_CameraPosition.x -= m_CameraSpeed;
		}

		if (event.GetKeyCode() == EE_KEY_D)
		{
			m_CameraPosition.x += m_CameraSpeed;
		}

		if (event.GetKeyCode() == EE_KEY_W)
		{
			m_CameraPosition.y += m_CameraSpeed;
		}

		if (event.GetKeyCode() == EE_KEY_S)
		{
			m_CameraPosition.y -= m_CameraSpeed;
		}*/

		return false;
	}
private:
	std::shared_ptr<ErigonEngine::Shader> m_Shader;
	std::shared_ptr<ErigonEngine::Shader> m_ShaderBlue;
	std::shared_ptr<ErigonEngine::VertexArray> m_VertexArray;
	std::shared_ptr<ErigonEngine::VertexArray> m_Square;

	ErigonEngine::OrtographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraSpeed = 5.f;
	float m_CameraRotationSpeed = 30.0f;
};


class Sandbox : public ErigonEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};


ErigonEngine::Application* ErigonEngine::CreateApplication()
{
	return new Sandbox();
}