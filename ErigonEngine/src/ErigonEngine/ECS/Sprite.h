#pragma once
#include <EECS.h>
#include "ErigonEngine/Renderer/Texture.h"
#include "ErigonEngine/Tools/Color.h"
#include "Transform.h"

namespace ErigonEngine
{
	class Sprite : public Erigon::ECS::Component<Sprite>
	{
	public:
		Sprite(const std::string& texturePath);
		Sprite(const glm::vec4& color);
		Sprite(const glm::vec3& color);
		~Sprite();

		void SetColor(const glm::vec3& color);
		void SetColor(const glm::vec4& color);
		inline uint32 GetHexColor() const { return color->GetHexValue(); };

		void SetTexture(const std::string& texturePath);
		inline Ref<Texture2D> GetTexture() const { return texture; }

		void Update(const Transform& transform);

	private:
		Ref<Texture2D> texture;
		Color* color;
	};
}