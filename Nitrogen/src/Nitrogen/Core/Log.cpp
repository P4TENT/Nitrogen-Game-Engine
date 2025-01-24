#include "ntgpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"  // Include async headers

namespace Nitrogen {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        // Initialize the thread pool for async logging
        spdlog::init_thread_pool(8192, 1); // 8192 queue size, 1 thread for processing log requests

        std::vector<spdlog::sink_ptr> logSinks;

        // Create sinks
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/Client.log", true));

        // Set patterns for sinks
        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        // Create async logger
        s_CoreLogger = std::make_shared<spdlog::logger>("NITROGEN", logSinks.begin(), logSinks.end());
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::critical);  // Optional: Automatically flush on certain levels

        // Create client logger
        s_ClientLogger = std::make_shared<spdlog::logger>("APP", logSinks.begin(), logSinks.end());
        spdlog::register_logger(s_ClientLogger);
        s_ClientLogger->set_level(spdlog::level::trace);
        s_ClientLogger->flush_on(spdlog::level::critical);  // Optional: Automatically flush on certain levels

        // Set the flush interval for async logger (flushes every 1000 seconds)
        spdlog::flush_every(std::chrono::seconds(3));
    }
}