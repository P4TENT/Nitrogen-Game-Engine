#pragma once

#include <Nitrogen.h>

#include <imgui.h>

#include "ToolsPart.h"
#include "shellapi.h"

namespace Nitrogen {
	class CH3NO2Layer : public Layer
	{
	public:
		CH3NO2Layer();

        void OnAttach() override;
		void OnUpdate(Timestep deltaT) override;
        void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
	    OrthographicCameraController m_CameraController;
        ToolsPart m_ToolsPart;
        std::string m_CurrentProjectPath = "";
        std::string m_CurrentProjectLogPath = "";
	
        bool m_IsOpenProjDialogOpen = false;
    };
}