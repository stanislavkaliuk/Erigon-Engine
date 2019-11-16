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
	void OnPostUpdate(ErigonEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ErigonEngine::Event& e) override;

private:
	ErigonEngine::OrthographicCameraController m_CameraController;
	ErigonEngine::ShaderLibrary m_ShaderLibrary;
	ErigonEngine::Ref<ErigonEngine::Texture2D> texture;
};