#pragma once

struct CombatStats
{
public:
	int TotalPoisonDamageDone = 0;
	int TotalWeaponDamageDone = 0;
	int TotalHPPotionsUsed = 0;
	int TotalSuperHPPotionsUsed = 0;
	int TotalDamageReflected = 0;
	int TotalFireDamageDone = 0;
	int TotalIceDamageDone = 0;
	int TotalThunderDamageDone = 0;
	int TotalTimesEvadedAttacks = 0;
	int TotalTimesNotEvadedAttacks = 0;
	int TotalWeaponAttacksMade = 0;
	int TotalHealingFromLifesteal = 0;
	int TotalTimesLifestealHealed = 0;
	int TotalArrowsUsed = 0;

	int TotalDamageReceived = 0;
	int TotalEnemyEvadeableAttacksMade = 0;
	int TotalTimesEnemyEvadedAttacks = 0;

	bool BestGearSaved = false;
	int PlayerMaxHp = 0;
	int BestAttack = 0;
	int BestAccuracy = 0;
	int BestDefence = 0;

	bool EnemyStatsSaved = false;
	int EnemyMaxHP = 0;
	int EnemyAttack = 0;
	int EnemyAccuracy = 0;
	int EnemyDefence = 0;

	int TotalCombatTicks = 0;
	int NumWins = 0;
	int NumIterations = 0;

	CombatStats& operator +=(const std::shared_ptr<CombatStats>& rhs)
	{
		TotalPoisonDamageDone += rhs->TotalPoisonDamageDone;
		TotalWeaponDamageDone += rhs->TotalWeaponDamageDone;
		TotalHPPotionsUsed += rhs->TotalHPPotionsUsed;
		TotalSuperHPPotionsUsed += rhs->TotalSuperHPPotionsUsed;
		TotalDamageReflected += rhs->TotalDamageReflected;
		TotalFireDamageDone += rhs->TotalFireDamageDone;
		TotalIceDamageDone += rhs->TotalIceDamageDone;
		TotalThunderDamageDone += rhs->TotalThunderDamageDone;
		TotalTimesEvadedAttacks += rhs->TotalTimesEvadedAttacks;
		TotalTimesNotEvadedAttacks += rhs->TotalTimesNotEvadedAttacks;
		TotalWeaponAttacksMade += rhs->TotalWeaponAttacksMade;
		TotalHealingFromLifesteal += rhs->TotalHealingFromLifesteal;
		TotalTimesLifestealHealed += rhs->TotalTimesLifestealHealed;
		TotalArrowsUsed += rhs->TotalArrowsUsed;

		TotalDamageReceived += rhs->TotalDamageReceived;
		TotalEnemyEvadeableAttacksMade += rhs->TotalEnemyEvadeableAttacksMade;
		TotalTimesEnemyEvadedAttacks += rhs->TotalTimesEnemyEvadedAttacks;

		BestGearSaved = rhs->BestGearSaved;
		PlayerMaxHp = rhs->PlayerMaxHp;
		BestAttack = rhs->BestAttack;
		BestAccuracy = rhs->BestAccuracy;
		BestDefence = rhs->BestDefence;

		EnemyMaxHP = rhs->EnemyMaxHP;
		EnemyAttack = rhs->EnemyAttack;
		EnemyAccuracy = rhs->EnemyAccuracy;
		EnemyDefence = rhs->EnemyDefence;

		TotalCombatTicks += rhs->TotalCombatTicks;
		NumWins += rhs->NumWins;
		NumIterations += rhs->NumIterations;
		return *this;
	}

	void Reset()
	{
		TotalPoisonDamageDone = 0;
		TotalWeaponDamageDone = 0;
		TotalHPPotionsUsed = 0;
		TotalSuperHPPotionsUsed = 0;
		TotalDamageReflected = 0;
		TotalFireDamageDone = 0;
		TotalIceDamageDone = 0;
		TotalThunderDamageDone = 0;
		TotalTimesEvadedAttacks = 0;
		TotalTimesNotEvadedAttacks = 0;
		TotalWeaponAttacksMade = 0;
		TotalHealingFromLifesteal = 0;
		TotalTimesLifestealHealed = 0;
		TotalArrowsUsed = 0;

		TotalDamageReceived = 0;
		TotalEnemyEvadeableAttacksMade = 0;
		TotalTimesEnemyEvadedAttacks = 0;

		BestGearSaved = false;
		PlayerMaxHp = 0;
		BestAttack = 0;
		BestAccuracy = 0;
		BestDefence = 0;

		EnemyStatsSaved = false;
		EnemyMaxHP = 0;
		EnemyAttack = 0;
		EnemyAccuracy = 0;
		EnemyDefence = 0;

		TotalCombatTicks = 0;
		NumWins = 0;
		NumIterations = 0;
	}
};