#pragma once

#include <Nitrogen.h>

#include <imgui.h>

#include <shlobj.h>

// OpenFolderDialog() IS TEMPORARY - TODO: MAKE A NEW EXPLORER FROM SCRATCH
static std::string OpenFolderDialog()
{
    wchar_t exePath[MAX_PATH];

    // Get the full path of the current executable
    DWORD length = GetModuleFileName(NULL, exePath, MAX_PATH);

    if (length == 0)
    {
        // Handle error if the function fails
        std::wcerr << L"Failed to get executable path!" << std::endl;
    }

    std::wstring path = std::wstring(exePath);

    if (path.empty()) NTG_CLIENT_ERROR("The selected Path is Empty!");

    // Extract the folder path from the executable path (get directory)
    size_t pos = path.find_last_of(L"\\/");
    if (pos != std::wstring::npos)
    {
        path = path.substr(0, pos); // Remove the executable name, keep the directory
    }

    // Go 3 directories back
    int backCount = 3;
    for (int i = 0; i < backCount; i++) {
        pos = path.find_last_of(L"\\/");
        if (pos != std::wstring::npos) {
            path = path.substr(0, pos); // Move 1 directory back
        }
        else {
            // If there's not enough directories, just break out early
            break;
        }
    }

    std::wstring folderName = L"Projects";

    if (!path.empty() && path.back() != L'\\' && path.back() != L'/') {
        path += L"\\";
    }

    // Append the folder
    path += folderName;

    BROWSEINFOW bi = { 0 };
    bi.lpszTitle = L"Select a Project.";

    if (!path.empty()) {
        // Convert the starting path to a PIDLIST_ABSOLUTE
        PIDLIST_ABSOLUTE pidlRoot;
        if (SUCCEEDED(SHParseDisplayName(path.c_str(), NULL, &pidlRoot, 0, NULL))) {
            bi.pidlRoot = pidlRoot;
        }
    }

    // Open the folder picker dialog
    PIDLIST_ABSOLUTE pidl = SHBrowseForFolder(&bi);
    if (pidl != NULL)
    {
        LPWSTR path;
        if (SHGetPathFromIDList(pidl, path))
        {
            std::wstring wstr(path);

            return std::string(wstr.begin(), wstr.end());  // Return the selected folder path
        }
    }
    return "";  // Return empty string if the user cancels
}

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

            // * OPEN PROJECT POPUP
            if (ImGui::Button("Open Project"))
            {
                // OpenFolderDialog() IS TEMPORARY - TODO: MAKE A NEW EXPLORER FROM SCRATCH
                std::string folderPath = OpenFolderDialog();
                if (!folderPath.empty())
                {
                    CurrentProjectPath = folderPath;
                    size_t pos = CurrentProjectPath.find_last_of("/\\");
                    std::string ProjectName = "Nitro-Engine: " + CurrentProjectPath.substr(pos + 1);  // Extract the folder name after the last separator
                    Application::Get().GetWindow().SetWindowTitle(ProjectName.c_str());
                }
            }

            // * RUN DEBUG / RELEASE
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
                if (CurrentProjectPath != "") // Check if the path is empty
                {
                    if (selectedOption == 0) // Release
                    {
                        std::string command = "cd /d " + CurrentProjectPath + "/backend/scripts && RunRelease.bat";
                        int result = system(command.c_str());
                        if (result != 0)
                        {
                            // Handle the error if the batch file fails to execute
                            std::cerr << "Running Error";
                        }
                    }
                    else if (selectedOption == 1) // Debug
                    {
                        std::string command = "cd /d " + CurrentProjectPath + "/backend/scripts && RunDebug.bat";
                        int result = system(command.c_str());
                        if (result != 0)
                        {
                            // Handle the error if the batch file fails to execute
                            std::cerr << "Running Error";
                        }
                    }
                }
                else
                {
                    ImGui::OpenPopup("Warning!");
                }
            }

            // Popup for Warning
            if (ImGui::BeginPopup("Warning!"))
            {
                // Set the window size for the popup
                ImGui::SetWindowSize(ImVec2(300, 150), ImGuiCond_Always);

                // Display a warning message
                ImGui::Text("There is no project selected!");
                ImVec2 windowSize = ImGui::GetWindowSize();
                ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize("Ok").x, ImGui::CalcTextSize("Ok").y - 20); // Padding
                ImVec2 centerPos = ImVec2((windowSize.x - buttonSize.x) * 0.5f, (windowSize.y - buttonSize.y) * 0.5f);
                ImGui::SetCursorPos(centerPos);

                // Buttons to close the popup or perform an action
                if (ImGui::Button("Ok"))
                {
                    // Close the popup when Ok is clicked
                    ImGui::CloseCurrentPopup();  // Close the popup
                }
                ImGui::EndPopup();
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
        std::string CurrentProjectPath;
	};
}