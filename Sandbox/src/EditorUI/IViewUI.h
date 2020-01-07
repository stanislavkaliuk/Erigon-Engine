#pragma once
#include <imgui\imgui.h>

namespace ErigonEngine
{
	namespace Editor
	{
		class IViewUI
		{
		public:
			virtual void Setup() = 0;
			virtual void Draw() = 0;
			bool IsActive() const { return active; }
			bool OnFocus() const { return focus; }
			ImVec2 GetSize() const { return size; }
		protected:
			bool active;
			bool focus;
			ImVec2 size;
		};
	}
}