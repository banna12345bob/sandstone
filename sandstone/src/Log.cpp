#include "Log.h"

#if !defined(SS_DIST)
#include <spdlog/sinks/stdout_color_sinks.h>
#endif
#include <spdlog/sinks/basic_file_sink.h>

namespace Sandstone {

	std::shared_ptr < spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr < spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Sandstone.log", true));
		logSinks[0]->set_pattern("[%T] [%l] %n: %v");

#if !defined(SS_DIST)
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks[1]->set_pattern("%^[%T] %n: %v%$");
#endif

		s_CoreLogger = std::make_shared<spdlog::logger>("SANDSTONE", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}

}