#include <format>
#include <string_view>

#include "StatusEffectText.h"

#include "interfaces/IOutputTarget.h"

// Status changes
void StatusEffectText::DisplayFellAsleepMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_target.Emit(std::format("{}'s {} fell asleep!", defendingPlayerName, defendingPokemonName));
}

void StatusEffectText::DisplayWokenUpMsg(std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{} has woken up!", attackingPokemonName));
}

void StatusEffectText::DisplayIsAsleepMsg(std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{} is sleeping.", attackingPokemonName));
}

void StatusEffectText::DisplayFrozenSolidMsg(std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{} is frozen solid!", attackingPokemonName));
}

void StatusEffectText::DisplayThawedMsg(std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{} thawed out!", attackingPokemonName));
}

void StatusEffectText::DisplayNoLongerConfusedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{}'s {} is no longer confused!", attackingPlayerName, attackingPokemonName));
}

void StatusEffectText::DisplayIsConfusedMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{}'s {} is confused!", attackingPlayerName, attackingPokemonName));
}

void StatusEffectText::DisplayHurtItselfConfuseMsg() const
{
	m_target.Emit(std::format("It hurt itself in its confusion!"));
}

void StatusEffectText::DisplayCantMoveParalysisMsg(std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{} couldn't move because it's paralyzed!", attackingPokemonName));
}

void StatusEffectText::DisplayFlinchMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{}'s {} flinched and couldn't move!", attackingPlayerName, attackingPokemonName));
}

void StatusEffectText::DisplayRechargeMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{}'s {} must recharge!", attackingPlayerName, attackingPokemonName));
}

// Barriers / field effects
void StatusEffectText::DisplayNoLongerProtectedMist(std::string_view playerName) const
{
	m_target.Emit(std::format("{}'s team is no longer protected by mist!", playerName));
}

void StatusEffectText::DisplayFieldEffectFadedMsg(std::string_view playerName, std::string_view effect) const
{
	m_target.Emit(std::format("{}'s team's {} wore off!", playerName, effect));
}

// Post-turn effects
void StatusEffectText::DisplayLeechSeedSappedMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_target.Emit(std::format("{}'s {}'s health is sapped by Leech Seed.", playerName, pokemonName));
}

void StatusEffectText::DisplayDamagedByStatusPostTurn(std::string_view playerName, std::string_view pokemonName, std::string_view status) const
{
	m_target.Emit(std::format("{}'s {} was damaged by {}.", playerName, pokemonName, status));
}

void StatusEffectText::DisplayHurtByBoundMsg(std::string_view playerName, std::string_view pokemonName, std::string_view boundMoveName) const
{
	m_target.Emit(std::format("{}'s {} was hurt by {}!", playerName, pokemonName, boundMoveName));
}

void StatusEffectText::DisplayFreedFromBoundMsg(std::string_view playerName, std::string_view pokemonName, std::string_view boundMoveName) const
{
	m_target.Emit(std::format("{}'s {} was freed from {}!", playerName, pokemonName, boundMoveName));
}

// Rampage
void StatusEffectText::DisplayRampageConfusionMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{}'s {} became confused due to fatigue!", attackingPlayerName, attackingPokemonName));
}

// Bide
void StatusEffectText::DisplayBideStoringEnergyMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName) const
{
	m_target.Emit(std::format("{}'s {} is storing energy!", attackingPlayerName, attackingPokemonName));
}

// Disable
void StatusEffectText::DisplayMoveIsDisabledMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view moveName) const
{
	m_target.Emit(std::format("{}'s {}'s {} is disabled!", attackingPlayerName, attackingPokemonName, moveName));
}

void StatusEffectText::DisplayMoveNoLongerDisabledMsg(std::string_view attackingPlayerName, std::string_view attackingPokemonName, std::string_view disabledMoveName) const
{
	m_target.Emit(std::format("{}'s {}'s {} is no longer disabled!", attackingPlayerName, attackingPokemonName, disabledMoveName));
}

void StatusEffectText::DisplaySubstituteFadedMsg(std::string_view defendingPlayerName, std::string_view defendingPokemonName) const
{
	m_target.Emit(std::format("{}'s {}'s substitute faded!", defendingPlayerName, defendingPokemonName));
}

// Faint
void StatusEffectText::DisplayFaintedMsg(std::string_view playerName, std::string_view pokemonName) const
{
	m_target.Emit(std::format("{}'s {} has fainted!", playerName, pokemonName));
}

void StatusEffectText::NewLine() const
{
	m_target.Emit("");
}