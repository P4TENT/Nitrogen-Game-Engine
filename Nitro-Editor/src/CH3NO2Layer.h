#pragma once

#include <Nitrogen.h>

#include <imgui.h>

#include "ToolsPart.h"
#include "shellapi.h"

namespace Nitrogen {
	class CH3NO2Layer : public Nitrogen::Layer
	{
	public:
		CH3NO2Layer()
			: Layer("CH3NO2 Layer"), m_CameraController(1280.f / 720.f)
		{
            ImGuiIO& io = ImGui::GetIO();
            ImFont* NitroFont = io.Fonts->AddFontFromFileTTF("src/fonts/Lato-Regular.ttf", 18);
            io.FontDefault = NitroFont;
		}

		void OnUpdate(Timestep deltaT) override
		{
			m_CameraController.OnUpdate(deltaT);

			RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RendererCommand::Clear();

			Renderer::BeginScene(m_CameraController.GetCamera());
			Renderer::EndScene();
		}

        void CH3NO2Layer::OnImGuiRender() override
        {
            ///////////////////////////////////////////
            // IMGUI DOCKSPACE ////////////////////////
            ///////////////////////////////////////////
            static bool dockspaceOpen = true;
            static bool optFullscreen = true;
            static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

            if (optFullscreen)
            {
                ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
                ImGui::SetNextWindowSize(viewport->WorkSize);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }

            ImGui::Begin("Dockspace", &dockspaceOpen, windowFlags);

            if (optFullscreen)
                ImGui::PopStyleVar(2);

            // Create the dockspace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspaceID = ImGui::GetID("MainDockspace");
                ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
            }
            else
            {
                ImGui::Text("Docking is not enabled! Please enable docking in ImGuiIO.");
            }

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {           
                    if (ImGui::MenuItem("Open Project"))
                    {
                        m_CurrentProjectPath = m_ToolsPart.OpenProject();
                        if (m_CurrentProjectPath != "")
                        m_ToolsPart.GetRunOption() == 0 ?
                            m_CurrentProjectLogPath = m_CurrentProjectPath + "\\bin\\Release-windows-x86_64\\" + m_ToolsPart.GetCurrentProjectName() + "\\logs\\Client.log" :
                            m_CurrentProjectLogPath = m_CurrentProjectPath + "\\bin\\Debug-windows-x86_64\\" + m_ToolsPart.GetCurrentProjectName() + "\\logs\\Client.log";
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Project"))
                {
                    if (ImGui::MenuItem("Open Project In Explorer"))
                    {
                        if (m_CurrentProjectPath != "") 
                        {
                            ShellExecuteA(NULL, "open", m_CurrentProjectPath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
                        } 
                        else 
                        {
                            ImGui::OpenPopup("Warning!");
                        }
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            m_ToolsPart.ConsoleTab(m_CurrentProjectLogPath);

            m_ToolsPart.OnUpdate();

            ImGui::End(); // End dockspace
        }

		void OnEvent(Nitrogen::Event& e) override
		{
			m_CameraController.OnEvent(e);
		}

	private:
	    Nitrogen::OrthographicCameraController m_CameraController;
        ToolsPart m_ToolsPart;
        std::string m_CurrentProjectPath = "";
        std::string m_CurrentProjectLogPath = "";
	};
}