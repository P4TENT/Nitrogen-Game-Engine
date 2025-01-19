#pragma once

#include "ntgpch.h"

#include "Nitrogen/Core/Core.h"
#include "Events/Event.h"

namespace Nitrogen{
	struct WindowProps {
		std::string Title;
		NTGUINT Width;
		NTGUINT Height;

		WindowProps(const std::string& title = "Nitrogen Engine", NTGUINT width = 1280, NTGUINT height = 720)
			: Title(title), Width(width), Height(height) {}
	};
	
	class Window 
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual NTGUINT GetWidth() const = 0;
		virtual NTGUINT GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}