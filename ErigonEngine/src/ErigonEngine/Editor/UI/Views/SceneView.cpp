#include "eepch.h"
#include "SceneView.h"
#include "ErigonEngine\Renderer\Renderer2D.h"
#include "ErigonEngine\Editor\UI\EditorUIController.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void SceneView::Setup(void* controller)
		{
			active = true;
			windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking;
			framebufferTextureId = Renderer2D::GetSnap();
			viewType = ViewType::SceneView;
			masterController = controller;
		}

		void SceneView::Draw()
		{
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			ImGuiIO io = ImGui::GetIO();
			ImVec2 screenSize = io.DisplaySize;
			glm::vec2 renderSize = sizeSelectorData.sizes.at(sizeSelectorData.selectedSizeItemIndex);
			ImGui::SetNextWindowPos(ImVec2(screenSize.x / 2.0f - renderSize.x / 2.0f, 22));
			ImGui::SetNextWindowSize(ImVec2(renderSize.x, renderSize.y));
			ImGui::Begin("Scene View", !active ? &active : nullptr, windowFlags);
			ImVec2 currentSize = ImGui::GetWindowSize();
			resized = size.x != currentSize.x || size.y != currentSize.y;
			size = currentSize;
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddImage((void*)(uintptr_t)framebufferTextureId, pos, ImVec2(pos.x + size.x - 1, pos.y + size.y - 1), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::PopStyleVar();
			DrawMenuBar();

			ImGui::End();
		}

		void SceneView::SendCallback(const Event& event)
		{
			EventManager::InvokeEvent(event.GetEventType(), const_cast<Event&>(event));
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
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
			if (ImGui::BeginMenu(sizeSelectorData.items[sizeSelectorData.selectedSizeItemIndex]))
			{
				ImGui::SetNextItemWidth(150.0f);
				if (ImGui::ListBox("", &sizeSelectorData.selectedSizeItemIndex, sizeSelectorData.items, IM_ARRAYSIZE(sizeSelectorData.items), 2))
				{
					ApplySize();
				}
				ImGui::EndMenu();
			}
			ImGui::PopStyleVar();
		}

		void SceneView::ApplySize()
		{
			glm::vec2 size = sizeSelectorData.sizes.at(sizeSelectorData.selectedSizeItemIndex);
			SceneViewSizeChangedEvent event(size);
			SendCallback(event);
		}
	}
}