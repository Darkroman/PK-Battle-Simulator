#pragma once

#include <span>

class Player;
class BattlePokemon;
struct pokemonMove;
class BattleCalculations;
class RandomEngine;
struct ScoringResults;

namespace MediumMoveScoring
{
	void EvaluateBestDamageMove(std::span<ScoringResults>& results, const BattlePokemon& targetMon);
}