#include "Log.h"

#include <spdlog\sinks\stdout_color_sinks.h>

#include "Consts.h"

std::shared_ptr<spdlog::logger> lbe::Log::Logger;

void lbe::Log::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");
	Logger = spdlog::stdout_color_mt("LBE");
	Logger->set_level(LOGGER_LEVEL);
	LBE_INFO("Initialized Logger!");
}
