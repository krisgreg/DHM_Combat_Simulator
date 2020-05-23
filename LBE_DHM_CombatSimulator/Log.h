#pragma once
#include <spdlog\spdlog.h>

namespace lbe
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> Logger;

	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return Logger; }
	};
}

// Logger macros
#define LBE_TRACE(...)    ::lbe::Log::GetLogger()->trace(__VA_ARGS__)
#define LBE_INFO(...)     ::lbe::Log::GetLogger()->info(__VA_ARGS__)
#define LBE_WARN(...)     ::lbe::Log::GetLogger()->warn(__VA_ARGS__)
#define LBE_ERROR(...)    ::lbe::Log::GetLogger()->error(__VA_ARGS__)
#define LBE_CRITICAL(...) ::lbe::Log::GetLogger()->critical(__VA_ARGS__)

// https://github.com/gabime/spdlog