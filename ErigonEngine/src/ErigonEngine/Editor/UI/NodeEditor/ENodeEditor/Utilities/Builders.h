#pragma once
#include "imgui.h"
#include "../ENodeEditor.h"
#include "Math2d.h"

namespace ImGui
{
	namespace NodeEditor
	{
		namespace Utilities
		{
			struct BPNodeBuilder
			{
				BPNodeBuilder(ImTextureID texture = nullptr, int textureWidth = 0, int textureHeight = 0);

				void Begin(NodeId id);
				void End();

				void Header(const  ImVec4& color = ImVec4(1, 1, 1, 1));
				void EndHeader();

				void Input(PinId id);
				void EndInput();

				void Middle();

				void Output(PinId id);
				void EndOutput();

			private:
				enum class Stage
				{
					Invalid,
					Begin,
					Header,
					Content,
					Input, 
					Output,
					Middle,
					End
				};

				bool SetStage(Stage newStage);
				void Pin(PinId id, PinKind kind);
				void EndPin();

				ImTextureID HeaderTextureId;
				int HeaderTextureWidth;
				int HeaderTextureHeight;

				NodeId CurrentNodeId;
				Stage CurrentStage;
				ImU32 HeaderColor;
				rect NodeRect;
				rect HeaderRect;
				rect ContentRect;
				bool HasHeader;
			};


		}
	}
}