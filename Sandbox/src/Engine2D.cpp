#include "Engine2D.h"
#include "ErigonEngine/Renderer/OpenGL/OpenGLShader.h"
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Engine2D::Engine2D() : Layer("2D Engine"), m_CameraController(1280.0f/720.0f)
{

}

void Engine2D::OnAttach()
{
	m_VertexArray = ErigonEngine::VertexArray::Create();
	float vertices[5*4]
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	ErigonEngine::Ref<ErigonEngine::VertexBuffer> m_VertexBuffer;
	m_VertexBuffer = ErigonEngine::VertexBuffer::Create(vertices, sizeof(vertices));

	ErigonEngine::BufferLayout inputBufferLayout = 
	{
		{ErigonEngine::ShaderDataType::Float3, "a_Position"},
		{ErigonEngine::ShaderDataType::Float2, "a_TexCoord"}
	};

	m_VertexBuffer->SetLayout(inputBufferLayout);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	uint32_t indicies[6] = { 0, 1, 2, 2, 3, 0 };
	ErigonEngine::Ref<ErigonEngine::IndexBuffer> m_IndexBuffer;
	m_IndexBuffer = ErigonEngine::IndexBuffer::Create(indicies, sizeof(indicies));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	m_Shader = m_ShaderLibrary.Load("assets/shaders/Texture.egl");
	m_Texture = ErigonEngine::Texture2D::Create("assets/textures/texture2.png");

	std::dynamic_pointer_cast<ErigonEngine::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<ErigonEngine::OpenGLShader>(m_Shader)->UploadUniformI("u_Texture", 0);
	
}

void Engine2D::OnDetach()
{

}

void Engine2D::OnUpdate(ErigonEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	ErigonEngine::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
	ErigonEngine::RenderCommand::Clear();

	ErigonEngine::Renderer::BeginScene(m_CameraController.GetCamera());
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
	m_Texture->Bind(0);
	ErigonEngine::Renderer::Submit(m_Shader, m_VertexArray, scale);

	ErigonEngine::Renderer::EndScene();
}

void Engine2D::OnImGuiRender()
{
	ImGui::Begin("Camera Transform");
	const glm::vec3 vecPosition = m_CameraController.GetCamera().GetPosition();
	float position[3] = { vecPosition.x, vecPosition.y, vecPosition.z };
	ImGui::DragFloat3("Position", position);
	float value = m_CameraController.GetCamera().GetRotation();
	ImGui::DragFloat("Rotation", &value);
	ImGui::End();
}

void Engine2D::OnEvent(ErigonEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
