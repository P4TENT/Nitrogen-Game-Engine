#pragma once

#include "Nitrogen/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "spdlog/sinks/basic_file_sink.h" 

namespace Nitrogen{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

// CORE LOG MACROS
#define NTG_CORE_FATAL(...)      ::Nitrogen::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define NTG_CORE_ERROR(...)      ::Nitrogen::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NTG_CORE_WARN(...)       ::Nitrogen::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NTG_CORE_INFO(...)       ::Nitrogen::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NTG_CORE_TRACE(...)      ::Nitrogen::Log::GetCoreLogger()->trace(__VA_ARGS__)

// CLIENT LOG MACROS
#define NTG_CLIENT_FATAL(...)    ::Nitrogen::Log::GetClientLogger()->critical(__VA_ARGS__)
#define NTG_CLIENT_ERROR(...)    ::Nitrogen::Log::GetClientLogger()->error(__VA_ARGS__)
#define NTG_CLIENT_WARN(...)     ::Nitrogen::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NTG_CLIENT_INFO(...)     ::Nitrogen::Log::GetClientLogger()->info(__VA_ARGS__)
#define NTG_CLIENT_TRACE(...)    ::Nitrogen::Log::GetClientLogger()->trace(__VA_ARGS__)