#pragma once

#include <span>

class BattlePokemon;
class Player;
class RandomEngine;
struct PokemonMoveSlot;
struct ScoringResults;

namespace AIMoveScoring
{
	PokemonMoveSlot* GetWinningMove(const Player& self, const Player& targetPlayer, BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng);
	PokemonMoveSlot* EvaluateScoredMoves(std::span<ScoringResults>& results, RandomEngine& rng);
	void RunScoringRoutine(ScoringResults& results, const Player& self, const Player& targetPlayer, const PokemonMoveSlot& move, const BattlePokemon& selfMon, const BattlePokemon& targetMon);
	unsigned int CalculateSpeed(const BattlePokemon&);
}