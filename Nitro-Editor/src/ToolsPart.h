#pragma once

#include <Nitrogen.h>
#include <imgui.h>
#include <shlobj.h>
#include <string>
#include <fstream>
#include <filesystem> 
#include <thread>  // Include thread support
#include <iostream> // Include for std::cerr

// OpenFolderDialog() IS TEMPORARY - TODO: MAKE A NEW EXPLORER FROM SCRATCH
static std::string OpenFolderDialog()
{
    wchar_t exePath[MAX_PATH];

    // Get the full path of the current executable
    DWORD length = GetModuleFileName(NULL, exePath, MAX_PATH);

    if (length == 0)
    {
        std::wcerr << L"Failed to get executable path!" << std::endl;
    }

    std::wstring path = std::wstring(exePath);

    if (path.empty()) NTG_CLIENT_ERROR("The selected Path is Empty!");

    size_t pos = path.find_last_of(L"\\/");

    if (pos != std::wstring::npos)
    {
        path = path.substr(0, pos);
    }

    int backCount = 3;
    for (int i = 0; i < backCount; i++) {
        pos = path.find_last_of(L"\\/");

        if (pos != std::wstring::npos) {
            path = path.substr(0, pos);
        }
        else {
            break;
        }
    }

    std::wstring folderName = L"Projects";

    if (!path.empty() && path.back() != L'\\' && path.back() != L'/') {
        path += L"\\";  // Ensure path ends with backslash
    }

    path += folderName;

    BROWSEINFOW bi = { 0 };
    bi.lpszTitle = L"Select a Project.";

    if (!path.empty()) {
        PIDLIST_ABSOLUTE pidlRoot;
        if (SUCCEEDED(SHParseDisplayName(path.c_str(), NULL, &pidlRoot, 0, NULL))) {
            bi.pidlRoot = pidlRoot;
        }
    }

    PIDLIST_ABSOLUTE pidl = SHBrowseForFolder(&bi);
    if (pidl != NULL)
    {
        wchar_t path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path))
        {
            std::wstring wstr(path);
            return std::string(wstr.begin(), wstr.end());  // Return selected folder
        }
    }
    return "";  // Return empty string if user cancels
}


namespace Nitrogen {

    class ToolsPart
    {
    public:
        std::string OpenProject()
        {
            std::string folderPath = OpenFolderDialog();
            if (!folderPath.empty())
            {
                m_CurrentProjectPath = folderPath;
                size_t pos = m_CurrentProjectPath.find_last_of("/\\");
                m_ProjectName = m_CurrentProjectPath.substr(pos + 1);
                std::string ProjectName = "Nitro-Engine: " + m_ProjectName;
                Application::Get().GetWindow().SetWindowTitle(ProjectName.c_str());
                return m_CurrentProjectPath;
            }
            return ""; // Return empty string if no project was selected
        }



        void NoProjectSelectedPopup()
        {
            if (ImGui::BeginPopup("Warning!"))
            {
                ImGui::SetWindowSize(ImVec2(300, 150), ImGuiCond_Always);
                ImGui::Text("There is no project selected!");
                ImVec2 windowSize = ImGui::GetWindowSize();
                ImVec2 buttonSize = ImVec2(ImGui::CalcTextSize("Ok").x, ImGui::CalcTextSize("Ok").y - 20);
                ImVec2 centerPos = ImVec2((windowSize.x - buttonSize.x) * 0.5f, (windowSize.y - buttonSize.y) * 0.5f);
                ImGui::SetCursorPos(centerPos);

                if (ImGui::Button("Ok"))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }



        void ConsoleTab(const std::string& logFilePath)
        {
            static std::string logContent;
            static std::size_t lastFileSize = 0;
            static bool autoScroll = true;

            ImGui::Begin("Console", nullptr);
            ImVec2 windowSize = ImVec2(500, 300);
            ImGui::SetWindowSize(windowSize, ImGuiCond_FirstUseEver);

            if (!logFilePath.empty()) {
                std::filesystem::path fsPath = logFilePath;
                std::size_t currentFileSize = std::filesystem::file_size(fsPath);

                if (currentFileSize != lastFileSize) {
                    lastFileSize = currentFileSize;

                    std::ifstream logFile(logFilePath);
                    if (logFile.is_open()) {
                        std::stringstream buffer;
                        buffer << logFile.rdbuf();
                        logContent = buffer.str();
                        logFile.close();
                    }
                    else {
                        logContent = "Failed to open log file: " + logFilePath;
                    }
                }
            }
            else {
                logContent = "Nitrogen Engine.";
            }

            // Start the child window for the log content
            ImGui::BeginChild("LogRegion", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true, ImGuiWindowFlags_HorizontalScrollbar);

            // Process the logContent line by line
            std::istringstream logStream(logContent);
            std::string line;
            while (std::getline(logStream, line)) {
                // Check if the line contains "[info]" and change color accordingly
                if (line.find("[info]") != std::string::npos) {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.21f, 0.53f, 0.28f, 1.0f)); // Set text color to green
                }
                else if (line.find("[warning]") != std::string::npos) {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.61f, 0.53f, 0.28f, 1.0f)); // Set text color to green
                }
                else if (line.find("[error]") != std::string::npos) {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.71f, 0.43f, 0.28f, 1.0f)); // Set text color to green
                }
                else if (line.find("[critical]") != std::string::npos) {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.61f, 0.23f, 0.28f, 1.0f)); // Set text color to green
                }
                else {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // Default color
                }

                ImGui::TextUnformatted(line.c_str()); // Display the line

                // Pop the color style after each line
                ImGui::PopStyleColor();
            }

            // Auto-scroll to the bottom if enabled
            if (autoScroll && ImGui::GetScrollY() < ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0f);
            }
            ImGui::EndChild();

            // Auto-scroll toggle
            ImGui::Checkbox("Auto-Scroll", &autoScroll);

            ImGui::End();
        }



        void OnUpdate()
        {
            ImGui::Begin("Project", nullptr);
            ImVec2 windowSize = ImVec2(300, 200);
            ImGui::SetWindowSize(windowSize);

            const char* options[] = { "Release", "Debug" };
            ImGui::SetNextItemWidth(100);
            if (ImGui::BeginCombo("##BuildOptions", options[m_SelectedOption]))
            {
                for (int i = 0; i < IM_ARRAYSIZE(options); i++)
                {
                    bool isSelected = (m_SelectedOption == i);
                    if (ImGui::Selectable(options[i], isSelected))
                    {
                        m_SelectedOption = i;
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
                if (!m_CurrentProjectPath.empty())
                {
                    std::string command;
                    if (m_SelectedOption == 0) {
                        command = "cd /d " + m_CurrentProjectPath + "/backend/scripts && RunRelease.bat";
                    }
                    else if (m_SelectedOption == 1) {
                        command = "cd /d " + m_CurrentProjectPath + "/backend/scripts && RunDebug.bat";
                    }

                    // Run the command in a separate thread
                    std::thread commandThread(&ToolsPart::RunCommandInThread, this, command);
                    commandThread.detach();  // Detach to let it run independently
                }
                else
                {
                    ImGui::OpenPopup("Warning!");
                }
            }

            NoProjectSelectedPopup();
            ImGui::End();
        }



        std::string GetCurrentProjectPath() const { return m_CurrentProjectPath; }
        std::string GetCurrentProjectName() const { return m_ProjectName; }
        int GetRunOption() const { return m_SelectedOption; }



    private:
        void RunCommandInThread(const std::string& command)
        {
            int result = system(command.c_str());
            if (result != 0)
            {
                std::cerr << "Running Error" << std::endl;
            }
        }

    private:
        std::string m_CurrentProjectPath = "";
        std::string m_ProjectName;
        int m_SelectedOption = 0;
    };
}