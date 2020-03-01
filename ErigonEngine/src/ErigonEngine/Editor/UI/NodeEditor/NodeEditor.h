#pragma once
#include "ENodeEditor\ENodeEditor.h"

namespace ENodeEditor = ImGui::NodeEditor;
namespace ErigonEngine
{
	namespace Editor
	{
		class NodeEditor
		{
		public:
			void Attach();
			void Detach();

			void Update();

		private:
			ENodeEditor::EditorContext* context;
			bool open;
		};
	}
}
