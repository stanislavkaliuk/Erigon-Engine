#include "eepch.h"
#include "Builders.h"
#include "Interop.h"

ImGui::NodeEditor::Utilities::BPNodeBuilder::BPNodeBuilder(ImTextureID texture, int textureWidth, int textureHeight) : HeaderTextureId(texture), HeaderTextureWidth(textureWidth), HeaderTextureHeight(textureHeight), CurrentNodeId(0), CurrentStage(Stage::Invalid), HasHeader(false)
{

}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::Begin(NodeId id)
{
	HasHeader = false;
	HeaderRect = rect();

	PushStyleVar(StyleVar_NodePadding, ImVec4(8, 4, 8, 8));
	BeginNode(id);

	ImGui::PushID(id.AsPointer());
	CurrentNodeId = id;

	SetStage(Stage::Begin);
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::End()
{
	SetStage(Stage::End);
	EndNode();
	if (ImGui::IsItemVisible())
	{
		auto alpha = static_cast<int>(255 * ImGui::GetStyle().Alpha);
		auto drawList = GetNodeBackgroundDrawList(CurrentNodeId);

		const auto halfBorderWidth = NodeEditor::GetStyle().NodeBorderWidth * 0.5f;
		auto headerColor = IM_COL32(0, 0, 0, alpha) | (HeaderColor & IM_COL32(255, 255, 255, 0));
		if (!HeaderRect.is_empty() && HeaderTextureId)
		{
			const auto uv = ImVec2(HeaderRect.w / (float)(4 * HeaderTextureWidth), HeaderRect.h / (float)(4.0f * HeaderTextureHeight));
			
			drawList->AddImageRounded(HeaderTextureId, to_imvec(HeaderRect.top_left()) - ImVec2(8 - halfBorderWidth, 4 - halfBorderWidth),
				to_imvec(HeaderRect.bottom_right()) + ImVec2(8 - halfBorderWidth, 0),
			ImVec2(0.0f, 0.0f), uv, headerColor, NodeEditor::GetStyle().NodeRounding, 1 | 2);

			auto headerSeparartorRect = NodeEditor::rect(HeaderRect.bottom_left(), ContentRect.top_right());
		
		
			if (!headerSeparartorRect.is_empty())
			{
				drawList->AddLine(to_imvec(headerSeparartorRect.top_left()) + ImVec2(-(8 - halfBorderWidth), -0.5f),
					to_imvec(headerSeparartorRect.top_right()) + ImVec2(8-halfBorderWidth, -0.5f),
					ImColor(255,255,255,96*alpha/(3*255)),1.0f);
			}
		}

		CurrentNodeId = 0;
		ImGui::PopID();
		NodeEditor::PopStyleVar();
		SetStage(Stage::Invalid);
	}
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::Header(const ImVec4& color)
{
	HeaderColor = ImColor(color);
	SetStage(Stage::Header);
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::EndHeader()
{
	SetStage(Stage::Content);
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::Input(PinId id)
{
	if (CurrentStage == Stage::Begin)
	{
		SetStage(Stage::Content);
	}

	const auto applyPadding = (CurrentStage == Stage::Input);
	SetStage(Stage::Input);
	if (applyPadding)
	{
		ImGui::Spring();
	}

	Pin(id, PinKind::Input);
	ImGui::BeginHorizontal(id.AsPointer());
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::EndInput()
{
	ImGui::EndHorizontal();
	EndPin();
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::Middle()
{
	if (CurrentStage == Stage::Begin)
	{
		SetStage(Stage::Content);
	}

	SetStage(Stage::Middle);
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::Output(PinId id)
{
	if (CurrentStage == Stage::Begin)
	{
		SetStage(Stage::Content);
	}

	const auto applyPadding = (CurrentStage == Stage::Output);

	SetStage(Stage::Output);

	if (applyPadding)
		ImGui::Spring(0);

	Pin(id, PinKind::Output);

	ImGui::BeginHorizontal(id.AsPointer());
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::EndOutput()
{
	ImGui::EndHorizontal();

	EndPin();
}

bool ImGui::NodeEditor::Utilities::BPNodeBuilder::SetStage(Stage newStage)
{
    if (newStage == CurrentStage)
        return false;

    auto oldStage = CurrentStage;
    CurrentStage = newStage;

    ImVec2 cursor;
    switch (oldStage)
    {
    case Stage::Begin:
        break;

    case Stage::Header:
        ImGui::EndHorizontal();
        HeaderRect = ImGui_GetItemRect();

        // spacing between header and content
        ImGui::Spring(0, ImGui::GetStyle().ItemSpacing.y * 2.0f);

        break;

    case Stage::Content:
        break;

    case Stage::Input:
        NodeEditor::PopStyleVar(2);

        ImGui::Spring(1, 0);
        ImGui::EndVertical();

        // #debug
        // ImGui::GetWindowDrawList()->AddRect(
        //     ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));

        break;

    case Stage::Middle:
        ImGui::EndVertical();

        // #debug
        // ImGui::GetWindowDrawList()->AddRect(
        //     ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));

        break;

    case Stage::Output:
        NodeEditor::PopStyleVar(2);

        ImGui::Spring(1, 0);
        ImGui::EndVertical();

        // #debug
        // ImGui::GetWindowDrawList()->AddRect(
        //     ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 0, 0, 255));

        break;

    case Stage::End:
        break;

    case Stage::Invalid:
        break;
    }

    switch (newStage)
    {
    case Stage::Begin:
        ImGui::BeginVertical("node");
        break;

    case Stage::Header:
        HasHeader = true;

        ImGui::BeginHorizontal("header");
        break;

    case Stage::Content:
        if (oldStage == Stage::Begin)
            ImGui::Spring(0);

        ImGui::BeginHorizontal("content");
        ImGui::Spring(0, 0);
        break;

    case Stage::Input:
        ImGui::BeginVertical("inputs", ImVec2(0, 0), 0.0f);

        NodeEditor::PushStyleVar(NodeEditor::StyleVar_PivotAlignment, ImVec2(0, 0.5f));
        NodeEditor::PushStyleVar(NodeEditor::StyleVar_PivotSize, ImVec2(0, 0));

        if (!HasHeader)
            ImGui::Spring(1, 0);
        break;

    case Stage::Middle:
        ImGui::Spring(1);
        ImGui::BeginVertical("middle", ImVec2(0, 0), 1.0f);
        break;

    case Stage::Output:
        if (oldStage == Stage::Middle || oldStage == Stage::Input)
            ImGui::Spring(1);
        else
            ImGui::Spring(1, 0);
        ImGui::BeginVertical("outputs", ImVec2(0, 0), 1.0f);

        NodeEditor::PushStyleVar(NodeEditor::StyleVar_PivotAlignment, ImVec2(1.0f, 0.5f));
        NodeEditor::PushStyleVar(NodeEditor::StyleVar_PivotSize, ImVec2(0, 0));

        if (!HasHeader)
            ImGui::Spring(1, 0);
        break;

    case Stage::End:
        if (oldStage == Stage::Input)
            ImGui::Spring(1, 0);
        if (oldStage != Stage::Begin)
            ImGui::EndHorizontal();
        ContentRect = ImGui_GetItemRect();

        //ImGui::Spring(0);
        ImGui::EndVertical();
        NodeRect = ImGui_GetItemRect();
        break;

    case Stage::Invalid:
        break;
    }

    return true;
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::Pin(PinId id, PinKind kind)
{
    NodeEditor::BeginPin(id, kind);
}

void ImGui::NodeEditor::Utilities::BPNodeBuilder::EndPin()
{
    NodeEditor::EndPin();
}
