#pragma once

#include <span>

struct ScoringResults;
class Player;
class BattlePokemon;
struct pokemonMove;
class RandomEngine;

namespace AIMoveScoring
{
	pokemonMove* GetWinningMove(const Player& self, const Player& targetPlayer, BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng);
	pokemonMove* EvaluateScoredMoves(std::span<ScoringResults>& results, RandomEngine& rng);
	ScoringResults RunScoringRoutine(ScoringResults& results, const Player& self, const Player& targetPlayer, const pokemonMove& move, const BattlePokemon& selfMon, const BattlePokemon& targetMon);
	unsigned int CalculateSpeed(const BattlePokemon&);
}