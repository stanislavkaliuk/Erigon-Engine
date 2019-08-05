#pragma once

#include "ErigonEngine/Core/Window.h"
#include "ErigonEngine/Renderer/GraphicsContext.h"

namespace ErigonEngine
{
	class WinWindow : public IWindow
	{
	public:
		WinWindow(const WindowProps& props);
		virtual ~WinWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallback& callback) override { m_Data.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		HWND* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			EventCallback EventCallback;
			bool VSync;
		};

		WindowData m_Data;
	};
}