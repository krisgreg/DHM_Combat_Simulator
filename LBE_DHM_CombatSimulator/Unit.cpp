#include "Unit.h"

#include <random>

#include "Resources.h"
#include "HitStruct.h"


Unit::Unit()
{
}


Unit::~Unit()
{
}

HitStruct Unit::RecieveHit(int AttackerAttack, DamageType TypeOfDamage, int AttackerAccuracy, int AttackerNumHits)
{
	if (TypeOfDamage == DamageType::Melee || 
		TypeOfDamage == DamageType::Ranged || 
		TypeOfDamage == DamageType::RangedFire || 
		TypeOfDamage == DamageType::RangedIce ||
		TypeOfDamage == DamageType::NonReflectableMagic ||
		TypeOfDamage == DamageType::Fire ||
		TypeOfDamage == DamageType::Ice ||
		TypeOfDamage == DamageType::Thunder ||
		TypeOfDamage == DamageType::IgnoreGhostDefence)
	{
		if (bHasSandstormCover)
		{
			return HitStruct{ false, 0, HitType::NoHit };
		}
	}

	if (TypeOfDamage == DamageType::Ice)
	{
		if (!bHasColdResistance)
		{
			if (bIsVulnerableToCold)
			{
				TakeDamage(AttackerAttack * 2, TypeOfDamage);
				return HitStruct{ true, AttackerAttack * 2, HitType::Hit };
			}
			else
			{
				TakeDamage(AttackerAttack, TypeOfDamage);
				return HitStruct{ true, AttackerAttack, HitType::Hit };
			}
		}
		else
		{
			return HitStruct{ false, 0, HitType::NoHit };
		}
	}

	if (TypeOfDamage == DamageType::Drowning)
	{
		if (!bHasOxygenTank)
		{
			TakeDamage(AttackerAttack, TypeOfDamage);
			return HitStruct{ true, AttackerAttack, HitType::Hit };
		}
		else
		{
			return HitStruct{ false, 0, HitType::NoHit };
		}
	}

	if (TypeOfDamage == DamageType::Melee || 
		TypeOfDamage == DamageType::Ranged || 
		TypeOfDamage == DamageType::RangedFire || 
		TypeOfDamage == DamageType::RangedIce || 
		TypeOfDamage == DamageType::Magic || 
		TypeOfDamage == DamageType::NonReflectableMagic)
	{
		if (bHasEvadeChance)
		{
			if (TypeOfUnit == UnitType::Type_Enemy)
			{
				Stats->TotalEnemyEvadeableAttacksMade += 1;
			}

			if (bGuaranteeNextEvade)
			{
				if (TypeOfUnit == UnitType::Type_Player)
				{
					Stats->TotalTimesEvadedAttacks += 1;
				}
				else
				{
					Stats->TotalTimesEnemyEvadedAttacks += 1;
				}

				bGuaranteeNextEvade = false;
				return HitStruct{ false, 0, HitType::Evade };
			}
			else if ((rand() % 100) < EvadeChance && NumTurnsStunned == 0)
			{
				if (TypeOfUnit == UnitType::Type_Player)
				{
					Stats->TotalTimesEvadedAttacks += 1;
				}
				else
				{
					Stats->TotalTimesEnemyEvadedAttacks += 1;
				}

				if (EnchantedEvadeChance > 0 && rand() % EvadeChance < EnchantedEvadeChance)
				{
					bGuaranteeNextEvade = true;
				}
				return HitStruct{ false, 0, HitType::Evade };
			}
		}

		if (TypeOfUnit == UnitType::Type_Player)
		{
			Stats->TotalTimesNotEvadedAttacks += 1;
		}
	}

	if (TypeOfDamage == DamageType::Fire || 
		TypeOfDamage == DamageType::Thunder || 
		TypeOfDamage == DamageType::Magic || 
		TypeOfDamage == DamageType::Poison || 
		TypeOfDamage == DamageType::Reflected || 
		TypeOfDamage == DamageType::Spike || 
		TypeOfDamage == DamageType::Retaliated || 
		TypeOfDamage == DamageType::NonReflectableMagic || 
		TypeOfDamage == DamageType::NonEvadableMagic)
	{
		if (TypeOfDamage == DamageType::Fire && bHasFireResistance)
		{
			return HitStruct{ false, 0, HitType::NoHit };
		}
		if (TypeOfDamage == DamageType::Thunder && bHasThunderResistance)
		{
			return HitStruct{ false, 0, HitType::NoHit };
		}

		if ((TypeOfDamage == DamageType::Fire && bIsVulnerableToFire) || (TypeOfDamage == DamageType::Thunder && bIsVulnerableToThunder))
		{
			TakeDamage(AttackerAttack * 2, TypeOfDamage);
			return HitStruct{ true, AttackerAttack * 2, HitType::Hit };
		}
		else
		{
			TakeDamage(AttackerAttack, TypeOfDamage);
			return HitStruct{ true, AttackerAttack, HitType::Hit };
		}
	}

	if (bIsImmuneToRanged && (TypeOfDamage == DamageType::Ranged || TypeOfDamage == DamageType::RangedFire || TypeOfDamage == DamageType::RangedIce))
	{
		return HitStruct{ false, 0, HitType::NoHit };
	}
	else if (bIsImmuneToMelee && (TypeOfDamage == DamageType::Melee || TypeOfDamage == DamageType::IgnoreGhostDefence))
	{
		return HitStruct{ false, 0, HitType::NoHit };
	}

	int Damage = 0;
	for (int i = 0; i < AttackerNumHits; i++)
	{
		if ((TypeOfDamage == DamageType::RangedFire && bIsVulnerableToFire) ||
			(TypeOfDamage == DamageType::RangedIce && bIsVulnerableToCold))
		{
			Damage += rand() % ((AttackerAttack * 2) + 1);
		}
		else
		{
			Damage += rand() % (AttackerAttack + 1);
		}

		if (TypeOfUnit == UnitType::Type_Enemy)
		{
			if (TypeOfDamage == DamageType::Ranged ||
				TypeOfDamage == DamageType::RangedFire ||
				TypeOfDamage == DamageType::Ice)
			{
				Stats->TotalArrowsUsed += 1;
			}
		}
	}

	int Difference; 
	if (Defence % 2 == 1 && rand() % 2 == 0)
	{
		Difference = (int)((float)(Defence + 1) / 2.f) - AttackerAccuracy;
	}
	else
	{
		Difference = (int)((float)Defence / 2.f) - AttackerAccuracy;
	}

	if (Difference <= 0 || (bIsGhost && TypeOfDamage == DamageType::IgnoreGhostDefence))
	{
		TakeDamage(Damage, TypeOfDamage);
	}
	else if (rand() % (Difference + 1) == 0)
	{
		TakeDamage(Damage, TypeOfDamage);
	}
	else
	{
		return HitStruct{ false, 0, HitType::NoHit };
	}

	if (bCanRetaliateDamage)
	{
		if ((RetaliateDamageType == WeaponType::Any) ||
			(RetaliateDamageType == WeaponType::Melee && (TypeOfDamage == DamageType::Melee || TypeOfDamage == DamageType::IgnoreGhostDefence)) ||
			(RetaliateDamageType == WeaponType::Ranged && (TypeOfDamage == DamageType::Ranged || TypeOfDamage == DamageType::RangedFire || TypeOfDamage == DamageType::RangedIce)))
		{
			DamageToRetaliate += RetaliateDamage;
		}
	}

	return HitStruct{ true, Damage, HitType::Hit };
}

void Unit::TakeDamage(int Damage, DamageType TypeOfDamage)
{
	if (bIsReflectActive && !(TypeOfDamage == DamageType::Poison || TypeOfDamage == DamageType::NonReflectableMagic))
	{
		if (TypeOfUnit == UnitType::Type_Player && Resources::ReflectSpellLevel >= 2 && Damage == 0)
		{
			// Reflect did not proc because of upgraded reflect
		}
		else
		{
			DamageToReflect += Damage;
			bIsReflectActive = false;
		}
	}
	else
	{
		if (bIsImmuneToMagic && (TypeOfDamage == DamageType::Magic || TypeOfDamage == DamageType::Fire || TypeOfDamage == DamageType::Thunder || TypeOfDamage == DamageType::Ice || TypeOfDamage == DamageType::NonReflectableMagic || TypeOfDamage == DamageType::NonEvadableMagic))
		{
			return;
		}

		

		CurrentHP -= Damage;
		if (CurrentHP < 0)
		{
			CurrentHP = 0;
		}
		if (TypeOfUnit == UnitType::Type_Player)
		{
			Stats->TotalDamageReceived += Damage;
		}
		else
		{
			if (TypeOfDamage == DamageType::Melee)						{ Stats->TotalWeaponDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::Ranged)				{ Stats->TotalWeaponDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::RangedFire)			{ Stats->TotalWeaponDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::RangedIce)				{ Stats->TotalWeaponDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::Magic)					{ }
			else if (TypeOfDamage == DamageType::NonReflectableMagic)	{ }
			else if (TypeOfDamage == DamageType::NonEvadableMagic)		{ }
			else if (TypeOfDamage == DamageType::Fire)					{ Stats->TotalFireDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::Ice)					{ Stats->TotalIceDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::Thunder)				{ Stats->TotalThunderDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::Poison)				{ Stats->TotalPoisonDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::Reflected)				{ Stats->TotalDamageReflected += Damage; }
			else if (TypeOfDamage == DamageType::Spike)					{ Stats->TotalWeaponDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::IgnoreGhostDefence)	{ Stats->TotalWeaponDamageDone += Damage; }
			else if (TypeOfDamage == DamageType::Drowning)				{ }
			else if (TypeOfDamage == DamageType::Retaliated)			{ }
		}
	}
}

void Unit::ApplyPoison(int Damage)
{
	if (PoisonDamage < Damage)
	{
		PoisonDamage = Damage;
	}

	if (!bIsPoisoned)
	{
		PoisonDamage = Damage;
		bIsPoisoned = true;
	}
}

void Unit::Infect()
{
	bHasInfectedDebuff = true;
}

void Unit::Stun(int NumTurns, StunType TypeOfStun)
{
	if (bIsImmuneToMagic && TypeOfStun == StunType::Thunder)
	{
		return;
	}

	if (TypeOfStun == StunType::Thunder && bIsVulnerableToThunder)
	{
		NumTurnsStunned = NumTurns * 2;
	}
	else
	{
		NumTurnsStunned = NumTurns;
	}
}

int Unit::GetAttack()
{
	return Attack;
}

int Unit::GetAccuracy()
{
	return Accuracy;
}

int Unit::GetDefence()
{
	return Defence;
}

int Unit::GetMaxHP()
{
	return MaxHP;
}

int Unit::GetCurrentHP()
{
	return CurrentHP;
}

bool Unit::IsGhost()
{
	return bIsGhost;
}

bool Unit::IsImmuneToMelee()
{
	return bIsImmuneToMelee;
}

bool Unit::IsImmuneToRanged()
{
	return bIsImmuneToRanged;
}

bool Unit::IsImmuneToMagic()
{
	return bIsImmuneToMagic;
}

int Unit::GetNumTurnsStunned()
{
	return NumTurnsStunned;
}

bool Unit::CanRetaliate()
{
	return bCanRetaliateDamage;
}

WeaponType Unit::GetRetaliationType()
{
	return RetaliateDamageType;
}

bool Unit::IsPoisoned()
{
	return bIsPoisoned;
}

void Unit::LinkStatsStruct(std::shared_ptr<CombatStats> NewStatsStruct)
{
	Stats = NewStatsStruct;
	NewStatsStruct->BestAccuracy = 998;
	Stats->BestAccuracy = 999;
}
