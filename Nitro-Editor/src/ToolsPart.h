#pragma once

#include <imgui.h>
#include <string>
#include <fstream>
#include <filesystem> 
#include <thread> 
#include <iostream>

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
        void NoProjectSelectedPopup();

        std::string OpenProject();
        void ConsoleTab(const std::string& logFilePath);
        void Explorer();
        void OnUpdate();

        inline std::string GetCurrentProjectPath() const { return m_CurrentProjectPath; }
        inline std::string GetCurrentProjectName() const { return m_ProjectName; }
        inline int GetRunOption() const { return m_SelectedOption; }

    private:
        void RunCommandInThread(const std::string& command);
        void DisplayDirectoryTree(const std::filesystem::path& directory);

    private:
        std::string m_CurrentProjectPath = "";
        std::string m_ProjectName = "";
        std::string m_EditorVersion = "0.0.1r";
        int m_SelectedOption = 0;
    };
}