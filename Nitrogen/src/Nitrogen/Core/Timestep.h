#pragma once

#include <cmath>

namespace Nitrogen{
	class Timestep
	{
	public:
		Timestep(float time = 0.f, int precision = 5)
			: m_Time(time), decimals(precision) {}

		float GetSeconds() const { return RoundToDecimals(m_Time, decimals); }

		float GetMilliseconds() const { return RoundToDecimals(m_Time * 1000.f, decimals); }

		void SetDecimals(int precision) { decimals = precision; }

		// Retsurns the time in SECONDS
		operator float() const { return m_Time; }

	private:
		float m_Time;   
		int decimals;   

		float RoundToDecimals(float value, int n) const {
			float scale = (float)std::pow(10.f, n);
			return std::round(value * scale) / scale;
		}
	};
}
