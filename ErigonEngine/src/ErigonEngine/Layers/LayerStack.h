#pragma once

#include "ErigonEngine/Core/Core.h"

#include "Layer.h"

#include <vector>

namespace ErigonEngine
{
	class LayerStack
	{
		public:
			LayerStack();
			~LayerStack();

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);
			void PopLayer(Layer* layer);
			void PopOverlay(Layer* layer);

			std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
			std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerStackInserts = 0;
	};
}