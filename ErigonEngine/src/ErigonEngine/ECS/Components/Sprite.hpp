#pragma once
#include "ErigonEngine\Renderer\Shader.h"
#include "ErigonEngine\Renderer\Texture.h"
#include "ErigonEngine\Tools\Color.h"

namespace ErigonEngine
{
	namespace ECS
	{
		struct Sprite
		{
			Ref<Texture2D> texture;
			Color spriteColor;
			Ref<Shader> shader;

			void SetColor(const glm::vec3& color)
			{
				this->spriteColor = color;
			}

			void SetColor(const glm::vec4& color)
			{
				this->spriteColor = color;
			}

			glm::vec4 GetColor()
			{
				return this->spriteColor;
			}

			inline uint32 GetHexColor() { return spriteColor.GetHexValue(); };

			void SetTexture(const std::string& texturePath)
			{
				texture.reset();
				texture = Texture2D::Create(texturePath);
			}

			inline Ref<Texture2D> GetTexture() const { return texture; }

			void SetShader(const char* path)
			{
				shader.reset();
				shader = Shader::Create(path);
			}

			inline Ref<Shader> GetShader() const { return shader; }
		};
	}
}