#include "eepch.h"
#include "Properties.h"

namespace ErigonEngine::Editor
{
	void Properties::Setup(void* controller)
	{
		active = true;
		windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
		viewType = ViewType::Inspector;
		masterController = controller;
	}

	void Properties::Draw()
	{
		ImGuiIO io = ImGui::GetIO();
		ImVec2 screenSize = io.DisplaySize;
		ImVec2 desiredWindowSize = ImVec2(350, 1080);
		ImGui::SetNextWindowPos(ImVec2(screenSize.x - desiredWindowSize.x, screenSize.y - desiredWindowSize.y));
		ImGui::SetNextWindowSize(desiredWindowSize);
		ImGui::SetNextWindowContentSize(desiredWindowSize);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Properties", !active ? &active : nullptr, windowFlags);
		ImGui::Text("Property");
		ImGui::GetWindowDrawList()->AddLine(ImGui::GetCursorScreenPos(), ImVec2(ImGui::GetCursorScreenPos().x + desiredWindowSize.x, ImGui::GetCursorScreenPos().y), ImColor(255, 255, 255));
		ImGui::PopStyleVar();
		ImGui::End();
	}

	void Properties::DrawDetailContainer()
	{

	}
}
