#include <SFML/Graphics.hpp>
#include <ImGui\imgui.h>
#include <ImGui\imgui-SFML.h>
#include <random>
#include <memory>
#include <thread>
#include <future>

#include "Consts.h"
#include "Log.h"
#include "TextureLoader.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemies.h"
#include "Resources.h"
#include "CombatStatsStruct.h"


sf::Clock SimClock;
sf::Time SimTime;

std::vector<std::future<std::shared_ptr<CombatStats>>> ThreadResults;

std::shared_ptr<CombatStats> Simulate(EnemyType TypeOfEnemy)
{
	Player Player;
	Enemy CurrentEnemy(&Player);
	CurrentEnemy.SetType(TypeOfEnemy);
	Player.SetEnemy(&CurrentEnemy);

	std::shared_ptr<CombatStats> Stats = std::make_shared<CombatStats>();
	Player.LinkStatsStruct(Stats);
	CurrentEnemy.LinkStatsStruct(Stats);

	int PlayerHp = (Resources::PlayerHPCurrentlySelected + 1) * 10;

	LBE_INFO("Thread Started!");

	for (int i = 0; i < 10000; i++)
	{
		Player.Init(PlayerHp);
		CurrentEnemy.ResetStats();

		if (Player.Simulate())
		{
			Stats->NumWins += 1;
		}

		Stats->NumIterations += 1;
	}

	LBE_INFO("Thread Finished! returning...");
	return Stats;
}

void StartSimulating(EnemyType TypeOfEnemy)
{
	SimClock.restart();
	Resources::CurrentIteration = 0;
	Resources::NumWins = 0;
	Resources::bIsCurrentlySimulating = true;
	Resources::ResetStats();
	ThreadResults.clear();
	for (int i = 0; i < Resources::NumIterations / lbe::THREAD_ITERATION_SIZE; i++)
	{
		ThreadResults.push_back(std::async(Simulate, TypeOfEnemy));
	}
}

float AverageOverIterations(int StatToAverage)
{
	return ((float)StatToAverage / (float)Resources::CurrentIteration);
}

void CreateButton(const char* ButtonText, EnemyType TypeOfEnemy)
{
	if (ImGui::Button(ButtonText, ImVec2(160, 40)))
	{
		Enemies::SetCurrentEnemyType(TypeOfEnemy);
		StartSimulating(TypeOfEnemy);
	}
}

void CreateProgressBar(const ImVec4 ColorBG, const ImVec4 ColorFG, float FillPercent, float StatValue)
{
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ColorBG);
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ColorFG);

	//char StatbarText[20];
	//sprintf_s(StatbarText, sizeof(StatbarText), "%f", StatValue);
	//ImGui::ProgressBar(FillPercent, ImVec2(-1, 0), StatbarText);

	char StatbarText[20];
	sprintf_s(StatbarText, sizeof(StatbarText), "");
	ImGui::ProgressBar(FillPercent, ImVec2(-1, 14), StatbarText);

	//ImGui::ProgressBar(FillPercent);

	ImGui::PopStyleColor(2);
}

void SpacedSeparator()
{
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
}

int main()
{
	lbe::Log::Init();
	lbe::TextureLoader::InitTextures();

	std::srand(std::time(nullptr));

#ifdef _DEBUG
	sf::RenderWindow window(sf::VideoMode(lbe::SCREEN_SIZE.x, lbe::SCREEN_SIZE.y), lbe::WINDOW_NAME);
#else
	sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width - lbe::DEFAULT_SCREEN_SIZE_REDUCTION.x, sf::VideoMode::getDesktopMode().height - lbe::DEFAULT_SCREEN_SIZE_REDUCTION.y), lbe::WINDOW_NAME);
	window.setPosition(sf::Vector2i(0, 0));
#endif

	window.setFramerateLimit(60);

	sf::Image DiamondhuntIcon;
	DiamondhuntIcon = lbe::TextureLoader::DiamondHuntIcon.copyToImage();
	window.setIcon(372, 372, DiamondhuntIcon.getPixelsPtr());

	int WindowHeight = window.getSize().y;

	ImGui::SFML::Init(window);

	static bool bOpenAllHeaders = true;
	static bool bCollapseAllHeaders = false;

	const int NUM_PRESETS = 18;
	static bool bUsePreset[NUM_PRESETS];
	for (auto &i : bUsePreset)
	{
		i = false;
	}

	const char* PLAYER_HP_OPTIONS[] = { "10", "20", "30", "40", "50", "60", "70", "80" };
	const char* CUSTOM_DAMAGE_RETALIATION_TYPES[] = { "Any", "Melee", "Ranged" };

	Resources::LoadCustomPresets();

	sf::Clock Clock;
	sf::Time dt;
	while (window.isOpen())
	{
		dt = Clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::Resized)
			{
				WindowHeight = window.getSize().y;
			}
		}

		ImGui::SFML::Update(window, dt);
		//ImGui::ShowDemoWindow();

		static bool no_titlebar = false;
		static bool no_scrollbar = false;
		static bool no_menu = false;
		static bool no_move = true;
		static bool no_resize = true;
		static bool no_collapse = true;
		static bool no_nav = false;
		static bool no_background = false;
		static bool no_bring_to_front = false;

		ImGuiWindowFlags window_flags = 0;
		if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
		if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
		if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
		if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
		if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
		if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
		if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
		if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
		if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

		// ---------------- Gear Selector Window -----------------------------------------------------------------------------------------
		ImGui::SetNextWindowPos(ImVec2(20, 20));
		ImGui::SetNextWindowSize(ImVec2(650, WindowHeight - 40));

		ImGui::Begin("Gear Selector", NULL, window_flags);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::MenuItem("Open All Headers", NULL, &bOpenAllHeaders);
				ImGui::MenuItem("Collapse All Headers", NULL, &bCollapseAllHeaders);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Presets"))
			{
				ImGui::MenuItem("Starter",			NULL, &bUsePreset[0]);
				ImGui::MenuItem("Fields",			NULL, &bUsePreset[1]);
				ImGui::MenuItem("Forest",			NULL, &bUsePreset[2]);
				ImGui::MenuItem("Caves",			NULL, &bUsePreset[3]);
				ImGui::MenuItem("Volcano",			NULL, &bUsePreset[4]);
				ImGui::MenuItem("Northern Fields",	NULL, &bUsePreset[5]);
				ImGui::MenuItem("Haunted Mansion",	NULL, &bUsePreset[6]);
				ImGui::MenuItem("Desert",			NULL, &bUsePreset[7]);
				ImGui::MenuItem("Ocean",			NULL, &bUsePreset[8]);
				ImGui::MenuItem("Jungle",			NULL, &bUsePreset[9]);
				ImGui::MenuItem("Dungeon Entrance", NULL, &bUsePreset[10]);
				ImGui::MenuItem("Dungeon",			NULL, &bUsePreset[11]);
				ImGui::MenuItem("Coffin",			NULL, &bUsePreset[12]);
				ImGui::MenuItem("Castle",			NULL, &bUsePreset[13]);
				ImGui::MenuItem("Cemetery",			NULL, &bUsePreset[14]);
				ImGui::MenuItem("Factory",			NULL, &bUsePreset[15]);
				ImGui::MenuItem("Haunted Woods",	NULL, &bUsePreset[16]);
				ImGui::MenuItem("Deep Ocean",		NULL, &bUsePreset[17]);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Custom Presets"))
			{
				for (auto &kv : Resources::CustomPresetButtonToggles)
				{
					ImGui::MenuItem(kv.first.c_str(), NULL, &kv.second);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		if (bOpenAllHeaders)
		{
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Weapons"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Shield / Offhand"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Armor"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Back / Other"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Gloves"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Neck"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Rings"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Research & Quests"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Spells and Emblems"), 2);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Potions"), 2);
			bOpenAllHeaders = false;
		}
		if (bCollapseAllHeaders)
		{
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Weapons"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Shield / Offhand"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Armor"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Back / Other"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Gloves"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Neck"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Rings"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Research & Quests"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Spells and Emblems"), 0);
			ImGui::GetStateStorage()->SetInt(ImGui::GetID("Potions"), 0);
			bCollapseAllHeaders = false;
		}
		for (int i = 0; i < NUM_PRESETS; i++)
		{
			if (bUsePreset[i])
			{
				Resources::UsePreset(i);
				bUsePreset[i] = false;
			}
		}
		for (auto &kv : Resources::CustomPresetButtonToggles)
		{
			if (kv.second)
			{
				//LBE_TRACE("Preset loaded: {0}", Resources::CustomPresets.at(kv.first));
				strcpy_s(Resources::SaveStringText, Resources::CustomPresets.at(kv.first).c_str());
				Resources::LoadSaveString();
				kv.second = false;
			}
		}
		ImGui::Text("Select what resources you have available!");
		if (ImGui::CollapsingHeader("Presets"))
		{
			ImGui::Spacing();
			//ImGui::InputText(" Save String", Resources::SaveStringText, IM_ARRAYSIZE(Resources::SaveStringText));
			//ImGui::Spacing();
			if (ImGui::Button("Copy Preset String\n  to Clipboard", ImVec2(160, 40)))
			{
				Resources::GenerateSaveString();
				ImGui::SetClipboardText(Resources::SaveStringText);
			}
			ImGui::SameLine();
			if (ImGui::Button("Load Preset String\n from Clipboard", ImVec2(160, 40)))
			{
				strcpy_s(Resources::SaveStringText, ImGui::GetClipboardText());
				Resources::LoadSaveString();
			}
			SpacedSeparator();
			ImGui::InputText(" Preset Name", Resources::SavePresetName, IM_ARRAYSIZE(Resources::SavePresetName));
			ImGui::Spacing();
			if (ImGui::Button("Save Preset", ImVec2(160, 40)))
			{
				if (Resources::SavePresetName[0] != '\0')
				{
					Resources::GenerateSaveString();
					Resources::SavePreset();
					Resources::LoadCustomPresets();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete Preset", ImVec2(160, 40)))
			{
				if (Resources::SavePresetName[0] != '\0')
				{
					Resources::DeletePreset();
					Resources::LoadCustomPresets();
				}
			}
			ImGui::Spacing();
		}
		if (ImGui::CollapsingHeader("Weapons"))
		{
			ImGui::Spacing();
			ImGui::Checkbox("Rusty Sword", &Resources::bHasRustySword); ImGui::SameLine(150);
			ImGui::Checkbox("Stinger", &Resources::bHasStinger); ImGui::SameLine(300);
			ImGui::Checkbox("Iron Dagger", &Resources::bHasIronDagger); ImGui::SameLine(450);
			ImGui::Checkbox("Skeleton Sword", &Resources::bHasSkeletonSword);
			ImGui::Checkbox("Scythe", &Resources::bHasScythe); ImGui::SameLine(150);
			ImGui::Checkbox("Enchanted Scythe", &Resources::bHasEnchantedScythe); ImGui::SameLine(300);
			ImGui::Checkbox("Mace", &Resources::bHasMace);
			ImGui::Checkbox("Trident", &Resources::bHasTrident); ImGui::SameLine(150);
			ImGui::Checkbox("Poison Trident+", &Resources::bHasPoisonTridentPlus); ImGui::SameLine(300);
			ImGui::Checkbox("Silver Scimitar", &Resources::bHasSilverScimitar);
			SpacedSeparator();
			ImGui::Checkbox("Poison Spear", &Resources::bHasPoisonSpear); ImGui::SameLine(150);
			ImGui::Checkbox("Poison Spear+", &Resources::bHasPoisonSpearPlus);
			SpacedSeparator();
			ImGui::Checkbox("Bow", &Resources::bHasBow); ImGui::SameLine(150);
			ImGui::Checkbox("Super Bow", &Resources::bHasSuperBow); ImGui::SameLine(300);
			ImGui::Checkbox("Enchanted Super Bow", &Resources::bHasEnchantedSuperBow);
			ImGui::Checkbox("Arrows", &Resources::bHasArrows); ImGui::SameLine(150);
			ImGui::Checkbox("Fire Arrows", &Resources::bHasFireArrows); ImGui::SameLine(300);
			ImGui::Checkbox("Ice Arrows", &Resources::bHasIceArrows); ImGui::SameLine(450);
			ImGui::Checkbox("Poison Arrows", &Resources::bHasPoisonArrows);
			ImGui::Checkbox("Arrows+", &Resources::bHasArrowsPlus); ImGui::SameLine(450);
			ImGui::Checkbox("Poison Arrows+", &Resources::bHasPoisonArrowsPlus);
			SpacedSeparator();
			ImGui::Checkbox("Mage Staff", &Resources::bHasMageStaff);
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Shield / Offhand"))
		{
			ImGui::Spacing();
			ImGui::Checkbox("Skeleton Shield", &Resources::bHasSkeletonShield); ImGui::SameLine(150);
			ImGui::Checkbox("Jungle Shield", &Resources::bHasJungleShield); ImGui::SameLine(300);
			ImGui::Checkbox("Knights Shield", &Resources::bHasKnightsShield); ImGui::SameLine(450);
			ImGui::Checkbox("Super Jungle Shield", &Resources::bHasSuperJungleShield);
			SpacedSeparator();
			ImGui::Checkbox("Offhand Dagger", &Resources::bHasOffHandDagger);
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Armor"))
		{
			ImGui::Spacing();
			ImGui::RadioButton("Head: None",		&Resources::BestHeadArmor, 0); ImGui::SameLine(200);
			ImGui::RadioButton("Body: None",		&Resources::BestBodyArmor, 0); ImGui::SameLine(400);
			ImGui::RadioButton("Legs: None",		&Resources::BestLegArmor, 0);

			ImGui::RadioButton("Head: Bear Fur",	&Resources::BestHeadArmor, 1); ImGui::SameLine(200);
			ImGui::RadioButton("Body: Bear Fur",	&Resources::BestBodyArmor, 1); ImGui::SameLine(400);
			ImGui::RadioButton("Legs: Bear Fur",	&Resources::BestLegArmor, 1);

			ImGui::RadioButton("Head: Snake",		&Resources::BestHeadArmor, 2); ImGui::SameLine(200);
			ImGui::RadioButton("Body: Snake",		&Resources::BestBodyArmor, 2); ImGui::SameLine(400);
			ImGui::RadioButton("Legs: Snake",		&Resources::BestLegArmor, 2);

			ImGui::RadioButton("Head: Lava Snake",	&Resources::BestHeadArmor, 3); ImGui::SameLine(200);
			ImGui::RadioButton("Body: Lava Snake",	&Resources::BestBodyArmor, 3); ImGui::SameLine(400);
			ImGui::RadioButton("Legs: Lava Snake",	&Resources::BestLegArmor, 3);

			ImGui::RadioButton("Head: Lizard",		&Resources::BestHeadArmor, 4); ImGui::SameLine(200);
			ImGui::RadioButton("Body: Lizard",		&Resources::BestBodyArmor, 4); ImGui::SameLine(400);
			ImGui::RadioButton("Legs: Lizard",		&Resources::BestLegArmor, 4);

			ImGui::RadioButton("Head: Elephant",	&Resources::BestHeadArmor, 5); ImGui::SameLine(200);
			ImGui::RadioButton("Body: Elephant",	&Resources::BestBodyArmor, 5); ImGui::SameLine(400);
			ImGui::RadioButton("Legs: Elephant",	&Resources::BestLegArmor, 5);

			ImGui::RadioButton("Head: Promethium",	&Resources::BestHeadArmor, 6); ImGui::SameLine(200);
			ImGui::RadioButton("Body: Promethium",	&Resources::BestBodyArmor, 6); ImGui::SameLine(400);
			ImGui::RadioButton("Legs: Promethium",	&Resources::BestLegArmor, 6);

			ImGui::RadioButton("Head: Titanium",	&Resources::BestHeadArmor, 7); ImGui::SameLine(200);
			ImGui::RadioButton("Body: Titanium",	&Resources::BestBodyArmor, 7); ImGui::SameLine(400);
			ImGui::RadioButton("Legs: Titanium",	&Resources::BestLegArmor, 7);

			ImGui::RadioButton("Head: Ocean Soldier", &Resources::BestHeadArmor, 8);

			ImGui::RadioButton("Head: Ocean Soldier+", &Resources::BestHeadArmor, 9);

			SpacedSeparator();
			ImGui::Checkbox("Mage Robes", &Resources::bHasMageRobes); ImGui::SameLine(200);
			ImGui::Checkbox("Reaper Robes", &Resources::bHasReaperRobes);
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Back / Other"))
		{
			ImGui::Spacing();
			ImGui::Checkbox("Oxygen Tank", &Resources::bHasOxygenTank);					ImGui::SameLine(200);
			ImGui::Checkbox("Ancient Oxygen Tank", &Resources::bHasAncientOxygenTank);
			ImGui::Checkbox("Snake Cloak", &Resources::bHasSnakeCloak);					ImGui::SameLine(200);
			ImGui::Checkbox("Lava Snake Cloak", &Resources::bHasLavaSnakeCloak);		ImGui::SameLine(400);
			ImGui::Checkbox("Lizard Cloak", &Resources::bHasLizardCloak);
			ImGui::Checkbox("Elephant Cloak", &Resources::bHasElephantCloak);
			SpacedSeparator();
			ImGui::Checkbox("Lightbulb", &Resources::bHasLightbulb);					ImGui::SameLine(200);
			ImGui::Checkbox("Shark Fin", &Resources::bHasSharkFin);
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Gloves"))
		{
			ImGui::Spacing();
			ImGui::Checkbox("Fire Gloves", &Resources::bHasFireGloves); ImGui::SameLine(200);
			ImGui::Checkbox("Ice Gloves", &Resources::bHasIceGloves);
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Neck"))
		{
			ImGui::Spacing();
			ImGui::Text("Berserker Amulet:");
			ImGui::RadioButton("No Amulet", &Resources::BerserkerAmuletLevel, 0);
			ImGui::RadioButton("Amulet: None", &Resources::BerserkerAmuletLevel, 1); ImGui::SameLine(200);
			ImGui::RadioButton("Amulet: Sapphire", &Resources::BerserkerAmuletLevel, 2); ImGui::SameLine(400);
			ImGui::RadioButton("Amulet: Emerald", &Resources::BerserkerAmuletLevel, 3);
			ImGui::RadioButton("Amulet: Ruby", &Resources::BerserkerAmuletLevel, 4); ImGui::SameLine(200);
			ImGui::RadioButton("Amulet: Diamond", &Resources::BerserkerAmuletLevel, 5); ImGui::SameLine(400);
			ImGui::RadioButton("Amulet: Blood Diamond", &Resources::BerserkerAmuletLevel, 6);
			SpacedSeparator();
			ImGui::Checkbox("Ghost Scan Amulet", &Resources::bHasGhostScanAmulet);
			ImGui::Checkbox("Invisibility Amulet", &Resources::bHasInvisibilityAmulet);
			ImGui::Checkbox("Enchanted Invisibility Amulet", &Resources::bHasEnchantedInvisibilityAmulet);
			ImGui::Checkbox("Oxygen Amulet", &Resources::bHasOxygenAmulet);
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Rings"))
		{
			ImGui::Spacing();
			ImGui::Text("Berserker Ring:");
			ImGui::RadioButton("No Ring", &Resources::BerserkerRingLevel, 0);
			ImGui::RadioButton("Ring: None", &Resources::BerserkerRingLevel, 1); ImGui::SameLine(200);
			ImGui::RadioButton("Ring: Sapphire", &Resources::BerserkerRingLevel, 2); ImGui::SameLine(400);
			ImGui::RadioButton("Ring: Emerald", &Resources::BerserkerRingLevel, 3);
			ImGui::RadioButton("Ring: Ruby", &Resources::BerserkerRingLevel, 4); ImGui::SameLine(200);
			ImGui::RadioButton("Ring: Diamond", &Resources::BerserkerRingLevel, 5); ImGui::SameLine(400);
			ImGui::RadioButton("Ring: Blood Diamond", &Resources::BerserkerRingLevel, 6);
			SpacedSeparator();
			ImGui::Checkbox("Ghost Scan Ring", &Resources::bHasGhostScanRing);
			ImGui::Checkbox("Invisibility Ring", &Resources::bHasInvisibilityRing);
			ImGui::Checkbox("Enchanted Invisibility Ring", &Resources::bHasEnchantedInvisibilityRing);
			ImGui::Checkbox("Oxygen Ring", &Resources::bHasOxygenRing);
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Research & Quests"))
		{
			ImGui::Spacing();
			ImGui::Checkbox("5x Poison Damage", &Resources::bHasPoisonDamageResearch);
			SpacedSeparator();
			ImGui::Checkbox("Witch's Potion Part 2", &Resources::bHasCompletedWitchsPotionPartTwo);
			if (Resources::bHasCompletedWitchsPotionPartTwo)
			{
				Resources::BerserkerAmuletLevel = 6;
			}
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Spells and Emblems"))
		{
			ImGui::Spacing();
			ImGui::Combo("Player HP", &Resources::PlayerHPCurrentlySelected, PLAYER_HP_OPTIONS, IM_ARRAYSIZE(PLAYER_HP_OPTIONS));
			SpacedSeparator();
			ImGui::RadioButton("No Fire", &Resources::FireSpellLevel, 0); ImGui::SameLine(200);
			ImGui::RadioButton("Fire", &Resources::FireSpellLevel, 1); ImGui::SameLine(400);
			ImGui::RadioButton("Upgraded Fire", &Resources::FireSpellLevel, 2);

			ImGui::RadioButton("No Reflect", &Resources::ReflectSpellLevel, 0); ImGui::SameLine(200);
			ImGui::RadioButton("Reflect", &Resources::ReflectSpellLevel, 1); ImGui::SameLine(400);
			ImGui::RadioButton("Upgraded Reflect", &Resources::ReflectSpellLevel, 2);

			ImGui::RadioButton("No Thunder", &Resources::ThunderSpellLevel, 0); ImGui::SameLine(200);
			ImGui::RadioButton("Thunder", &Resources::ThunderSpellLevel, 1); ImGui::SameLine(400);
			ImGui::RadioButton("Upgraded Thunder", &Resources::ThunderSpellLevel, 2);

			ImGui::RadioButton("No Lifesteal", &Resources::LifestealSpellLevel, 0); ImGui::SameLine(200);
			ImGui::RadioButton("Lifesteal", &Resources::LifestealSpellLevel, 1); ImGui::SameLine(400);
			ImGui::RadioButton("Upgraded Lifesteal", &Resources::LifestealSpellLevel, 2);

			ImGui::RadioButton("No Sandstorm", &Resources::SandstormSpellLevel, 0); ImGui::SameLine(200);
			ImGui::RadioButton("Sandstorm", &Resources::SandstormSpellLevel, 1); ImGui::SameLine(400);
			ImGui::RadioButton("Upgraded Sandstorm", &Resources::SandstormSpellLevel, 2);
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Potions"))
		{
			ImGui::Spacing();
			ImGui::Checkbox("HP Potion", &Resources::bHasHPPotion);
			ImGui::Checkbox("Freeze Potion", &Resources::bHasFreezePotion);
			ImGui::Checkbox("Accuracy Potion", &Resources::bHasAccuracyPotion);
			ImGui::Checkbox("Ghost Scan Potion", &Resources::bHasGhostScanPotion);
			ImGui::Checkbox("Super HP Potion", &Resources::bHasSuperHPPotion);
			ImGui::Checkbox("Strength Potion", &Resources::bHasStrengthPotion);
			ImGui::Spacing();
		}
		ImGui::End();

		// ---------------- Combat Simulator Window ----------------------------------------------------------------------------------------
		ImGui::SetNextWindowPos(ImVec2(690, 20));
		ImGui::SetNextWindowSize(ImVec2(650, WindowHeight - 40));

		ImGui::Begin("Combat Simulator", NULL, window_flags);
		ImGui::Spacing();
		ImGui::InputInt("Iterations", &Resources::NumIterations, 100000, 1000000);
		SpacedSeparator();
		// Custom
		if (ImGui::CollapsingHeader("Custom"))
		{
			ImGui::InputInt("HP", &Resources::CustomMaxHP, 1, 10);
			ImGui::InputInt("Attack", &Resources::CustomAttack, 1, 10);
			ImGui::InputInt("Accuracy", &Resources::CustomAccuracy, 1, 10);
			ImGui::InputInt("Defence", &Resources::CustomDefence, 1, 10);
			ImGui::InputInt("Multi-hit", &Resources::CustomNumHits, 1, 10);
			SpacedSeparator();
			//ImGui::Checkbox("Is Skeleton", &Resources::bIsCustomSkeleton); ImGui::SameLine(200);
			ImGui::Checkbox("Is Ghost", &Resources::bIsCustomGhost);
			ImGui::Checkbox("Vulnerable To Fire", &Resources::bIsCustomVulnerableToFire); ImGui::SameLine(210);
			ImGui::Checkbox("Vulnerable To Ice", &Resources::bIsCustomVulnerableToIce); ImGui::SameLine(420);
			ImGui::Checkbox("Vulnerable To Thunder", &Resources::bIsCustomVulnerableToThunder);
			SpacedSeparator();
			ImGui::Checkbox("Requires Cold Resistance", &Resources::bCustomRequireColdResistance);
			if (Resources::bCustomRequireColdResistance)
			{
				ImGui::InputInt("Min Cold Damage", &Resources::CustomMinColdDamage, 1, 1);
				ImGui::InputInt("Max Cold Damage", &Resources::CustomMaxColdDamage, 1, 1);
			}
			SpacedSeparator();
			ImGui::Checkbox("Requires Oxygen", &Resources::bCustomRequireOxygen);
			if (Resources::bCustomRequireOxygen)
			{
				ImGui::InputInt("Min Drowning Damage", &Resources::CustomMinDrowningDamage, 1, 1);
				ImGui::InputInt("Max Drowning Damage", &Resources::CustomMaxDrowningDamage, 1, 1);
			}
			SpacedSeparator();
			ImGui::Checkbox("Has Magic Attack", &Resources::bCustomHasMagicAttack);
			if (Resources::bCustomHasMagicAttack)
			{
				ImGui::InputInt("1/x Magic Chance", &Resources::CustomMagicAttackChance, 1, 1);
				ImGui::InputInt("Min Magic Damage", &Resources::CustomMinMagicDamage, 1, 1);
				ImGui::InputInt("Max Magic Damage", &Resources::CustomMaxMagicDamage, 1, 1);
			}
			SpacedSeparator();
			ImGui::Checkbox("Has Heal Ability", &Resources::bCustomHasHealAbility);
			if (Resources::bCustomHasHealAbility)
			{
				ImGui::InputInt("1/x Heal Chance", &Resources::CustomHealAbilityChance, 1, 1);
				ImGui::InputInt("Min Heal Power", &Resources::CustomMinAbilityHeal, 1, 1);
				ImGui::InputInt("Max Heal Power", &Resources::CustomMaxAbilityHeal, 1, 1);
			}
			SpacedSeparator();
			ImGui::Checkbox("Has Charge Ability", &Resources::bCustomHasChargeAbility);
			if (Resources::bCustomHasChargeAbility)
			{
				ImGui::SameLine(210);
				ImGui::Checkbox("Charge Ability Heals", &Resources::bCustomChargeDoesHealingInsteadOfDamage);
				ImGui::SameLine(420);
				ImGui::Checkbox("Only Charge Once", &Resources::bOnlyUseChargeAbilityOnce);
				ImGui::InputInt("1/x Charge Chance", &Resources::CustomChargeAbilityChance, 1, 1);
				ImGui::InputInt("Min Charge Power", &Resources::CustomMinChargeAbilityPower, 1, 1);
				ImGui::InputInt("Max Charge Power", &Resources::CustomMaxChargeAbilityPower, 1, 1);
				ImGui::InputInt("Charge Cast Time", &Resources::CustomChargeCastTime, 1, 1);
				ImGui::Checkbox("Charge Uses Threshold?", &Resources::bCustomChargeUsesThreshold);
				if (Resources::bCustomChargeUsesThreshold)
				{
					ImGui::InputInt("Charge Ability Threshold", &Resources::CustomChargeThreshold, 1, 1);
				}
			}
			SpacedSeparator();
			ImGui::Checkbox("Can Infect", &Resources::bCustomCanInfect);
			if (Resources::bCustomCanInfect)
			{
				ImGui::InputInt("Infection Threshold", &Resources::CustomInfectThreshold, 1, 1);
			}
			SpacedSeparator();
			ImGui::Checkbox("Has Wound Effect", &Resources::bCustomHasWoundEffect);
			if (Resources::bCustomHasWoundEffect)
			{
				ImGui::InputInt("Wound Damage", &Resources::CustomWoundDamage, 1, 1);
			}
			SpacedSeparator();
			ImGui::Checkbox("Has Swarm Attack", &Resources::bCustomHasSwarmAttack);
			if (Resources::bCustomHasSwarmAttack)
			{
				ImGui::InputInt("Swarm Size", &Resources::CustomSwarmSize, 1, 1);
				ImGui::InputInt("Swarm Damage", &Resources::CustomSwarmDamage, 1, 1);
			}
			SpacedSeparator();
			ImGui::Checkbox("Has Auto Attack Charge", &Resources::bCustomHasAutoAttackCharge);
			if (Resources::bCustomHasAutoAttackCharge)
			{
				ImGui::InputInt("Attacks Needed To Charge", &Resources::CustomAttacksNeededToCharge, 1, 1);
				ImGui::InputInt("Min Charge Damage", &Resources::CustomAutoAttackChargeMinDamage, 1, 1);
				ImGui::InputInt("Max Charge Damage", &Resources::CustomAutoAttackChargeMaxDamage, 1, 1);
			}
			SpacedSeparator();
			ImGui::Checkbox("Can Evade", &Resources::bCustomHasEvadeChance);
			if (Resources::bCustomHasEvadeChance)
			{
				ImGui::InputInt("x/100 Evade Chance", &Resources::CustomEvadeChance, 1, 1);
				ImGui::InputInt("x/100 Enchanted Evade Chance", &Resources::CustomEnchantedEvadeChance, 1, 1);
				if (Resources::CustomEnchantedEvadeChance > Resources::CustomEvadeChance)
				{
					Resources::CustomEvadeChance = Resources::CustomEnchantedEvadeChance;
				}
			}
			SpacedSeparator();
			ImGui::Checkbox("Has Damage Retaliation", &Resources::bCustomCanRetaliateDamage);
			if (Resources::bCustomCanRetaliateDamage)
			{
				ImGui::Combo("Damage Type To Retaliate", &Resources::CustomRetaliateDamageType, CUSTOM_DAMAGE_RETALIATION_TYPES, IM_ARRAYSIZE(CUSTOM_DAMAGE_RETALIATION_TYPES));
				ImGui::InputInt("Retaliation Damage", &Resources::CustomRetaliateDamage, 1, 1);
			}
			SpacedSeparator();
			CreateButton("Sim Custom", EnemyType::Custom);
		}
		// Fields Enemies
		if (ImGui::CollapsingHeader("Fields"))
		{
			CreateButton("Chicken",				EnemyType::Chicken);			ImGui::SameLine();
			CreateButton("Rat",					EnemyType::Rat);				ImGui::SameLine();
			CreateButton("Bee",					EnemyType::Bee);
			CreateButton("Blood Chicken",		EnemyType::BloodChicken);		ImGui::SameLine();
			CreateButton("Blood Rat",			EnemyType::BloodRat);			ImGui::SameLine();
			CreateButton("Blood Bee",			EnemyType::BloodBee);
			CreateButton("3x Chicken",			EnemyType::TripleChicken);		ImGui::SameLine();
			CreateButton("3x Blood Chicken",	EnemyType::TripleBloodChicken);
		}
		// Forest
		if (ImGui::CollapsingHeader("Forest"))
		{
			CreateButton("Snake",		EnemyType::Snake);				ImGui::SameLine();
			CreateButton("Ent",			EnemyType::Ent);				ImGui::SameLine();
			CreateButton("Thief",		EnemyType::Thief);
			CreateButton("Blood Snake", EnemyType::BloodSnake);			ImGui::SameLine();
			CreateButton("Blood Ent",	EnemyType::BloodEnt);			ImGui::SameLine();
			CreateButton("Blood Thief", EnemyType::BloodThief);
		}
		// Caves
		if (ImGui::CollapsingHeader("Caves"))
		{
			CreateButton("Bear",			EnemyType::Bear);				ImGui::SameLine();
			CreateButton("Bat",				EnemyType::Bat);				ImGui::SameLine();
			CreateButton("Skeleton",		EnemyType::Skeleton);
			CreateButton("Blood Bear",		EnemyType::BloodBear);			ImGui::SameLine();
			CreateButton("Blood Bat",		EnemyType::BloodBat);			ImGui::SameLine();
			CreateButton("Blood Skeleton",	EnemyType::BloodSkeleton);
		}
		// Volcano
		if (ImGui::CollapsingHeader("Volcano"))
		{
			CreateButton("Lava Snake",			EnemyType::LavaSnake);			ImGui::SameLine();
			CreateButton("Fire Hawk",			EnemyType::FireHawk);			ImGui::SameLine();
			CreateButton("Fire Mage",			EnemyType::FireMage);
			CreateButton("Blood Lava Snake",	EnemyType::BloodLavaSnake);		ImGui::SameLine();
			CreateButton("Blood Fire Hawk",		EnemyType::BloodFireHawk);		ImGui::SameLine();
			CreateButton("Blood Fire Mage",		EnemyType::BloodFireMage);
			CreateButton("3x Fire Hawk",		EnemyType::TripleFireHawk);	ImGui::SameLine();
			CreateButton("3x Blood Fire Hawk",	EnemyType::TripleBloodFireHawk);
		}
		// Northern Fields
		if (ImGui::CollapsingHeader("Northern Fields"))
		{
			CreateButton("Ice Hawk",			EnemyType::IceHawk);			ImGui::SameLine();
			CreateButton("Frozen Ent",			EnemyType::FrozenEnt);			ImGui::SameLine();
			CreateButton("Golem",				EnemyType::Golem);
			CreateButton("Blood Ice Hawk",		EnemyType::BloodIceHawk);		ImGui::SameLine();
			CreateButton("Blood Frozen Ent",	EnemyType::BloodFrozenEnt);		ImGui::SameLine();
			CreateButton("Blood Golem",			EnemyType::BloodGolem);
			CreateButton("3x Ice Hawk",			EnemyType::TripleIceHawk);		ImGui::SameLine();
			CreateButton("3x Blood Ice Hawk",	EnemyType::TripleBloodIceHawk);
		}
		// Haunted Mansion
		if (ImGui::CollapsingHeader("Haunted Mansion"))
		{
			CreateButton("Ghost",					EnemyType::Ghost);				ImGui::SameLine();
			CreateButton("Skeleton Ghost",			EnemyType::SkeletonGhost);		ImGui::SameLine();
			CreateButton("Reaper",					EnemyType::Reaper);
			CreateButton("Blood Haunted Mansion",	EnemyType::BloodReaper);
		}
		// Desert
		if (ImGui::CollapsingHeader("Desert"))
		{
			CreateButton("Desert Lizard Boss",			EnemyType::DesertLizardBoss);		ImGui::SameLine();
			CreateButton("Blood Desert\nLizard Boss",	EnemyType::BloodDesertLizardBoss);
			CreateButton("Desert Lizard 2",				EnemyType::DesertLizard2);			ImGui::SameLine();
			CreateButton("Scorpion",					EnemyType::Scorpion);				ImGui::SameLine();
			CreateButton("Lizard",						EnemyType::Lizard);
			CreateButton("Blood Desert Lizard 2",		EnemyType::BloodDesertLizard2);		ImGui::SameLine();
			CreateButton("Blood Scorpion",				EnemyType::BloodScorpion);			ImGui::SameLine();
			CreateButton("Blood Lizard",				EnemyType::BloodLizard);
		}
		// Ocean
		if (ImGui::CollapsingHeader("Ocean"))
		{
			CreateButton("Squid",				EnemyType::Squid);				ImGui::SameLine();
			CreateButton("Pufferfish",			EnemyType::PufferFish);			ImGui::SameLine();
			CreateButton("Shark",				EnemyType::Shark);
			CreateButton("Blood Squid",			EnemyType::BloodSquid);			ImGui::SameLine();
			CreateButton("Blood Pufferfish",	EnemyType::BloodPufferFish);	ImGui::SameLine();
			CreateButton("Blood Shark",			EnemyType::BloodShark);
		}
		// Jungle
		if (ImGui::CollapsingHeader("Jungle"))
		{
			CreateButton("Tribe",				EnemyType::Tribe);			ImGui::SameLine();
			CreateButton("Elephant",			EnemyType::Elephant);		ImGui::SameLine();
			CreateButton("Gorilla",				EnemyType::Gorilla);
			CreateButton("Blood Jungle Pack",	EnemyType::BloodJunglePack);
		}
		// Dungeon Entrance
		if (ImGui::CollapsingHeader("Dungeon Entrance"))
		{
			CreateButton("Skeleton Mage Boss 1", EnemyType::SkeletonMageBoss1);		ImGui::SameLine();
			CreateButton("Skeleton Mage Boss 2", EnemyType::SkeletonMageBoss2);
			CreateButton("Skeleton Mage Boss 3", EnemyType::SkeletonMageBoss3);		ImGui::SameLine();
			CreateButton("Skeleton Mage Boss 4", EnemyType::SkeletonMageBoss4);

			CreateButton("Poison Tribe",	EnemyType::PoisonTribe);	ImGui::SameLine();
			CreateButton("Statue",			EnemyType::Statue);			ImGui::SameLine();
			CreateButton("Gargoyle",		EnemyType::Gargoyle);
		}
		// Dungeon
		if (ImGui::CollapsingHeader("Dungeon"))
		{
			CreateButton("Skeleton Monks",		EnemyType::SkeletonMonks);		ImGui::SameLine();
			CreateButton("Dark Mage",			EnemyType::DarkMage);			ImGui::SameLine();
			CreateButton("Skeleton Prisoner",	EnemyType::SkeletonPrisoner);
		}
		// Coffin
		if (ImGui::CollapsingHeader("Coffin"))
		{
			CreateButton("Skeleton King",		EnemyType::SkeletonKing);
		}
		// Castle
		if (ImGui::CollapsingHeader("Castle"))
		{
			CreateButton("Castle Knight",	EnemyType::CastleKnight);	ImGui::SameLine();
			CreateButton("Dragon",			EnemyType::Dragon);			ImGui::SameLine();
			CreateButton("Castle Mage",		EnemyType::CastleMage);
		}
		// Cemetery
		if (ImGui::CollapsingHeader("Cemetery"))
		{
			CreateButton("Angel",				EnemyType::Angel);						ImGui::SameLine();
			CreateButton("Zombie",				EnemyType::Zombie);						ImGui::SameLine();
			CreateButton("BabySkeleton",		EnemyType::BabySkeleton);
			CreateButton("Skeleton Boss",		EnemyType::CemeterySkeletonBoss);		ImGui::SameLine();
			CreateButton("Ice Skeleton Boss",	EnemyType::CemeteryIceSkeletonBoss);	ImGui::SameLine();
			CreateButton("Fire Skeleton Boss",	EnemyType::CemeteryFireSkeletonBoss);
		}
		// Factory
		if (ImGui::CollapsingHeader("Factory"))
		{
			CreateButton("Robot Archer",	EnemyType::RobotArcher);	ImGui::SameLine();
			CreateButton("Robot Mage",		EnemyType::RobotMage);		ImGui::SameLine();
			CreateButton("Robot Wheelie",	EnemyType::RobotWheelie);
		}
		// Haunted Woods
		if (ImGui::CollapsingHeader("Haunted Woods"))
		{
			CreateButton("Curious Ghost",		EnemyType::CuriousGhostBoss);
			CreateButton("Ghost Pack",			EnemyType::GhostPack);			ImGui::SameLine();
			CreateButton("Skeleton Ghost 2",	EnemyType::SkeletonGhost2);		ImGui::SameLine();
			CreateButton("Reaper 2",			EnemyType::Reaper2);
		}
		// Deep Ocean
		if (ImGui::CollapsingHeader("Deep Ocean"))
		{
			CreateButton("Poison Squid",	EnemyType::PoisonSquid);	ImGui::SameLine();
			CreateButton("Trident Soldier",	EnemyType::TridentSoldier);	ImGui::SameLine();
			CreateButton("Piranhas",		EnemyType::Piranhas);
		}
		SpacedSeparator();
		ImGui::Text("Results:");
		ImGui::Text("Current Enemy: %s", Enemies::GetEnemyName().c_str());
		ImGui::Text("Current Iteration: %i", Resources::CurrentIteration);
		ImGui::Text("Number of Wins:    %i", Resources::Stats.NumWins);
		if (Resources::Resources::Stats.NumWins > 0)
		{
			ImGui::Text("Current Winrate: %.2f%%", ((float)Resources::Stats.NumWins / (float)Resources::CurrentIteration)*100.f);
		}
		else if (Resources::CurrentIteration == 0)
		{
			ImGui::Text("Current Winrate: N/A");
		}
		else
		{
			ImGui::Text("Current Winrate: 0.00%%");
		}
		if (Resources::bIsCurrentlySimulating)
		{
			ImGui::Text("Sim elapsed time: In Progress");
		}
		else
		{
			ImGui::Text("Sim elapsed time: %i ms", SimTime.asMilliseconds());
		}
		SpacedSeparator();
		ImGui::Text("Player Stats:");
		ImGui::Text("Max HP: %i   Attack: %i   Accuracy: %i   Defence: %i", Resources::Stats.PlayerMaxHp, Resources::Stats.BestAttack, Resources::Stats.BestAccuracy, Resources::Stats.BestDefence);


		std::array<float, 5> PlayerStatsArr = { AverageOverIterations(Resources::Stats.TotalWeaponDamageDone),
												AverageOverIterations(Resources::Stats.TotalPoisonDamageDone),
												AverageOverIterations(Resources::Stats.TotalFireDamageDone),
												AverageOverIterations(Resources::Stats.TotalDamageReflected),
												AverageOverIterations(Resources::Stats.TotalThunderDamageDone)};
		float HighestStatValue = *std::max_element(PlayerStatsArr.begin(), PlayerStatsArr.end());
		//LBE_TRACE("HighestStatValue: {:03.2f}", HighestStatValue);

		ImGui::Text("Enemy Stats:");
		ImGui::Text("Max HP: %i   Attack: %i   Accuracy: %i   Defence: %i", Resources::Stats.EnemyMaxHP, Resources::Stats.EnemyAttack, Resources::Stats.EnemyAccuracy, Resources::Stats.EnemyDefence);
		SpacedSeparator();
		ImGui::Text("Averages:");
		SpacedSeparator();
		ImGui::Text("Fight Length:     %.2f", AverageOverIterations(Resources::Stats.TotalCombatTicks));
		SpacedSeparator();
		ImGui::Text("Player Stats:");
		ImGui::Text("Weapon Damage:      %.2f", AverageOverIterations(Resources::Stats.TotalWeaponDamageDone));
		ImGui::SameLine(240);
		CreateProgressBar(lbe::STAT_BAR_BACKGROUND, lbe::WEAPON_BAR_FOREGROUND, AverageOverIterations(Resources::Stats.TotalWeaponDamageDone) / HighestStatValue, AverageOverIterations(Resources::Stats.TotalWeaponDamageDone));
		ImGui::Text("Poison Damage:      %.2f", AverageOverIterations(Resources::Stats.TotalPoisonDamageDone));
		ImGui::SameLine(240);
		CreateProgressBar(lbe::STAT_BAR_BACKGROUND, lbe::POISON_BAR_FOREGROUND, AverageOverIterations(Resources::Stats.TotalPoisonDamageDone) / HighestStatValue, AverageOverIterations(Resources::Stats.TotalPoisonDamageDone));
		ImGui::Text("Fire Damage:        %.2f", AverageOverIterations(Resources::Stats.TotalFireDamageDone));
		ImGui::SameLine(240);
		CreateProgressBar(lbe::STAT_BAR_BACKGROUND, lbe::FIRE_BAR_FOREGROUND, AverageOverIterations(Resources::Stats.TotalFireDamageDone) / HighestStatValue, AverageOverIterations(Resources::Stats.TotalFireDamageDone));
		ImGui::Text("Ice Damage:         %.2f", AverageOverIterations(Resources::Stats.TotalIceDamageDone));
		ImGui::SameLine(240);
		CreateProgressBar(lbe::STAT_BAR_BACKGROUND, lbe::ICE_BAR_FOREGROUND, AverageOverIterations(Resources::Stats.TotalIceDamageDone) / HighestStatValue, AverageOverIterations(Resources::Stats.TotalIceDamageDone));
		ImGui::Text("Reflected Damage:   %.2f", AverageOverIterations(Resources::Stats.TotalDamageReflected));
		ImGui::SameLine(240);
		CreateProgressBar(lbe::STAT_BAR_BACKGROUND, lbe::REFLECT_BAR_FOREGROUND, AverageOverIterations(Resources::Stats.TotalDamageReflected) / HighestStatValue, AverageOverIterations(Resources::Stats.TotalDamageReflected));
		ImGui::Text("Thunder Damage:     %.2f", AverageOverIterations(Resources::Stats.TotalThunderDamageDone));
		ImGui::SameLine(240);
		CreateProgressBar(lbe::STAT_BAR_BACKGROUND, lbe::THUNDER_BAR_FOREGROUND, AverageOverIterations(Resources::Stats.TotalThunderDamageDone) / HighestStatValue, AverageOverIterations(Resources::Stats.TotalThunderDamageDone));
		ImGui::Text("HP Potions:         %.2f%%", AverageOverIterations(Resources::Stats.TotalHPPotionsUsed) * 100.f);
		ImGui::Text("Super HP Potions:   %.2f%%", AverageOverIterations(Resources::Stats.TotalSuperHPPotionsUsed) * 100.f);
		ImGui::Text("Attacks Evaded:     %.2f (%.2f%%)", AverageOverIterations(Resources::Stats.TotalTimesEvadedAttacks), ((float)Resources::Stats.TotalTimesEvadedAttacks / (((float)Resources::Stats.TotalTimesNotEvadedAttacks) + (float)Resources::Stats.TotalTimesEvadedAttacks)) * 100.f);
		ImGui::Text("Attacks Made:       %.2f", AverageOverIterations(Resources::Stats.TotalWeaponAttacksMade));
		ImGui::Text("Total Life Stolen:  %.2f", AverageOverIterations(Resources::Stats.TotalHealingFromLifesteal));
		ImGui::Text("Lifesteal times:    %.2f", AverageOverIterations(Resources::Stats.TotalTimesLifestealHealed));
		ImGui::Text("Arrows Used:        %.2f", AverageOverIterations(Resources::Stats.TotalArrowsUsed));

		SpacedSeparator();

		ImGui::Text("Enemy Stats:");
		ImGui::Text("Damage Done:      %.2f", AverageOverIterations(Resources::Stats.TotalDamageReceived));
		ImGui::Text("Evade Chance:     %i%%", Enemies::GetEvadeChance());
		if (Enemies::HasEvadeChance())
		{
			ImGui::Text("Attacks Evaded:   %.2f%%", ((float)Resources::Stats.TotalTimesEnemyEvadedAttacks / (float)Resources::Stats.TotalEnemyEvadeableAttacksMade) * 100.f);
		}
		ImGui::End();
		
		// ---------------- Simulation -----------------------------------------------------------------------------------------------------
		if (Resources::bIsCurrentlySimulating)
		{
			auto i = ThreadResults.begin();
			while (i != ThreadResults.end())
			{
				if ((*i).wait_for(std::chrono::milliseconds::min()) != std::future_status::timeout)
				{
					Resources::Stats += (*i).get();
					Resources::CurrentIteration = Resources::Stats.NumIterations;
					i = ThreadResults.erase(i);
				}
				else
				{
					++i;
				}
			}

			if (Resources::CurrentIteration == Resources::NumIterations)
			{
				Resources::bIsCurrentlySimulating = false;
				SimTime = SimClock.restart();
			}
		}

		window.clear();
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}