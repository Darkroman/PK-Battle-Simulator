#include <utility>

#include "TurnProcessor.h"

#include "BattleContext.h"
#include "BattleCalculations.h"
#include "StatusEffectProcessor.h"
#include "WinChecker.h"
#include "SwitchExecutor.h"
#include "MoveExecutor.h"
#include "../entities/PlayerDecisionOutcome.h"
#include "../entities/pokemonMove.h"
#include "../entities/Player.h"
#include "../entities/controllers/IPlayerController.h"

constexpr int SwitchPriority{ 6 };

TurnProcessor::TurnProcessor(BattleContext& context, BattleCalculations& calculations, StatusEffectProcessor& statusProcessor, WinChecker& winChecker, SwitchExecutor& switchExecutor, MoveExecutor& moveExecutor)
	: m_context(context)
	, m_calculations(calculations)
	, m_statusProcessor(statusProcessor)
	, m_winChecker(winChecker)
	, m_switchExecutor(switchExecutor)
	, m_moveExecutor(moveExecutor)
	{}

void TurnProcessor::DetermineTurnOrder()
{
	if (m_context.playerOne->IsSwitching() && m_context.playerTwo->IsSwitching())
	{
		m_calculations.RandomizeTurnOrder();
		return;
	}

	const pokemonMove* moveOne = m_context.playerOneCurrentMove;
	const pokemonMove* moveTwo = m_context.playerTwoCurrentMove;

	int moveOnePriority = (m_context.playerOne->IsSwitching()) ? SwitchPriority : moveOne->GetPriority();
	int moveTwoPriority = (m_context.playerTwo->IsSwitching()) ? SwitchPriority : moveTwo->GetPriority();

	if (moveOnePriority > moveTwoPriority)
	{
		m_calculations.SetFirst(*m_context.playerOne, *m_context.playerTwo);
		return;
	}
	else if (moveOnePriority < moveTwoPriority)
	{
		m_calculations.SetFirst(*m_context.playerTwo, *m_context.playerOne);
		return;
	}

	unsigned int playerOneSpeed = m_calculations.CalculatePokemonSpeed(*m_context.playerOneCurrentPokemon);
	unsigned int playerTwoSpeed = m_calculations.CalculatePokemonSpeed(*m_context.playerTwoCurrentPokemon);

	if (playerOneSpeed > playerTwoSpeed)
	{
		m_calculations.SetFirst(*m_context.playerOne, *m_context.playerTwo);
		return;
	}
	else if (playerTwoSpeed > playerOneSpeed)
	{
		m_calculations.SetFirst(*m_context.playerTwo, *m_context.playerOne);
		return;
	}
	else
	{
		m_calculations.RandomizeTurnOrder();
	}
}

TurnSwitchState TurnProcessor::ExecuteTurn()
{
	m_context.attackingPokemon->SetRaging(false);

	if (m_context.attackingPlayer->IsSwitching())
	{
		m_switchExecutor.ExecuteSwitch(*m_context.attackingPlayer, m_context.attackingPokemon);

		return TurnSwitchState::ContinueRound;
	}

	else
	{
		if (!m_statusProcessor.CheckPerformativeStatus())
		{

			return TurnSwitchState::ContinueRound;
		}

		m_moveExecutor.ExecuteMove();
	}

	if (m_winChecker.CheckWinCondition(*m_context.attackingPlayer, *m_context.defendingPlayer))
	{
		return TurnSwitchState::Victory;
	}

	if (m_winChecker.CheckWinCondition(*m_context.defendingPlayer, *m_context.attackingPlayer))
	{
		return TurnSwitchState::Victory;
	}

	if (!m_context.attackingPlayer->IsPendingSwitch())
	{
		curTurnState = TurnSwitchState::ContinueRound;
		return TurnSwitchState::ContinueRound;
	}
	else
	{
		curTurnState = TurnSwitchState::PromptUserForSwitch;
		return TurnSwitchState::PromptUserForSwitch;
	}
}

void TurnProcessor::SwapRoles()
{
	std::swap(m_context.attackingPlayer, m_context.defendingPlayer);
	std::swap(m_context.attackingPokemon, m_context.defendingPokemon);
	m_context.currentMove = (m_context.playerOneCurrentMove == m_context.currentMove) ? m_context.playerTwoCurrentMove : m_context.playerOneCurrentMove;
	m_context.currentMoveEffect = (m_context.playerOneCurrentMoveEffect == m_context.currentMoveEffect) ? m_context.playerTwoCurrentMoveEffect : m_context.playerOneCurrentMoveEffect;
}

TurnSwitchState TurnProcessor::CheckPendingSwitch()
{
	switch (curTurnState)
	{
		case TurnSwitchState::ContinueRound:
		{
			curTurnState = TurnSwitchState::ContinueRound;
			return TurnSwitchState::ContinueRound;
		}
		break;

		case TurnSwitchState::PromptUserForSwitch:
		{
			curTurnState = PromptUserForSwitch();
			return curTurnState;
		}
		break;

		case TurnSwitchState::WaitForSwitchInput:
		{
			curTurnState = ProcessSwitch();
			return curTurnState;
		}
		break;
	}

	return curTurnState;
}

TurnSwitchState TurnProcessor::PromptUserForSwitch()
{
	m_context.attackingPlayer->GetController().PromptForSwitch(*m_context.attackingPlayer, *m_context.defendingPlayer, *m_context.attackingPokemon, *m_context.defendingPokemon);

	return TurnSwitchState::WaitForSwitchInput;
}

TurnSwitchState TurnProcessor::ProcessSwitch()
{
	const bool playerNeedsSwitch = m_context.attackingPlayer->IsPendingSwitch();

	if (playerNeedsSwitch && !m_context.attackingPlayer->GetController().HasDecision())
	{
		return TurnSwitchState::WaitForSwitchInput;
	}

	if (playerNeedsSwitch)
	{
		PlayerDecisionOutcome decision = m_context.attackingPlayer->GetController().TakeDecision();

		m_context.attackingPlayer->SetPokemonToSwitchTo(decision.chosenPokemon);
	}

	ResolveSwitch(playerNeedsSwitch);

	return TurnSwitchState::ContinueRound;
}

void TurnProcessor::ResolveSwitch(bool playerNeedsSwitch)
{
	if (playerNeedsSwitch)
	{
		m_switchExecutor.ExecuteSwitch(*m_context.attackingPlayer, m_context.attackingPokemon);
		m_context.attackingPlayer->SetPendingSwitch(false);
	}
}