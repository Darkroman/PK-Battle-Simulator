#include "AIMoveClassifier.h"

#include "AIScoreTag.h"
#include "../../pokemonMove.h"
#include "../../../moves/MoveEffectEnums.h"

AIScoreTag AIMoveClassifier::Classify(const pokemonMove& move)
{
	if (move.GetPriority() > 0 && move.GetMoveEffectEnum() == MoveEffect::NormalHit)
	{
		return AIScoreTag::PriorityDamage;
	}

	auto it = s_effectToTag.find(move.GetMoveEffectEnum());
	if (it != s_effectToTag.end())
	{
		return it->second;
	}
	return AIScoreTag::Other;
}