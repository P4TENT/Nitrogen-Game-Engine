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
		// Initialize ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		// Enable ImGui features
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		// Setup Dear ImGui style (Make it visually appealing)
		ImGui::StyleColorsDark(); // Dark theme
		//ImGui::StyleColorsClassic(); // Uncomment this if you prefer the classic theme

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 10.0f; // Rounded window corners
		style.FrameRounding = 5.0f; // Rounded frames
		style.GrabRounding = 5.0f; // Rounded sliders and grab handles
		style.PopupRounding = 10.0f; // Rounded popups
		style.ScrollbarRounding = 5.0f; // Rounded scrollbars

		// Color Scheme: Make the colors more vibrant and smooth
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f); // Dark window background
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f); // Darker frame background
		style.Colors[ImGuiCol_Button] = ImVec4(0.40f, 0.60f, 0.80f, 1.00f); // Light blue button color
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.70f, 1.00f, 1.00f); // Hovered button color
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.50f, 0.80f, 1.00f); // Active button color

		// Customize borders and separator appearance
		style.Colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); // Lighter border
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); // Border shadow transparency

		// Multi-Viewport adjustments for platform windows (if enabled)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 10.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f; // Full opacity for the platform windows
		}

		// Setup Platform/Renderer bindings (GLFW and OpenGL)
		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
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
		ImGui::ShowDemoWindow(&show);
	}
}