#pragma once

#include <spdlog/spdlog.h>

namespace Nitrogen {
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define NTG_CORE_TRACE(...)    ::Nitrogen::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NTG_CORE_INFO(...)     ::Nitrogen::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NTG_CORE_WARN(...)     ::Nitrogen::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NTG_CORE_ERROR(...)    ::Nitrogen::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NTG_CORE_CRITICAL(...) ::Nitrogen::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define NTG_TRACE(...)         ::Nitrogen::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NTG_INFO(...)          ::Nitrogen::Log::GetClientLogger()->info(__VA_ARGS__)
#define NTG_WARN(...)          ::Nitrogen::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NTG_ERROR(...)         ::Nitrogen::Log::GetClientLogger()->error(__VA_ARGS__)
#define NTG_CRITICAL(...)      ::Nitrogen::Log::GetClientLogger()->critical(__VA_ARGS__)