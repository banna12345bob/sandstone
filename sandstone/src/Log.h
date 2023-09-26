#pragma once

#include<memory>

#include "core.h"
#include "spdlog/spdlog.h"

namespace Sandstone {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr < spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr < spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr < spdlog::logger> s_CoreLogger;
		static std::shared_ptr < spdlog::logger> s_ClientLogger;
	};

}


/* ------------------------- Core log macros ------------------------- */
#define SS_CORE_TRACE(...)   ::Sandstone::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SS_CORE_INFO(...)    ::Sandstone::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SS_CORE_WARN(...)    ::Sandstone::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SS_CORE_ERROR(...)   ::Sandstone::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SS_CORE_FATAL(...)   ::Sandstone::Log::GetCoreLogger()->critical(__VA_ARGS__)

/* ------------------------ Client log macros ------------------------ */
#define SS_TRACE(...)        ::Sandstone::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SS_INFO(...)         ::Sandstone::Log::GetClientLogger()->info(__VA_ARGS__)
#define SS_WARN(...)         ::Sandstone::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SS_ERROR(...)        ::Sandstone::Log::GetClientLogger()->error(__VA_ARGS__)
#define SS_FATAL(...)        ::Sandstone::Log::GetClientLogger()->critical(__VA_ARGS__)
