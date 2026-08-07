#pragma once

#include <span>

class BattlePokemon;
struct ScoringResults;

namespace MediumMoveScoring
{
	void EvaluateBestDamageMove(std::span<ScoringResults>& results, const BattlePokemon& targetMon);
}