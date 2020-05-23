#pragma once
#include "Unit.h"

class Enemy;

class Player : public Unit
{
private:
	// spells
	int FireCooldown = 0;
	int ReflectCooldown = 0;
	int ThunderCooldown = 0;
	int LifestealCooldown = 0;
	int LifestealDuration = 0;
	int SandstormCooldown = 0;

	// potions
	bool bHasUsedHPPotion = false;
	bool bHasUsedFreezePotion = false;
	bool bHasUsedAccuracyPotion = false;
	bool bHasUsedSuperHPPotion = false;

	// equipment
	bool bHasLightbulbEquipped = false;
	int LightbulbCharge = 0;
	bool bCanSeeGhosts = false;
	bool bIsAccuracyPotionActive = false;
	bool bIsUsingPoisonWeapon = false;
	int WeaponPoisonDamage = 1;
	bool bHasDoubleGhostDamage = false;
	DamageType WeaponDamageType = DamageType::Melee;
	bool bNeedsDefenceNextTurn = true;

	int BestWeaponID = -1;
	int BestWeaponAverageDamage = -1;
	int BestMeleeWeaponID = -1;
	int BestMeleeWeaponAverageDamage = -1;
	int BestRangedWeaponID = -1;
	int BestRangedWeaponAverageDamage = -1;

	bool bHasUsedDeathGracePeriod = false;

	Enemy* CurrentEnemy;
public:
	Player();
	~Player();

	void Init(int HP);
	void SetEnemy(Enemy* NewEnemy);
	void Tick();
	bool Simulate(); // true = victory

	void EquipBestGear(WeaponType TypeOfWeapon = WeaponType::Any);
	void EquipBestPoisonWeapon();
	void EquipBestWeapon(WeaponType TypeOfWeapon = WeaponType::Any);
	bool EquipWeaponSet(int WeaponSet);
	void EquipBestArmor();
	bool EquipBestOxygenTank();
	void CastThunder();
	void CastReflect();
	void CastFire();
	void CastLifesteal();
	void CastSandstorm();
};

