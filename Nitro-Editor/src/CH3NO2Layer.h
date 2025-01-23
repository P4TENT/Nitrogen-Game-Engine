#pragma once

#include <Nitrogen.h>

#include <imgui.h>

#include <cstdlib>

namespace Nitrogen {
	class CH3NO2Layer : public Nitrogen::Layer
	{
	public:
		CH3NO2Layer()
			: Layer("CH3NO2 Layer"), m_CameraController(1280.f / 720.f)
		{
		}

		void OnUpdate(Timestep deltaT) override
		{
			m_CameraController.OnUpdate(deltaT);

			RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RendererCommand::Clear();

			Renderer::BeginScene(m_CameraController.GetCamera());
			Renderer::EndScene();
		}

        void OnImGuiRender() override
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

            // Begin the main dockspace window
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
            ///////////////////////////////////////////
            // IMGUI DOCKSPACE ////////////////////////
            ///////////////////////////////////////////

            ///////////////////////////////////////////
            // TOOLS WINDOW ///////////////////////////
            ///////////////////////////////////////////
            ImGui::Begin("Tools");

            const char* options[] = { "Release", "Debug" };
            static int selectedOption = 0;
            ImGui::SetNextItemWidth(100);
            if (ImGui::BeginCombo("##BuildOptions", options[selectedOption]))
            {
                for (int i = 0; i < IM_ARRAYSIZE(options); i++)
                {
                    bool isSelected = (selectedOption == i);
                    if (ImGui::Selectable(options[i], isSelected))
                    {
                        selectedOption = i;
                    }
                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
            ImGui::SameLine();
            if (ImGui::Button("Run"))
            {
                if (selectedOption == 0) // Release
                {
                    int result = system("cd /d D:\\Code\\C++\\Nitrogen-Game-Engine\\Projects\\Sandbox\\backend\\scripts && RunRelease.bat");
                    if (result != 0)
                    {
                        // Handle the error if the batch file fails to execute
                        std::cerr << "Running Error";
                    }
                }
                else if (selectedOption == 1) // Debug
                {
                    int result = system("cd /d D:\\Code\\C++\\Nitrogen-Game-Engine\\Projects\\Sandbox\\backend\\scripts && RunDebug.bat");
                    if (result != 0)
                    {
                        // Handle the error if the batch file fails to execute
                        std::cerr << "Running Error";
                    }
                }
            }
            ///////////////////////////////////////////
            // TOOLS WINDOW ///////////////////////////
            ///////////////////////////////////////////

            ImGui::End(); // End tools window

            ImGui::End(); // End dockspace
        }


		void OnEvent(Nitrogen::Event& e) override
		{
			m_CameraController.OnEvent(e);
		}

	private:
		Nitrogen::OrthographicCameraController m_CameraController;
	};
}