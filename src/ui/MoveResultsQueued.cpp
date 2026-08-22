#include "MoveResultsQueued.h"

#include "../common/EnumUtils.h"

#include "../data/MoveID.h"

#include "BattleEvents.h"
#include "BattleEventQueue.h"
#include "EffectivenessText.h"

#include <string_view>

// Basic Move Results
MoveResultsQueued::MoveResultsQueued(BattleEventQueue& queue)
	: m_queue(queue)
{}

void MoveResultsQueued::DisplayNoopMsg() const
{
	m_queue.PushEvent({BattleEvents::Noop, {}
		});
}

void MoveResultsQueued::UsedTextDialog(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view currentMoveName) const
{
	m_queue.PushEvent({BattleEvents::UsedMove, { attackingPlayerName, attackingPokemonName, currentMoveName } });
}

void MoveResultsQueued::DisplayCritTextDialog(bool isCriticalHit) const
{
	if (isCriticalHit)
	{
		m_queue.PushEvent({BattleEvents::CriticalHit, {} });
	}
}

void MoveResultsQueued::DisplayOHKOTextDialog() const
{
	m_queue.PushEvent({ BattleEvents::OHKO, {} });
}

void MoveResultsQueued::DisplayEffectivenessTextDialog(std::string_view defendingPlayerName, std::string_view defendingPokemonName, EffectivenessText e) const
{
	using E = EffectivenessText;

	switch (e)
	{
	case E::Less:
		m_queue.PushEvent({BattleEvents::NotVery, { defendingPlayerName, defendingPokemonName } });
		break;

	case E::Super:
		m_queue.PushEvent({BattleEvents::Super, { defendingPlayerName, defendingPokemonName } });
		break;

	case E::No:
		m_queue.PushEvent({BattleEvents::No, { defendingPlayerName, defendingPokemonName } });
		break;

	default:
		return;
	}
}

void MoveResultsQueued::DisplayAttackMissedTextDialog(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AttackMissed, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayAttackAvoidedTextDialog(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AttackAvoided, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayFailedTextDialog() const
{
	m_queue.PushEvent({BattleEvents::Failed, {} });
}

void MoveResultsQueued::DisplayDirectDamageInflictedMsg(unsigned int damage) const
{
	if (damage > 0)
	{
		m_queue.PushEvent({BattleEvents::DirectDamage, { damage } });
	}
}

void MoveResultsQueued::DisplaySubstituteDamageTextDialog(std::string_view defendingPlayerName, std::string_view defendingPokemonName, int substituteHP, bool hasSubstitute, bool hitSubstitute) const
{
	if (hitSubstitute && substituteHP > 0)
	{
		m_queue.PushEvent({BattleEvents::SubstituteDamage, { defendingPlayerName, defendingPokemonName } });
	}
}

// Specialized Results
void MoveResultsQueued::DisplayMultiAttackMsg(std::string_view defendingPokemonName, int timesHit) const
{
	m_queue.PushEvent({ BattleEvents::MultiHit, { defendingPokemonName, timesHit } });
}

void MoveResultsQueued::DisplayEnemySwitchMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::EnemySwitch, { attackingPokemonName } });
}

void MoveResultsQueued::BoundMoveText(std::string_view attackingPlayerName, std::string_view defendingPlayerName, std::string_view attackingPokemonName, std::string_view defendingPokemonName, MoveID id) const
{
	switch (id)
	{
		case MoveID::Bind:
			m_queue.PushEvent({BattleEvents::Bind, { defendingPlayerName, defendingPokemonName, attackingPlayerName, attackingPokemonName } });
			break;

		case MoveID::Wrap:
			m_queue.PushEvent({BattleEvents::Wrap, { defendingPlayerName, defendingPokemonName, attackingPlayerName, attackingPokemonName } });
			break;

		case MoveID::FireSpin:
			m_queue.PushEvent({BattleEvents::FireSpin, { defendingPlayerName, defendingPokemonName } });
			break;

		case MoveID::Clamp:
			m_queue.PushEvent({BattleEvents::Clamp, { attackingPlayerName, attackingPokemonName, defendingPlayerName, defendingPokemonName } });
			break;

		default:
			m_queue.PushEvent({BattleEvents::BoundNotFound, { EnumIndex(id) } });
	}
}

void MoveResultsQueued::DisplaySplashMsg() const
{
	m_queue.PushEvent({BattleEvents::Splash, {} });
}

void MoveResultsQueued::DisplayNoMovesLeftStruggleMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::NoMovesLeftStruggle, { attackingPlayerName, attackingPokemonName } });
}

// Charging
void MoveResultsQueued::DisplayRazorWindChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::RazorWindCharge, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayFlyChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::FlyCharge, { attackingPokemonName } });
}

void MoveResultsQueued::DisplaySolarBeamChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::SolarBeamCharge, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayDigChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::DigCharge, { attackingPokemonName } });
}

void MoveResultsQueued::DisplaySkullBashChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::SkullBashCharge, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplaySkyAttackChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::SkyAttackCharge, { attackingPlayerName, attackingPokemonName } });
}

// Recoil
void MoveResultsQueued::DisplayJumpKickCrashMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::JumpKickCrash, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayRecoilMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::Recoil, { attackingPlayerName, attackingPokemonName } });
}

// HP Results
void MoveResultsQueued::DisplayEnergyDrainedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::EnergyDrained, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayRecoveredHPRestoredMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::RestoredHP, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayHPFullMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::HPFull, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayRestMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::Rest, { attackingPlayerName, attackingPokemonName } });
}

// Status
void MoveResultsQueued::DisplayBurnSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BurnSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayFreezeSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::FreezeSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayParalyzeSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::ParalyzeSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayPoisonSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::PoisonSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayBadlyPoisonSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BadlyPoisonSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplaySleepSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::SleepSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayBecameConfuseMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BecameConfused, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayAlreadyPoisonedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AlreadyPoisoned, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayAlreadyParalyzedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AlreadyParalyzed, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayAlreadyAsleepMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AlreadyAsleep, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayDoesntAffectMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::StatusImmune, { defendingPlayerName, defendingPokemonName } });
}

// Stat Stage
void MoveResultsQueued::DisplayStatRaised2Msg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view statName) const
{
	m_queue.PushEvent({BattleEvents::StatRaised2, { attackingPlayerName, attackingPokemonName, statName } });
}

void MoveResultsQueued::DisplayStatRaised1Msg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view statName) const
{
	m_queue.PushEvent({BattleEvents::StatRaised1, { attackingPlayerName, attackingPokemonName, statName } });
}

void MoveResultsQueued::DisplayStatRaiseFailMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view statName) const
{
	m_queue.PushEvent({BattleEvents::StatRaiseFail, { attackingPlayerName, attackingPokemonName, statName } });
}

void MoveResultsQueued::DisplayStatLowered2Msg(std::string_view defendingPlayerName, std::string_view defendingPokemonName, std::string_view statName) const
{
	m_queue.PushEvent({BattleEvents::StatLowered2, { defendingPlayerName, defendingPokemonName, statName } });
}

void MoveResultsQueued::DisplayStatLowered1Msg(std::string_view defendingPlayerName, std::string_view defendingPokemonName, std::string_view statName) const
{
	m_queue.PushEvent({BattleEvents::StatLowered1, { defendingPlayerName, defendingPokemonName, statName } });
}

void MoveResultsQueued::DisplayStatLoweredFailMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName, std::string_view statName) const
{
	m_queue.PushEvent({BattleEvents::StatLoweredFail, { defendingPlayerName, defendingPokemonName, statName } });
}

// Volatile Status
void MoveResultsQueued::DisplayFocusEnergyMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::FocusEnergy, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayMistMsg(std::string_view attackingPlayerName) const
{
	m_queue.PushEvent({BattleEvents::Mist, { attackingPlayerName } });
}

void MoveResultsQueued::DisplayProtectedByMistMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::ProtectedByMist, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplaySeededMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::Seeded, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayLightScreenMsg(std::string_view attackingPlayerName) const
{
	m_queue.PushEvent({BattleEvents::LightScreen, { attackingPlayerName } });
}

void MoveResultsQueued::DisplayHazeMsg() const
{
	m_queue.PushEvent({BattleEvents::Haze, {} });
}

void MoveResultsQueued::DisplayRageStartedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::RageStarted, { attackingPlayerName, attackingPokemonName }
		});
}

void MoveResultsQueued::DisplayReflectMsg(std::string_view attackingPlayerName) const
{
	m_queue.PushEvent({BattleEvents::Reflect, { attackingPlayerName } });
}

// Substitute
void MoveResultsQueued::DisplayAlreadyHasSubstituteMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AlreadyHasSubstitute, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayNotEnoughHPSubstituteMsg() const
{
	m_queue.PushEvent({BattleEvents::NotEnoughHPSubstitute,{} });
}

void MoveResultsQueued::DisplayPutInSubstituteMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::PutInSubstitute, { attackingPlayerName, attackingPokemonName } });
}

// Copy
void MoveResultsQueued::DisplayLearnedMimicMoveMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view lastUsedMoveName) const
{
	m_queue.PushEvent({BattleEvents::LearnedMimicMove, { attackingPlayerName, attackingPokemonName, lastUsedMoveName } });
}

void MoveResultsQueued::DisplayTransformMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::Transform, { attackingPlayerName, attackingPokemonName, defendingPokemonName } });
}

void MoveResultsQueued::DisplayMetronomeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view moveName) const
{
	m_queue.PushEvent({BattleEvents::Metronome, { attackingPlayerName, attackingPokemonName, moveName } });
}

void MoveResultsQueued::DisplayConversionMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view attackingPokemonNewType) const
{
	m_queue.PushEvent({BattleEvents::Conversion, { attackingPlayerName, attackingPokemonName, attackingPokemonNewType } });
}

// Bide
void MoveResultsQueued::DisplayBideUnleashedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BideUnleashed, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueued::DisplayBideStoringEnergyMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BideStoringEnergy, { attackingPlayerName, attackingPokemonName } });
}

// Disabled
void MoveResultsQueued::DisplayMoveDisabledMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName, std::string_view moveName) const
{
	m_queue.PushEvent({BattleEvents::MoveDisabled, { defendingPlayerName, defendingPokemonName, moveName } });
}

// Switching
void MoveResultsQueued::SwitchOutNoFaintMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({BattleEvents::SwitchOutNoFaint, { playerName, pokemonName } });
}

void MoveResultsQueued::SwitchOutMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({BattleEvents::SwitchOut, { playerName, pokemonName } });
}

void MoveResultsQueued::PlayerChoosesMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({BattleEvents::PlayerChooses, { playerName, pokemonName } });
}