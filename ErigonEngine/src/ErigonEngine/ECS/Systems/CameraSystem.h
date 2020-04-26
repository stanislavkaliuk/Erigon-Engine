#pragma once
#include <System.hpp>
#include "ErigonEngine/Input/KeyCodes.h"
#include "ErigonEngine/Input/Input.h"
#include "ErigonEngine/Events/EditorEvent.h"
#include "../Components/Transform.hpp"
#include "../Components/Camera.hpp"

namespace ErigonEngine
{
	class CameraSystem : public ::ECS::System
	{
	public:
		void Init(const glm::vec2& renderWindowSize);
		void Init() override {};
		void Update(float deltaTime) override;
		void OnEvent(const Event& e);
		bool OnSceneViewChanged(Editor::SceneViewSizeChangedEvent& e);
		void UpdateProjection(const glm::vec2& size);
		void UpdateView(const glm::vec3& position);
		ECS::Camera* GetCamera() noexcept { return camera == nullptr ? nullptr : camera; }
	private:
		void GetCameraComponent();
		const float CAMERA_MAX_SPEED = 2.5f;
		const int NEAR_CLIP_PLANE = -1;
		const int FAR_CLIP_PLANE = 50;
		ECS::Camera* camera;
		glm::vec2 renderWindowSize;
	};


}