#pragma once
#include <string>
#include <ErigonEngine/Core/Core.h>
#include <ErigonEngine/Core/Types.h>

namespace ErigonEngine
{
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;
		virtual void Bind(uint32 textureId, uint32 width, uint32 height) const = 0;
		virtual void Unbind() const = 0;
		static Ref<FrameBuffer> Create();
	};
}