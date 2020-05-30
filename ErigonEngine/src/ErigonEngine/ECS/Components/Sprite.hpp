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
			Sprite()
			{

			}

			Sprite(const Sprite& other)
			{
				this->texture.reset(other.texture.get());
				this->shader.reset(other.shader.get());
				this->spriteColor = other.spriteColor;
			}

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

			void SetTexture(Ref<Texture2D> textureRef)
			{
				texture.reset();
				texture = textureRef;
			}

			inline Ref<Texture2D> GetTexture() const { return texture; }

			void SetShader(const char* path)
			{
				shader = Shader::Create(path);
			}

			void SetShader(Ref<Shader> shaderRef)
			{
				shader = shaderRef;
			}

			inline Ref<Shader> GetShader() const { return shader; }
		};
	}
}