#pragma once

#include "eepch.h"
#include "ErigonEngine/Core/Core.h"
#include "ErigonEngine/Events/Event.h"

namespace ErigonEngine
{
	struct WindowProps
	{
		std::string Title;

		WindowProps(const std::string& title = "Erigon Engine")
			: Title(title)
		{
		}
	};

	class IWindow
	{
	public:
		virtual ~IWindow() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static IWindow* Create(const WindowProps& props = WindowProps());
	};

}