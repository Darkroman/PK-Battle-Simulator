#include <vector>
#include <memory>

#include "BattleContext.h"
#include "../data/StringToTypes.h"

BattleContext::BattleContext(std::vector<std::unique_ptr<Player>>& vec_players)
  : vec_aiPlayers([]() { std::vector<Player*> v; v.reserve(2); return v; }()),
    vec_outOfPokemon([]() { std::vector<Player*> v; v.reserve(2); return v; }()),
    playerOne(vec_players[0].get()),
	playerTwo(vec_players[1].get())
{}

void BattleStateFlags::ResetBattleFlags()
{
    hit = false;
    hitSubstitute = false;
    isCriticalHit = false;
    moveWasUsed = false;
    currentEffectiveness = Effectiveness::Normal;
}

void BattleContext::ResetTurnState()
{
    lastDamagingMove = nullptr;
    lastDamageApplied = 0;
    pixelsLost = 0;

    initialPowerMultiplier = 10;

    effectiveness = 4096;

    flags.ResetBattleFlags();
}

void BattleContext::ResetBattleState()
{
    flags.ResetBattleFlags();

    //vec_aiPlayers.clear(); <-- This is already done in PresetupBattle() in GameEngine
    vec_outOfPokemon.clear();

    playerOneCurrentPokemon = nullptr;
    playerTwoCurrentPokemon = nullptr;

    playerOneCurrentMove = nullptr;
    playerTwoCurrentMove = nullptr;

    attackingPlayer = nullptr;
    defendingPlayer = nullptr;

    attackingPokemon = nullptr;
    defendingPokemon = nullptr;

    currentMove = nullptr;
    lastDamagingMove = nullptr;

    battleTurn = 0;

    damageTaken = 0;
    damageTakenCategory = Category::None;

    pixelsLost = 0;
    prevPixels = 400;
    damageInPixels = 0;

    initialPowerMultiplier = 10;
    effectiveness = 4096;
}