#include "SceneViewUI.h"

namespace ErigonEngine
{
	namespace Editor
	{
		void SceneViewUI::Setup()
		{
			framebufferTextureId = ErigonEngine::Renderer2D::GetSnap();
		}

		void SceneViewUI::Draw()
		{
			ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar;
			ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
			ImGui::Begin("Scene View", &active);
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImGui::GetWindowDrawList()->AddImage((void*)(uintptr_t)framebufferTextureId, pos, ImVec2(pos.x + size.x, pos.y + size.y), ImVec2(0, 1), ImVec2(1, 0));
			size = ImGui::GetWindowSize();
			ImGui::End();
		}
	}
}