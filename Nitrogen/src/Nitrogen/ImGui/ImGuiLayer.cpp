#include "ntgpch.h"
#include "ImGuiLayer.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Nitrogen/Core/CoreApp.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Nitrogen{

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		NTG_PROFILE_FUNCTION();

		// Initialize ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Enable ImGui features
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark(); 
		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 0.0f;
		style.FrameRounding = 2.0f;
		style.GrabRounding = 2.0f;
		style.PopupRounding = 2.0f;
		style.ScrollbarRounding = 2.0f;

		style.FramePadding = ImVec2(6, 4);
		style.ItemSpacing = ImVec2(8, 6);
		style.WindowPadding = ImVec2(10, 10);
		style.IndentSpacing = 12;
		style.ScrollbarSize = 14.0f;

		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.24f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.26f, 0.28f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.10f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.14f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.06f, 0.06f, 0.08f, 1.00f);

		style.Colors[ImGuiCol_Border] = ImVec4(0.28f, 0.28f, 0.30f, 1.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); 

		style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.22f, 0.30f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.38f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.18f, 0.28f, 0.42f, 1.00f);

		style.Colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.16f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.28f, 0.38f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.28f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.12f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.20f, 0.25f, 1.00f);

		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.22f, 0.30f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.28f, 0.38f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.18f, 0.28f, 0.42f, 1.00f);

		style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.22f, 0.30f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.28f, 0.38f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.18f, 0.28f, 0.42f, 1.00f);

		style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.92f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.52f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.38f, 0.50f, 1.00f);

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings (GLFW and OpenGL)
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
		NTG_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		NTG_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		NTG_PROFILE_FUNCTION();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
	}
}