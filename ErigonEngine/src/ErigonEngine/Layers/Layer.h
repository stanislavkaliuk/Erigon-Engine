#pragma once

#include "ErigonEngine/Core/Core.h"
#include "ErigonEngine/Events/Event.h"
#include "ErigonEngine/Core/Timestep.h"

namespace ErigonEngine
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep timestep) {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}