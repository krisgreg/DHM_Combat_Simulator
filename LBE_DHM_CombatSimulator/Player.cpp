#include "Player.h"

#include <random>

#include "Log.h"
#include "Enemy.h"
#include "Resources.h"
#include "Consts.h"
#include "Enemies.h"

Player::Player()
{
	TypeOfUnit = UnitType::Type_Player;
}


Player::~Player()
{
}

void Player::Init(int HP)
{
	MaxHP = HP;
	CurrentHP = MaxHP;
	Attack = 0;
	Accuracy = 0;
	Defence = 0;
	WeaponAttackCooldown = 3;

	CurrentAttackCooldown = WeaponAttackCooldown;
	FireCooldown = 0;
	ReflectCooldown = 0;
	ThunderCooldown = 0;
	LifestealCooldown = 0;
	LifestealDuration = 0;
	SandstormCooldown = 0;
	SandstormDuration = 0;

	bHasUsedHPPotion = false;
	bHasUsedFreezePotion = false;
	bHasUsedAccuracyPotion = false;
	bHasUsedSuperHPPotion = false;

	bIsReflectActive = false;
	DamageToReflect = 0;
	bHasPoisonActive = false;
	bIsPoisoned = false;
	TurnsUntilPoisonTick = 2;
	PoisonDamage = 1;
	bHasSpikeDamage = false;
	DamageToRetaliate = 0;
	bHasInfectedDebuff = false;

	bHasLightbulbEquipped = false;
	bCanSeeGhosts = false;
	bHasEvadeChance = false;
	bIsAccuracyPotionActive = false;
	bIsUsingPoisonWeapon = false;
	bHasDoubleGhostDamage = false;
	bGuaranteeNextEvade = false;
	bNeedsDefenceNextTurn = true;

	bHasColdResistance = false;
	bHasFireResistance = false;
	bHasThunderResistance = false;

	bHasSandstormCover = false;
	bHasLightningstormCover = false;
	SandstormDuration = 0;

	bHasUsedDeathGracePeriod = false;

	BestWeaponID = -1;
	BestWeaponAverageDamage = 0;
	BestMeleeWeaponID = -1;
	BestMeleeWeaponAverageDamage = 0;
	BestRangedWeaponID = -1;
	BestRangedWeaponAverageDamage = 0;
}

void Player::SetEnemy(Enemy* NewEnemy)
{
	CurrentEnemy = NewEnemy;
}

void Player::Tick()
{
	if (FireCooldown > 0)
	{
		FireCooldown -= 1;
	}
	if (ReflectCooldown > 0)
	{
		ReflectCooldown -= 1;
	}
	if (ThunderCooldown > 0)
	{
		ThunderCooldown -= 1;
	}
	if (LifestealCooldown > 0)
	{
		LifestealCooldown -= 1;
	}
	if (CurrentAttackCooldown > 0)
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
	if (SandstormDuration > 0)
	{
		SandstormDuration -= 1;
		if (SandstormDuration == 0)
		{
			bHasSandstormCover = false;
			bHasLightningstormCover = false;
		}
		else if (bHasLightningstormCover)
		{
			int ThunderDamage = (rand() % 6) + 10;
			if (Resources::bHasReaperRobes)
			{
				ThunderDamage *= 3;
			}
			else if (Resources::bHasMageRobes)
			{
				ThunderDamage *= 2;
			}
			CurrentEnemy->RecieveHit(ThunderDamage, DamageType::Thunder);
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

	if (bHasLightbulbEquipped)
	{
		if (LightbulbCharge >= 10)
		{
			CurrentEnemy->RecieveHit((rand() % 6) + 10, DamageType::Thunder);
			LightbulbCharge = 0;
		}
		else
		{
			LightbulbCharge++;
		}
	}

	if (CurrentAttackCooldown == 0)
	{
		if ((CurrentEnemy->IsGhost() && bCanSeeGhosts) || (!CurrentEnemy->IsGhost()))
		{
			HitStruct EnemyHit;
			if (CurrentEnemy->IsGhost() && bHasDoubleGhostDamage)
			{
				EnemyHit = CurrentEnemy->RecieveHit(Attack * 2, WeaponDamageType, INT_MAX, NumHits);
			}
			else if (bIsAccuracyPotionActive)
			{
				EnemyHit = CurrentEnemy->RecieveHit(Attack, WeaponDamageType, INT_MAX, NumHits);
				bIsAccuracyPotionActive = false;
			}
			else
			{
				EnemyHit = CurrentEnemy->RecieveHit(Attack, WeaponDamageType, Accuracy, NumHits);
			}

			if (bHasSpikeDamage && EnemyHit.bHit)
			{
				int SpikeDamage = (rand() % 3) + 1;
				CurrentEnemy->RecieveHit(SpikeDamage, DamageType::Spike);
			}

			if (bIsUsingPoisonWeapon && EnemyHit.bHit)
			{
				if (Resources::bHasPoisonDamageResearch)
				{
					CurrentEnemy->ApplyPoison(WeaponPoisonDamage + 4);
				}
				else
				{
					CurrentEnemy->ApplyPoison(WeaponPoisonDamage);
				}
			}

			if (LifestealDuration > 0 && EnemyHit.bHit && EnemyHit.Damage > 0 && (WeaponDamageType == DamageType::Melee || WeaponDamageType == DamageType::IgnoreGhostDefence))
			{
				LifestealDuration--;
				CurrentHP += EnemyHit.Damage;
				Stats->TotalHealingFromLifesteal += EnemyHit.Damage;
				if (CurrentHP > MaxHP)
				{
					Stats->TotalHealingFromLifesteal -= (CurrentHP - MaxHP);
					CurrentHP = MaxHP;
				}
				Stats->TotalTimesLifestealHealed += 1;
			}
		}
		CurrentAttackCooldown = WeaponAttackCooldown;
		Stats->TotalWeaponAttacksMade += 1;
	}

	if (DamageToReflect > 0)
	{
		CurrentEnemy->RecieveHit(DamageToReflect, DamageType::Reflected);
		DamageToReflect = 0;
	}
}

bool Player::Simulate()
{
	CurrentEnemy->ResetEnemiesToKillVector();
	if (CurrentEnemy->GetType() == EnemyType::BloodReaper)
	{
		CurrentEnemy->AddEnemyToKill(EnemyType::BloodReaper);
		CurrentEnemy->AddEnemyToKill(EnemyType::BloodGhost);
		CurrentEnemy->AddEnemyToKill(EnemyType::BloodSkeletonGhost);

		EnemyType NextEnemy = CurrentEnemy->GetNewEnemyToKill();
		Enemies::SetCurrentEnemyType(NextEnemy);
		CurrentEnemy->ResetStats();
	}

	CurrentEnemy->SaveStats();

	while (true)
	{
		Stats->TotalCombatTicks += 1;
		bNeedsDefenceNextTurn = true;
		EquipBestGear();
		if (Resources::ThunderSpellLevel > 0 && ThunderCooldown == 0)
		{
			if (CurrentEnemy->GetType() == EnemyType::RobotWheelie)
			{
				if (CurrentEnemy->IsEnraged() && CurrentEnemy->GetNumTurnsStunned() == 0)
				{
					CastThunder();
				}
			}
			else if (CurrentEnemy->GetType() == EnemyType::RobotMage)
			{
				if (CurrentEnemy->IsNextAttackCharge())
				{
					CastThunder();
				}
				else if (CurrentEnemy->HasUsedChargeAttack())
				{
					CastThunder();
				}
			}
			else if (CurrentEnemy->GetType() == EnemyType::BloodReaper)
			{
				if (CurrentEnemy->GetRemainingEnemiesToKill() == 0)
				{
					CastThunder();
				}
				else if (CurrentEnemy->GetCurrentHP() > 150)
				{
					CastThunder();
				}
			}
			else if (CurrentEnemy->DoesChargeAbilityHeal())
			{
				if (CurrentEnemy->IsNextAttackCharge())
				{
					CastThunder();
				}
			}
			else
			{
				CastThunder();
			}
		}
		if (Resources::ReflectSpellLevel > 0 && ReflectCooldown == 0 && !bIsReflectActive)
		{
			if (CurrentEnemy->IsNextAttackCharge())
			{
				CastReflect();
			}
			else if (!CurrentEnemy->HasChargeAttack())
			{
				CastReflect();
			}
		}
		if (Resources::FireSpellLevel > 0 && FireCooldown == 0)
		{
			CastFire();
		}
		if (Resources::bHasFreezePotion && !bHasUsedFreezePotion && CurrentEnemy->GetNumTurnsStunned() <= 1)
		{
			if (CurrentEnemy->GetType() == EnemyType::RobotWheelie)
			{
				if (CurrentEnemy->IsEnraged() && CurrentEnemy->GetNumTurnsStunned() == 0)
				{
					CurrentEnemy->Stun(5, StunType::Freeze);
					bHasUsedFreezePotion = true;
				}
			}
			else if (CurrentEnemy->GetType() == EnemyType::RobotMage)
			{
				if (CurrentEnemy->IsNextAttackCharge() && CurrentEnemy->GetNumTurnsStunned() == 0)
				{
					CurrentEnemy->Stun(5, StunType::Freeze);
					bHasUsedFreezePotion = true;
				}
			}
			else if (CurrentEnemy->DoesChargeAbilityHeal())
			{
				if (CurrentEnemy->IsNextAttackCharge())
				{
					CurrentEnemy->Stun(5, StunType::Freeze);
					bHasUsedFreezePotion = true;
				}
			}
			else
			{
				CurrentEnemy->Stun(5, StunType::Freeze);
				bHasUsedFreezePotion = true;
			}
		}
		if (Resources::bHasAccuracyPotion && !bHasUsedAccuracyPotion)
		{
			if (CurrentEnemy->GetType() == EnemyType::BloodReaper)
			{
				if (Enemies::GetCurrentEnemyType() == EnemyType::BloodReaper)
				{
					bIsAccuracyPotionActive = true;
					bHasUsedAccuracyPotion = true;
				}
			}
			else
			{
				bIsAccuracyPotionActive = true;
				bHasUsedAccuracyPotion = true;
			}
		}
		if (Resources::SandstormSpellLevel > 0 && SandstormCooldown == 0)
		{
			if (CurrentEnemy->GetNumTurnsStunned() == 0 && !bIsReflectActive && CurrentEnemy->WillAttackNextTick())
			{
				CastSandstorm();
			}
		}

		if (CurrentEnemy->GetType() == EnemyType::BloodReaper)
		{
			if (CurrentHP <= 15 && LifestealCooldown == 0)
			{
				CastLifesteal();
			}
		}
		else
		{
			if (CurrentHP <= CurrentEnemy->GetAttack() && LifestealCooldown == 0)
			{
				CastLifesteal();
			}
		}

		if (!CurrentEnemy->WillAttackWithBlockableAttackNextTick())
		{
			bNeedsDefenceNextTurn = false;
			EquipBestGear();
		}

		if (LifestealDuration > 0)
		{
			EquipBestGear(WeaponType::Melee);
		}

		if (CurrentEnemy->CanRetaliate())
		{
			if (CurrentEnemy->GetRetaliationType() == WeaponType::Melee)
			{
				EquipBestGear(WeaponType::Ranged);
			}
			else if (CurrentEnemy->GetRetaliationType() == WeaponType::Ranged)
			{
				EquipBestGear(WeaponType::Melee);
			}
		}

		if (CurrentEnemy->IsImmuneToMelee())
		{
			EquipBestGear(WeaponType::Ranged);
		}
		else if (CurrentEnemy->IsImmuneToRanged())
		{
			EquipBestGear(WeaponType::Melee);
		}

		if (!CurrentEnemy->IsPoisoned() && bIsAccuracyPotionActive)
		{
			EquipBestPoisonWeapon();
		}
		else if (!CurrentEnemy->IsPoisoned() && CurrentEnemy->GetDefence() == 0)
		{
			EquipBestPoisonWeapon();
		}

		if (bIsReflectActive && Resources::ReflectSpellLevel == 1)
		{
			Defence = 0;
		}

		if (bHasUsedDeathGracePeriod)
		{
			if (Resources::bHasHPPotion && !bHasUsedHPPotion)
			{
				CurrentHP += 5;
				bHasUsedHPPotion = true;
				bHasUsedDeathGracePeriod = false;
				Stats->TotalHPPotionsUsed += 1;
			}
			else if (Resources::bHasSuperHPPotion && !bHasUsedSuperHPPotion)
			{
				CurrentHP += 25;
				bHasUsedSuperHPPotion = true;
				bHasUsedDeathGracePeriod = false;
				Stats->TotalSuperHPPotionsUsed += 1;
			}
		}

		Tick();
		if (CurrentEnemy->IsDead())
		{
			if (CurrentEnemy->GetRemainingEnemiesToKill() > 0)
			{
				EnemyType NextEnemy = CurrentEnemy->GetNewEnemyToKill();
				Enemies::SetCurrentEnemyType(NextEnemy);
				CurrentEnemy->ResetStats();

				BestWeaponID = -1;
				BestWeaponAverageDamage = -1;
				BestMeleeWeaponID = -1;
				BestMeleeWeaponAverageDamage = -1;
				BestRangedWeaponID = -1;
				BestRangedWeaponAverageDamage = -1;
			}
			else
			{
				return true;
			}
		}
		CurrentEnemy->Tick();
		if (CurrentEnemy->ShouldEscapeNow())
		{
			return false;
		}
		if (CurrentHP <= 0)
		{
			if (bHasUsedDeathGracePeriod)
			{
				return false;
			}
			else
			{
				bHasUsedDeathGracePeriod = true;
			}
		}
		else
		{
			bHasUsedDeathGracePeriod = false;
		}
	}
}

void Player::EquipBestGear(WeaponType TypeOfWeapon)
{
	Attack = 0;
	Defence = 0;
	Accuracy = 0;

	// Weapon
	EquipBestWeapon(TypeOfWeapon);
	// Armor (rest of the gear)
	EquipBestArmor();

	if (!Stats->BestGearSaved)
	{
		Stats->PlayerMaxHp = MaxHP;
		Stats->BestAttack = Attack;
		Stats->BestAccuracy = Accuracy;
		Stats->BestDefence = Defence;
		Stats->BestGearSaved = true;
	}
}

void Player::EquipBestPoisonWeapon()
{
	bHasSpikeDamage = false;
	bHasDoubleGhostDamage = false;
	WeaponPoisonDamage = 1;
	bIsUsingPoisonWeapon = true;
	WeaponDamageType = DamageType::Melee;

	bool bCanPoisonMelee = true;
	bool bCanPoisonRanged = true;

	if ((CurrentEnemy->CanRetaliate() && CurrentEnemy->GetRetaliationType() == WeaponType::Melee)  || CurrentEnemy->IsImmuneToMelee())	{ bCanPoisonMelee = false; }
	if ((CurrentEnemy->CanRetaliate() && CurrentEnemy->GetRetaliationType() == WeaponType::Ranged) || CurrentEnemy->IsImmuneToRanged())	{ bCanPoisonRanged = false; }

	if (Resources::bHasPoisonTridentPlus && bCanPoisonMelee)									{ Attack = 18; Accuracy = 12; WeaponPoisonDamage = 16; }
	else if (Resources::bHasSuperBow && Resources::bHasPoisonArrowsPlus && bCanPoisonRanged)	{ Attack = 17; Accuracy = 10; WeaponPoisonDamage = 16; WeaponDamageType = DamageType::Ranged; }
	else if (Resources::bHasBow && Resources::bHasPoisonArrowsPlus && bCanPoisonRanged)			{ Attack = 17; Accuracy = 7;  WeaponPoisonDamage = 16; WeaponDamageType = DamageType::Ranged; }
	else if (Resources::bHasPoisonSpearPlus && bCanPoisonMelee)									{ Attack = 5;  Accuracy = 5;  WeaponPoisonDamage = 16; }
	else if (Resources::bHasSuperBow && Resources::bHasPoisonArrows && bCanPoisonRanged)		{ Attack = 12; Accuracy = 10; WeaponDamageType = DamageType::Ranged; }
	else if (Resources::bHasBow && Resources::bHasPoisonArrows && bCanPoisonRanged)				{ Attack = 12; Accuracy = 7;  WeaponDamageType = DamageType::Ranged; }
	else if (Resources::bHasPoisonSpear && bCanPoisonMelee)										{ Attack = 3;  Accuracy = 5; }
	else 
	{
		bIsUsingPoisonWeapon = false;
		EquipBestWeapon();
	}

	if (Resources::BerserkerAmuletLevel > 0) { Attack += Resources::BerserkerAmuletLevel; }
	if (Resources::BerserkerRingLevel > 0)	 { Attack += Resources::BerserkerRingLevel; }

	if (Resources::bHasStrengthPotion) { Attack = (int)(Attack * 1.25f); Accuracy = (int)(Accuracy * 1.25f); }
}

void Player::EquipBestWeapon(WeaponType TypeOfWeapon)
{
	if (BestWeaponID == -1)
	{
		for (int ID = 0; ID < lbe::NUM_WEAPON_SETS; ID++)
		{
			Defence = 0;

			EquipWeaponSet(ID);
			EquipBestArmor();

			double ExpectedDamage = CurrentEnemy->GetExpectedWeaponDamage(Attack, WeaponDamageType, Accuracy, NumHits, bHasSpikeDamage, bHasDoubleGhostDamage);
			if (WeaponDamageType == DamageType::Melee || WeaponDamageType == DamageType::IgnoreGhostDefence)
			{
				if (ExpectedDamage > BestMeleeWeaponAverageDamage)
				{
					BestMeleeWeaponAverageDamage = ExpectedDamage;
					BestMeleeWeaponID = ID;
				}
			}
			else // ranged damage
			{
				if (ExpectedDamage > BestRangedWeaponAverageDamage)
				{
					BestRangedWeaponAverageDamage = ExpectedDamage;
					BestRangedWeaponID = ID;
				}
			}
		}
		if (BestMeleeWeaponAverageDamage >= BestRangedWeaponAverageDamage)
		{
			BestWeaponAverageDamage = BestMeleeWeaponAverageDamage;
			BestWeaponID = BestMeleeWeaponID;
		}
		else
		{
			BestWeaponAverageDamage = BestRangedWeaponAverageDamage;
			BestWeaponID = BestRangedWeaponID;
		}
	}

	if (TypeOfWeapon == WeaponType::Any)
	{
		EquipWeaponSet(BestWeaponID);
	}
	else if (TypeOfWeapon == WeaponType::Melee)
	{
		EquipWeaponSet(BestMeleeWeaponID);
	}
	else if (TypeOfWeapon == WeaponType::Ranged)
	{
		EquipWeaponSet(BestRangedWeaponID);
	}
}

bool Player::EquipWeaponSet(int WeaponSet)
{
	bHasSpikeDamage = false;
	bIsUsingPoisonWeapon = false;
	bHasDoubleGhostDamage = false;
	WeaponDamageType = DamageType::Melee;
	NumHits = 1;

	if (WeaponSet == 0)																			{ Attack = 0;  Accuracy = 0; }
	else if (WeaponSet == 1  && Resources::bHasRustySword)										{ Attack = 1;  Accuracy = 1; }
	else if (WeaponSet == 2  && Resources::bHasStinger)											{ Attack = 2;  Accuracy = 1; }
	else if (WeaponSet == 3  && Resources::bHasIronDagger)										{ Attack = 3;  Accuracy = 2; }
	else if (WeaponSet == 4  && Resources::bHasSkeletonSword)									{ Attack = 5;  Accuracy = 5; }
	else if (WeaponSet == 5  && Resources::bHasBow && Resources::bHasArrows)					{ Attack = 8;  Accuracy = 7;	WeaponDamageType = DamageType::Ranged; }
	else if (WeaponSet == 6  && Resources::bHasBow && Resources::bHasFireArrows)				{ Attack = 10; Accuracy = 7;	WeaponDamageType = DamageType::RangedFire; }
	else if (WeaponSet == 7  && Resources::bHasBow && Resources::bHasIceArrows)					{ Attack = 12; Accuracy = 7;	WeaponDamageType = DamageType::RangedIce; }
	else if (WeaponSet == 8  && Resources::bHasBow && Resources::bHasArrowsPlus)				{ Attack = 17; Accuracy = 7;	WeaponDamageType = DamageType::Ranged; }
	else if (WeaponSet == 9  && Resources::bHasSuperBow && Resources::bHasArrows)				{ Attack = 8;  Accuracy = 10;	WeaponDamageType = DamageType::Ranged; }
	else if (WeaponSet == 10 && Resources::bHasSuperBow && Resources::bHasFireArrows)			{ Attack = 10; Accuracy = 10;	WeaponDamageType = DamageType::RangedFire; }
	else if (WeaponSet == 11 && Resources::bHasSuperBow && Resources::bHasIceArrows)			{ Attack = 12; Accuracy = 10;	WeaponDamageType = DamageType::RangedIce; }
	else if (WeaponSet == 12 && Resources::bHasSuperBow && Resources::bHasArrowsPlus)			{ Attack = 17; Accuracy = 10;	WeaponDamageType = DamageType::Ranged; }
	else if (WeaponSet == 13 && Resources::bHasEnchantedSuperBow && Resources::bHasArrows)		{ Attack = 8;  Accuracy = 10;	WeaponDamageType = DamageType::Ranged;		NumHits = 2; }
	else if (WeaponSet == 14 && Resources::bHasEnchantedSuperBow && Resources::bHasFireArrows)	{ Attack = 10; Accuracy = 10;	WeaponDamageType = DamageType::RangedFire;	NumHits = 2; }
	else if (WeaponSet == 15 && Resources::bHasEnchantedSuperBow && Resources::bHasIceArrows)	{ Attack = 12; Accuracy = 10;	WeaponDamageType = DamageType::RangedIce;	NumHits = 2; }
	else if (WeaponSet == 16 && Resources::bHasEnchantedSuperBow && Resources::bHasArrowsPlus)	{ Attack = 17; Accuracy = 10;	WeaponDamageType = DamageType::Ranged;		NumHits = 2; }
	else if (WeaponSet == 17 && Resources::bHasScythe)											{ Attack = 12; Accuracy = 7; 	WeaponDamageType = DamageType::IgnoreGhostDefence; }
	else if (WeaponSet == 18 && Resources::bHasMace)											{ Attack = 13; Accuracy = 9;	bHasSpikeDamage = true; }
	else if (WeaponSet == 19 && Resources::bHasTrident)											{ Attack = 18; Accuracy = 12; }
	else if (WeaponSet == 20 && Resources::bHasPoisonTridentPlus)								{ Attack = 18; Accuracy = 12;	WeaponPoisonDamage = 16; bIsUsingPoisonWeapon = true; }
	else if (WeaponSet == 21 && Resources::bHasEnchantedScythe)									{ Attack = 12; Accuracy = 7;	WeaponDamageType = DamageType::IgnoreGhostDefence; bHasDoubleGhostDamage = true; }
	else if (WeaponSet == 22 && Resources::bHasSilverScimitar)									{ Attack = 25; Accuracy = 15; }
	else
	{
		Attack = 0;
		Accuracy = 0;
		return false;
	}

	return true;
}

void Player::EquipBestArmor()
{
	// Off-hand
	if (!bNeedsDefenceNextTurn && Resources::bHasOffHandDagger) { Defence = 0; Attack += 5; }
	else if (Resources::bHasSuperJungleShield)					{ Defence = 14; }
	else if (Resources::bHasKnightsShield)						{ Defence = 10; }
	else if (Resources::bHasJungleShield)						{ Defence = 6; }
	else if (Resources::bHasSkeletonShield)						{ Defence = 3; }
	else if (Resources::bHasOffHandDagger)						{ Defence = 0; Attack += 5; }
	else														{ Defence = 0; }

	// Armor
	if (Resources::BestHeadArmor == 0)		{ }
	else if (!bNeedsDefenceNextTurn && CurrentEnemy->RequiresColdResistance() && Resources::BestHeadArmor >= 1) { Defence += 1; }
	else if (Resources::BestHeadArmor == 1) { Defence += 1; }
	else if (Resources::BestHeadArmor == 2) { Defence += 2; }
	else if (Resources::BestHeadArmor == 3) { Defence += 3; }
	else if (Resources::BestHeadArmor == 4) { Defence += 4; }
	else if (Resources::BestHeadArmor == 5) { Defence += 6; }
	else if (Resources::BestHeadArmor == 6) { Defence += 8; }
	else if (Resources::BestHeadArmor == 7) { Defence += 10; }
	else if (Resources::BestHeadArmor == 8) { Defence += 12; }
	else if (Resources::BestHeadArmor == 9) { Defence += 15; }

	if (Resources::BestBodyArmor == 0)		{ }
	else if (!bNeedsDefenceNextTurn && CurrentEnemy->RequiresColdResistance() && Resources::BestBodyArmor >= 1) { Defence += 3; }
	else if (Resources::BestBodyArmor == 1) { Defence += 3; }
	else if (Resources::BestBodyArmor == 2) { Defence += 4; }
	else if (Resources::BestBodyArmor == 3) { Defence += 5; }
	else if (Resources::BestBodyArmor == 4) { Defence += 6; }
	else if (Resources::BestBodyArmor == 5) { Defence += 8; }
	else if (Resources::BestBodyArmor == 6) { Defence += 12; }
	else if (Resources::BestBodyArmor == 7) { Defence += 14; }

	if (Resources::BestLegArmor == 0)	   { }
	else if (!bNeedsDefenceNextTurn && CurrentEnemy->RequiresColdResistance() && Resources::BestLegArmor >= 1) { Defence += 2; }
	else if (Resources::BestLegArmor == 1) { Defence += 2; }
	else if (Resources::BestLegArmor == 2) { Defence += 3; }
	else if (Resources::BestLegArmor == 3) { Defence += 4; }
	else if (Resources::BestLegArmor == 4) { Defence += 5; }
	else if (Resources::BestLegArmor == 5) { Defence += 7; }
	else if (Resources::BestLegArmor == 6) { Defence += 10; }
	else if (Resources::BestLegArmor == 7) { Defence += 12; }

	if (Resources::BestHeadArmor == 1 && Resources::BestBodyArmor == 1 && Resources::BestLegArmor == 1)
	{
		bHasColdResistance = true;
	}
	else if (!bNeedsDefenceNextTurn && CurrentEnemy->RequiresColdResistance() && Resources::BestHeadArmor >= 1 && Resources::BestBodyArmor >= 1 && Resources::BestLegArmor >= 1)
	{
		bHasColdResistance = true;
	}
	else
	{
		bHasColdResistance = false;
	}

	// Back / other
	bHasLightbulbEquipped = false;
	WeaponAttackCooldown = 3;

	if (!bNeedsDefenceNextTurn && Resources::bHasSharkFin && CurrentEnemy->RequiresOxygen())	{ Defence += 0; WeaponAttackCooldown = 1; }
	else if (!bNeedsDefenceNextTurn && Resources::bHasLightbulb)								{ Defence += 1; bHasLightbulbEquipped = true; }
	else if (Resources::bHasElephantCloak)														{ Defence += 7; }
	else if (Resources::bHasLizardCloak)														{ Defence += 5; }
	else if (Resources::bHasLavaSnakeCloak)														{ Defence += 4; }
	else if (Resources::bHasSnakeCloak)															{ Defence += 3; }
	else if (EquipBestOxygenTank())																{ }
	else if (Resources::bHasLightbulb)															{ Defence += 1; bHasLightbulbEquipped = true; }

	EvadeChance = 0;
	EnchantedEvadeChance = 0;
	// Neck
	if (Resources::bHasCompletedWitchsPotionPartTwo)
	{
		Attack += Resources::BerserkerAmuletLevel;
	}

	if (CurrentEnemy->IsGhost() && !Resources::bHasGhostScanPotion && !Resources::bHasGhostScanRing && Resources::bHasGhostScanAmulet)	{ bCanSeeGhosts = true; }
	else if (CurrentEnemy->RequiresOxygen() && !Resources::bHasOxygenRing && !bHasOxygenTank && Resources::bHasOxygenAmulet)			{ bHasOxygenTank = true; }
	else if (Resources::BerserkerAmuletLevel > 0 && !Resources::bHasCompletedWitchsPotionPartTwo)										{ Attack += Resources::BerserkerAmuletLevel; }
	else if (Resources::bHasEnchantedInvisibilityAmulet)																				{ bHasEvadeChance = true; EvadeChance += 10; EnchantedEvadeChance += 10; }
	else if (Resources::bHasInvisibilityAmulet)																							{ bHasEvadeChance = true; EvadeChance += 10; }

	// Rings
	if (Resources::BerserkerRingLevel > 0)			{ Attack += Resources::BerserkerRingLevel; }
	if (Resources::bHasEnchantedInvisibilityRing)	{ bHasEvadeChance = true; EvadeChance += 10; EnchantedEvadeChance += 10; }
	else if (Resources::bHasInvisibilityRing)		{ bHasEvadeChance = true; EvadeChance += 10; }
	if (Resources::bHasGhostScanRing)				{ bCanSeeGhosts = true; }
	if (Resources::bHasOxygenRing)					{ bHasOxygenTank = true; }

	// Potions
	if (Resources::bHasGhostScanPotion) { bCanSeeGhosts = true; }
	if (Resources::bHasStrengthPotion) { Attack = (int)(Attack * 1.25f); Accuracy = (int)(Accuracy * 1.25f); }
}

bool Player::EquipBestOxygenTank()
{
	if		(Resources::bHasAncientOxygenTank)	{ Defence += 2; bHasOxygenTank = true; }
	else if (Resources::bHasOxygenTank)			{ Defence += 1; bHasOxygenTank = true; }
	else
	{
		return false;
	}

	return true;
}

void Player::CastThunder()
{
	int ThunderDamage = (rand() % 6) + 10;
	if (Resources::bHasReaperRobes)
	{
		ThunderDamage *= 3;
	}
	else if (Resources::bHasMageRobes)
	{
		ThunderDamage *= 2;
	}
	if (Resources::bHasMageStaff)
	{
		ThunderDamage += 3;
	}
	CurrentEnemy->RecieveHit(ThunderDamage, DamageType::Thunder);

	if (Resources::ThunderSpellLevel == 2)
	{
		CurrentEnemy->Stun((int)(ThunderDamage / 2), StunType::Thunder);
	}

	if (Resources::SandstormSpellLevel >= 2)
	{
		if (SandstormCooldown == 0)
		{
			CastSandstorm();
		}
		if (bHasSandstormCover)
		{
			bHasLightningstormCover = true;
		}
	}

	ThunderCooldown = 60;
}

void Player::CastReflect()
{
	if (!CurrentEnemy->IsImmuneToMagic())
	{
		bIsReflectActive = true;
		ReflectCooldown = 30;
	}
}

void Player::CastFire()
{
	int SpellDamage = (rand() % 4);
	DamageType SpellDamageType = DamageType::Fire;
	if (Resources::bHasReaperRobes)
	{
		SpellDamage *= 3;
	}
	else if (Resources::bHasMageRobes)
	{
		SpellDamage *= 2;
	}

	if (Resources::FireSpellLevel == 2)
	{
		SpellDamage *= 2;
	}
	if (Resources::bHasMageStaff)
	{
		SpellDamage += 3;
	}
	if (Resources::bHasIceGloves)
	{
		if (rand() % 2 == 0)
		{
			SpellDamage += 6;
			SpellDamageType = DamageType::Ice;
		}
	}
	else if (Resources::bHasFireGloves)
	{
		SpellDamage += 3;
	}

	CurrentEnemy->RecieveHit(SpellDamage, SpellDamageType);
	FireCooldown = 15;
}

void Player::CastLifesteal()
{
	if (Resources::LifestealSpellLevel == 1)
	{
		LifestealDuration = 1;
	}
	else if (Resources::LifestealSpellLevel == 2)
	{
		LifestealDuration = 3;
	}
	LifestealCooldown = 60 * 5;
}

void Player::CastSandstorm()
{
	bHasSandstormCover = true;
	SandstormDuration = 10;

	SandstormCooldown = 60 * 15;
}
