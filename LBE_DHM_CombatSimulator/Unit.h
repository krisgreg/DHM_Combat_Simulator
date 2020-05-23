#pragma once
#include <memory>

#include "Enums.h"
#include "HitStruct.h"
#include "CombatStatsStruct.h"

class Unit
{
protected:
	std::shared_ptr<CombatStats> Stats;
	UnitType TypeOfUnit;

	// Base Stats
	int MaxHP = 10;
	int CurrentHP = 10;
	int Attack = 0;
	int Accuracy = 0;
	int Defence = 0;
	int WeaponAttackCooldown = 3;
	// Counters
	int CurrentAttackCooldown = WeaponAttackCooldown;
	int NumTurnsStunned = 0;
	// Reflect
	bool bIsReflectActive = false;
	int DamageToReflect = 0;
	// Poison
	bool bHasPoisonActive = false;
	bool bIsPoisoned = false;
	int TurnsUntilPoisonTick = 2;
	int PoisonDamage = 1;
	// Gear Effects
	int bHasSpikeDamage = false;
	bool bHasOxygenTank = false;
	// Evade
	bool bHasEvadeChance = false;
	int EvadeChance = 0;
	int EnchantedEvadeChance = 0;
	bool bGuaranteeNextEvade = false;
	// Type
	bool bIsSkeleton = false;
	bool bIsGhost = false;
	// Infect
	bool bHasInfectedDebuff = false;
	// Vulnerabilities
	bool bIsVulnerableToFire = false;
	bool bIsVulnerableToCold = false;
	bool bIsVulnerableToThunder = false;
	// Immunities
	bool bIsImmuneToMelee = false;
	bool bIsImmuneToRanged = false;
	bool bIsImmuneToMagic = false;
	bool bHasColdResistance = false;
	bool bHasFireResistance = false;
	bool bHasThunderResistance = false;
	// Retaliate
	bool bCanRetaliateDamage = false;
	WeaponType RetaliateDamageType = WeaponType::Melee;
	int RetaliateDamage = 0;
	int DamageToRetaliate = 0;
	// Multi-hit
	int NumHits = 1;
	// Sandstorm
	bool bHasSandstormCover = false;
	bool bHasLightningstormCover = false;
	int SandstormDuration = 0;

public:
	Unit();
	~Unit();

	HitStruct RecieveHit(int AttackerAttack, DamageType TypeOfDamage, int AttackerAccuracy = 0, int AttackerNumHits = 1);
	void TakeDamage(int Damage, DamageType TypeOfDamage);
	void ApplyPoison(int Damage);
	void Infect();
	void Stun(int NumTurns, StunType TypeOfStun);

	int GetAttack();
	int GetAccuracy();
	int GetDefence();
	int GetMaxHP();
	int GetCurrentHP();
	bool IsGhost();
	bool IsImmuneToMelee();
	bool IsImmuneToRanged();
	bool IsImmuneToMagic();
	int GetNumTurnsStunned();
	bool CanRetaliate();
	WeaponType GetRetaliationType();
	bool IsPoisoned();

	virtual void Tick() = 0;
	void LinkStatsStruct(std::shared_ptr<CombatStats> NewStatsStruct);
};

