#include "eepch.h"
#include "NodeEditor.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void NodeEditor::Attach()
		{
			context = ENodeEditor::CreateEditor();
		}

		void NodeEditor::Detach()
		{
			ENodeEditor::DestroyEditor(context);
		}

		void NodeEditor::Update()
		{
			if(ImGui::Begin("Node Editor", &open))
			{
				using namespace ENodeEditor;
				SetCurrentEditor(context);
				Begin("Scenario Editor");
				{
					int id = 1;
					BeginNode(id++);
					{
						ImGui::Text("Node A");

						BeginPin(id++, PinKind::Input);
						{
							ImGui::Text("-> In");
						}
						EndPin();

						ImGui::SameLine();

						BeginPin(id++, PinKind::Output);
						{
							ImGui::Text("Out ->");
						}
						EndPin();
					}
					EndNode();
				}
				End();
			}
			ImGui::End();
			
		}
	}
}