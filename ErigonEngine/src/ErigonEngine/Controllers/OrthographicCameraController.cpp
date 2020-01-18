#include "eepch.h"
#include "OrthographicCameraController.h"
#include "ErigonEngine/Input/KeyCodes.h"
#include "ErigonEngine/Input/Input.h"

namespace ErigonEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio) : m_AspectRatio(aspectRatio),
	m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
		
	}

	void OrthographicCameraController::OnUpdate(Timestep deltaTime)
	{
		m_CameraPosition = m_Camera.GetPosition();
		m_CameraRotation = m_Camera.GetRotation();

		if (Input::IsKeyPressed(EE_KEY_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * deltaTime;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * deltaTime;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * deltaTime;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraSpeed * deltaTime;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraSpeed * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
		}

		if (m_CameraRotation > 180.0f)
		{
			m_CameraRotation -= 360.0f;
		}
		else if (m_CameraRotation <= -180.0f)
		{
			m_CameraRotation += 360.0f;
		}

		m_Camera.SetTransform(m_CameraPosition, m_CameraRotation);
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(EE_BIND_EVENT(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(EE_BIND_EVENT(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::UpdateProjection()
	{
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.25f, 5.0f);
		UpdateProjection();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth()/ (float)e.GetHeight();
		UpdateProjection();
		return false;
	}
}
