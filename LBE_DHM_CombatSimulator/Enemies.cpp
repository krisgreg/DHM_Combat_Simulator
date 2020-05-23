#include "Enemies.h"
#include "Log.h"
#include "Resources.h"

// Base Stats
int Enemies::MaxHP = 10;
int Enemies::Attack = 1;
int Enemies::Accuracy = 1;
int Enemies::Defence = 0;
int Enemies::WeaponAttackCooldown = 3;
// Type
bool Enemies::bIsSkeleton = false;
bool Enemies::bIsGhost = false;
// Cold Resistance
bool Enemies::bRequiresColdResistance = false;
int Enemies::MinColdDamage = 1;
int Enemies::MaxColdDamage = 4;
// Oxygen 
bool Enemies::bRequiresOxygenTank = false;
int Enemies::MinDrowningDamage = 5;
int Enemies::MaxDrowningDamage = 15;
// Vulnerabilities
bool Enemies::bIsVulnerableToFire = false;
bool Enemies::bIsVulnerableToCold = false;
bool Enemies::bIsVulnerableToThunder = false;
// Evade
bool Enemies::bHasEvadeChance = false;
int Enemies::EvadeChance = 0;
int Enemies::EnchantedEvadeChance = 0;
bool Enemies::bCanRetaliateDamage = false;
WeaponType Enemies::RetaliateDamageType = WeaponType::Melee;
int Enemies::RetaliateDamage = 0;
bool Enemies::bCanInfect = false;
int Enemies::InfectThreshold = 0;
bool Enemies::bHasWoundEffect = false;
int Enemies::WoundDamage = 0;
// Auto Attack Charge
bool Enemies::bHasAutoAttackCharge = false;
int Enemies::AttacksNeededToCharge = 4;
int Enemies::AutoAttackChargeMinDamage = 30;
int Enemies::AutoAttackChargeMaxDamage = 40;
// Swarm Attack
bool Enemies::bHasSwarmAttack = false;
int Enemies::SwarmSize = 6;
int Enemies::SwarmDamage = 1;
// Multi-hit
int Enemies::NumHits = 1;
// Immunities
bool Enemies::bHasColdResistance = false;
bool Enemies::bHasFireResistance = false;
bool Enemies::bHasThunderResistance = false;
// Magic Attack
bool Enemies::bHasMagicAttack = false;
int Enemies::MinMagicDamage = 0;
int Enemies::MaxMagicDamage = 4;
int Enemies::MagicAttackChance = 1;
// Heal
bool Enemies::bHasHealAbility = false;
int Enemies::MinAbilityHeal = 1;
int Enemies::MaxAbilityHeal = 5;
int Enemies::HealAbilityChance = 3;
// Charge Attack
bool Enemies::bHasChargeAbility = false;
bool Enemies::bChargeDoesHealingInsteadOfDamage = false;
int Enemies::MinChargeAbilityPower = 30;
int Enemies::MaxChargeAbilityPower = 40;
int Enemies::ChargeAbilityChance = 1;
int Enemies::ChargeCastTime = 7;
bool Enemies::bOnlyUseChargeAbilityOnce = false;
bool Enemies::bChargeUsesThreshold = false;
int Enemies::ChargeThreshold = 0;
// sandstorm
bool Enemies::bHasSandstormThreshold = false;
int Enemies::SandstormThreshold = 0;

EnemyType Enemies::CurrentEnemy = EnemyType::Chicken;
std::string Enemies::EnemyName = std::string("Chicken");

Enemies::Enemies()
{
}

Enemies::~Enemies()
{
}

int Enemies::GetMaxHP()
{
	return MaxHP;
}

int Enemies::GetAttack()
{
	return Attack;
}

int Enemies::GetAccuracy()
{
	return Accuracy;
}

int Enemies::GetDefence()
{
	return Defence;
}

int Enemies::GetWeaponAttackCooldown()
{
	return WeaponAttackCooldown;
}

bool Enemies::IsSkeleton()
{
	return bIsSkeleton;
}

bool Enemies::IsGhost()
{
	return bIsGhost;
}

bool Enemies::RequiresColdResistance()
{
	return bRequiresColdResistance;
}

int Enemies::GetMinColdDamage()
{
	return MinColdDamage;
}

int Enemies::GetMaxColdDamage()
{
	return MaxColdDamage;
}

bool Enemies::RequiresOxygenTank()
{
	return bRequiresOxygenTank;
}

int Enemies::GetMinDrowningDamage()
{
	return MinDrowningDamage;
}

int Enemies::GetMaxDrowningDamage()
{
	return MaxDrowningDamage;
}

bool Enemies::IsVulnerableToFire()
{
	return bIsVulnerableToFire;
}

bool Enemies::IsVulnerableToCold()
{
	return bIsVulnerableToCold;
}

bool Enemies::IsVulnerableToThunder()
{
	return bIsVulnerableToThunder;
}

bool Enemies::HasEvadeChance()
{
	return bHasEvadeChance;
}

int Enemies::GetEvadeChance()
{
	return EvadeChance;
}

bool Enemies::GetEnchantedEvadeChance()
{
	return EnchantedEvadeChance;
}

bool Enemies::CanRetaliateDamage()
{
	return bCanRetaliateDamage;
}

WeaponType Enemies::GetRetaliateDamageType()
{
	return RetaliateDamageType;
}

int Enemies::GetRetaliateDamage()
{
	return RetaliateDamage;
}

bool Enemies::CanInfect()
{
	return bCanInfect;
}

int Enemies::GetInfectThreshold()
{
	return InfectThreshold;
}

bool Enemies::HasWoundEffect()
{
	return bHasWoundEffect;
}

int Enemies::GetWoundDamage()
{
	return WoundDamage;
}

bool Enemies::HasAutoAttackCharge()
{
	return bHasAutoAttackCharge;
}

int Enemies::GetAttacksNeededToCharge()
{
	return AttacksNeededToCharge;
}

int Enemies::GetAutoAttackChargeMinDamage()
{
	return AutoAttackChargeMinDamage;
}

int Enemies::GetAutoAttackChargeMaxDamage()
{
	return AutoAttackChargeMaxDamage;
}

bool Enemies::HasSwarmAttack()
{
	return bHasSwarmAttack;
}

int Enemies::GetSwarmSize()
{
	return SwarmSize;
}

int Enemies::GetSwarmDamage()
{
	return SwarmDamage;
}

int Enemies::GetNumHits()
{
	return NumHits;
}

bool Enemies::HasColdResistance()
{
	return bHasColdResistance;
}

bool Enemies::HasFireResistance()
{
	return bHasFireResistance;
}

bool Enemies::HasThunderResistance()
{
	return bHasThunderResistance;
}

bool Enemies::HasMagicAttack()
{
	return bHasMagicAttack;
}

int Enemies::GetMinMagicDamage()
{
	return MinMagicDamage;
}

int Enemies::GetMaxMagicDamage()
{
	return MaxMagicDamage;
}

int Enemies::GetMagicAttackChance()
{
	return MagicAttackChance;
}

bool Enemies::HasHealAbility()
{
	return bHasHealAbility;
}

int Enemies::GetMinAbilityHeal()
{
	return MinAbilityHeal;
}

int Enemies::GetMaxAbilityHeal()
{
	return MaxAbilityHeal;
}

int Enemies::GetHealAbilityChance()
{
	return HealAbilityChance;
}

bool Enemies::HasChargeAbility()
{
	return bHasChargeAbility;
}

bool Enemies::ChargeDoesHealingInsteadOfDamage()
{
	return bChargeDoesHealingInsteadOfDamage;
}

int Enemies::GetMinChargeAbilityPower()
{
	return MinChargeAbilityPower;
}

int Enemies::GetMaxChargeAbilityPower()
{
	return MaxChargeAbilityPower;
}

int Enemies::GetChargeAbilityChance()
{
	return ChargeAbilityChance;
}

int Enemies::GetChargeCastTime()
{
	return ChargeCastTime;
}

bool Enemies::ChargeUsesThreshold()
{
	return bChargeUsesThreshold;
}

int Enemies::GetChargeThreshold()
{
	return ChargeThreshold;
}

bool Enemies::OnlyUseChargeAbilityOnce()
{
	return bOnlyUseChargeAbilityOnce;
}

bool Enemies::HasSandstormThreshold()
{
	return bHasSandstormThreshold;
}

int Enemies::GetSandstormThreshold()
{
	return SandstormThreshold;
}

EnemyType Enemies::GetCurrentEnemyType()
{
	return CurrentEnemy;
}

std::string Enemies::GetEnemyName()
{
	return EnemyName;
}

bool Enemies::SetCurrentEnemyType(EnemyType NewEnemyType)
{
	// Type
	bIsSkeleton = false;
	bIsGhost = false;
	// Vulnerabilities
	bIsVulnerableToFire = false;
	bIsVulnerableToCold = false;
	bIsVulnerableToThunder = false;
	// Cold Resistance
	bRequiresColdResistance = false;
	MinColdDamage = 1;
	MaxColdDamage = 4;
	// Oxygen
	bRequiresOxygenTank = false;
	MinDrowningDamage = 5;
	MaxDrowningDamage = 15;
	// Evade
	bHasEvadeChance = false;
	EvadeChance = 0;
	EnchantedEvadeChance = 0;
	// Retaliate
	bCanRetaliateDamage = false;
	RetaliateDamageType = WeaponType::Melee;
	RetaliateDamage = 0;
	// Infection
	bCanInfect = false;
	InfectThreshold = 0;
	// Wound
	bHasWoundEffect = false;
	WoundDamage = 0;
	// Auto Attack Charge
	bHasAutoAttackCharge = false;
	AttacksNeededToCharge = 4;
	AutoAttackChargeMinDamage = 30;
	AutoAttackChargeMaxDamage = 40;
	// Swarm Attack
	bHasSwarmAttack = false;
	SwarmSize = 6;
	SwarmDamage = 1;
	// Multi-hit
	NumHits = 1;
	// Immunities
	bHasColdResistance = false;
	bHasFireResistance = false;
	bHasThunderResistance = false;
	// Magic Attack
	bHasMagicAttack = false;
	MinMagicDamage = 0;
	MaxMagicDamage = 4;
	MagicAttackChance = 1;
	// Heal
	bHasHealAbility = false;
	MinAbilityHeal = 1;
	MaxAbilityHeal = 5;
	HealAbilityChance = 3;
	// Charge Attack
	bHasChargeAbility = false;
	bChargeDoesHealingInsteadOfDamage = false;
	MinChargeAbilityPower = 30;
	MaxChargeAbilityPower = 40;
	ChargeAbilityChance = 1;
	ChargeCastTime = 7;
	bChargeUsesThreshold = false;
	ChargeThreshold = 0;
	bOnlyUseChargeAbilityOnce = false;
	// Sandstorm
	bHasSandstormThreshold = false;
	SandstormThreshold = 0;
	// Base Stats
	WeaponAttackCooldown = 3;
	EnemyName = "Unspecified";

	// Custom
	if (NewEnemyType == EnemyType::Custom)
	{
		// Custom Enemy Base Stats
		MaxHP = Resources::CustomMaxHP;
		Attack = Resources::CustomAttack;
		Accuracy = Resources::CustomAccuracy;
		Defence = Resources::CustomDefence;
		// Custom Multi-hit
		NumHits = Resources::CustomNumHits;
		// Custom Enemy Type
		bIsSkeleton = Resources::bIsCustomSkeleton;
		bIsGhost = Resources::bIsCustomGhost;
		// Custom Vulnerabilities
		bIsVulnerableToFire = Resources::bIsCustomVulnerableToFire;
		bIsVulnerableToCold = Resources::bIsCustomVulnerableToIce;
		bIsVulnerableToThunder = Resources::bIsCustomVulnerableToThunder;
		// Custom Cold Resistance
		bRequiresColdResistance = Resources::bCustomRequireColdResistance;
		MinColdDamage = Resources::CustomMinColdDamage;
		MaxColdDamage = Resources::CustomMaxColdDamage;
		// Custom Oxygen
		bRequiresOxygenTank = Resources::bCustomRequireOxygen;
		MinDrowningDamage = Resources::CustomMinDrowningDamage;
		MaxDrowningDamage = Resources::CustomMaxDrowningDamage;
		// Custom Infection
		bCanInfect = Resources::bCustomCanInfect;
		InfectThreshold = Resources::CustomInfectThreshold;
		// Custom Wound
		bHasWoundEffect = Resources::bCustomHasWoundEffect;
		WoundDamage = Resources::CustomWoundDamage;
		// Custom Swarm Attack
		bHasSwarmAttack = Resources::bCustomHasSwarmAttack;
		SwarmSize = Resources::CustomSwarmSize;
		SwarmDamage = Resources::CustomSwarmDamage;
		// Custom Auto Attack Charge
		bHasAutoAttackCharge = Resources::bCustomHasAutoAttackCharge;
		AttacksNeededToCharge = Resources::CustomAttacksNeededToCharge;
		AutoAttackChargeMinDamage = Resources::CustomAutoAttackChargeMinDamage;
		AutoAttackChargeMaxDamage = Resources::CustomAutoAttackChargeMaxDamage;
		// Custom Evade
		bHasEvadeChance = Resources::bCustomHasEvadeChance;
		EvadeChance = Resources::CustomEvadeChance;
		EnchantedEvadeChance = Resources::CustomEnchantedEvadeChance;
		// Custom Retaliate
		bCanRetaliateDamage = Resources::bCustomCanRetaliateDamage;
		if (Resources::CustomRetaliateDamageType == 0)
		{
			RetaliateDamageType = WeaponType::Any;
		}
		else if (Resources::CustomRetaliateDamageType == 1)
		{
			RetaliateDamageType = WeaponType::Melee;
		}
		else if (Resources::CustomRetaliateDamageType == 2)
		{
			RetaliateDamageType = WeaponType::Ranged;
		}
		RetaliateDamage = Resources::CustomRetaliateDamage;
		// Custom Magic Attack
		bHasMagicAttack = Resources::bCustomHasMagicAttack;
		MinMagicDamage = Resources::CustomMinMagicDamage;
		MaxMagicDamage = Resources::CustomMaxMagicDamage;
		MagicAttackChance = Resources::CustomMagicAttackChance;
		// Custom Heal Ability
		bHasHealAbility = Resources::bCustomHasHealAbility;
		MinAbilityHeal = Resources::CustomMinAbilityHeal;
		MaxAbilityHeal = Resources::CustomMaxAbilityHeal;
		HealAbilityChance = Resources::CustomHealAbilityChance;
		// Custom Charge Ability
		bHasChargeAbility = Resources::bCustomHasChargeAbility;
		bChargeDoesHealingInsteadOfDamage = Resources::bCustomChargeDoesHealingInsteadOfDamage;
		MinChargeAbilityPower = Resources::CustomMinChargeAbilityPower;
		MaxChargeAbilityPower = Resources::CustomMaxChargeAbilityPower;
		ChargeAbilityChance = Resources::CustomChargeAbilityChance;
		ChargeCastTime = Resources::CustomChargeCastTime;
		bChargeUsesThreshold = Resources::bCustomChargeUsesThreshold;
		ChargeThreshold = Resources::CustomChargeThreshold;

		EnemyName = "Custom";
	}
	// Fields
	else if (NewEnemyType == EnemyType::Chicken)
	{
		MaxHP = 10;
		Attack = 1;
		Accuracy = 1;
		Defence = 0;
		EnemyName = "Chicken";
	}
	else if (NewEnemyType == EnemyType::Rat)
	{
		MaxHP = 5;
		Attack = 2;
		Accuracy = 1;
		Defence = 0;
		EnemyName = "Rat";
	}
	else if (NewEnemyType == EnemyType::Bee)
	{
		MaxHP = 3;
		Attack = 1;
		Accuracy = 3;
		Defence = 0;
		EnemyName = "Bee";
		WeaponAttackCooldown = 2;
	}
	else if (NewEnemyType == EnemyType::BloodChicken)
	{
		MaxHP = 200;
		Attack = 8;
		Accuracy = 7;
		Defence = 17;
		EnemyName = "Blood Chicken";
	}
	else if (NewEnemyType == EnemyType::BloodRat)
	{
		MaxHP = 100;
		Attack = 15;
		Accuracy = 8;
		Defence = 17;
		EnemyName = "Blood Rat";
	}
	else if (NewEnemyType == EnemyType::BloodBee)
	{
		MaxHP = 50;
		Attack = 25;
		Accuracy = 9;
		Defence = 10;
		EnemyName = "Blood Bee";
		WeaponAttackCooldown = 2;
	}
	else if (NewEnemyType == EnemyType::TripleChicken)
	{
		MaxHP = 30;
		Attack = 1;
		Accuracy = 1;
		Defence = 0;
		EnemyName = "Triple Chicken";
		WeaponAttackCooldown = 2;
	}
	else if (NewEnemyType == EnemyType::TripleBloodChicken)
	{
		MaxHP = 600;
		Attack = 8;
		Accuracy = 7;
		Defence = 17;
		EnemyName = "Triple Blood Chicken";
		WeaponAttackCooldown = 2;
	}
	// Forest
	else if (NewEnemyType == EnemyType::Snake)
	{
		MaxHP = 15;
		Attack = 2;
		Accuracy = 2;
		Defence = 0;
		EnemyName = "Snake";
	}
	else if (NewEnemyType == EnemyType::Ent)
	{
		MaxHP = 30;
		Attack = 1;
		Accuracy = 1;
		Defence = 5;
		EnemyName = "Ent";
	}
	else if (NewEnemyType == EnemyType::Thief)
	{
		MaxHP = 10;
		Attack = 3;
		Accuracy = 3;
		Defence = 0;
		EnemyName = "Thief";
	}
	else if (NewEnemyType == EnemyType::BloodSnake)
	{
		MaxHP = 450;
		Attack = 18;
		Accuracy = 10;
		Defence = 15;
		EnemyName = "Blood Snake";
	}
	else if (NewEnemyType == EnemyType::BloodEnt)
	{
		MaxHP = 450;
		Attack = 10;
		Accuracy = 5;
		Defence = 20;
		EnemyName = "Blood Ent";
	}
	else if (NewEnemyType == EnemyType::BloodThief)
	{
		MaxHP = 400;
		Attack = 15;
		Accuracy = 10;
		Defence = 15;
		EnemyName = "Blood Thief";
	}
	// Caves
	else if (NewEnemyType == EnemyType::Bear)
	{
		MaxHP = 25;
		Attack = 2;
		Accuracy = 0;
		Defence = 3;
		EnemyName = "Bear";
	}
	else if (NewEnemyType == EnemyType::Bat)
	{
		MaxHP = 20;
		Attack = 2;
		Accuracy = 3;
		Defence = 0;
		EnemyName = "Bat";
		WeaponAttackCooldown = 2;
	}
	else if (NewEnemyType == EnemyType::Skeleton)
	{
		MaxHP = 10;
		Attack = 5;
		Accuracy = 5;
		Defence = 5;
		EnemyName = "Skeleton";
		bIsSkeleton = true;
	}
	else if (NewEnemyType == EnemyType::BloodBear)
	{
		MaxHP = 800;
		Attack = 15;
		Accuracy = 10;
		Defence = 15;
		EnemyName = "Blood Bear";
	}
	else if (NewEnemyType == EnemyType::BloodBat)
	{
		MaxHP = 600;
		Attack = 15;
		Accuracy = 12;
		Defence = 15;
		EnemyName = "Blood Bat";
		WeaponAttackCooldown = 2;
	}
	else if (NewEnemyType == EnemyType::BloodSkeleton)
	{
		MaxHP = 1000;
		Attack = 20;
		Accuracy = 14;
		Defence = 15;
		EnemyName = "Blood Skeleton";
		bIsSkeleton = true;
	}
	// Volcano
	else if (NewEnemyType == EnemyType::LavaSnake)
	{
		MaxHP = 20;
		Attack = 6;
		Accuracy = 6;
		Defence = 7;
		EnemyName = "Lava Snake";
		bIsVulnerableToCold = true;
	}
	else if (NewEnemyType == EnemyType::FireHawk)
	{
		MaxHP = 50;
		Attack = 5;
		Accuracy = 5;
		Defence = 3;
		EnemyName = "Fire Hawk";
		bIsVulnerableToCold = true;
		WeaponAttackCooldown = 4;
	}
	else if (NewEnemyType == EnemyType::FireMage)
	{
		MaxHP = 20;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Fire Mage";
		bIsVulnerableToCold = true;

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 3;
		MagicAttackChance = 1; // 1/1 = 100%

		bHasHealAbility = true;
		MinAbilityHeal = 1;
		MaxAbilityHeal = 5;
		HealAbilityChance = 3; // 1/3 = 33%
	}
	else if (NewEnemyType == EnemyType::BloodLavaSnake)
	{
		MaxHP = 800;
		Attack = 24;
		Accuracy = 24;
		Defence = 24;
		EnemyName = "Blood Lava Snake";
		bIsVulnerableToCold = true;
	}
	else if (NewEnemyType == EnemyType::BloodFireHawk)
	{
		MaxHP = 500;
		Attack = 15;
		Accuracy = 25;
		Defence = 26;
		EnemyName = "Blood Fire Hawk";
		bIsVulnerableToCold = true;
		WeaponAttackCooldown = 4;
	}
	else if (NewEnemyType == EnemyType::BloodFireMage)
	{
		MaxHP = 200;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Blood Fire Mage";
		bIsVulnerableToCold = true;

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 10;
		MagicAttackChance = 1; // 1/1 = 100%

		bHasHealAbility = true;
		MinAbilityHeal = 30;
		MaxAbilityHeal = 60;
		HealAbilityChance = 3; // 1/3 = 33%

		LBE_WARN("Blood Fire Mage's abilities only implemented with approximate values!");
	}
	else if (NewEnemyType == EnemyType::TripleFireHawk)
	{
		MaxHP = 150;
		Attack = 5;
		Accuracy = 5;
		Defence = 3;
		EnemyName = "Triple Fire Hawk";
		bIsVulnerableToCold = true;
		WeaponAttackCooldown = 2;
	}
	else if (NewEnemyType == EnemyType::TripleBloodFireHawk)
	{
		MaxHP = 1500;
		Attack = 15;
		Accuracy = 25;
		Defence = 26;
		EnemyName = "Triple Blood Fire Hawk";
		bIsVulnerableToCold = true;
		WeaponAttackCooldown = 2;
	}
	// Northern Fields
	else if (NewEnemyType == EnemyType::IceHawk)
	{
		MaxHP = 50;
		Attack = 7;
		Accuracy = 4;
		Defence = 4;
		EnemyName = "Ice Hawk";
		bRequiresColdResistance = true;
		MinColdDamage = 1;
		MaxColdDamage = 4;
		bIsVulnerableToFire = true;
		WeaponAttackCooldown = 4;
	}
	else if (NewEnemyType == EnemyType::FrozenEnt)
	{
		MaxHP = 40;
		Attack = 3;
		Accuracy = 6;
		Defence = 12;
		EnemyName = "Frozen Ent";
		bRequiresColdResistance = true;
		MinColdDamage = 1;
		MaxColdDamage = 4;
		bIsVulnerableToFire = true;
	}
	else if (NewEnemyType == EnemyType::Golem)
	{
		MaxHP = 30;
		Attack = 7;
		Accuracy = 8;
		Defence = 6;
		EnemyName = "Golem";
		bRequiresColdResistance = true;
		MinColdDamage = 1;
		MaxColdDamage = 4;
		bIsVulnerableToFire = true;
	}
	else if (NewEnemyType == EnemyType::BloodIceHawk)
	{
		MaxHP = 800;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Blood Ice Hawk";
		bRequiresColdResistance = true;
		MinColdDamage = 1;
		MaxColdDamage = 4;
		bIsVulnerableToFire = true;
		WeaponAttackCooldown = 4;

		bHasMagicAttack = true;
		MinMagicDamage = 30;
		MaxMagicDamage = 80;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	else if (NewEnemyType == EnemyType::BloodFrozenEnt)
	{
		MaxHP = 3500;
		Attack = 0;
		Accuracy = 0;
		Defence = 25;
		EnemyName = "Blood Frozen Ent";
		bRequiresColdResistance = true;
		MinColdDamage = 1;
		MaxColdDamage = 4;
		bIsVulnerableToFire = true;

		bHasMagicAttack = true;
		MinMagicDamage = 1;
		MaxMagicDamage = 6;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	else if (NewEnemyType == EnemyType::BloodGolem)
	{
		MaxHP = 2000;
		Attack = 35;
		Accuracy = 15;
		Defence = 24;
		EnemyName = "Blood Golem";
		bRequiresColdResistance = true;
		MinColdDamage = 1;
		MaxColdDamage = 4;
		bIsVulnerableToFire = true;
		NumHits = 2;
	}
	else if (NewEnemyType == EnemyType::TripleIceHawk)
	{
		MaxHP = 150;
		Attack = 7;
		Accuracy = 4;
		Defence = 4;
		EnemyName = "Triple Ice Hawk";
		bRequiresColdResistance = true;
		MinColdDamage = 1;
		MaxColdDamage = 4;
		bIsVulnerableToFire = true;
		WeaponAttackCooldown = 2;
	}
	else if (NewEnemyType == EnemyType::TripleBloodIceHawk)
	{
		MaxHP = 2400;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Triple Blood Ice Hawk";
		bRequiresColdResistance = true;
		MinColdDamage = 1;
		MaxColdDamage = 4;
		bIsVulnerableToFire = true;
		WeaponAttackCooldown = 2;

		bHasMagicAttack = true;
		MinMagicDamage = 30;
		MaxMagicDamage = 80;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	// Haunted Mansion
	else if (NewEnemyType == EnemyType::Ghost)
	{
		MaxHP = 50;
		Attack = 7;
		Accuracy = 7;
		Defence = 6;
		EnemyName = "Ghost";
		bIsGhost = true;
	}
	else if (NewEnemyType == EnemyType::SkeletonGhost)
	{
		MaxHP = 70;
		Attack = 7;
		Accuracy = 7;
		Defence = 15;
		EnemyName = "Skeleton Ghost";
		bIsGhost = true;
	}
	else if (NewEnemyType == EnemyType::Reaper)
	{
		MaxHP = 30;
		Attack = 15;
		Accuracy = 12;
		Defence = 10;
		EnemyName = "Reaper";
		bIsGhost = true;
	}
	else if (NewEnemyType == EnemyType::BloodGhost)
	{
		MaxHP = 1000;
		Attack = 50;
		Accuracy = 24;
		Defence = 50;
		EnemyName = "Blood Haunted Mansion";
		bIsGhost = true;
	}
	else if (NewEnemyType == EnemyType::BloodSkeletonGhost)
	{
		MaxHP = 1000;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Blood Haunted Mansion";
		bIsGhost = true;

		bHasEvadeChance = true;
		EvadeChance = 10;

		bHasMagicAttack = true;
		MinMagicDamage = 10;
		MaxMagicDamage = 15;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	else if (NewEnemyType == EnemyType::BloodReaper)
	{
		MaxHP = 1000;
		Attack = 75;
		Accuracy = 24;
		Defence = 65;
		EnemyName = "Blood Haunted Mansion";
		bIsGhost = true;
	}
	// Desert
	else if (NewEnemyType == EnemyType::DesertLizardBoss)
	{
		MaxHP = 100;
		Attack = 7;
		Accuracy = 7;
		Defence = 7;
		EnemyName = "Desert Lizard Boss";
		bIsVulnerableToCold = true;

		bHasChargeAbility = true;
		MinChargeAbilityPower = 30;
		MaxChargeAbilityPower = 40;
		ChargeAbilityChance = 1;
		ChargeCastTime = 7;
		bChargeUsesThreshold = true;
		ChargeThreshold = 50;
		bOnlyUseChargeAbilityOnce = true;
	}
	else if (NewEnemyType == EnemyType::DesertLizard2)
	{
		MaxHP = 200;
		Attack = 3;
		Accuracy = 10;
		Defence = 10;
		EnemyName = "Desert Lizard 2";
		bIsVulnerableToCold = true;

		bHasChargeAbility = true;
		MinChargeAbilityPower = 30;
		MaxChargeAbilityPower = 40;
		ChargeAbilityChance = 21;
		ChargeCastTime = 7;
	}
	else if (NewEnemyType == EnemyType::Scorpion)
	{
		MaxHP = 30;
		Attack = 12;
		Accuracy = 8;
		Defence = 14;
		EnemyName = "Scorpion";
		bIsVulnerableToCold = true;
	}
	else if (NewEnemyType == EnemyType::Lizard)
	{
		MaxHP = 30;
		Attack = 12;
		Accuracy = 7;
		Defence = 14;
		EnemyName = "Lizard";
		bIsVulnerableToCold = true;
		bHasEvadeChance = true;
		EvadeChance = 50;
	}
	else if (NewEnemyType == EnemyType::BloodDesertLizardBoss)
	{
		MaxHP = 1000;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Blood Desert Lizard Boss";
		bIsVulnerableToCold = true;

		bHasChargeAbility = true;
		MinChargeAbilityPower = 50;
		MaxChargeAbilityPower = 100;
		ChargeAbilityChance = 1;
		ChargeCastTime = 2;
	}
	else if (NewEnemyType == EnemyType::BloodDesertLizard2)
	{
		MaxHP = 1000;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Blood Desert Lizard 2";

		bIsVulnerableToCold = true;

		bHasChargeAbility = true;
		MinChargeAbilityPower = 50;
		MaxChargeAbilityPower = 100;
		ChargeAbilityChance = 1;
		ChargeCastTime = 2;
	}
	else if (NewEnemyType == EnemyType::BloodScorpion)
	{
		MaxHP = 1000;
		Attack = 13;
		Accuracy = 60;
		Defence = 14;
		EnemyName = "Blood Scorpion";

		bIsVulnerableToCold = true;

		bHasSandstormThreshold = true;
		SandstormThreshold = 200;
	}
	else if (NewEnemyType == EnemyType::BloodLizard)
	{
		MaxHP = 2000;
		Attack = 50;
		Accuracy = 23;
		Defence = 14;
		EnemyName = "Blood Lizard";

		bIsVulnerableToCold = true;
		bHasEvadeChance = true;
		EvadeChance = 90;
	}
	// Ocean
	else if (NewEnemyType == EnemyType::Squid)
	{
		MaxHP = 75;
		Attack = 12;
		Accuracy = 8;
		Defence = 24;
		EnemyName = "Squid";

		bRequiresOxygenTank = true;
		bIsVulnerableToThunder = true;
		bHasFireResistance = true;
	}
	else if (NewEnemyType == EnemyType::PufferFish)
	{
		MaxHP = 100;
		Attack = 5;
		Accuracy = 6;
		Defence = 15;
		EnemyName = "PufferFish";
		WeaponAttackCooldown = 2;

		bRequiresOxygenTank = true;
		bIsVulnerableToThunder = true;
		bHasFireResistance = true;

		bCanRetaliateDamage = true;
		RetaliateDamageType = WeaponType::Melee;
		RetaliateDamage = 10;
	}
	else if (NewEnemyType == EnemyType::Shark)
	{
		MaxHP = 100;
		Attack = 20;
		Accuracy = 6;
		Defence = 16;
		EnemyName = "Shark";

		bRequiresOxygenTank = true;
		bIsVulnerableToThunder = true;
		bHasFireResistance = true;
	}
	else if (NewEnemyType == EnemyType::BloodSquid)
	{
		MaxHP = 6000;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Blood Squid";

		bRequiresOxygenTank = true;
		bIsVulnerableToThunder = true;
		bHasFireResistance = true;

		bHasMagicAttack = true;
		MinMagicDamage = 20;
		MaxMagicDamage = 25;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	else if (NewEnemyType == EnemyType::BloodPufferFish)
	{
		MaxHP = 3500;
		Attack = 70;
		Accuracy = 30;
		Defence = 25;
		EnemyName = "Blood PufferFish";
		WeaponAttackCooldown = 2;

		bRequiresOxygenTank = true;
		bIsVulnerableToThunder = true;
		bHasFireResistance = true;

		bCanRetaliateDamage = true;
		RetaliateDamageType = WeaponType::Melee;
		RetaliateDamage = 50;
	}
	else if (NewEnemyType == EnemyType::BloodShark)
	{
		MaxHP = 3000;
		Attack = 25;
		Accuracy = 25;
		Defence = 32;
		EnemyName = "Blood Shark";
		WeaponAttackCooldown = 1;

		bRequiresOxygenTank = true;
		bIsVulnerableToThunder = true;
		bHasFireResistance = true;
	}
	// Jungle
	else if (NewEnemyType == EnemyType::Tribe)
	{
		MaxHP = 150;
		Attack = 20;
		Accuracy = 12;
		Defence = 8;
		EnemyName = "Tribe";
	}
	else if (NewEnemyType == EnemyType::Elephant)
	{
		MaxHP = 300;
		Attack = 2;
		Accuracy = 10;
		Defence = 18;
		EnemyName = "Elephant";
	}
	else if (NewEnemyType == EnemyType::Gorilla)
	{
		MaxHP = 150;
		Attack = 6;
		Accuracy = 12;
		Defence = 17;
		EnemyName = "Gorilla";
	}
	else if (NewEnemyType == EnemyType::BloodJunglePack)
	{
		MaxHP = 1500;
		Attack = 50;
		Accuracy = 27;
		Defence = 35;
		EnemyName = "Blood Jungle Pack";
	}
	// Dungeon Entrance
	else if (NewEnemyType == EnemyType::SkeletonMageBoss1)
	{
		MaxHP = 50;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Skeleton Mage Boss 1";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 5;
		MagicAttackChance = 1;
	}
	else if (NewEnemyType == EnemyType::SkeletonMageBoss2)
	{
		MaxHP = 150;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Skeleton Mage Boss 2";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 5;
		MagicAttackChance = 1;
	}
	else if (NewEnemyType == EnemyType::SkeletonMageBoss3)
	{
		MaxHP = 350;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Skeleton Mage Boss 3";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 5;
		MagicAttackChance = 1;
	}
	else if (NewEnemyType == EnemyType::SkeletonMageBoss4)
	{
		MaxHP = 150;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Skeleton Mage Boss 4";

		bHasMagicAttack = true;
		MinMagicDamage = 10;
		MaxMagicDamage = 15;
		MagicAttackChance = 1;

		bHasChargeAbility = true;
		MinChargeAbilityPower = 30;
		MaxChargeAbilityPower = 40;
		ChargeAbilityChance = 1; // 1/1 = 100%
		ChargeCastTime = 3;
		bChargeUsesThreshold = true;
		ChargeThreshold = 75;
		bOnlyUseChargeAbilityOnce = true;
	}
	else if (NewEnemyType == EnemyType::PoisonTribe)
	{
		MaxHP = 150;
		Attack = 15;
		Accuracy = 12;
		Defence = 8;
		EnemyName = "Poison Tribe";
		
		bHasWoundEffect = true;
		WoundDamage = 1;
	}
	else if (NewEnemyType == EnemyType::Statue)
	{
		MaxHP = 800;
		Attack = 2;
		Accuracy = 12;
		Defence = 15;
		EnemyName = "Statue";
	}
	else if (NewEnemyType == EnemyType::Gargoyle)
	{
		MaxHP = 150;
		Attack = 8;
		Accuracy = 12;
		Defence = 8;
		EnemyName = "Gargoyle";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 15;
		MagicAttackChance = 2;
	}
	// Dungeon
	else if (NewEnemyType == EnemyType::SkeletonMonks)
	{
		MaxHP = 200;
		Attack = 10;
		Accuracy = 12;
		Defence = 0;
		EnemyName = "Skeleton Monks";

		bHasChargeAbility = true;
		bChargeDoesHealingInsteadOfDamage = true;
		MinChargeAbilityPower = 100;
		MaxChargeAbilityPower = 100;
		ChargeAbilityChance = 1; // 1/1 = 100%
		ChargeCastTime = 3;
		bChargeUsesThreshold = true;
		ChargeThreshold = 60;
	}
	else if (NewEnemyType == EnemyType::DarkMage)
	{
		MaxHP = 200;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Dark Mage";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 15;
		MagicAttackChance = 1; // 1/1 = 100%

		bHasHealAbility = true;
		MinAbilityHeal = 1;
		MaxAbilityHeal = 11;
		HealAbilityChance = 3; // 1/3 = 33%

		bHasChargeAbility = true;
		MinChargeAbilityPower = 70;
		MaxChargeAbilityPower = 78;
		ChargeAbilityChance = 1; // 1/1 = 100%
		ChargeCastTime = 3;
		bChargeUsesThreshold = true;
		ChargeThreshold = 120;
	}
	else if (NewEnemyType == EnemyType::SkeletonPrisoner)
	{
		MaxHP = 100;
		Attack = 10;
		Accuracy = 13;
		Defence = 18;
		EnemyName = "Skeleton Prisoner";
	}
	// Coffin
	else if (NewEnemyType == EnemyType::SkeletonKing)
	{
		MaxHP = 350;
		Attack = 20;
		Accuracy = 13;
		Defence = 20;
		bIsSkeleton = true;
		EnemyName = "Skeleton King";
	}
	// Castle
	else if (NewEnemyType == EnemyType::CastleKnight)
	{
		MaxHP = 300;
		Attack = 20;
		Accuracy = 16;
		Defence = 53;
		EnemyName = "Castle Knight";
	}
	else if (NewEnemyType == EnemyType::Dragon)
	{
		MaxHP = 200;
		Attack = 20;
		Accuracy = 16;
		Defence = 30;
		EnemyName = "Dragon";

		bHasAutoAttackCharge = true;
		AttacksNeededToCharge = 4;
		AutoAttackChargeMinDamage = 30;
		AutoAttackChargeMaxDamage = 40;
	}
	else if (NewEnemyType == EnemyType::CastleMage)
	{
		MaxHP = 900;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Castle Mage";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 5;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	// Cemetery
	else if (NewEnemyType == EnemyType::Angel)
	{
		MaxHP = 500;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Angel";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 8;
		MagicAttackChance = 1; // 1/1 = 100%

		bHasHealAbility = true;
		MinAbilityHeal = 5;
		MaxAbilityHeal = 15;
		HealAbilityChance = 1; // 1/1 = 100%
	}
	else if (NewEnemyType == EnemyType::Zombie)
	{
		MaxHP = 200;
		Attack = 25;
		Accuracy = 19;
		Defence = 53;
		EnemyName = "Zombie";

		bCanInfect = true;
		InfectThreshold = 150;
	}
	else if (NewEnemyType == EnemyType::BabySkeleton)
	{
		MaxHP = 250;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Baby Skeleton";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 40;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	else if (NewEnemyType == EnemyType::CemeterySkeletonBoss)
	{
		MaxHP = 800;
		Attack = 10;
		Accuracy = 20;
		Defence = 20;
		EnemyName = "Cemetery Skeleton Boss";

		bHasChargeAbility = true;
		MinChargeAbilityPower = 100;
		MaxChargeAbilityPower = 150;
		ChargeAbilityChance = 41;
		ChargeCastTime = 7;
		bOnlyUseChargeAbilityOnce = true;
	}
	else if (NewEnemyType == EnemyType::CemeteryIceSkeletonBoss)
	{
		MaxHP = 700;
		Attack = 15;
		Accuracy = 22;
		Defence = 16;
		EnemyName = "Cemetery Ice Skeleton Boss";

		bIsVulnerableToFire = true;

		bRequiresColdResistance = true;
		MinColdDamage = 5;
		MaxColdDamage = 15;

		bHasChargeAbility = true;
		MinChargeAbilityPower = 100;
		MaxChargeAbilityPower = 150;
		ChargeAbilityChance = 41;
		ChargeCastTime = 7;
		bOnlyUseChargeAbilityOnce = true;
	}
	else if (NewEnemyType == EnemyType::CemeteryFireSkeletonBoss)
	{
		MaxHP = 1100;
		Attack = 15;
		Accuracy = 22;
		Defence = 16;
		EnemyName = "Cemetery Fire Skeleton Boss";

		bIsVulnerableToCold = true;

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 20;
		MagicAttackChance = 4; // 1/4 = 25%

		bHasChargeAbility = true;
		MinChargeAbilityPower = 100;
		MaxChargeAbilityPower = 150;
		ChargeAbilityChance = 41;
		ChargeCastTime = 7;
		bOnlyUseChargeAbilityOnce = true;
	}
	// Factory
	else if (NewEnemyType == EnemyType::RobotArcher)
	{
		MaxHP = 275;
		Attack = 60;
		Accuracy = 22;
		Defence = 53;
		EnemyName = "Robot Archer";
	}
	else if (NewEnemyType == EnemyType::RobotMage)
	{
		MaxHP = 350;
		Attack = 0;
		Accuracy = 0;
		Defence = 26;
		EnemyName = "Robot Mage";

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 7;
		MagicAttackChance = 1; // 1/1 = 100%

		bHasChargeAbility = true;
		MinChargeAbilityPower = 80;
		MaxChargeAbilityPower = 100;
		ChargeAbilityChance = 1;
		ChargeCastTime = 3;
		bChargeUsesThreshold = true;
		ChargeThreshold = 280;
		bOnlyUseChargeAbilityOnce = true;
	}
	else if (NewEnemyType == EnemyType::RobotWheelie)
	{
		MaxHP = 750;
		Attack = 20;
		Accuracy = 22;
		Defence = 0;
		EnemyName = "Robot Wheelie";
	}
	// Haunted Woods
	else if (NewEnemyType == EnemyType::CuriousGhostBoss)
	{
		MaxHP = 1250;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Curious Ghost";
		bIsGhost = true;
	}
	else if (NewEnemyType == EnemyType::GhostPack)
	{
		MaxHP = 1500;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Ghost Pack";
		bIsGhost = true;

		bHasMagicAttack = true;
		MinMagicDamage = 0;
		MaxMagicDamage = 10;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	else if (NewEnemyType == EnemyType::SkeletonGhost2)
	{
		MaxHP = 750;
		Attack = 60;
		Accuracy = 22;
		Defence = 60;
		EnemyName = "Skeleton Ghost 2";
		bIsGhost = true;

		bHasEvadeChance = true;
		EvadeChance = 10;
		EnchantedEvadeChance = 10;
	}
	else if (NewEnemyType == EnemyType::Reaper2)
	{
		MaxHP = 1000;
		Attack = 60;
		Accuracy = 22;
		Defence = 60;
		EnemyName = "Reaper 2";
		bIsGhost = true;
	}
	// Deep Ocean
	else if (NewEnemyType == EnemyType::PoisonSquid)
	{
		MaxHP = 1000;
		Attack = 0;
		Accuracy = 0;
		Defence = 0;
		EnemyName = "Poison Squid";

		bIsVulnerableToThunder = true;
		bRequiresOxygenTank = true;
		bHasFireResistance = true;

		bHasMagicAttack = true;
		MinMagicDamage = 20;
		MaxMagicDamage = 20;
		MagicAttackChance = 1; // 1/1 = 100%
	}
	else if (NewEnemyType == EnemyType::TridentSoldier)
	{
		MaxHP = 750;
		Attack = 50;
		Accuracy = 22;
		Defence = 40;
		EnemyName = "Trident Soldier";

		bIsVulnerableToThunder = true;
		bRequiresOxygenTank = true;
		bHasFireResistance = true;
	}
	else if (NewEnemyType == EnemyType::Piranhas)
	{
		MaxHP = 850;
		Attack = 5;
		Accuracy = 23;
		Defence = 6;
		EnemyName = "Piranhas";

		bIsVulnerableToThunder = true;
		bRequiresOxygenTank = true;
		bHasFireResistance = true;

		bHasSwarmAttack = true;
		SwarmSize = 6;
		SwarmDamage = 1;
	}
	else
	{
		LBE_ERROR("Enemy set to a type without type information");
		return false;
	}
	
	return true;
}
