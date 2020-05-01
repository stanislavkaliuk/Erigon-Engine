#pragma once
#include <System.hpp>
#include "ErigonEngine\Renderer\VertexArray.h"
#include "../Components/Camera.hpp"
#include "CameraSystem.h"

#include <memory>

namespace ErigonEngine
{
	class RenderSystem : public ::ECS::System
	{
	public:
		void Init(CameraSystem& cameraSys);
		void Init() override;
		void Update(float deltaTime) override;
	private:
		Ref<VertexArray> quadVertexArray;
	};
}