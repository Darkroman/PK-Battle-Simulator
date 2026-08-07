#include "WinChecker.h"

#include "BattleContext.h"
#include "../entities/Player.h"

WinChecker::WinChecker(BattleContext& context)
    : m_context(context)
	{}

bool WinChecker::CheckWinCondition(Player& sourcePlayer, Player& targetPlayer)
{
	if (m_context.vec_outOfPokemon.empty())
	{
		return false;
	}

	if (&targetPlayer == m_context.vec_outOfPokemon[0])
	{
		sourcePlayer.SetWinCondition(true);
		return true;
	}

	return false;
}