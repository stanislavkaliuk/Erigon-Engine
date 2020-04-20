#include "eepch.h"
#include "CameraSystem.h"
#include <EECS_Controller.hpp>


extern ECS::EECS_Controller gECSController;

namespace ErigonEngine
{
	void CameraSystem::Init(const glm::vec2& renderWindowSize)
	{
		ECS::Camera camera = GetComponent<ECS::Camera>(); 
		camera.RecalculateProjectionMatrix(renderWindowSize);
		camera.RecalculatViewMatrix(GetComponent<ECS::Transform>().position);
	}

	void CameraSystem::Update(float deltaTime)
	{
		ECS::Transform transform = gECSController.GetComponent<ECS::Transform>(*entities.begin());
		glm::vec3 position = transform.position;

		if (Input::IsKeyPressed(EE_KEY_A))
		{
			position.x -= CAMERA_MAX_SPEED * deltaTime;
			position.y -= CAMERA_MAX_SPEED * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_D))
		{
			position.x += CAMERA_MAX_SPEED * deltaTime;
			position.y += CAMERA_MAX_SPEED * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_W))
		{
			position.x += CAMERA_MAX_SPEED * deltaTime;
			position.y += CAMERA_MAX_SPEED * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_S))
		{
			position.x -= CAMERA_MAX_SPEED * deltaTime;
			position.y -= CAMERA_MAX_SPEED * deltaTime;
		}

		transform.position = position;
		UpdateView(position);
	}

	void CameraSystem::OnEvent(const Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Editor::SceneViewSizeChangedEvent>(EE_BIND_EVENT(CameraSystem::OnSceneViewChanged));
	}

	template<typename T>
	T& CameraSystem::GetComponent()
	{
		return gECSController.GetComponent<T>(*entities.begin());
	}

	bool CameraSystem::OnSceneViewChanged(Editor::SceneViewSizeChangedEvent& e)
	{
		UpdateProjection(e.GetSize());
		return true;
	}

	void CameraSystem::UpdateProjection(const glm::vec2& size)
	{
		GetComponent<ECS::Camera>().RecalculateProjectionMatrix(size);
	}

	void CameraSystem::UpdateView(const glm::vec3& position)
	{
		GetComponent<ECS::Camera>().RecalculatViewMatrix(position);
	}
}