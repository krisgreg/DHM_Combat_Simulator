#pragma once

namespace lbe
{
	enum Orientation
	{
		Horizontal,
		Vertical
	};

	enum ButtonState
	{
		Deselected,
		Selected,
		Clicked
	};

	enum Layer
	{
		Background,
		Collision,
		Object,
		Meta
	};

	enum NetworkState
	{
		Host,
		Client
	};
}

enum class Spell
{
	Fire,
	Reflect,
	Thunder,
	Lifesteal
};

enum class Potion
{
	HP,
	Freeze,
	Accuracy,
	GhostScan,
	SuperHP,
	Strength
};

enum class EnemyType
{
	// Custom
	Custom,
	// Fields
	Chicken,
	Rat,
	Bee,
	BloodChicken,
	BloodRat,
	BloodBee,
	TripleChicken,
	TripleBloodChicken,
	// Forest
	Snake,
	Ent,
	Thief,
	BloodSnake,
	BloodEnt,
	BloodThief,
	// Caves
	Bear,
	Bat,
	Skeleton,
	BloodBear,
	BloodBat,
	BloodSkeleton,
	// Volcano
	LavaSnake,
	FireHawk,
	FireMage,
	BloodLavaSnake,
	BloodFireHawk,
	BloodFireMage,
	TripleFireHawk,
	TripleBloodFireHawk,
	// Northern Fields
	IceHawk,
	FrozenEnt,
	Golem,
	BloodIceHawk,
	BloodFrozenEnt,
	BloodGolem,
	TripleIceHawk,
	TripleBloodIceHawk,
	// Haunted Mansion
	Ghost,
	SkeletonGhost,
	Reaper,
	BloodGhost,
	BloodSkeletonGhost,
	BloodReaper,
	// Desert
	DesertLizardBoss,
	DesertLizard2,
	Scorpion,
	Lizard,
	BloodDesertLizardBoss,
	BloodDesertLizard2,
	BloodScorpion,
	BloodLizard,
	// Ocean
	Squid,
	PufferFish,
	Shark,
	BloodSquid,
	BloodPufferFish,
	BloodShark,
	// Jungle
	Tribe,
	Elephant,
	Gorilla,
	BloodJunglePack,
	// Dungeon Entrance
	SkeletonMageBoss1,
	SkeletonMageBoss2,
	SkeletonMageBoss3,
	SkeletonMageBoss4,
	PoisonTribe,
	Statue,
	Gargoyle,
	// Dungeon
	SkeletonMonks,
	DarkMage,
	SkeletonPrisoner,
	// Coffin
	SkeletonKing,
	// Castle
	CastleKnight,
	Dragon,
	CastleMage,
	// Cemetery
	Angel,
	Zombie,
	BabySkeleton,
	CemeterySkeletonBoss,
	CemeteryIceSkeletonBoss,
	CemeteryFireSkeletonBoss,
	// Factory
	RobotArcher,
	RobotMage,
	RobotWheelie,
	// Haunted Woods
	CuriousGhostBoss,
	GhostPack,
	SkeletonGhost2,
	Reaper2,
	// Deep Ocean
	PoisonSquid,
	TridentSoldier,
	Piranhas
};

enum class UnitType
{
	Type_Player,
	Type_Enemy
};

enum class DamageType
{
	Melee,
	Ranged,
	RangedFire,
	RangedIce,
	Magic,
	NonReflectableMagic,
	NonEvadableMagic,
	Fire,
	Ice,
	Thunder,
	Poison,
	Reflected,
	Spike,
	IgnoreGhostDefence,
	Drowning,
	Retaliated
};

enum class StunType
{
	Thunder,
	Freeze
};

enum class WeaponType
{
	Any,
	Melee,
	Ranged
};

enum class HitType
{
	Hit,
	NoHit,
	Evade
};