#include <ErigonEngine.h>
#include <ErigonEngine/Renderer/OpenGL/OpenGLShader.h>
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public ErigonEngine::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f,0.0f,0.0f), m_CameraRotation(0.0f)
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
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
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
			uniform mat4 u_Transform;
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
			uniform mat4 u_Transform;
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

std::string fragmentBlue = R"(
			#version 410
			layout(location = 0) out vec4 color;
			uniform vec4 u_CustomColor;
			void main()
			{
				color = u_CustomColor;
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//glm::vec4 redColor(0.8f, 0.1f, 0.0f, 1.0f);
		glm::vec4 color(m_SquareColor, 1.0f);

		for (int i = 0; i < 5; i++)
		{
			glm::vec3 pos(i * 0.11f, 0.0f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			std::dynamic_pointer_cast<ErigonEngine::OpenGLShader>(m_ShaderBlue)->UploadUniformF4("u_CustomColor", color);
			/*
			if (i % 2 == 0)
			{
				std::dynamic_pointer_cast<ErigonEngine::OpenGLShader>(m_ShaderBlue)->UploadUniformF4("u_CustomColor", (int)deltaTime.GetTimeSinceStart() % 2 == 0.0f ? redColor : blueColor);
			}
			else
			{
				std::dynamic_pointer_cast<ErigonEngine::OpenGLShader>(m_ShaderBlue)->UploadUniformF4("u_CustomColor", (int)deltaTime.GetTimeSinceStart() % 2 == 0.0f ? blueColor : redColor);
			}
			*/		
			ErigonEngine::Renderer::Submit(m_ShaderBlue, m_Square, transform);
		}

		//ErigonEngine::Renderer::Submit(m_Shader, m_VertexArray);

		ErigonEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Color settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_SquareColor),ImGuiColorEditFlags_DisplayRGB);
		ImGui::End();
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
		return false;
	}
private:
	std::shared_ptr<ErigonEngine::Shader> m_Shader;
	std::shared_ptr<ErigonEngine::VertexArray> m_VertexArray;

	std::shared_ptr<ErigonEngine::Shader> m_ShaderBlue;
	std::shared_ptr<ErigonEngine::VertexArray> m_Square;

	ErigonEngine::OrtographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraSpeed = 5.f;
	float m_CameraRotationSpeed = 30.0f;

	glm::vec3 m_SquareColor = { 0.2f,0.3f,0.8f };
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