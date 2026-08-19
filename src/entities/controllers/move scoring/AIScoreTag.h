#pragma once

enum class AIScoreTag
{
	HighCritRatio,
	OHKO,
	PriorityDamage,
	TargetUsedMinimize,
	RecoilOnHit,
	Gust,
	Earthquake,
	AlwaysHit,
	ChargeMove,
	SkyAttack, 
	RechargeMove,
	Leech,
	DreamEater,
	SelfFaintingDamage,
	SuperFang,
	Healing,
	Rest,
	Sleep,
	Paralyze,
	Poison,
	Toxic,
	Confuse,
	Disable,
	Seed,
	ForceSwitch,
	SelfAttackBoost,
	SelfDefenseBoost,
	SelfSpeedBoost,
	//SelfSpABoost, // unused for now
	SelfSpDBoost,
	//SelfAccuracyBoost, // unused for now
	SelfEvasionBoost,
	Growth,
	TargetAttackDecrease,
	TargetDefenseDecrease,
	TargetSpeedDecrease,
	//TargetSpecialAttackDecrease, // unused for now
	//TargetSpecialDefenseDecrease, // unused for now
	TargetAccuracyDecrease,
	//TargetEvasionDecrease, // unused for now
	FocusEnergy,
	Splash,
	Mist,
	LightScreen,
	Reflect,
	Haze,
	Mimic,
	Metronome,
	MirrorMove,
	Transform,
	Conversion,
	Substitute,
	Other
};