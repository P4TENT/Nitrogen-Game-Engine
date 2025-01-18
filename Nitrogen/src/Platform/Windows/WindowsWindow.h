#pragma once

#include "Core/Window.h"

#include <GLFW/glfw3.h>

namespace Nitrogen {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowStructure& props);
		virtual ~WindowsWindow() override;

		virtual void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline std::string GetTitle() const override { return m_Data.Title; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled = 1) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const override { return m_Window; }
	private:
		virtual void Init(const WindowStructure& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}