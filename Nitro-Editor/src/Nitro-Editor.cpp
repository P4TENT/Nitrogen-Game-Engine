#include <Nitrogen.h>

#include "CH3NO2Layer.h"

namespace Nitrogen {
	class NitroEditor : public Nitrogen::Application
	{
	public:
		NitroEditor()
		{
			PushLayer(new CH3NO2Layer());
		}

		~NitroEditor()
		{

		}
	};
}

Nitrogen::Application* Nitrogen::CreateApplication()
{
	return new NitroEditor();
}