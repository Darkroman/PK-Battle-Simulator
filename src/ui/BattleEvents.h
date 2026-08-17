#pragma once

#include <array>
#include <string_view>
#include <variant>

#include "EffectivenessText.h"
#include "../entities/BattlePokemon.h"

enum class BattleEvents;

struct QueuedBattleEvent
{
	BattleEvents event;
	using UIArg = std::variant<std::monostate, std::string_view, unsigned int, int, EffectivenessText, Status>;
	std::array<UIArg, 4> args{};
};

enum class BattleEvents
{
	//// --- MOVERESULTS --- ////
	// Basic Move Results
	Noop,
	UsedMove,
	CriticalHit,
	Effectiveness,
	AttackMissed,
	AttackAvoided,
	Failed,
	SubstituteDamage,
	DirectDamage,

	// Effectiveness
	NotVery,
	Super,
	No,
	OHKO,

	// Specialized Results
	MultiHit,
	EnemySwitch,
	BoundMove,
	Splash,
	NoMovesLeftStruggle,

	// Partial Trap
	Bind,
	Wrap,
	FireSpin,
	Clamp,
	BoundNotFound,

	// Charging
	RazorWindCharge,
	FlyCharge,
	SolarBeamCharge,
	DigCharge,
	SkullBashCharge,
	SkyAttackCharge,

	// Recoil
	JumpKickCrash,
	Recoil,

	// HP Results
	EnergyDrained,
	RestoredHP,
	HPFull,
	Rest,

	// Status
	BurnSuccess,
	FreezeSuccess,
	ParalyzeSuccess,
	PoisonSuccess,
	BadlyPoisonSuccess,
	SleepSuccess,
	BecameConfused,
	AlreadyPoisoned,
	AlreadyParalyzed,
	AlreadyAsleep,
	StatusImmune,

	// Stat Stage
	StatRaised2,
	StatRaised1,
	StatRaiseFail,
	StatLowered2,
	StatLowered1,
	StatLoweredFail,

	// Volatile Statuses
	FocusEnergy,
	Mist,
	ProtectedByMist,
	Seeded,
	LightScreen,
	Haze,
	Reflect,

	// Substitute
	AlreadyHasSubstitute,
	NotEnoughHPSubstitute,
	PutInSubstitute,

	// Copy
	LearnedMimicMove,
	Transform,
	Metronome,
	Conversion,

	// Bide
	BideUnleashed,
	BideStoringEnergy,

	// Disabled
	RampageDisabled,
	MoveDisabled,
	BideDisabled,

	// Switching
	SwitchOutNoFaint,
	SwitchOut,
	PlayerChooses,

	//// --- STATUS EFFECT RESULTS --- ////
	// Status Changes
	FellAsleep,
	WokenUp,
	IsAsleep,
	FrozenSolid,
	Thawed,
	NoLongerConfused,
	IsConfused,
	HurtItselfConfusion,
	CantMoveParalysis,
	Flinch,
	Recharge,

	// Barriers / field effects
	NoLongerProtectedMist,
	FieldEffectFaded,

	// Post-turn effects
	LeechSeedSapped,
	DamagedByStatusPostTurn,
	HurtByBound,
	FreedFromBound,

	// Rampage
	RampageConfusion,

	// Rage
	RageStarted,
	//StatRaised1,
	//StatRaiseFail,

	// Disable
	MoveIsDisabled,
	MoveNoLongerDisabled,

	// Substitute
	SubstituteFaded,

	// Faint
	Fainted,

	// New line
	NewLine,

	// Pause (for switch prompts)
	Pause
};