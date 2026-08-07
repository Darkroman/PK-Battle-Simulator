#pragma once

struct BattleContext;

namespace BattleAIProcedures
{
	void InitAIPlayers(BattleContext& context);
	void UpdateEnemyActivePokemon(const BattleContext& context);
	void RefineEnemyModel(const BattleContext& context);
}