#pragma once
#include "ErigonEngine/Renderer/OrtographicCamera.h"
#include "ErigonEngine/Core/TimeStep.h"
#include "ErigonEngine/Events/ApplicationEvent.h"
#include "ErigonEngine/Events/MouseEvent.h"

namespace ErigonEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio);

		void OnUpdate(Timestep deltaTime);
		void OnEvent(Event& e);
		
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		float GetZoomLevel() const { return m_ZoomLevel; }
	
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition = {0.0f,0.0f, 0.0f};
		float m_CameraSpeed = 2.5f;
		float m_CameraRotationSpeed = 15.0f;
		float m_CameraRotation = 0.0f;
	};
}
