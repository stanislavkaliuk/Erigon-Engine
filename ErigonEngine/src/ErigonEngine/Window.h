#pragma once

#include "eepch.h"
#include "ErigonEngine/Core.h"
#include "ErigonEngine/Events/Event.h"

namespace ErigonEngine
{

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Erigon Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Width(width),Height(height){}
	};

	class ERIGON_API IWindow
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		virtual ~IWindow() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallback& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static IWindow* Create(const WindowProps& props = WindowProps());
	};

}