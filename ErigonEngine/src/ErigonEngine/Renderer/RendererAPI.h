#pragma once
#include <DirectXMath.h>
#include "VertexArray.h"

namespace ErigonEngine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, DirectX11 = 2
		};

	public:
		virtual void SetClearColor(const DirectX::XMFLOAT4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}