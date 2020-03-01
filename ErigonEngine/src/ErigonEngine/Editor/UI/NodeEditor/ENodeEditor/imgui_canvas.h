#pragma once

#include <imgui.h>
#include <imgui_internal.h>

namespace ImGui
{
	namespace NodeEditor
	{
		struct CanvasView
		{
			ImVec2 Origin;
			float Scale = 1.0f;
			float InvScale = 1.0f;

			CanvasView() = default;
			CanvasView(const ImVec2& origin, float scale) : Origin(origin), Scale(scale), InvScale(scale ? 1.0f / scale : 0.0f)
			{

			}

			void Set(const ImVec2& origin, float scale)
			{
				*this = CanvasView(origin, scale);
			}
		};

		struct Canvas
		{
			bool Begin(const char* id, const ImVec2& size);
			bool Begin(ImGuiID id, const ImVec2& size);

			void End();

			void SetView(const ImVec2& origin, float scale);
			void SetView(const CanvasView& view);

			void CenterView(const ImVec2& canvasPoint);
			CanvasView CalculateCenterView(const ImVec2& canvasPoint) const;

			void CenterView(const ImRect& canvasRect);
			CanvasView CalculateCenterView(const ImRect& canvasRect) const;

			void Suspend();
			void Resume();

			// Transforms point from canvas plane to ImGui.
			ImVec2 FromLocal(const ImVec2& point) const;
			ImVec2 FromLocal(const ImVec2& point, const CanvasView& view) const;

			// Transforms vector from canvas plant to ImGui.
			ImVec2 FromLocalV(const ImVec2& vector) const;
			ImVec2 FromLocalV(const ImVec2& vector, const CanvasView& view) const;

			// Transforms point from ImGui to canvas plane.
			ImVec2 ToLocal(const ImVec2& point) const;
			ImVec2 ToLocal(const ImVec2& point, const CanvasView& view) const;

			// Transforms vector from ImGui to canvas plane.
			ImVec2 ToLocalV(const ImVec2& vector) const;
			ImVec2 ToLocalV(const ImVec2& vector, const CanvasView& view) const;


			const ImRect& Rect() const { return m_WidgetRect; }
			const ImRect& ViewRect() const { return m_ViewRect; }
			ImRect CalcViewRect(const CanvasView& view) const;
			const CanvasView& View() const { return m_View; }
			const ImVec2& ViewOrigin()  const { return m_View.Origin; }
			float ViewScale() const { return m_View.Scale; }
			bool IsSuspended() const { return m_SuspendCounter > 0; }

			void UpdateViewTransformPosition();

			void SaveInputState();
			void RestoreInputState();

			void EnterLocalSpace();
			void LeaveLocalSpace();

			bool m_InBeginEnd = false;

			ImVec2 m_WidgetPosition;
			ImVec2 m_WidgetSize;
			ImRect m_WidgetRect;

			ImDrawList* m_DrawList = nullptr;
			int m_ExpectedChannel = 0;

			int m_DrawListCommadBufferSize = 0;
			int m_DrawListStartVertexIndex = 0;

			CanvasView  m_View;
			ImRect      m_ViewRect;

			ImVec2 m_ViewTransformPosition;

			int m_SuspendCounter = 0;

			float m_LastFringeScale = 1.0f;

			ImVec2 m_MousePosBackup;
			ImVec2 m_MousePosPrevBackup;
			ImVec2 m_MouseClickedPosBackup[IM_ARRAYSIZE(ImGuiIO::MouseClickedPos)];
			ImVec2 m_WindowCursorMaxBackup;
		};
	}
}