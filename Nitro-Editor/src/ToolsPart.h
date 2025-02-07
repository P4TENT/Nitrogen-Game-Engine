#pragma once

#include <imgui.h>
#include <string>
#include <fstream>
#include <filesystem> 
#include <thread> 

static std::string OpenFolderDialog()
{
    // Get the current working directory
    std::filesystem::path path = std::filesystem::current_path();

    std::filesystem::path newPath = path;
    while (newPath.filename().string() != "Nitrogen-Game-Engine") {
        if (newPath == newPath.root_path()) {
            std::cerr << "Directory 'Nitrogen-Game-Engine' not found in the path hierarchy!" << std::endl;
            return "";  
        }
        newPath = newPath.parent_path();
    }
    std::filesystem::current_path(newPath.string() + "\\Projects");

    std::vector<std::string> ProjectPaths;
    std::vector<std::string> ProjectNames;

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (std::filesystem::is_directory(entry.status())) {
            ProjectPaths.push_back(entry.path().string());
            ProjectNames.push_back(entry.path().filename().string());
        }
    }

    std::string selectedProject = "";

    ImGui::OpenPopup("Open Project");
    if(ImGui::BeginPopup("Open Project"))
    { 
        ImGui::BeginChild("Open Project...", ImVec2(400,200), true);
        ImGui::TextColored(ImVec4(0.4f, 0.5f, 0.7f, 0.7f), "Open Nitrogen Project...");
        uint16_t idx = 0;
        for (std::string project : ProjectNames)
        {
            ImGui::Separator();
        
            if (ImGui::Selectable(("  Project " + project).c_str(), false, 0, ImVec2(380, 20)))
            {
                selectedProject = ProjectPaths[idx].c_str();
            }

            idx++;
        }
        ImGui::Separator();

        ImGui::EndChild();
        ImGui::EndPopup();
    }

    return selectedProject;
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


        void Explorer()
        {
            ImGui::Begin("Project Explorer");

            if (m_CurrentProjectPath.empty())
            {
                ImGui::Text("No project selected.");
                ImGui::End();
                return;
            }

            ImGui::Text("Project: %s", m_ProjectName.c_str());
            ImGui::Separator();

            std::filesystem::path fs_currentProjPath = m_CurrentProjectPath + "\\" + m_ProjectName + "\\src";

            // Start displaying the tree from the root project directory
            if (ImGui::TreeNode(fs_currentProjPath.filename().string().c_str()))
            {
                DisplayDirectoryTree(fs_currentProjPath);
                ImGui::TreePop();
            }

            ImGui::End();
        }


        void OnUpdate()
        {
            ImGui::Begin("Project", nullptr, ImGuiWindowFlags_NoScrollbar);
            ImVec2 windowSize = ImVec2(300, 200);
            ImGui::SetWindowSize(windowSize);

            ImVec4 titleColor = ImVec4(0.7f, 0.8f, 0.7f, 1.0f);  // Green accent color (nitrogen-like)
            ImVec4 textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // White text
            ImVec4 separatorColor = ImVec4(0.4f, 0.5f, 0.6f, 0.5f);  // Light green separator

            // Title text with nitrogen theme colors
            std::string editorShi = (m_ProjectName.empty()) ? "Nitrogen Editor Version " + m_EditorVersion : "Project " + m_ProjectName;
            ImGui::TextColored(titleColor, "%s", editorShi.c_str());

            // Separator with a nitrogen-style green color
            ImGui::PushStyleColor(ImGuiCol_Separator, separatorColor);
            ImGui::Separator();
            ImGui::PopStyleColor();

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

        void DisplayDirectoryTree(const std::filesystem::path& directory)
        {
            // Ensure path exists and is a directory
            if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
                return;

            // Separate directories and files
            std::vector<std::filesystem::path> directories;
            std::vector<std::filesystem::path> files;

            for (const auto& entry : std::filesystem::directory_iterator(directory))
            {
                if (entry.is_directory())
                    directories.push_back(entry.path());
                else
                    files.push_back(entry.path());
            }

            // Sort directories and files alphabetically
            std::sort(directories.begin(), directories.end());
            std::sort(files.begin(), files.end());

            // Display directories first
            for (const auto& dir : directories)
            {
                // Tree node for directories (expandable)
                ImGui::Separator();
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.48f, 0.58f, 0.76f, 1.0f)); // Yellowish color for folders
                bool opened = ImGui::TreeNode(dir.filename().string().c_str());
                ImGui::PopStyleColor(); // Restore original text color

                if (opened)
                {
                    DisplayDirectoryTree(dir); // Recursively display subdirectories
                    ImGui::TreePop();
                }

            }

            // Display files (non-expandable)
            for (const auto& file : files)
            {
                ImGui::Selectable(("    " + file.filename().string()).c_str());
            }
        }

    private:
        std::string m_CurrentProjectPath = "";
        std::string m_ProjectName = "";
        std::string m_EditorVersion = "0.0.1r";
        int m_SelectedOption = 0;
    };
}