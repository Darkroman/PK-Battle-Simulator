#include "SwitchExecutor.h"

#include "BattleContext.h"
#include "../entities/BattlePokemon.h"
#include "../entities/Player.h"
#include "../ui/interfaces/IMoveResultsUI.h"
#include "../entities/controllers/AIController.h"

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

	for (auto& aiPlayer : m_context.vec_aiPlayers)
	{
		aiPlayer->GetAIController().OnActivePokemonChanged(m_context);
	}

	player.SetIsSwitching(false);

	m_moveResultsUI.PlayerChoosesMsg(player.GetPlayerNameView(), pokemon->GetPokemonNameView());
}