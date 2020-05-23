#pragma once
#include "Enums.h"

#include <map>

#include "Consts.h"
#include "CombatStatsStruct.h"

class Resources
{
public:
	// Weapons
	static bool bHasRustySword;
	static bool bHasStinger;
	static bool bHasIronDagger;
	static bool bHasSkeletonSword;
	static bool bHasScythe;
	static bool bHasEnchantedScythe;
	static bool bHasPoisonSpear;
	static bool bHasPoisonSpearPlus;
	static bool bHasMace;
	static bool bHasTrident;
	static bool bHasPoisonTridentPlus;
	static bool bHasSilverScimitar;
	static bool bHasBow;
	static bool bHasSuperBow;
	static bool bHasEnchantedSuperBow;
	static bool bHasArrows;
	static bool bHasFireArrows;
	static bool bHasIceArrows;
	static bool bHasPoisonArrows;
	static bool bHasArrowsPlus;
	static bool bHasPoisonArrowsPlus;
	static bool bHasMageStaff;
	// Off-hand
	static bool bHasSkeletonShield;
	static bool bHasJungleShield;
	static bool bHasKnightsShield;
	static bool bHasSuperJungleShield;
	static bool bHasOffHandDagger;
	// Armor
	static int BestHeadArmor;
	static int BestBodyArmor;
	static int BestLegArmor;
	static bool bHasMageRobes;
	static bool bHasReaperRobes;
	// Back/other
	static bool bHasOxygenTank;
	static bool bHasAncientOxygenTank;
	static bool bHasSnakeCloak;
	static bool bHasLavaSnakeCloak;
	static bool bHasLizardCloak;
	static bool bHasElephantCloak;
	static bool bHasLightbulb;
	static bool bHasSharkFin;
	// Neck
	static int BerserkerAmuletLevel;
	static bool bHasGhostScanAmulet;
	static bool bHasInvisibilityAmulet;
	static bool bHasEnchantedInvisibilityAmulet;
	static bool bHasOxygenAmulet;
	// Ring
	static int BerserkerRingLevel;
	static bool bHasGhostScanRing;
	static bool bHasInvisibilityRing;
	static bool bHasEnchantedInvisibilityRing;
	static bool bHasOxygenRing;
	// Gloves 
	static bool bHasFireGloves;
	static bool bHasIceGloves;
	// Research & Quests
	static bool bHasPoisonDamageResearch;
	static bool bHasCompletedWitchsPotionPartTwo;
	// Spells and Emblems
	static int PlayerHPCurrentlySelected;
	static int FireSpellLevel;
	static int ReflectSpellLevel;
	static int ThunderSpellLevel;
	static int LifestealSpellLevel;
	static int SandstormSpellLevel;
	// Potions
	static bool bHasHPPotion;
	static bool bHasFreezePotion;
	static bool bHasAccuracyPotion;
	static bool bHasGhostScanPotion;
	static bool bHasSuperHPPotion;
	static bool bHasStrengthPotion;

	// Simulation data
	static int NumIterations;
	static int CurrentIteration;
	static int NumWins;
	static bool bIsCurrentlySimulating;

	// Custom Enemy Base Stats
	static int CustomMaxHP;
	static int CustomAttack;
	static int CustomAccuracy;
	static int CustomDefence;
	// Custom Multi-hit
	static int CustomNumHits;
	// Custom Enemy Type
	static bool bIsCustomSkeleton;
	static bool bIsCustomGhost;
	// Custom Vulnerabilities
	static bool bIsCustomVulnerableToFire;
	static bool bIsCustomVulnerableToIce;
	static bool bIsCustomVulnerableToThunder;
	// Custom Cold Resistance
	static bool bCustomRequireColdResistance;
	static int CustomMinColdDamage;
	static int CustomMaxColdDamage;
	// Custom Oxygen
	static bool bCustomRequireOxygen;
	static int CustomMinDrowningDamage;
	static int CustomMaxDrowningDamage;
	// Custom Infection
	static bool bCustomCanInfect;
	static int CustomInfectThreshold;
	// Custom Wound
	static bool bCustomHasWoundEffect;
	static int CustomWoundDamage;
	// Custom Swarm Attack
	static bool bCustomHasSwarmAttack;
	static int CustomSwarmSize;
	static int CustomSwarmDamage;
	// Custom Auto Attack Charge
	static bool bCustomHasAutoAttackCharge;
	static int CustomAttacksNeededToCharge;
	static int CustomAutoAttackChargeMinDamage;
	static int CustomAutoAttackChargeMaxDamage;
	// Custom Evade
	static bool bCustomHasEvadeChance;
	static int CustomEvadeChance;
	static int CustomEnchantedEvadeChance;
	// Custom Retaliate
	static bool bCustomCanRetaliateDamage;
	static int CustomRetaliateDamageType;
	static int CustomRetaliateDamage;
	// Custom Magic Attack
	static bool bCustomHasMagicAttack;
	static int CustomMinMagicDamage;
	static int CustomMaxMagicDamage;
	static int CustomMagicAttackChance;
	// Custom Heal Ability
	static bool bCustomHasHealAbility;
	static int CustomMinAbilityHeal;
	static int CustomMaxAbilityHeal;
	static int CustomHealAbilityChance;
	// Custom Charge Ability
	static bool bCustomHasChargeAbility;
	static bool bCustomChargeDoesHealingInsteadOfDamage;
	static int CustomMinChargeAbilityPower;
	static int CustomMaxChargeAbilityPower;
	static int CustomChargeAbilityChance;
	static int CustomChargeCastTime;
	static bool bCustomChargeUsesThreshold;
	static int CustomChargeThreshold;
	static bool bOnlyUseChargeAbilityOnce;

	// Stats
	static CombatStats Stats;

	// Presets
	static char SaveStringText[lbe::SAVE_STRING_MAX_SIZE];
	static char SavePresetName[lbe::SAVE_PRESET_NAME_MAX_SIZE];
	static std::map<std::string, std::string> CustomPresets;
	static std::map<std::string, bool> CustomPresetButtonToggles;

	Resources();
	~Resources();

	static bool HasAtLeastOneKindOfArrow();
	static void ResetStats();
	static void ResetGear();
	static void UsePreset(int PresetNumber);
	static void GenerateSaveString();
	static void LoadSaveString();
	static void LoadCustomPresets();
	static void SavePreset();
	static void DeletePreset();

private:
	static void LoadKeyValuePair(const std::string Key, const std::string Value);
};

