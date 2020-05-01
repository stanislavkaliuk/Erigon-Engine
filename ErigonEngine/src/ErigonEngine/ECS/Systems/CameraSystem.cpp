#include "eepch.h"
#include "CameraSystem.h"
#include <EECS_Controller.hpp>


extern ECS::EECS_Controller gECSController;

namespace ErigonEngine
{
	void CameraSystem::Init(const glm::vec2& renderWindowSize)
	{
		this->renderWindowSize = renderWindowSize;
	}

	void CameraSystem::Update(float deltaTime)
	{
		if (entities.empty())
		{
			return;
		}
		else if (camera == nullptr)
		{
			GetCameraComponent();
			camera->RecalculateProjectionMatrix(renderWindowSize);
			camera->RecalculatViewMatrix(gECSController.GetComponent<ECS::Transform>(*entities.begin())->position);
		}

		std::shared_ptr<ECS::Transform> transform = gECSController.GetComponent<ECS::Transform>(*entities.begin());
		glm::vec3 position = transform->position;

		if (Input::IsKeyPressed(EE_KEY_A))
		{
			position.x -= CAMERA_MAX_SPEED * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_D))
		{
			position.x += CAMERA_MAX_SPEED * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_W))
		{
			position.y += CAMERA_MAX_SPEED * deltaTime;
		}

		if (Input::IsKeyPressed(EE_KEY_S))
		{
			position.y -= CAMERA_MAX_SPEED * deltaTime;
		}

		transform->position = position;
		UpdateView(position);
	}

	void CameraSystem::OnEvent(const Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Editor::SceneViewSizeChangedEvent>(EE_BIND_EVENT(CameraSystem::OnSceneViewChanged));
	}

	void CameraSystem::GetCameraComponent()
	{
		if (entities.empty())
		{
			return;
		}

		camera = gECSController.GetComponent<ECS::Camera>(*entities.begin());
	}

	bool CameraSystem::OnSceneViewChanged(Editor::SceneViewSizeChangedEvent& e)
	{
		renderWindowSize = e.GetSize();
		UpdateProjection(renderWindowSize);
		return true;
	}

	void CameraSystem::UpdateProjection(const glm::vec2& size)
	{
		if (camera != nullptr)
		{
			camera->RecalculateProjectionMatrix(size);
		}
	}

	void CameraSystem::UpdateView(const glm::vec3& position)
	{
		if (camera != nullptr)
		{
			camera->RecalculatViewMatrix(position);
		}
	}
}