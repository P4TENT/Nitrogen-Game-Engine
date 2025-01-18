#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/AppEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Nitrogen {

	struct WindowStructure {
		std::string Title;
		uint32_t Width, Height;

		WindowStructure(const std::string& title = "Nitrogen Engine", uint32_t width = 1280, uint32_t height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	using EventCallbackFn = std::function<void(Event&)>;

	class Window
	{
	public:

		virtual ~Window() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual std::string GetTitle() const = 0;

		virtual void OnUpdate() = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		
		static Scope<Window> Create(const WindowStructure& windowProps = WindowStructure());
	};
}