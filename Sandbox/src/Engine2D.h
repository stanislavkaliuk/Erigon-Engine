#pragma once
#include "ErigonEngine.h"

class Engine2D : public ErigonEngine::Layer
{
public:
	Engine2D();
	virtual ~Engine2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(ErigonEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ErigonEngine::Event& e) override;

private:
	ErigonEngine::OrthographicCameraController m_CameraController;
	ErigonEngine::ShaderLibrary m_ShaderLibrary;
	ErigonEngine::Ref<ErigonEngine::VertexArray> m_VertexArray;
	ErigonEngine::Ref<ErigonEngine::Shader> m_Shader;
	ErigonEngine::Ref<ErigonEngine::Texture2D> m_Texture;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};