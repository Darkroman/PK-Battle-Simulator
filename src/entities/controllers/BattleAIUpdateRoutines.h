#pragma once

struct BattleContext;

namespace BattleAIUpdateRoutines
{
	void InitAIPlayers(BattleContext& context);
	void UpdateEnemyActivePokemon(const BattleContext& context);
	void RefineEnemyModel(const BattleContext& context);
	void ResetAIObservedMoves(BattleContext& context);
}