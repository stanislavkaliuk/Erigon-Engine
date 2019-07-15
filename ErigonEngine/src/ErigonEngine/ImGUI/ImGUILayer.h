#pragma once

#include "ErigonEngine/Layers/Layer.h"
#include "ErigonEngine/Events/KeyEvent.h"
#include "ErigonEngine/Events/MouseEvent.h"
#include "ErigonEngine/Events/ApplicationEvent.h"

namespace ErigonEngine
{
	class ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		~ImGUILayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}