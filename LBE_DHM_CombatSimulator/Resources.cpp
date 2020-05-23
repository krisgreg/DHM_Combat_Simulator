#include "Resources.h"

#include <sstream>
#include <string>
#include <filesystem>
#include <fstream>

#include "Log.h"

// Weapons
bool Resources::bHasRustySword = false;
bool Resources::bHasStinger = false;
bool Resources::bHasIronDagger = false;
bool Resources::bHasSkeletonSword = false;
bool Resources::bHasScythe = false;
bool Resources::bHasEnchantedScythe = false;
bool Resources::bHasPoisonSpear = false;
bool Resources::bHasPoisonSpearPlus = false;
bool Resources::bHasMace = false;
bool Resources::bHasTrident = false;
bool Resources::bHasPoisonTridentPlus = false;
bool Resources::bHasSilverScimitar = false;
bool Resources::bHasBow = false;
bool Resources::bHasSuperBow = false;
bool Resources::bHasEnchantedSuperBow = false;
bool Resources::bHasArrows = false;
bool Resources::bHasFireArrows = false;
bool Resources::bHasIceArrows = false;
bool Resources::bHasPoisonArrows = false;
bool Resources::bHasArrowsPlus = false;
bool Resources::bHasPoisonArrowsPlus = false;
bool Resources::bHasMageStaff = false;

// Off-hand
bool Resources::bHasSkeletonShield = false;
bool Resources::bHasJungleShield = false;
bool Resources::bHasKnightsShield = false;
bool Resources::bHasSuperJungleShield = false;
bool Resources::bHasOffHandDagger = false;

// Armor
int Resources::BestHeadArmor = 0;
int Resources::BestBodyArmor = 0;
int Resources::BestLegArmor = 0;
bool Resources::bHasMageRobes = false;
bool Resources::bHasReaperRobes = false;

// Back/other
bool Resources::bHasOxygenTank = false;
bool Resources::bHasAncientOxygenTank = false;
bool Resources::bHasSnakeCloak = false;
bool Resources::bHasLavaSnakeCloak = false;
bool Resources::bHasLizardCloak = false;
bool Resources::bHasElephantCloak = false;
bool Resources::bHasLightbulb = false;
bool Resources::bHasSharkFin = false;

// Neck
int Resources::BerserkerAmuletLevel = 0;
bool Resources::bHasGhostScanAmulet = false;
bool Resources::bHasInvisibilityAmulet = false;
bool Resources::bHasEnchantedInvisibilityAmulet = false;
bool Resources::bHasOxygenAmulet = false;

// Ring
int Resources::BerserkerRingLevel = 0;
bool Resources::bHasGhostScanRing = false;
bool Resources::bHasInvisibilityRing = false;
bool Resources::bHasEnchantedInvisibilityRing = false;
bool Resources::bHasOxygenRing = false;

// Gloves 
bool Resources::bHasFireGloves = false;
bool Resources::bHasIceGloves = false;

// Research & Quests
bool Resources::bHasPoisonDamageResearch = false;
bool Resources::bHasCompletedWitchsPotionPartTwo = false;

// Spells and Emblems
int Resources::PlayerHPCurrentlySelected = 0;
int Resources::FireSpellLevel = 0;
int Resources::ReflectSpellLevel = 0;
int Resources::ThunderSpellLevel = 0;
int Resources::LifestealSpellLevel = 0;
int Resources::SandstormSpellLevel = 0;

// Potions
bool Resources::bHasHPPotion = false;
bool Resources::bHasFreezePotion = false;
bool Resources::bHasAccuracyPotion = false;
bool Resources::bHasGhostScanPotion = false;
bool Resources::bHasSuperHPPotion = false;
bool Resources::bHasStrengthPotion = false;

// Simulation data
int Resources::NumIterations = 100000;
int Resources::CurrentIteration = 0;
int Resources::NumWins = 0;
bool Resources::bIsCurrentlySimulating = false;

// Custom Enemy Base Stats
int Resources::CustomMaxHP = 10;
int Resources::CustomAttack = 0;
int Resources::CustomAccuracy = 0;
int Resources::CustomDefence = 0;
// Custom Multi-hit
int Resources::CustomNumHits = 1;
// Custom Enemy Type
bool Resources::bIsCustomSkeleton = false;
bool Resources::bIsCustomGhost = false;
// Custom Cold Resistance
bool Resources::bCustomRequireColdResistance = false;
int Resources::CustomMinColdDamage = 1;
int Resources::CustomMaxColdDamage = 4;
// Custom Oxygen
bool Resources::bCustomRequireOxygen = false;
int Resources::CustomMinDrowningDamage = 5;
int Resources::CustomMaxDrowningDamage = 15;
// Custom Infection
bool Resources::bCustomCanInfect = false;
int Resources::CustomInfectThreshold = 150;
// Custom Wound
bool Resources::bCustomHasWoundEffect = false;
int Resources::CustomWoundDamage = 1;
// Custom Swarm Attack
bool Resources::bCustomHasSwarmAttack = false;
int Resources::CustomSwarmSize = 6;
int Resources::CustomSwarmDamage = 1;
// Custom Auto Attack Charge
bool Resources::bCustomHasAutoAttackCharge = false;
int Resources::CustomAttacksNeededToCharge = 4;
int Resources::CustomAutoAttackChargeMinDamage = 30;
int Resources::CustomAutoAttackChargeMaxDamage = 40;
// Custom Evade
bool Resources::bCustomHasEvadeChance = false;
int Resources::CustomEvadeChance = 10;
int Resources::CustomEnchantedEvadeChance = 0;
// Custom Retaliate
bool Resources::bCustomCanRetaliateDamage = false;
int Resources::CustomRetaliateDamageType = 1;
int Resources::CustomRetaliateDamage = 10;
// Custom Vulnerabilities
bool Resources::bIsCustomVulnerableToFire = false;
bool Resources::bIsCustomVulnerableToIce = false;
bool Resources::bIsCustomVulnerableToThunder = false;
// Custom Magic Attack
bool Resources::bCustomHasMagicAttack = false;
int Resources::CustomMinMagicDamage = 0;
int Resources::CustomMaxMagicDamage = 4;
int Resources::CustomMagicAttackChance = 1;
// Custom Heal Ability
bool Resources::bCustomHasHealAbility = false;
int Resources::CustomMinAbilityHeal = 1;
int Resources::CustomMaxAbilityHeal = 5;
int Resources::CustomHealAbilityChance = 3;
// Custom Charge Ability
bool Resources::bCustomHasChargeAbility = false;
bool Resources::bCustomChargeDoesHealingInsteadOfDamage = false;
int Resources::CustomMinChargeAbilityPower = 30;
int Resources::CustomMaxChargeAbilityPower = 40;
int Resources::CustomChargeAbilityChance = 21;
int Resources::CustomChargeCastTime = 7;
bool Resources::bCustomChargeUsesThreshold = false;
int Resources::CustomChargeThreshold = 0;
bool Resources::bOnlyUseChargeAbilityOnce = false;

// Stats
CombatStats Resources::Stats;

// Presets
char Resources::SaveStringText[] = "";
char Resources::SavePresetName[] = "";
std::map<std::string, std::string> Resources::CustomPresets;
std::map<std::string, bool> Resources::CustomPresetButtonToggles;

Resources::Resources()
{
}


Resources::~Resources()
{
}

bool Resources::HasAtLeastOneKindOfArrow()
{
	if (Resources::bHasPoisonArrows || Resources::bHasIceArrows || Resources::bHasFireArrows || Resources::bHasArrows || Resources::bHasArrowsPlus)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Resources::ResetStats()
{
	Resources::Stats.Reset();
}

void Resources::ResetGear()
{
	// Weapons
	bHasRustySword = false;
	bHasStinger = false;
	bHasIronDagger = false;
	bHasSkeletonSword = false;
	bHasScythe = false;
	bHasEnchantedScythe = false;
	bHasPoisonSpear = false;
	bHasPoisonSpearPlus = false;
	bHasMace = false;
	bHasTrident = false;
	bHasPoisonTridentPlus = false;
	bHasSilverScimitar = false;
	bHasBow = false;
	bHasSuperBow = false;
	bHasEnchantedSuperBow = false;
	bHasArrows = false;
	bHasFireArrows = false;
	bHasIceArrows = false;
	bHasPoisonArrows = false;
	bHasArrowsPlus = false;
	bHasPoisonArrowsPlus = false;
	bHasMageStaff = false;
	// Off-hand
	bHasSkeletonShield = false;
	bHasJungleShield = false;
	bHasKnightsShield = false;
	bHasSuperJungleShield = false;
	bHasOffHandDagger = false;
	// Armor
	BestHeadArmor = 0;
	BestBodyArmor = 0;
	BestLegArmor = 0;
	bHasMageRobes = false;
	bHasReaperRobes = false;
	// Back/other
	bHasOxygenTank = false;
	bHasAncientOxygenTank = false;
	bHasSnakeCloak = false;
	bHasLavaSnakeCloak = false;
	bHasLizardCloak = false;
	bHasElephantCloak = false;
	bHasLightbulb = false;
	bHasSharkFin = false;
	// Neck
	BerserkerAmuletLevel = 0;
	bHasGhostScanAmulet = false;
	bHasInvisibilityAmulet = false;
	bHasEnchantedInvisibilityAmulet = false;
	bHasOxygenAmulet = false;
	// Ring
	BerserkerRingLevel = 0;
	bHasGhostScanRing = false;
	bHasInvisibilityRing = false;
	bHasEnchantedInvisibilityRing = false;
	bHasOxygenRing = false;
	// Gloves 
	bHasFireGloves = false;
	bHasIceGloves = false;
	// Research & Quests
	bHasPoisonDamageResearch = false;
	bHasCompletedWitchsPotionPartTwo = false;
	// Spells and Emblems
	PlayerHPCurrentlySelected = 0;
	FireSpellLevel = 0;
	ReflectSpellLevel = 0;
	ThunderSpellLevel = 0;
	LifestealSpellLevel = 0;
	SandstormSpellLevel = 0;
	// Potions
	bHasHPPotion = false;
	bHasFreezePotion = false;
	bHasAccuracyPotion = false;
	bHasGhostScanPotion = false;
	bHasSuperHPPotion = false;
	bHasStrengthPotion = false;
}

void Resources::UsePreset(int PresetNumber)
{
	ResetGear();

	// Gear available before combat unlocks
	bHasRustySword = true;
	BestHeadArmor = 1;
	BestBodyArmor = 1;
	BestLegArmor  = 1;

	// Gear available after Fields
	if (PresetNumber >= 1)
	{
		//bHasArrows = true;
		bHasStinger = true;
		bHasRustySword = false;
		PlayerHPCurrentlySelected = 1;
	}

	// Gear available after Forest
	if (PresetNumber >= 2)
	{
		BestHeadArmor = 2;
		BestBodyArmor = 2;
		BestLegArmor  = 2;
		bHasIronDagger = true;
		bHasStinger = false;
		bHasHPPotion = true;
		PlayerHPCurrentlySelected = 2;
	}

	// Gear available after Caves
	if (PresetNumber >= 3)
	{
		bHasSkeletonShield = true;
		bHasSkeletonSword = true;
		bHasIronDagger = false;
		bHasFreezePotion = true;
	}

	// Gear available after Volcano
	if (PresetNumber >= 4)
	{
		BestHeadArmor = 3;
		BestBodyArmor = 3;
		BestLegArmor  = 3;
		//bHasFireArrows = true;
		FireSpellLevel = 1;
		bHasAccuracyPotion = true;
	}

	// Gear available after Northern Fields
	if (PresetNumber >= 5)
	{
		//bHasIceArrows = true;
		bHasBow = true;
		bHasGhostScanPotion = true;
	}

	// Gear available after Haunted Mansion
	if (PresetNumber >= 6)
	{
		bHasScythe = true;
		bHasSkeletonSword = false;
		bHasGhostScanAmulet = true;
		bHasInvisibilityAmulet = true;
		ReflectSpellLevel = 1;
		PlayerHPCurrentlySelected = 3;
	}

	// Gear available after Desert
	if (PresetNumber >= 7)
	{
		BestHeadArmor = 4;
		BestBodyArmor = 4;
		BestLegArmor  = 4;
		ThunderSpellLevel = 2;
		//bHasPoisonArrows = true;
		bHasOxygenTank = true;
	}

	// Gear available after Ocean
	if (PresetNumber >= 8)
	{
		bHasSuperHPPotion = true;
		bHasPoisonDamageResearch = true;
		PlayerHPCurrentlySelected = 4;
	}

	// Gear available after Jungle
	if (PresetNumber >= 9)
	{
		BestHeadArmor = 5;
		BestBodyArmor = 5;
		BestLegArmor  = 5;
		bHasJungleShield = true;
		bHasSkeletonShield = false;
		bHasGhostScanRing = true;
		bHasInvisibilityRing = true;
		PlayerHPCurrentlySelected = 5;
		BerserkerAmuletLevel = 5;
	}

	// Gear available after Dungeon Entrance
	if (PresetNumber >= 10)
	{
		bHasPoisonSpear = true;
	}

	// Gear available after Dungeon
	if (PresetNumber >= 11)
	{
		bHasMace = true;
		bHasMageRobes = true;
	}

	// Gear available after Coffin
	if (PresetNumber >= 12)
	{
		BestHeadArmor = 6;
		BestBodyArmor = 6;
		BestLegArmor  = 6;
	}

	// Gear available after Castle
	if (PresetNumber >= 13)
	{
		bHasMageStaff = true;
		bHasKnightsShield = true;
		bHasJungleShield = false;
		bHasStrengthPotion = true;
		PlayerHPCurrentlySelected = 6;
		BerserkerRingLevel = 5;
	}

	// Gear available after Cemetery
	if (PresetNumber >= 14)
	{
		BestHeadArmor = 7;
		BestBodyArmor = 7;
		BestLegArmor  = 7;
		LifestealSpellLevel = 2;
		FireSpellLevel = 2;
		bHasCompletedWitchsPotionPartTwo = true;
		BerserkerAmuletLevel = 6;
	}

	// Gear available after Factory
	if (PresetNumber >= 15)
	{
		bHasSuperBow = true;
		bHasBow = false;
		bHasLightbulb = true;
		ReflectSpellLevel = 2;
		BerserkerRingLevel = 6;
	}

	// Gear available after Haunted Woods
	if (PresetNumber >= 16)
	{
		PlayerHPCurrentlySelected = 7;
		bHasEnchantedInvisibilityAmulet = true;
		bHasEnchantedInvisibilityRing = true;
		bHasEnchantedScythe = true;

		bHasInvisibilityAmulet = false;
		bHasInvisibilityRing = false;
		bHasScythe = false;
	}

	// Gear available after Deep Ocean
	if (PresetNumber >= 17)
	{
		bHasTrident = true;
		bHasPoisonTridentPlus = true;
		bHasPoisonSpearPlus = true;
		BestHeadArmor = 8;
		bHasOxygenAmulet = true;
		bHasOxygenRing = true;
	}
}

void Resources::GenerateSaveString()
{
	std::stringstream SaveStringStream;
	// Weapons
	if (bHasRustySword)			{ SaveStringStream << "WRS:T#"; }
	if (bHasStinger)			{ SaveStringStream << "WSt:T#"; }
	if (bHasIronDagger)			{ SaveStringStream << "WID:T#"; }
	if (bHasSkeletonSword)		{ SaveStringStream << "WSS:T#"; }
	if (bHasScythe)				{ SaveStringStream << "WSc:T#"; }
	if (bHasEnchantedScythe)	{ SaveStringStream << "WES:T#"; }
	if (bHasPoisonSpear)		{ SaveStringStream << "WPS:T#"; }
	if (bHasPoisonSpearPlus)	{ SaveStringStream << "WPSP:T#"; }
	if (bHasMace)				{ SaveStringStream << "WM:T#"; }
	if (bHasTrident)			{ SaveStringStream << "WT:T#"; }
	if (bHasPoisonTridentPlus)	{ SaveStringStream << "WPTP:T#"; }
	if (bHasSilverScimitar)		{ SaveStringStream << "WSSc:T#"; }
	if (bHasBow)				{ SaveStringStream << "WB:T#"; }
	if (bHasSuperBow)			{ SaveStringStream << "WSB:T#"; }
	if (bHasEnchantedSuperBow)	{ SaveStringStream << "WESB:T#"; }
	if (bHasArrows)				{ SaveStringStream << "WA:T#"; }
	if (bHasFireArrows)			{ SaveStringStream << "WFA:T#"; }
	if (bHasIceArrows)			{ SaveStringStream << "WIA:T#"; }
	if (bHasPoisonArrows)		{ SaveStringStream << "WPA:T#"; }
	if (bHasArrowsPlus)			{ SaveStringStream << "WAP:T#"; }
	if (bHasPoisonArrowsPlus)	{ SaveStringStream << "WPAP:T#"; }
	if (bHasMageStaff)			{ SaveStringStream << "WMS:T#"; }
	// Off-hand
	if (bHasSkeletonShield)		{ SaveStringStream << "OSS:T#"; }
	if (bHasJungleShield)		{ SaveStringStream << "OJS:T#"; }
	if (bHasKnightsShield)		{ SaveStringStream << "OKS:T#"; }
	if (bHasSuperJungleShield)	{ SaveStringStream << "OSJS:T#"; }
	if (bHasOffHandDagger)		{ SaveStringStream << "OOHD:T#"; }
	// Armor
	SaveStringStream << "AHA:" << BestHeadArmor << "#";
	SaveStringStream << "ABA:" << BestBodyArmor << "#";
	SaveStringStream << "ALA:" << BestLegArmor << "#";
	if (bHasMageRobes)		{ SaveStringStream << "AMR:T#"; }
	if (bHasReaperRobes)	{ SaveStringStream << "ARR:T#"; }
	// Back/other
	if (bHasOxygenTank)			{ SaveStringStream << "BOT:T#"; }
	if (bHasAncientOxygenTank)	{ SaveStringStream << "BAOT:T#"; }
	if (bHasSnakeCloak)			{ SaveStringStream << "BSC:T#"; }
	if (bHasLavaSnakeCloak)		{ SaveStringStream << "BLSC:T#"; }
	if (bHasLizardCloak)		{ SaveStringStream << "BLC:T#"; }
	if (bHasElephantCloak)		{ SaveStringStream << "BEC:T#"; }
	if (bHasLightbulb)			{ SaveStringStream << "BLB:T#"; }
	if (bHasSharkFin)			{ SaveStringStream << "BSF:T#"; }
	// Neck
	SaveStringStream << "NB:" << BerserkerAmuletLevel << "#";
	if (bHasGhostScanAmulet)				{ SaveStringStream << "NGS:T#"; }
	if (bHasInvisibilityAmulet)				{ SaveStringStream << "NI:T#"; }
	if (bHasEnchantedInvisibilityAmulet)	{ SaveStringStream << "NEI:T#"; }
	if (bHasOxygenAmulet)					{ SaveStringStream << "NO:T#"; }
	// Ring
	SaveStringStream << "RB:" << BerserkerRingLevel << "#";
	if (bHasGhostScanRing)				{ SaveStringStream << "RGS:T#"; }
	if (bHasInvisibilityRing)			{ SaveStringStream << "RI:T#"; }
	if (bHasEnchantedInvisibilityRing)	{ SaveStringStream << "REI:T#"; }
	if (bHasOxygenRing)					{ SaveStringStream << "RO:T#"; }
	// Gloves 
	if (bHasFireGloves) { SaveStringStream << "GF:T#"; }
	if (bHasIceGloves)	{ SaveStringStream << "GI:T#"; }
	// Research & Quests
	if (bHasPoisonDamageResearch)			{ SaveStringStream << "QPDR:T#"; }
	if (bHasCompletedWitchsPotionPartTwo)	{ SaveStringStream << "QCWPPT:T#"; }
	// Spells and Emblems
	SaveStringStream << "SHP:" << PlayerHPCurrentlySelected << "#";
	SaveStringStream << "SF:" << FireSpellLevel << "#";
	SaveStringStream << "SR:" << ReflectSpellLevel << "#";
	SaveStringStream << "ST:" << ThunderSpellLevel << "#";
	SaveStringStream << "SL:" << LifestealSpellLevel << "#";
	SaveStringStream << "SS:" << SandstormSpellLevel << "#";
	// Potions
	if (bHasHPPotion)			{ SaveStringStream << "PHP:T#"; }
	if (bHasFreezePotion)		{ SaveStringStream << "PF:T#"; }
	if (bHasAccuracyPotion)		{ SaveStringStream << "PA:T#"; }
	if (bHasGhostScanPotion)	{ SaveStringStream << "PGS:T#"; }
	if (bHasSuperHPPotion)		{ SaveStringStream << "PSHP:T#"; }
	if (bHasStrengthPotion)		{ SaveStringStream << "PS:T#"; }

	//LBE_TRACE("Save String: {0}", SaveStringStream.str());
	strcpy_s(SaveStringText, SaveStringStream.str().c_str());
}

void Resources::LoadSaveString()
{
	ResetGear();

	std::string SaveString = SaveStringText;
	std::string Delimiter = "#";

	size_t last = 0;
	size_t next = 0;
	while ((next = SaveString.find(Delimiter, last)) != std::string::npos)
	{
		std::string Token = SaveString.substr(last, next - last);
		std::string InnerDelimiter = ":";
		std::string Key = Token.substr(0, Token.find(InnerDelimiter));
		std::string Value = Token.substr(Token.find(InnerDelimiter) + 1, Token.size() + 1);
		LoadKeyValuePair(Key, Value);
		//LBE_TRACE("Key: {0}, Value: {1}", Key, Value);
		last = next + 1;
	}
}

void Resources::LoadCustomPresets()
{

	CustomPresets.clear();
	CustomPresetButtonToggles.clear();

	for (auto & p : std::experimental::filesystem::directory_iterator(lbe::CUSTOM_PRESET_PATH))
	{
		std::stringstream PresetStream;
		PresetStream << p;
		std::string PresetName(PresetStream.str());
		//LBE_TRACE("Preset: {0}", PresetName);

		std::string PresetData;
		std::ifstream PresetFile;
		PresetFile.open(PresetName, std::ios::in);
		if (PresetFile.is_open())
		{
			std::getline(PresetFile, PresetData);
		}
		else
		{
			LBE_WARN("Preset: {0} could not be loaded, file could not be opened.", PresetName);
		}
		PresetFile.close();

		PresetName.replace(PresetName.find(lbe::CUSTOM_PRESET_PATH), lbe::CUSTOM_PRESET_PATH.length(), "");
		PresetName.replace(PresetName.find(".preset"), 7, "");

		CustomPresets.insert(std::pair<std::string, std::string>(PresetName, PresetData));
		CustomPresetButtonToggles.insert(std::pair<std::string, bool>(PresetName, false));
	}

	
}

void Resources::SavePreset()
{
	std::stringstream FilePath;
	FilePath << lbe::CUSTOM_PRESET_PATH << SavePresetName << ".preset";
	
	std::ofstream PresetFile;
	PresetFile.open(FilePath.str());
	if (PresetFile.is_open())
	{
		PresetFile << SaveStringText;
	}
	else
	{
		LBE_WARN("Preset: {0} could not be loaded, file could not be opened.", FilePath.str());
	}
	PresetFile.close();
}

void Resources::DeletePreset()
{
	std::stringstream FilePath;
	FilePath << lbe::CUSTOM_PRESET_PATH << SavePresetName << ".preset";
	std::remove(FilePath.str().c_str());
}

void Resources::LoadKeyValuePair(const std::string Key, const std::string Value)
{
	// Weapons
	if (!Key.compare("WRS"))		{ bHasRustySword = true; }
	else if (!Key.compare("WSt"))	{ bHasStinger = true; }
	else if (!Key.compare("WID"))	{ bHasIronDagger = true; }
	else if (!Key.compare("WSS"))	{ bHasSkeletonSword = true; }
	else if (!Key.compare("WSc"))	{ bHasScythe = true; }
	else if (!Key.compare("WES"))	{ bHasEnchantedScythe = true; }
	else if (!Key.compare("WPS"))	{ bHasPoisonSpear = true; }
	else if (!Key.compare("WPSP"))	{ bHasPoisonSpearPlus = true; }
	else if (!Key.compare("WM"))	{ bHasMace = true; }
	else if (!Key.compare("WT"))	{ bHasTrident = true; }
	else if (!Key.compare("WPTP"))	{ bHasPoisonTridentPlus = true; }
	else if (!Key.compare("WSSc"))	{ bHasSilverScimitar = true; }
	else if (!Key.compare("WB"))	{ bHasBow = true; }
	else if (!Key.compare("WSB"))	{ bHasSuperBow = true; }
	else if (!Key.compare("WESB"))	{ bHasEnchantedSuperBow = true; }
	else if (!Key.compare("WA"))	{ bHasArrows = true; }
	else if (!Key.compare("WFA"))	{ bHasFireArrows = true; }
	else if (!Key.compare("WIA"))	{ bHasIceArrows = true; }
	else if (!Key.compare("WPA"))	{ bHasPoisonArrows = true; }
	else if (!Key.compare("WAP"))	{ bHasArrowsPlus = true; }
	else if (!Key.compare("WPAP"))	{ bHasPoisonArrowsPlus = true; }
	else if (!Key.compare("WMS"))	{ bHasMageStaff = true; }
	// Off-hand
	else if (!Key.compare("OSS"))	{ bHasSkeletonShield = true; }
	else if (!Key.compare("OJS"))	{ bHasJungleShield = true; }
	else if (!Key.compare("OKS"))	{ bHasKnightsShield = true; }
	else if (!Key.compare("OSJS"))	{ bHasSuperJungleShield = true; }
	else if (!Key.compare("OOHD"))	{ bHasOffHandDagger = true; }
	// Armor
	else if (!Key.compare("AHA"))	{ BestHeadArmor = atoi(Value.c_str()); }
	else if (!Key.compare("ABA"))	{ BestBodyArmor = atoi(Value.c_str()); }
	else if (!Key.compare("ALA"))	{ BestLegArmor = atoi(Value.c_str()); }
	else if (!Key.compare("AMR"))	{ bHasMageRobes = true; }
	else if (!Key.compare("ARR"))	{ bHasReaperRobes = true; }
	// Back/other
	else if (!Key.compare("BOT"))	{ bHasOxygenTank = true; }
	else if (!Key.compare("BAOT"))	{ bHasAncientOxygenTank = true; }
	else if (!Key.compare("BSC"))	{ bHasSnakeCloak = true; }
	else if (!Key.compare("BLSC"))	{ bHasLavaSnakeCloak = true; }
	else if (!Key.compare("BLC"))	{ bHasLizardCloak = true; }
	else if (!Key.compare("BEC"))	{ bHasElephantCloak = true; }
	else if (!Key.compare("BLB"))	{ bHasLightbulb = true; }
	else if (!Key.compare("BSF"))	{ bHasSharkFin = true; }
	// Neck
	else if (!Key.compare("NB"))	{ BerserkerAmuletLevel = atoi(Value.c_str()); }
	else if (!Key.compare("NGS"))	{ bHasGhostScanAmulet = true; }
	else if (!Key.compare("NI"))	{ bHasInvisibilityAmulet = true; }
	else if (!Key.compare("NEI"))	{ bHasEnchantedInvisibilityAmulet = true; }
	else if (!Key.compare("NO"))	{ bHasOxygenAmulet = true; }
	// Ring
	else if (!Key.compare("RB"))	{ BerserkerRingLevel = atoi(Value.c_str()); }
	else if (!Key.compare("RGS"))	{ bHasGhostScanRing = true; }
	else if (!Key.compare("RI"))	{ bHasInvisibilityRing = true; }
	else if (!Key.compare("REI"))	{ bHasEnchantedInvisibilityRing = true; }
	else if (!Key.compare("RO"))	{ bHasOxygenRing = true; }
	// Gloves 
	else if (!Key.compare("GF"))	{ bHasFireGloves = true; }
	else if (!Key.compare("GI"))	{ bHasIceGloves = true; }
	// Research & Quests
	else if (!Key.compare("QPDR"))	{ bHasPoisonDamageResearch = true; }
	else if (!Key.compare("QCWPPT")){ bHasCompletedWitchsPotionPartTwo = true; }
	// Spells and Emblems
	else if (!Key.compare("SHP"))	{ PlayerHPCurrentlySelected = atoi(Value.c_str()); }
	else if (!Key.compare("SF"))	{ FireSpellLevel = atoi(Value.c_str()); }
	else if (!Key.compare("SR"))	{ ReflectSpellLevel = atoi(Value.c_str()); }
	else if (!Key.compare("ST"))	{ ThunderSpellLevel = atoi(Value.c_str()); }
	else if (!Key.compare("SL"))	{ LifestealSpellLevel = atoi(Value.c_str()); }
	else if (!Key.compare("SS"))	{ SandstormSpellLevel = atoi(Value.c_str()); }
	// Potions
	else if (!Key.compare("PHP"))	{ bHasHPPotion = true; }
	else if (!Key.compare("PF"))	{ bHasFreezePotion = true; }
	else if (!Key.compare("PA"))	{ bHasAccuracyPotion = true; }
	else if (!Key.compare("PGS"))	{ bHasGhostScanPotion = true; }
	else if (!Key.compare("PSHP"))	{ bHasSuperHPPotion = true; }
	else if (!Key.compare("PS"))	{ bHasStrengthPotion = true; }
}
