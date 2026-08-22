#include "StatusEffectQueued.h"

#include "BattleEvents.h"
#include "BattleEventQueue.h"

#include <string_view>

StatusEffectQueued::StatusEffectQueued(BattleEventQueue& queue)
	: m_queue(queue)
{}

// Status changes
void StatusEffectQueued::DisplayFellAsleepMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::FellAsleep, { defendingPlayerName, defendingPokemonName }
		});
}

void StatusEffectQueued::DisplayWokenUpMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::WokenUp, { attackingPokemonName }
		});
}

void StatusEffectQueued::DisplayIsAsleepMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::IsAsleep, { attackingPokemonName }
		});
}

void StatusEffectQueued::DisplayFrozenSolidMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::FrozenSolid, { attackingPokemonName }
		});
}

void StatusEffectQueued::DisplayThawedMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::Thawed, { attackingPokemonName }
		});
}

void StatusEffectQueued::DisplayNoLongerConfusedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::NoLongerConfused, { attackingPlayerName, attackingPokemonName }
		});
}

void StatusEffectQueued::DisplayIsConfusedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::IsConfused, { attackingPlayerName, attackingPokemonName }
		});
}

void StatusEffectQueued::DisplayHurtItselfConfuseMsg() const
{
	m_queue.PushEvent({ BattleEvents::HurtItselfConfusion, {}
		});
}

void StatusEffectQueued::DisplayCantMoveParalysisMsg(std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::CantMoveParalysis, { attackingPokemonName }
		});
}

void StatusEffectQueued::DisplayFlinchMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::Flinch, { attackingPlayerName, attackingPokemonName }
		});
}

void StatusEffectQueued::DisplayRechargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::Recharge, { attackingPlayerName, attackingPokemonName }
		});
}

// Barriers / field effects
void StatusEffectQueued::DisplayNoLongerProtectedMist(std::string_view playerName) const
{
	m_queue.PushEvent({ BattleEvents::NoLongerProtectedMist, { playerName }
		});
}

void StatusEffectQueued::DisplayFieldEffectFadedMsg(std::string_view playerName, std::string_view effect) const
{
	m_queue.PushEvent({ BattleEvents::FieldEffectFaded, { playerName, effect }
		});
}

// Post-turn effects
void StatusEffectQueued::DisplayLeechSeedSappedMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({ BattleEvents::LeechSeedSapped, { playerName, pokemonName }
		});
}

void StatusEffectQueued::DisplayDamagedByStatusPostTurn(std::string_view playerName, std::string_view pokemonName, std::string_view status) const
{
	m_queue.PushEvent({ BattleEvents::DamagedByStatusPostTurn, { playerName, pokemonName, status }
		});
}

void StatusEffectQueued::DisplayHurtByBoundMsg(std::string_view playerName, std::string_view pokemonName, std::string_view boundMoveName) const
{
	m_queue.PushEvent({ BattleEvents::HurtByBound, { playerName, pokemonName, boundMoveName }
		});
}

void StatusEffectQueued::DisplayFreedFromBoundMsg(std::string_view playerName, std::string_view pokemonName, std::string_view boundMoveName) const
{
	m_queue.PushEvent({ BattleEvents::FreedFromBound, { playerName, pokemonName, boundMoveName }
		});
}

// Rampage
void StatusEffectQueued::DisplayRampageConfusionMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::RampageConfusion, { attackingPlayerName, attackingPokemonName }
		});
}

// Bide
void StatusEffectQueued::DisplayBideStoringEnergyMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::BideStoringEnergy, { attackingPlayerName, attackingPokemonName } });
}

// Disable
void StatusEffectQueued::DisplayMoveIsDisabledMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view moveName) const
{
	m_queue.PushEvent({ BattleEvents::MoveIsDisabled, { attackingPlayerName, attackingPokemonName, moveName }
		});
}

void StatusEffectQueued::DisplayMoveNoLongerDisabledMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view disabledMoveName) const
{
	m_queue.PushEvent({ BattleEvents::MoveNoLongerDisabled, { attackingPlayerName, attackingPokemonName, disabledMoveName }
		});
}

void StatusEffectQueued::DisplaySubstituteFadedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_queue.PushEvent({ BattleEvents::SubstituteFaded, { defendingPlayerName, defendingPokemonName }
		});
}

// Faint
void StatusEffectQueued::DisplayFaintedMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_queue.PushEvent({ BattleEvents::Fainted, { playerName, pokemonName }
		});
}

void StatusEffectQueued::NewLine() const
{
	m_queue.PushEvent({ BattleEvents::NewLine, {}
		});
}

// Blocking Events
void StatusEffectQueued::BlockForSwitching() const
{
	m_queue.PushEvent({ BattleEvents::Pause, {}
		});
}