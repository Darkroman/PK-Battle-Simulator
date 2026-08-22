#include "BattleAIUpdateRoutines.h"

#include "../../battle/BattleContext.h"

#include "../Player.h"

#include "AIController.h"

namespace BattleAIUpdateRoutines
{
	void InitAIPlayers(BattleContext& context)
	{
		for (const auto& player : context.vec_aiPlayers)
		{
			player->GetAIController().OnBattleStart(*player, context);
			player->GetAIController().OnActivePokemonChanged(context);
		}
	}

	void UpdateEnemyActivePokemon(const BattleContext& context)
	{
		for (const auto& player : context.vec_aiPlayers)
		{
			player->GetAIController().OnActivePokemonChanged(context);
		}
	}

	void RefineEnemyModel(const BattleContext& context)
	{
		for (const auto& player : context.vec_aiPlayers)
		{
			player->GetAIController().OnMoveResolved(context);
		}
	}

	void ResetAIObservedMoves(BattleContext& context)
	{
		for (auto* aiPlayers : context.vec_aiPlayers)
		{
			aiPlayers->GetAIController().ResetObservedMoves();
		}
	}
}