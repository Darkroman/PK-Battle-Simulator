#include <string_view>

#include "StatusEffectQueuedConsole.h"

#include "BattleEvents.h"
#include "BattleUIEventQueue.h"

StatusEffectQueuedConsole::StatusEffectQueuedConsole(BattleUIEventQueue& queue)
	: m_queue(queue)
{}

// Status changes
void StatusEffectQueuedConsole::DisplayFellAsleepMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::FellAsleep, { defendingPlayerName, defendingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayWokenUpMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::WokenUp, { attackingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayIsAsleepMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::IsAsleep, { attackingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayFrozenSolidMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::FrozenSolid, { attackingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayThawedMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::Thawed, { attackingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayNoLongerConfusedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::NoLongerConfused, { attackingPlayerName, attackingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayIsConfusedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::IsConfused, { attackingPlayerName, attackingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayHurtItselfConfuseMsg() const
{
	m_queue.PushEvent({ BattleEvents::HurtItselfConfusion, {}
		});
}

void StatusEffectQueuedConsole::DisplayCantMoveParalysisMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::CantMoveParalysis, { attackingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayFlinchMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::Flinch, { attackingPlayerName, attackingPokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayRechargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::Recharge, { attackingPlayerName, attackingPokemonName }
		});
}

// Barriers / field effects
void StatusEffectQueuedConsole::DisplayNoLongerProtectedMist(std::string_view playerName) const
{
	m_queue.PushEvent({ BattleEvents::NoLongerProtectedMist, { playerName }
		});
}

void StatusEffectQueuedConsole::DisplayFieldEffectFadedMsg(std::string_view playerName, std::string_view effect) const
{
	m_queue.PushEvent({ BattleEvents::FieldEffectFaded, { playerName, effect }
		});
}

// Post-turn effects
void StatusEffectQueuedConsole::DisplayLeechSeedSappedMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({ BattleEvents::LeechSeedSapped, { playerName, pokemonName }
		});
}

void StatusEffectQueuedConsole::DisplayDamagedByStatusPostTurn(std::string_view playerName, std::string_view pokemonName, std::string_view status) const
{
	m_queue.PushEvent({ BattleEvents::DamagedByStatusPostTurn, { playerName, pokemonName, status }
		});
}

void StatusEffectQueuedConsole::DisplayHurtByBoundMsg(std::string_view playerName, std::string_view pokemonName, std::string_view boundMoveName) const
{
	m_queue.PushEvent({ BattleEvents::HurtByBound, { playerName, pokemonName, boundMoveName }
		});
}

void StatusEffectQueuedConsole::DisplayFreedFromBoundMsg(std::string_view playerName, std::string_view pokemonName, std::string_view boundMoveName) const
{
	m_queue.PushEvent({ BattleEvents::FreedFromBound, { playerName, pokemonName, boundMoveName }
		});
}

// Rampage
void StatusEffectQueuedConsole::DisplayRampageConfusionMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::RampageConfusion, { attackingPlayerName, attackingPokemonName }
		});
}

// Bide
void StatusEffectQueuedConsole::DisplayBideStoringEnergyMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::BideStoringEnergy, { attackingPlayerName, attackingPokemonName } });
}

// Disable
void StatusEffectQueuedConsole::DisplayMoveIsDisabledMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view moveName) const
{
	m_queue.PushEvent({ BattleEvents::MoveIsDisabled, { attackingPlayerName, attackingPokemonName, moveName }
		});
}

void StatusEffectQueuedConsole::DisplayMoveNoLongerDisabledMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view disabledMoveName) const
{
	m_queue.PushEvent({ BattleEvents::MoveNoLongerDisabled, { attackingPlayerName, attackingPokemonName, disabledMoveName }
		});
}

void StatusEffectQueuedConsole::DisplaySubstituteFadedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::SubstituteFaded, { defendingPlayerName, defendingPokemonName }
		});
}

// Faint
void StatusEffectQueuedConsole::DisplayFaintedMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({ BattleEvents::Fainted, { playerName, pokemonName }
		});
}

void StatusEffectQueuedConsole::NewLine() const
{
	m_queue.PushEvent({ BattleEvents::NewLine, {}
		});
}

// Blocking Events
void StatusEffectQueuedConsole::BlockForSwitching() const
{
	m_queue.PushEvent({ BattleEvents::Pause, {}
		});
}