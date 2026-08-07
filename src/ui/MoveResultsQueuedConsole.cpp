#include <string_view>

#include "MoveResultsQueuedConsole.h"

#include "BattleEvents.h"
#include "EffectivenessText.h"
#include "BattleUIEventQueue.h"
#include "../data/MoveID.h"
#include "../common/EnumUtils.h"

// Basic Move Results
MoveResultsQueuedConsole::MoveResultsQueuedConsole(BattleUIEventQueue& queue)
	: m_queue(queue)
{}

void MoveResultsQueuedConsole::DisplayNoopMsg() const
{
	m_queue.PushEvent({BattleEvents::Noop, {}
		});
}

void MoveResultsQueuedConsole::UsedTextDialog(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view currentMoveName) const
{
	m_queue.PushEvent({BattleEvents::UsedMove, { attackingPlayerName, attackingPokemonName, currentMoveName } });
}

void MoveResultsQueuedConsole::DisplayCritTextDialog(bool isCriticalHit) const
{
	if (isCriticalHit)
	{
		m_queue.PushEvent({BattleEvents::CriticalHit, {} });
	}
}

void MoveResultsQueuedConsole::DisplayOHKOTextDialog() const
{
	m_queue.PushEvent({ BattleEvents::OHKO, {} });
}

void MoveResultsQueuedConsole::DisplayEffectivenessTextDialog(std::string_view defendingPlayerName, std::string_view defendingPokemonName, EffectivenessText e) const
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

void MoveResultsQueuedConsole::DisplayAttackMissedTextDialog(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AttackMissed, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayAttackAvoidedTextDialog(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AttackAvoided, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayFailedTextDialog() const
{
	m_queue.PushEvent({BattleEvents::Failed, {} });
}

void MoveResultsQueuedConsole::DisplayDirectDamageInflictedMsg(unsigned int damage) const
{
	if (damage > 0)
	{
		m_queue.PushEvent({BattleEvents::DirectDamage, { damage } });
	}
}

void MoveResultsQueuedConsole::DisplaySubstituteDamageTextDialog(std::string_view defendingPlayerName, std::string_view defendingPokemonName, int substituteHP, bool hasSubstitute, bool hitSubstitute) const
{
	if (hitSubstitute && substituteHP > 0)
	{
		m_queue.PushEvent({BattleEvents::SubstituteDamage, { defendingPlayerName, defendingPokemonName } });
	}
}

// Specialized Results
void MoveResultsQueuedConsole::DisplayMultiAttackMsg(std::string_view defendingPokemonName, int timesHit) const
{
	m_queue.PushEvent({ BattleEvents::MultiHit, { defendingPokemonName, timesHit } });
}

void MoveResultsQueuedConsole::DisplayEnemySwitchMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::EnemySwitch, { attackingPokemonName } });
}

void MoveResultsQueuedConsole::BoundMoveText(std::string_view attackingPlayerName, std::string_view defendingPlayerName, std::string_view attackingPokemonName, std::string_view defendingPokemonName, MoveID id) const
{
	switch (id)
	{
		case MoveID::Bind:
			m_queue.PushEvent({BattleEvents::Bind, { attackingPlayerName, defendingPlayerName, attackingPokemonName, defendingPokemonName } });
			break;

		case MoveID::Wrap:
			m_queue.PushEvent({BattleEvents::Wrap, { attackingPlayerName, defendingPlayerName, attackingPokemonName, defendingPokemonName } });
			break;

		case MoveID::FireSpin:
			m_queue.PushEvent({BattleEvents::FireSpin, { attackingPlayerName, defendingPlayerName, attackingPokemonName, defendingPokemonName } });
			break;

		case MoveID::Clamp:
			m_queue.PushEvent({BattleEvents::Clamp, { attackingPlayerName, defendingPlayerName, attackingPokemonName, defendingPokemonName } });
			break;

		default:
			m_queue.PushEvent({BattleEvents::BoundNotFound, { EnumIndex(id) } });
	}
}

void MoveResultsQueuedConsole::DisplaySplashMsg() const
{
	m_queue.PushEvent({BattleEvents::Splash, {} });
}

void MoveResultsQueuedConsole::DisplayNoMovesLeftStruggleMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::NoMovesLeftStruggle, { attackingPlayerName, attackingPokemonName } });
}

// Charging
void MoveResultsQueuedConsole::DisplayRazorWindChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::RazorWindCharge, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayFlyChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::FlyCharge, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplaySolarBeamChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::SolarBeamCharge, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayDigChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::DigCharge, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplaySkullBashChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::SkullBashCharge, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplaySkyAttackChargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::SkyAttackCharge, { attackingPlayerName, attackingPokemonName } });
}

// Recoil
void MoveResultsQueuedConsole::DisplayJumpKickCrashMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::JumpKickCrash, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayRecoilMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::Recoil, { attackingPlayerName, attackingPokemonName } });
}

// HP Results
void MoveResultsQueuedConsole::DisplayEnergyDrainedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::EnergyDrained, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayRecoveredHPRestoredMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::RestoredHP, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayHPFullMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::HPFull, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayRestMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::Rest, { attackingPlayerName, attackingPokemonName } });
}

// Status
void MoveResultsQueuedConsole::DisplayBurnSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BurnSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayFreezeSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::FreezeSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayParalyzeSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::ParalyzeSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayPoisonSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::PoisonSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayBadlyPoisonSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BadlyPoisonSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplaySleepSuccess(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::SleepSuccess, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayBecameConfuseMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BecameConfused, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayAlreadyPoisonedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AlreadyPoisoned, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayAlreadyParalyzedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AlreadyParalyzed, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayAlreadyAsleepMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AlreadyAsleep, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayDoesntAffectMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::StatusImmune, { defendingPlayerName, defendingPokemonName } });
}

// Stat Stage
void MoveResultsQueuedConsole::DisplayStatRaised2Msg(std::string_view statName, std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::StatRaised2, { statName, attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayStatRaised1Msg(std::string_view statName, std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::StatRaised1, { statName, attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayStatRaiseFailMsg(std::string_view statName, std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::StatRaiseFail, { statName, attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayStatLowered2Msg(std::string_view statName, std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::StatLowered2, { statName, defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayStatLowered1Msg(std::string_view statName, std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::StatLowered1, { statName, defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayStatLoweredFailMsg(std::string_view statName, std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::StatLoweredFail, { statName, defendingPlayerName, defendingPokemonName } });
}

// Volatile Status
void MoveResultsQueuedConsole::DisplayFocusEnergyMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::FocusEnergy, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayMistMsg(std::string_view attackingPlayerName) const
{
	m_queue.PushEvent({BattleEvents::Mist, { attackingPlayerName } });
}

void MoveResultsQueuedConsole::DisplayProtectedByMistMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::ProtectedByMist, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplaySeededMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::Seeded, { defendingPlayerName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayLightScreenMsg(std::string_view attackingPlayerName) const
{
	m_queue.PushEvent({BattleEvents::LightScreen, { attackingPlayerName } });
}

void MoveResultsQueuedConsole::DisplayHazeMsg() const
{
	m_queue.PushEvent({BattleEvents::Haze, {} });
}

void MoveResultsQueuedConsole::DisplayRageStartedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::RageStarted, { attackingPlayerName, attackingPokemonName }
		});
}

void MoveResultsQueuedConsole::DisplayReflectMsg(std::string_view attackingPlayerName) const
{
	m_queue.PushEvent({BattleEvents::Reflect, { attackingPlayerName } });
}

// Substitute
void MoveResultsQueuedConsole::DisplayAlreadyHasSubstituteMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::AlreadyHasSubstitute, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayNotEnoughHPSubstituteMsg() const
{
	m_queue.PushEvent({BattleEvents::NotEnoughHPSubstitute,{} });
}

void MoveResultsQueuedConsole::DisplayPutInSubstituteMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::PutInSubstitute, { attackingPlayerName, attackingPokemonName } });
}

// Copy
void MoveResultsQueuedConsole::DisplayLearnedMimicMoveMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view lastUsedMoveName) const
{
	m_queue.PushEvent({BattleEvents::LearnedMimicMove, { attackingPlayerName, attackingPokemonName, lastUsedMoveName } });
}

void MoveResultsQueuedConsole::DisplayTransformMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::Transform, { attackingPlayerName, attackingPokemonName, defendingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayMetronomeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view moveName) const
{
	m_queue.PushEvent({BattleEvents::Metronome, { attackingPlayerName, attackingPokemonName, moveName } });
}

void MoveResultsQueuedConsole::DisplayConversionMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view attackingPokemonNewType) const
{
	m_queue.PushEvent({BattleEvents::Conversion, { attackingPlayerName, attackingPokemonName, attackingPokemonNewType } });
}

// Bide
void MoveResultsQueuedConsole::DisplayBideUnleashedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BideUnleashed, { attackingPlayerName, attackingPokemonName } });
}

void MoveResultsQueuedConsole::DisplayBideStoringEnergyMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({BattleEvents::BideStoringEnergy, { attackingPlayerName, attackingPokemonName } });
}

// Disabled
void MoveResultsQueuedConsole::DisplayMoveDisabledMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName, std::string_view moveName) const
{
	m_queue.PushEvent({BattleEvents::MoveDisabled, { defendingPlayerName, defendingPokemonName, moveName } });
}

// Switching
void MoveResultsQueuedConsole::SwitchOutNoFaintMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({BattleEvents::SwitchOutNoFaint, { playerName, pokemonName } });
}

void MoveResultsQueuedConsole::SwitchOutMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({BattleEvents::SwitchOut, { playerName, pokemonName } });
}

void MoveResultsQueuedConsole::PlayerChoosesMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({BattleEvents::PlayerChooses, { playerName, pokemonName } });
}