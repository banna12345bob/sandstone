#pragma once

#include<memory>

#include "Core.h"
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


#if !defined(SS_DIST)
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
#else
/* ------------------------- Core log macros ------------------------- */
#define SS_CORE_TRACE(...)
#define SS_CORE_INFO(...)
#define SS_CORE_WARN(...)
#define SS_CORE_ERROR(...)
#define SS_CORE_FATAL(...)

/* ------------------------ Client log macros ------------------------ */
#define SS_TRACE(...)
#define SS_INFO(...)
#define SS_WARN(...)
#define SS_ERROR(...)
#define SS_FATAL(...)
#endif