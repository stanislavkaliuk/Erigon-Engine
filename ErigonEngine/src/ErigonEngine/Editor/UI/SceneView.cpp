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
			windowFlags = ImGuiWindowFlags_MenuBar;
			framebufferTextureId = Renderer2D::GetSnap();
		}

		void SceneView::Draw()
		{
			ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
			ImGui::Begin("Scene View", &active);
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddImage((void*)(uintptr_t)framebufferTextureId, pos, ImVec2(pos.x + size.x, pos.y + size.y), ImVec2(0, 1), ImVec2(1, 0));
			size = ImGui::GetWindowSize();
			ImGui::End();
		}
	}
}