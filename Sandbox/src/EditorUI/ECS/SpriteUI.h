#pragma once
#include "IComponentUI.h"
#include "ErigonEngine\ECS\Sprite.h"

namespace Editor
{
	class SpriteUI : public IComponentUI<ErigonEngine::Sprite>
	{
	public:
		virtual void Setup(ErigonEngine::Sprite* component) override;
		virtual void Draw() override;
	};
}
