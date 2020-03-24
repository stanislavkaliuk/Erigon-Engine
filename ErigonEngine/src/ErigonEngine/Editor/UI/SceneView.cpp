#include "eepch.h"
#include "SceneView.h"
#include "ErigonEngine\Renderer\Renderer2D.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void SceneView::Setup()
		{
			active = true;
			windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking;
			framebufferTextureId = Renderer2D::GetSnap();
			viewType = ViewType::SceneView;
		}

		void SceneView::Draw()
		{
			ImGuiIO io = ImGui::GetIO();
			ImVec2 screenSize = io.DisplaySize;
			ImGui::SetNextWindowPos(ImVec2(screenSize.x / 2.0f - 640, 0), ImGuiCond_Always);
			ImGui::SetNextWindowSize(ImVec2(1280, 720), ImGuiCond_Always);
			ImGui::Begin("Scene View", &active, windowFlags);
			ImVec2 currentSize = ImGui::GetWindowSize();
			resized = size.x != currentSize.x || size.y != currentSize.y;
			size = currentSize;
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddImage((void*)(uintptr_t)framebufferTextureId, pos, ImVec2(pos.x + size.x - 1, pos.y + size.y - 1), ImVec2(0, 1), ImVec2(1, 0));
			
			DrawMenuBar();

			ImGui::End();
		}

		void SceneView::DrawMenuBar()
		{
			if (ImGui::BeginMenuBar())
			{
				DrawSizeSelector();
			}
			ImGui::EndMenuBar();
		}

		void SceneView::DrawSizeSelector()
		{
			if (ImGui::BeginMenu(sizeSelectorData.items[sizeSelectorData.selectedSizeItemIndex]))
			{
				ImGui::SetNextItemWidth(150.0f);
				ImGui::ListBox("", &sizeSelectorData.selectedSizeItemIndex, sizeSelectorData.items, IM_ARRAYSIZE(sizeSelectorData.items), 2);
				ImGui::EndMenu();
			}
		}
	}
}