#pragma once

#include "ErigonEngine/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ErigonEngine
{
	class Log
	{
	public:
		static void Init();
		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}


//Core Log macros

#define EE_CORE_FATAL(...) ::ErigonEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define EE_CORE_ERROR(...) ::ErigonEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EE_CORE_INFO(...) ::ErigonEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EE_CORE_WARN(...) ::ErigonEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EE_CORE_TRACE(...) ::ErigonEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)


//Client Log macros

#define EE_FATAL(...) ::ErigonEngine::Log::GetClientLogger()->critical(__VA_ARGS__)
#define EE_ERROR(...) ::ErigonEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define EE_INFO(...) ::ErigonEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define EE_WARN(...) ::ErigonEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EE_TRACE(...) ::ErigonEngine::Log::GetClientLogger()->trace(__VA_ARGS__)