#pragma once

#include <string>
#include <ErigonEngine/Core/Core.h>
#include <ErigonEngine/Core/Types.h>

namespace ErigonEngine
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;

		virtual void Bind(uint32 viewportX, uint32 viewportY) const = 0;
		virtual void Bind(uint32 slot = 0) const = 0;
		virtual uint32_t GetTextureId() const = 0;
	};


	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create();
	};
}
