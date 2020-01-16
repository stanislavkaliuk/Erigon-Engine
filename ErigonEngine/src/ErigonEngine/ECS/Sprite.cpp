#include "eepch.h"
#include "Sprite.h"
#include <glm/glm.hpp>
#include "ErigonEngine/Renderer/Renderer2D.h"

namespace ErigonEngine
{
	Sprite::Sprite(const std::string& texturePath)
	{
		texture = Texture2D::Create(texturePath);
		color = new Color(255, 255, 255, 255);
	}

	Sprite::Sprite(const glm::vec4& color)
	{
		texture = nullptr;
		this->color = new Color(color.r, color.g, color.b, color.a);
	}

	Sprite::Sprite(const glm::vec3& color)
	{
		texture = nullptr;
		this->color = new Color(color.r, color.g, color.b);
	}

	Sprite::~Sprite()
	{
		delete color;
		texture.reset();
	}

	void Sprite::SetColor(const glm::vec3& color)
	{
		this->color->r = color.r;
		this->color->g = color.g;
		this->color->b = color.b;
		this->color->a = 255;
	}

	void Sprite::SetColor(const glm::vec4& color)
	{
		this->color->r = color.r;
		this->color->g = color.g;
		this->color->b = color.b;
		this->color->a = color.a;
	}

	void Sprite::SetTexture(const std::string& texturePath)
	{
		texture.reset();
		texture = Texture2D::Create(texturePath);
	}

	void Sprite::Update(const Transform& transform)
	{
		Renderer2D::Draw(transform.position, transform.scale, texture);
	}
}