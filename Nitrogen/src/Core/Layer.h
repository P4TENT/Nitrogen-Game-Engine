#pragma once

#include <string>
#include "Events/Event.h"

namespace Nitrogen {
	class Layer
	{
	public:
		Layer(const std::string& name = "Nitrogen Layer");

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline std::string GetName() const { return m_Name; }
	
	private:
		std::string m_Name;
	};
}