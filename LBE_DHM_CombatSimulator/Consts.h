#pragma once
#include <SFML/Graphics.hpp>
#include <ImGui\imgui.h>
#include <ImGui\imgui-SFML.h>
#include "Log.h"

namespace lbe
{
	const sf::Vector2f SCREEN_SIZE(1920, 1080);
	const sf::Vector2f DEFAULT_SCREEN_SIZE_REDUCTION(20, 80);
	const sf::String WINDOW_NAME("Diamondhunt Mobile Combat Simulator - 1.12");

	const spdlog::level::level_enum LOGGER_LEVEL = spdlog::level::trace;

	const double PI = 3.14159265359f;
	const double HalfC = PI / 180;

	const int NUM_WEAPON_SETS = 23;
	const int SAVE_STRING_MAX_SIZE = 2048;
	const int SAVE_PRESET_NAME_MAX_SIZE = 40;
	const int THREAD_ITERATION_SIZE = 10000;

	const sf::String DIAMONDHUNT_ICON("./assets/textures/diamond.png");
	const std::string CUSTOM_PRESET_PATH(".\\presets\\");

	const ImVec4 STAT_BAR_BACKGROUND(0.2f, 0.2f, 0.2f, 1.f);
	//const ImVec4 WEAPON_BAR_FOREGROUND(1.f, 1.f, 1.f, 1.f);
	//const ImVec4 WEAPON_BAR_FOREGROUND(0.6f, 0.6f, 0.6f, 1.f);
	//const ImVec4 POISON_BAR_FOREGROUND(0.41f, 0.73f, 0.03f, 1.f);
	//const ImVec4 FIRE_BAR_FOREGROUND(0.8f, 0.04f, 0.04f, 1.f);
	//const ImVec4 ICE_BAR_FOREGROUND(0.09f, 0.72f, 0.93f, 1.f);
	const ImVec4 WEAPON_BAR_FOREGROUND(1.f, 0.65f, 0.12f, 1.f);
	const ImVec4 POISON_BAR_FOREGROUND(0.f, 0.706f, 0.f, 1.f);
	const ImVec4 FIRE_BAR_FOREGROUND(1.f, 0.f, 0.f, 1.f);
	const ImVec4 ICE_BAR_FOREGROUND(0.06f, 0.66f, 0.86f, 1.f);
	const ImVec4 REFLECT_BAR_FOREGROUND(0.8f, 1.f, 1.f, 1.f);
	const ImVec4 THUNDER_BAR_FOREGROUND(0.93f, 0.85f, 0.09f, 1.f);
}