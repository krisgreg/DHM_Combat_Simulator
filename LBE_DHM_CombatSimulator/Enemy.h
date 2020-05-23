#pragma once
#include "Unit.h"

#include <vector>

#include "Enums.h"

class Player;

class Enemy : public Unit
{
private:
	EnemyType TypeOfEnemy;
	Player* player;

	// Timed Escape
	int TurnsUntilEscape = 99;
	bool bShouldEscapeNow = false;
	// Infection
	bool bCanInfect = false;
	int InfectThreshold = 0;
	// Wound
	bool bHasWoundEffect = false;
	int WoundDamage = 0;
	// Swarm Attack
	bool bHasSwarmAttack = false;
	int SwarmSize = 6;
	int SwarmDamage = 1;
	// Auto Attack Charge
	bool bHasAutoAttackCharge = false;
	int AttacksNeededToCharge = 4;
	int CurrentAttacksMadeTowardsCharge = 0;
	int AutoAttackChargeMinDamage = 30;
	int AutoAttackChargeMaxDamage = 40;
	// Sandstorm
	bool bHasSandstormThreshold = false;
	int SandstormThreshold = 0;
	// Environmental Effects
	bool bRequiresColdResistance = false;
	int MinColdDamage = 1;
	int MaxColdDamage = 4;
	bool bRequiresOxygenTank = false;
	int MinDrowningDamage = 5;
	int MaxDrowningDamage = 15;
	// Magic Attack
	bool bHasMagicAttack = false;
	int MinMagicDamage = 0;
	int MaxMagicDamage = 3;
	int MagicAttackChance = 1;
	// Heal
	bool bHasHealAbility = false;
	int MinAbilityHeal = 1;
	int MaxAbilityHeal = 5;
	int HealAbilityChance = 3;
	// Charge Ability
	bool bHasChargeAbility = false;
	bool bChargeDoesHealingInsteadOfDamage = false;
	int MinChargeAbilityPower = 30;
	int MaxChargeAbilityPower = 40;
	int ChargeAbilityChance = 1;
	int ChargeCastTime = 7;
	bool bChargeUsesThreshold = false;
	int ChargeThreshold = 0;
	bool bOnlyUseChargeAbilityOnce = false;
	bool bHasUsedChargeAbility = false;
	bool bIsCurrentlyCharging = false;
	int CurrentChargeTimer = 0;
	// Robot Wheelie
	bool bIsRobotWheelieEnraged = false;
	int RobotWheelieCooldown = 0;
	// Multiple Enemies in one fight
	std::vector<EnemyType> AllEnemiesToKill;

public:
	Enemy(Player* player);
	~Enemy();

	void SetType(EnemyType NewEnemyType);
	EnemyType GetType();

	void Tick();
	void ResetStats();
	bool IsDead();
	bool IsSkeleton();
	bool ShouldEscapeNow();
	bool IsNextAttackCharge();
	bool HasChargeAttack();
	bool DoesChargeAbilityHeal();
	bool HasUsedChargeAttack();
	bool OnlyUsesOneChargeAttack();
	bool IsEnraged();
	bool RequiresOxygen();
	bool RequiresColdResistance();
	double GetExpectedWeaponDamage(int Attack, DamageType TypeOfDamage, int Accuracy = 0, int NumHits = 1, bool bPlayerHasSpikeDamage = false, bool bPlayerHasDoubleGhostDamage = false);
	bool WillAttackWithBlockableAttackNextTick();
	bool WillAttackNextTick();
	void AddEnemyToKill(EnemyType NewEnemyToKill);
	EnemyType GetNewEnemyToKill();
	int GetRemainingEnemiesToKill();
	void ResetEnemiesToKillVector();
	void SaveStats();
};

