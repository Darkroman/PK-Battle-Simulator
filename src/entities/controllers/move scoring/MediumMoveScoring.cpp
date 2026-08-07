#include <algorithm>
#include <array>
#include <span>

#include "MediumMoveScoring.h"

#include "AIScoreTag.h"
#include "ScoringResultsStruct.h"
#include "../../BattlePokemon.h"
#include "../../../moves/MoveEffectEnums.h"

namespace MediumMoveScoring
{
	void EvaluateBestDamageMove(std::span<ScoringResults>& results, const BattlePokemon& targetMon)
	{
		std::array<ScoringResults*, 4> damagingMoves{};

		unsigned int highestDamage = 0;
		size_t count{};
		for (auto& result : results)
		{
			if (result.damage > 0)
			{
				damagingMoves[count] = &result;

				if (!(result.tag == AIScoreTag::RechargeMove || result.tag == AIScoreTag::SelfFaintingDamage)) // don't consider recharge or self-fainting moves into highest damage calculation
				{
					highestDamage = std::max(highestDamage, result.damage);
				}

				if (result.tag == AIScoreTag::ChargeMove || result.tag == AIScoreTag::SkyAttack) // halve the damage if two turn move and is not recharge move
				{
					result.damage /= 2;
				}
				++count;
			}
		}

		std::span<ScoringResults*> damagingMovesView{ damagingMoves.data(), count };

		for (auto& result : damagingMovesView)
		{
			bool isRechargeMove = result->tag == AIScoreTag::RechargeMove;

			bool canKill{};
			if (result->damage >= targetMon.GetCurrentHP())
			{
				canKill = true;
			}

			// If move is enough to kill target
			if (canKill)
			{
				if (result->move->GetMoveEffectEnum() == MoveEffect::Explosion)
				{
					// do nothing
				}
				else if (result->move->GetPriority() >= 1) // If move is priority +1 or more (ala quick attack)
				{
					result->score += 6;
				}
				else
				{
					result->score += 4; // add +4 to move score if above don't qualify
				}
			}

			// if move is not the highest damaging move, subtract score by 1 (whether it kills or not)
			if (result->damage < highestDamage)
			{
				result->score -= 1;
			}

			// This makes it so the recharge move should be the top scored move ONLY if other moves aren't guaranteed to kill at max damage
			if (isRechargeMove)
			{
				result->score -= 2;
			}

			// if self-fainting move
			if (result->move->GetMoveEffectEnum() == MoveEffect::Explosion)
			{
				result->score -= 2;
			}
		}
	}
}