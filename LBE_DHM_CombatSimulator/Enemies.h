#pragma once
#include "Enums.h"
#include <string>

class Enemies
{
private:
	// Base Stats
	static int MaxHP;
	static int Attack;
	static int Accuracy;
	static int Defence;
	static int WeaponAttackCooldown;
	// Type
	static bool bIsSkeleton;
	static bool bIsGhost;
	// Cold Resistance
	static bool bRequiresColdResistance;
	static int MinColdDamage;
	static int MaxColdDamage;
	// Oxygen 
	static bool bRequiresOxygenTank;
	static int MinDrowningDamage;
	static int MaxDrowningDamage;
	// Vulnerabilities
	static bool bIsVulnerableToFire;
	static bool bIsVulnerableToCold;
	static bool bIsVulnerableToThunder;
	// Evade
	static bool bHasEvadeChance;
	static int EvadeChance;
	static int EnchantedEvadeChance;
	// Retaliate
	static bool bCanRetaliateDamage;
	static WeaponType RetaliateDamageType;
	static int RetaliateDamage;
	// Infect
	static bool bCanInfect;
	static int InfectThreshold;
	// Wound
	static bool bHasWoundEffect;
	static int WoundDamage;
	// Auto Attack Charge
	static bool bHasAutoAttackCharge;
	static int AttacksNeededToCharge;
	static int AutoAttackChargeMinDamage;
	static int AutoAttackChargeMaxDamage;
	// Swarm Attack
	static bool bHasSwarmAttack;
	static int SwarmSize;
	static int SwarmDamage;
	// Multi-hit
	static int NumHits;
	// Immunities
	static bool bHasColdResistance;
	static bool bHasFireResistance;
	static bool bHasThunderResistance;
	// Magic Attack
	static bool bHasMagicAttack;
	static int MinMagicDamage;
	static int MaxMagicDamage;
	static int MagicAttackChance;
	// Heal
	static bool bHasHealAbility;
	static int MinAbilityHeal;
	static int MaxAbilityHeal;
	static int HealAbilityChance;
	// Charge Attack
	static bool bHasChargeAbility;
	static bool bChargeDoesHealingInsteadOfDamage;
	static int MinChargeAbilityPower;
	static int MaxChargeAbilityPower;
	static int ChargeAbilityChance;
	static int ChargeCastTime;
	static bool bChargeUsesThreshold;
	static int ChargeThreshold;
	static bool bOnlyUseChargeAbilityOnce;
	// Sandstorm
	static bool bHasSandstormThreshold;
	static int SandstormThreshold;

	static EnemyType CurrentEnemy;
	static std::string EnemyName;
public:
	Enemies();
	~Enemies();

	// Base Stats
	static int GetMaxHP();
	static int GetAttack();
	static int GetAccuracy();
	static int GetDefence();
	static int GetWeaponAttackCooldown();
	// Typings
	static bool IsSkeleton();
	static bool IsGhost();
	// Cold Resistance
	static bool RequiresColdResistance();
	static int GetMinColdDamage();
	static int GetMaxColdDamage();
	// Oxygen 
	static bool RequiresOxygenTank();
	static int GetMinDrowningDamage();
	static int GetMaxDrowningDamage();
	// Vulnerabilities
	static bool IsVulnerableToFire();
	static bool IsVulnerableToCold();
	static bool IsVulnerableToThunder();
	// Evade
	static bool HasEvadeChance();
	static int GetEvadeChance();
	static bool GetEnchantedEvadeChance();
	// Retaliate
	static bool CanRetaliateDamage();
	static WeaponType GetRetaliateDamageType();
	static int GetRetaliateDamage();
	// Infect
	static bool CanInfect();
	static int GetInfectThreshold();
	// Wound
	static bool HasWoundEffect();
	static int GetWoundDamage();
	// Auto Attack Charge
	static bool HasAutoAttackCharge();
	static int GetAttacksNeededToCharge();
	static int GetAutoAttackChargeMinDamage();
	static int GetAutoAttackChargeMaxDamage();
	// Swarm Attack
	static bool HasSwarmAttack();
	static int GetSwarmSize();
	static int GetSwarmDamage();
	// Multi-hit
	static int GetNumHits();
	// Immunities
	static bool HasColdResistance();
	static bool HasFireResistance();
	static bool HasThunderResistance();
	// Magic Attack
	static bool HasMagicAttack();
	static int GetMinMagicDamage();
	static int GetMaxMagicDamage();
	static int GetMagicAttackChance();
	// Heal
	static bool HasHealAbility();
	static int GetMinAbilityHeal();
	static int GetMaxAbilityHeal();
	static int GetHealAbilityChance();
	// Charge Attack
	static bool HasChargeAbility();
	static bool ChargeDoesHealingInsteadOfDamage();
	static int GetMinChargeAbilityPower();
	static int GetMaxChargeAbilityPower();
	static int GetChargeAbilityChance();
	static int GetChargeCastTime();
	static bool ChargeUsesThreshold();
	static int GetChargeThreshold();
	static bool OnlyUseChargeAbilityOnce();
	// Sandstorm
	static bool HasSandstormThreshold();
	static int GetSandstormThreshold();

	
	static EnemyType GetCurrentEnemyType();
	static std::string GetEnemyName();

	static bool SetCurrentEnemyType(EnemyType NewEnemyType);
};

