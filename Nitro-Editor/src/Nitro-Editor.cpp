#include <Nitrogen.h>
#include <Nitrogen/Core/EntryPoint.h>

#include "CH3NO2Layer.h"

namespace Nitrogen {
	class NitroEditor : public Application
	{
	public:
		NitroEditor()
			:	Application("Nitro-Editor")
		{
			PushLayer(new CH3NO2Layer());
		}

		~NitroEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new NitroEditor();
	}
}