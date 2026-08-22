#include "SwitchExecutor.h"

#include "../entities/BattlePokemon.h"
#include "../entities/Player.h"

#include "../entities/controllers/BattleAIUpdateRoutines.h"

#include "../ui/interfaces/IMoveResultsUI.h"

#include "BattleContext.h"

SwitchExecutor::SwitchExecutor(BattleContext& context, IMoveResultsUI& moveResultsUI) :
	m_context(context), m_moveResultsUI(moveResultsUI) {}

// BattlePokemon*& pokemon parameter intentional to reassign the passed in pointer.
// This keeps attackingPokemon pointer synchronized with the current active Pokemon.
void SwitchExecutor::ExecuteSwitch(Player& player, BattlePokemon*& pokemon)
{
	if (!pokemon->IsFainted())
	{
		m_moveResultsUI.SwitchOutNoFaintMsg(player.GetPlayerNameView(), pokemon->GetPokemonNameView());
	}
	else
	{
		m_moveResultsUI.SwitchOutMsg(player.GetPlayerNameView(), pokemon->GetPokemonNameView());
	}

	pokemon->ResetStatsOnSwitch();
	player.ResetActivePokemonTurnCount();
	pokemon = player.GetPokemonToSwitchTo();

	if (&player == m_context.playerOne)
	{
		if (m_context.playerTwoCurrentPokemon->IsBound())
		{
			m_context.playerTwoCurrentPokemon->SetBound(false);
			m_context.playerTwoCurrentPokemon->ResetBoundCounter();
			m_context.playerTwoCurrentPokemon->SetBoundTurnCount(0);
		}

		m_context.playerOneCurrentPokemon = pokemon;
	}
	else if (&player == m_context.playerTwo)
	{
		if (m_context.playerOneCurrentPokemon->IsBound())
		{
			m_context.playerOneCurrentPokemon->SetBound(false);
			m_context.playerOneCurrentPokemon->ResetBoundCounter();
			m_context.playerOneCurrentPokemon->SetBoundTurnCount(0);
		}

		m_context.playerTwoCurrentPokemon = pokemon;
	}

	BattleAIUpdateRoutines::UpdateEnemyActivePokemon(m_context);

	player.SetIsSwitching(false);

	m_moveResultsUI.PlayerChoosesMsg(player.GetPlayerNameView(), pokemon->GetPokemonNameView());
}