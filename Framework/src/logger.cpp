#include "logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

static bool isInitialized = false; 

static std::shared_ptr<spdlog::logger> coreLogger;
static std::shared_ptr<spdlog::logger> clientLogger;

std::shared_ptr<spdlog::logger> getCoreLogger() { return coreLogger; }
std::shared_ptr<spdlog::logger> getClientLogger() { return clientLogger; }

void initLogger() 
{
	if(!isInitialized)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("Framework");
		coreLogger->set_level(spdlog::level::trace);
		clientLogger = spdlog::stdout_color_mt("Game");
		clientLogger->set_level(spdlog::level::trace);
	}
	else
	{
		CORE_LOG_WARN("Logger is allready initialized");
	}
}

void shutdownLogger()
{
	coreLogger.reset();
	clientLogger.reset();
}