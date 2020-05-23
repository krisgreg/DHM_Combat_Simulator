#include "Enemy.h"

#include "Log.h"
#include "Player.h"
#include "Resources.h"
#include "Enemies.h"

Enemy::Enemy(Player* player) : player(player)
{
	TypeOfUnit = UnitType::Type_Enemy;
}

Enemy::~Enemy()
{
}

void Enemy::SetType(EnemyType NewEnemyType)
{
	TypeOfEnemy = NewEnemyType;
	ResetStats();
}

EnemyType Enemy::GetType()
{
	return TypeOfEnemy;
}

void Enemy::Tick()
{
	if (NumTurnsStunned > 0)
	{
		NumTurnsStunned -= 1;
	}

	if (SandstormDuration > 0)
	{
		SandstormDuration -= 1;
		if (SandstormDuration == 0)
		{
			bHasSandstormCover = false;
			bHasLightningstormCover = false;
		}
	}
	if (bHasSandstormThreshold && CurrentHP <= SandstormThreshold)
	{
		SandstormDuration = 1;
		bHasSandstormCover = true;
	}

	if (bCanInfect && CurrentHP <= InfectThreshold && NumTurnsStunned == 0)
	{
		player->Infect();
	}

	if (TypeOfEnemy == EnemyType::CuriousGhostBoss && NumTurnsStunned == 0)
	{
		TurnsUntilEscape -= 1;
		if (TurnsUntilEscape == 0)
		{
			bShouldEscapeNow = true;
		}
	}
	else if (TypeOfEnemy == EnemyType::CastleMage)
	{
		if (CurrentHP <= 600)
		{
			if (bIsImmuneToMelee && bIsImmuneToRanged)
			{
				bIsImmuneToMelee = true;
			}
			else if (NumTurnsStunned == 0 && rand() % 8 == 0)
			{
				if (bIsImmuneToMelee)
				{
					bIsImmuneToMelee = false;
					bIsImmuneToRanged = true;
				}
				else
				{
					bIsImmuneToMelee = true;
					bIsImmuneToRanged = false;
				}
			}
		}
	}
	else if (TypeOfEnemy == EnemyType::RobotWheelie)
	{
		if (RobotWheelieCooldown > 0)
		{
			RobotWheelieCooldown--;
		}

		if (bIsRobotWheelieEnraged && NumTurnsStunned > 0)
		{
			bIsRobotWheelieEnraged = false;
			RobotWheelieCooldown = 10;
		}

		if (bIsRobotWheelieEnraged)
		{
			int MagicDamage = (rand() % 11) + 10;
			player->RecieveHit(MagicDamage, DamageType::Magic);
		}

		if (!bIsRobotWheelieEnraged && RobotWheelieCooldown == 0 && NumTurnsStunned == 0 && rand() % 16 == 0)
		{
			bIsRobotWheelieEnraged = true;
		}

		if (bIsRobotWheelieEnraged && rand() % 4 == 0)
		{
			bIsRobotWheelieEnraged = false;
			RobotWheelieCooldown = 10;
		}
	}
	else if (TypeOfEnemy == EnemyType::GhostPack)
	{
		if (CurrentHP >= 1125 && player->GetNumTurnsStunned() == 0 && NumTurnsStunned == 0 && rand() % 16 == 0)
		{
			player->Stun(5, StunType::Freeze);
		}

		if (CurrentHP >= 375 && NumTurnsStunned == 0 && rand() % 6 == 0)
		{
			CurrentHP += (rand() % 11) + 10;
			if (CurrentHP > MaxHP)
			{
				CurrentHP = MaxHP;
			}
		}
	}

	if (bIsPoisoned)
	{
		TurnsUntilPoisonTick -= 1;
		if (TurnsUntilPoisonTick == 0)
		{
			RecieveHit(PoisonDamage, DamageType::Poison);
			TurnsUntilPoisonTick = 10;
		}
	}

	if (CurrentAttackCooldown > 0 && NumTurnsStunned == 0)
	{
		if (bHasInfectedDebuff)
		{
			if (rand() % 2 == 0)
			{
				CurrentAttackCooldown -= 1;
			}
		}
		else
		{
			CurrentAttackCooldown -= 1;
		}
	}

	if (bHasAutoAttackCharge && CurrentAttacksMadeTowardsCharge >= AttacksNeededToCharge)
	{
		CurrentAttacksMadeTowardsCharge = 0;
		int MagicDamage = (rand() % (AutoAttackChargeMaxDamage - AutoAttackChargeMinDamage + 1)) + AutoAttackChargeMinDamage;
		player->RecieveHit(MagicDamage, DamageType::Magic);
	}

	if (bIsCurrentlyCharging && NumTurnsStunned == 0)
	{
		CurrentChargeTimer -= 1;
	}

	if (bHasChargeAbility && NumTurnsStunned == 0)
	{
		if (!bIsCurrentlyCharging && ((!bChargeUsesThreshold) || (bChargeUsesThreshold && CurrentHP <= ChargeThreshold)) && !(bOnlyUseChargeAbilityOnce && bHasUsedChargeAbility) && rand() % ChargeAbilityChance == 0)
		{
			bIsCurrentlyCharging = true;
			CurrentChargeTimer = ChargeCastTime;
		}
		else if (bIsCurrentlyCharging && CurrentChargeTimer == 0 && CurrentAttackCooldown == 0)
		{
			if (bChargeDoesHealingInsteadOfDamage)
			{
				int Heal = (rand() % (MaxChargeAbilityPower - MinChargeAbilityPower + 1)) + MinChargeAbilityPower;
				CurrentHP += Heal;
				if (CurrentHP > MaxHP)
				{
					CurrentHP = MaxHP;
				}
			}
			else
			{
				int MagicDamage = (rand() % (MaxChargeAbilityPower - MinChargeAbilityPower + 1)) + MinChargeAbilityPower;
				player->RecieveHit(MagicDamage, DamageType::NonEvadableMagic);
			}

			if (TypeOfEnemy == EnemyType::RobotMage)
			{
				bIsImmuneToMelee = true;
				bIsImmuneToMagic = true;
			}
			bIsCurrentlyCharging = false;
			bHasUsedChargeAbility = true;
		}
	}

	if (CurrentAttackCooldown == 0 && !bIsCurrentlyCharging && NumTurnsStunned == 0)
	{
		if (bHasWoundEffect)
		{
			player->RecieveHit(WoundDamage, DamageType::Poison);
		}

		if (bHasHealAbility && CurrentHP != 0 && rand() % HealAbilityChance == 0)
		{
			int Heal = (rand() % (MaxAbilityHeal - MinAbilityHeal + 1)) + MinAbilityHeal;
			CurrentHP += Heal;
			if (CurrentHP > MaxHP)
			{
				CurrentHP = MaxHP;
			}
		}

		HitStruct EnemyHit;
		if (bHasMagicAttack && rand() % MagicAttackChance == 0)
		{
			int MagicDamage = (rand() % (MaxMagicDamage - MinMagicDamage + 1)) + MinMagicDamage;
			DamageType MagicAttackType = DamageType::Magic;
			if (TypeOfEnemy == EnemyType::GhostPack && CurrentHP >= 750)
			{
				MagicDamage += rand() % 6;
			}
			if (TypeOfEnemy == EnemyType::PoisonSquid || TypeOfEnemy == EnemyType::BloodSquid)
			{
				MagicAttackType = DamageType::NonReflectableMagic;
			}
			EnemyHit = player->RecieveHit(MagicDamage, MagicAttackType);
		}
		else if (bHasSwarmAttack)
		{
			for (int i = 0; i < SwarmSize; i++)
			{
				EnemyHit = player->RecieveHit(SwarmDamage, DamageType::Melee, Accuracy, NumHits);
				if (bHasAutoAttackCharge && (EnemyHit.TypeOfHit == HitType::Hit || EnemyHit.TypeOfHit == HitType::NoHit))
				{
					CurrentAttacksMadeTowardsCharge += 1;
				}
			}
		}
		else
		{
			EnemyHit = player->RecieveHit(Attack, DamageType::Melee, Accuracy, NumHits);
		}

		if (bHasAutoAttackCharge && !bHasSwarmAttack && (EnemyHit.TypeOfHit == HitType::Hit || EnemyHit.TypeOfHit == HitType::NoHit))
		{
			CurrentAttacksMadeTowardsCharge += 1;
		}

		CurrentAttackCooldown = WeaponAttackCooldown;
	}

	if (bRequiresColdResistance)
	{
		if (rand() % 2 == 0)
		{
			int ColdDamage = (rand() % (MaxColdDamage - MinColdDamage + 1)) + MinColdDamage;
			player->RecieveHit(ColdDamage, DamageType::Ice);
		}
	}

	if (bRequiresOxygenTank)
	{
		if (rand() % 2 == 0)
		{
			int DrowningDamage = (rand() % (MaxDrowningDamage - MinDrowningDamage + 1)) + MinDrowningDamage;
			player->RecieveHit(DrowningDamage, DamageType::Drowning);
		}
	}

	if (DamageToReflect > 0)
	{
		player->RecieveHit(DamageToReflect, DamageType::Reflected);
		DamageToReflect = 0;
	}

	if (DamageToRetaliate > 0)
	{
		player->RecieveHit(DamageToRetaliate, DamageType::Retaliated);
		DamageToRetaliate = 0;
	}
}

void Enemy::ResetStats()
{
	// Base Stats
	MaxHP = Enemies::GetMaxHP();
	Attack = Enemies::GetAttack();
	Accuracy = Enemies::GetAccuracy();
	Defence = Enemies::GetDefence();
	WeaponAttackCooldown = Enemies::GetWeaponAttackCooldown();
	// Type
	bIsSkeleton = Enemies::IsSkeleton();
	bIsGhost = Enemies::IsGhost();
	// Cold Resistance
	bRequiresColdResistance = Enemies::RequiresColdResistance();
	MinColdDamage = Enemies::GetMinColdDamage();
	MaxColdDamage = Enemies::GetMaxColdDamage();
	// Oxygen
	bRequiresOxygenTank = Enemies::RequiresOxygenTank();
	MinDrowningDamage = Enemies::GetMinDrowningDamage();
	MaxDrowningDamage = Enemies::GetMaxDrowningDamage();
	// Vulnerabilities
	bIsVulnerableToCold = Enemies::IsVulnerableToCold();
	bIsVulnerableToFire = Enemies::IsVulnerableToFire();
	bIsVulnerableToThunder = Enemies::IsVulnerableToThunder();
	// Evade
	bHasEvadeChance = Enemies::HasEvadeChance();
	EvadeChance = Enemies::GetEvadeChance();
	EnchantedEvadeChance = Enemies::GetEnchantedEvadeChance();
	// Retaliate
	bCanRetaliateDamage = Enemies::CanRetaliateDamage();
	RetaliateDamageType = Enemies::GetRetaliateDamageType();
	RetaliateDamage = Enemies::GetRetaliateDamage();
	// Infect
	bCanInfect = Enemies::CanInfect();
	InfectThreshold = Enemies::GetInfectThreshold();
	// Wound
	bHasWoundEffect = Enemies::HasWoundEffect();
	WoundDamage = Enemies::GetWoundDamage();
	// Swarm Attack
	bHasSwarmAttack = Enemies::HasSwarmAttack();
	SwarmSize = Enemies::GetSwarmSize();
	SwarmDamage = Enemies::GetSwarmDamage();
	// Auto Attack Charge
	bHasAutoAttackCharge = Enemies::HasAutoAttackCharge();
	AttacksNeededToCharge = Enemies::GetAttacksNeededToCharge();
	AutoAttackChargeMinDamage = Enemies::GetAutoAttackChargeMinDamage();
	AutoAttackChargeMaxDamage = Enemies::GetAutoAttackChargeMaxDamage();
	// Multi-hit
	NumHits = Enemies::GetNumHits();
	// Immunities
	bHasColdResistance = Enemies::HasColdResistance();
	bHasFireResistance = Enemies::HasFireResistance();
	bHasThunderResistance = Enemies::HasThunderResistance();
	// Magic Attack
	bHasMagicAttack	= Enemies::HasMagicAttack();
	MinMagicDamage = Enemies::GetMinMagicDamage();
	MaxMagicDamage = Enemies::GetMaxMagicDamage();
	MagicAttackChance = Enemies::GetMagicAttackChance();
	// Heal
	bHasHealAbility = Enemies::HasHealAbility();
	MinAbilityHeal = Enemies::GetMinAbilityHeal();
	MaxAbilityHeal = Enemies::GetMaxAbilityHeal();
	HealAbilityChance = Enemies::GetHealAbilityChance();
	// Charge Attack
	bHasChargeAbility = Enemies::HasChargeAbility();
	bChargeDoesHealingInsteadOfDamage = Enemies::ChargeDoesHealingInsteadOfDamage();
	MinChargeAbilityPower = Enemies::GetMinChargeAbilityPower();
	MaxChargeAbilityPower = Enemies::GetMaxChargeAbilityPower();
	ChargeAbilityChance = Enemies::GetChargeAbilityChance();
	ChargeCastTime = Enemies::GetChargeCastTime();
	bChargeUsesThreshold = Enemies::ChargeUsesThreshold();
	ChargeThreshold = Enemies::GetChargeThreshold();
	bOnlyUseChargeAbilityOnce = Enemies::OnlyUseChargeAbilityOnce();
	// Sandstorm
	bHasSandstormThreshold = Enemies::HasSandstormThreshold();
	SandstormThreshold = Enemies::GetSandstormThreshold();

	// Base Stats
	CurrentHP = MaxHP;
	CurrentAttackCooldown = WeaponAttackCooldown;
	// Reflect
	bIsReflectActive = false;
	DamageToReflect = 0;
	// Poison
	bHasPoisonActive = false;
	bIsPoisoned = false;
	PoisonDamage = 1;
	TurnsUntilPoisonTick = 2;
	// Weapon Effects
	bHasSpikeDamage = false;
	// Charge Attack
	bIsCurrentlyCharging = false;
	CurrentChargeTimer = 0;
	bHasUsedChargeAbility = false;
	// Retaliate
	DamageToRetaliate = 0;
	// Infect
	bHasInfectedDebuff = false;
	// Timed Escape
	TurnsUntilEscape = 99;
	bShouldEscapeNow = false;
	// Stun
	NumTurnsStunned = 0;
	// Immunities
	bIsImmuneToMelee = false;
	bIsImmuneToRanged = false;
	bIsImmuneToMagic = false;
	// Robot Wheelie
	bIsRobotWheelieEnraged = false;
	RobotWheelieCooldown = 0;
	// Evade
	bGuaranteeNextEvade = false;
	// Sandstorm
	bHasSandstormCover = false;
	bHasLightningstormCover = false;
	SandstormDuration = 0;
}

bool Enemy::IsDead()
{
	if (CurrentHP <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::IsSkeleton()
{
	return bIsSkeleton;
}

bool Enemy::ShouldEscapeNow()
{
	return bShouldEscapeNow;
}

bool Enemy::IsNextAttackCharge()
{
	if (bHasChargeAbility && !(bHasUsedChargeAbility && bOnlyUseChargeAbilityOnce))
	{
		if (bIsCurrentlyCharging)
		{
			return true;
		}
	}
	else if (bHasAutoAttackCharge)
	{
		if (CurrentAttacksMadeTowardsCharge >= AttacksNeededToCharge)
		{
			return true;
		}
	}

	return false;
}

bool Enemy::HasChargeAttack()
{
	if (bHasChargeAbility || bHasAutoAttackCharge)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::DoesChargeAbilityHeal()
{
	return bChargeDoesHealingInsteadOfDamage;
}

bool Enemy::HasUsedChargeAttack()
{
	return bHasUsedChargeAbility;
}

bool Enemy::OnlyUsesOneChargeAttack()
{
	return bOnlyUseChargeAbilityOnce;
}

bool Enemy::IsEnraged()
{
	return bIsRobotWheelieEnraged;
}

bool Enemy::RequiresOxygen()
{
	return bRequiresOxygenTank;
}

bool Enemy::RequiresColdResistance()
{
	return bRequiresColdResistance;
}

double Enemy::GetExpectedWeaponDamage(int Attack, DamageType TypeOfDamage, int Accuracy, int NumHits, bool bPlayerHasSpikeDamage, bool bPlayerHasDoubleGhostDamage)
{
	int AttackStrength = Attack;
	if ((TypeOfDamage == DamageType::RangedFire && bIsVulnerableToFire) ||
		(TypeOfDamage == DamageType::RangedIce && bIsVulnerableToCold))
	{
		AttackStrength *= 2;
	}
	if (bIsGhost && bPlayerHasDoubleGhostDamage)
	{
		AttackStrength *= 2;
	}

	int DefenceStrength = Defence;
	if (TypeOfDamage == DamageType::IgnoreGhostDefence && bIsGhost)
	{
		DefenceStrength = 0;
	}

	double HitChance;
	if (DefenceStrength % 2 == 1)
	{
		int DefMinusAccHigh = ((DefenceStrength + 1) / 2) - Accuracy;
		if (DefMinusAccHigh < 0)
		{
			DefMinusAccHigh = 0;
		}
		double HitChanceHigh = 1.f / ((double)DefMinusAccHigh + 1.f);

		int DefMinusAccLow = ((DefenceStrength - 1) / 2) - Accuracy;
		if (DefMinusAccLow < 0)
		{
			DefMinusAccLow = 0;
		}
		double HitChanceLow = 1.f / ((double)DefMinusAccLow + 1.f);

		HitChance = HitChanceHigh * 0.5f + HitChanceLow * 0.5f;
	}
	else
	{
		int DefMinusAcc = (DefenceStrength / 2) - Accuracy;
		if (DefMinusAcc < 0)
		{
			DefMinusAcc = 0;
		}
		HitChance = 1.f / ((double)DefMinusAcc + 1.f);
	}

	double ExpectedDamage = (double)AttackStrength * NumHits * HitChance;
	if (bPlayerHasSpikeDamage)
	{
		ExpectedDamage += 2.f * HitChance;
	}
	//LBE_TRACE("Hit Chance: {0:03.2f}, Expected Damage: {1:03.2f}", HitChance, ExpectedDamage);
	return ExpectedDamage;
}

bool Enemy::WillAttackWithBlockableAttackNextTick()
{
	if (NumTurnsStunned > 1)
	{
		// if enemy is stunned
		return false;
	}
	else if (bHasMagicAttack && MagicAttackChance == 1)
	{
		// if enemy only uses magic attacks
		return false;
	}
	else if (bIsCurrentlyCharging && (CurrentChargeTimer > 1 || NumTurnsStunned > 1))
	{
		// if enemy is charging but does not finish the charge next tick
		return false;
	}
	else if (CurrentAttackCooldown > 1)
	{
		// will not auto attack next tick
		return false;
	}

	return true;
}

bool Enemy::WillAttackNextTick()
{
	if (NumTurnsStunned > 1)
	{
		// if enemy is stunned
		return false;
	}

	if (bIsCurrentlyCharging && CurrentChargeTimer == 1)
	{
		return true;
	}
	else if (CurrentAttackCooldown == 1)
	{
		return true;
	}

	return false;
}

void Enemy::AddEnemyToKill(EnemyType NewEnemyToKill)
{
	AllEnemiesToKill.push_back(NewEnemyToKill);
}

EnemyType Enemy::GetNewEnemyToKill()
{
	int randomIndex = rand() % AllEnemiesToKill.size();
	EnemyType SelectedEnemyType = AllEnemiesToKill[randomIndex];
	auto iter = AllEnemiesToKill.begin();
	while (*iter != SelectedEnemyType) iter++;
	AllEnemiesToKill.erase(iter);
	return SelectedEnemyType;
}

int Enemy::GetRemainingEnemiesToKill()
{
	return AllEnemiesToKill.size();
}

void Enemy::ResetEnemiesToKillVector()
{
	AllEnemiesToKill.clear();
}

void Enemy::SaveStats()
{
	Stats->EnemyMaxHP = MaxHP;
	Stats->EnemyAttack = Attack;
	Stats->EnemyAccuracy = Accuracy;
	Stats->EnemyDefence = Defence;
	Stats->EnemyStatsSaved = true;
}
