#include "eepch.h"
#include "RenderSystem.h"
#include "../Components/Sprite.hpp"
#include "../Components/Transform.hpp"
#include "ErigonEngine\Renderer\Renderer2D.h"
#include "ErigonEngine\Renderer\Shader.h"
#include <EECS_Controller.hpp>
#include "ErigonEngine\Core\Application.h"

extern ECS::EECS_Controller gECSController;

namespace ErigonEngine
{
	CameraSystem* cameraSystem;

	void RenderSystem::Init(CameraSystem& cameraSys)
	{
		cameraSystem = &cameraSys;
		Init();
	}

	void RenderSystem::Init()
	{
		quadVertexArray.reset();
		quadVertexArray = VertexArray::Create();

		float squareVert[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVert, sizeof(squareVert));
		squareVB->SetLayout
		({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});

		quadVertexArray->AddVertexBuffer(squareVB);

		uint32_t sqIndicies[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(sqIndicies, sizeof(sqIndicies));

		quadVertexArray->SetIndexBuffer(squareIB);
	}

	void RenderSystem::Update(float deltaTime)
	{
		ECS::Camera* camera = cameraSystem->GetCamera();
		if (camera == nullptr)
		{
			return;
		}

		for (auto& entity : entities)
		{
			auto& transform = gECSController.GetComponent<ECS::Transform>(entity);
			auto& spriteRenderer = gECSController.GetComponent<ECS::Sprite>(entity);

			DrawCallData data{};

			data.color = spriteRenderer.GetColor();
			data.shader = spriteRenderer.GetShader();
			data.texture = spriteRenderer.GetTexture();
			data.vertexArray = quadVertexArray;
			data.transform = transform.GetTransformMatrix();
			data.viewProjection = camera->viewProjectionMatrix;
			
			Renderer2D::Draw(data);
		}
		
	}
}