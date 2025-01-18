#pragma once
#include "Core/Core.h"

namespace Nitrogen {

	class Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMBPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float>GetMousePosImpl() = 0;

	public:
		inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMBPressedImpl(button); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseXImpl(); }
		inline static std::pair<float, float>GetMousePos() { return s_Instance->GetMousePosImpl(); }

	private:
		static Input* s_Instance;
	};
}