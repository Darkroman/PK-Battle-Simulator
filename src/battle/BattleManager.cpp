#include <utility>

#include "BattleManager.h"

#include "BattleContext.h"
#include "RandomEngine.h"
#include "BattleAction.h"
#include "TurnProcessor.h"
#include "../common/BattleState.h"
#include "../ui/interfaces/IBattleAnnouncerUI.h"
#include "../ui/interfaces/IMoveResultsUI.h"
#include "../ui/interfaces/IStatusEffectUI.h"
#include "../data/StringToTypes.h"
#include "../entities/PlayerDecisionOutcome.h"
#include "../entities/BattlePokemon.h"
#include "../entities/Player.h"
#include "../entities/controllers/IPlayerController.h"
#include "../entities/controllers/BattleAIUpdateRoutines.h"

BattleManager::BattleManager(BattleContext& context, RandomEngine& rng, IBattleAnnouncerUI& battleAnnouncerUI, IMoveResultsUI& moveResultsUI, IStatusEffectUI& statusEffectUI)
	: m_context(context)
	, m_rng(rng)
	, m_battleAnnouncerUI(battleAnnouncerUI)
	, m_moveResultsUI(moveResultsUI)
	, m_statusEffectUI(statusEffectUI)
	, m_calculations(context, rng)
	, m_switchExecutor(context, moveResultsUI)
	, m_winChecker(context)
	, m_statusEffectProcessor(context, rng, statusEffectUI)
	, m_moveExecutor(context, m_calculations, m_statusEffectProcessor, moveResultsUI, statusEffectUI, rng)
	, m_turnProcessor(context, m_calculations, m_statusEffectProcessor, m_winChecker, m_switchExecutor, m_moveExecutor)
	, m_postTurnProcessor(context, m_calculations, statusEffectUI, m_statusEffectProcessor, m_winChecker, m_switchExecutor)
{
}

BattleRunResult BattleManager::RunBattle()
{
	bool playEvents{};

	switch (curBattleState)
	{
		case BattleState::StartBattle:
		{
			// Returns BattleState::DisplayFightingPokemon
			curBattleState = StartBattle();
		}
		break;

		case BattleState::DisplayFightingPokemon:
		{
			// Returns BattleState::BeginChooseAction
			curBattleState = DisplayFightingPokemon();
		}
		break;

		case BattleState::BeginChooseAction:
		{
			// Returns BattleState::WaitForPlayerInput
			curBattleState = BeginChooseAction();
		}
		break;

		case BattleState::WaitForPlayerInput:
		{
			// Returns either BattleState::WaitForPlayerInput or BattleState::DetermineTurnOrder
			curBattleState = ApplyPlayerDecisions();
		}
		break;

		case BattleState::DetermineTurnOrder:
		{
			// Returns BattleState::ProcessTurn or BattleState::Victory
			curBattleState = DetermineTurnOrder();
		}
		break;

		case BattleState::ProcessTurn:
		{
			// Returns either BattleState::PendingMidTurnSwitch, BattleState::SwapRoles, BattleState::ProcessPostTurn or BattleState::Victory
			curBattleState = ProcessTurn();

			if (curBattleState == BattleState::PendingMidTurnSwitch || curBattleState == BattleState::Victory)
			{
				playEvents = true;
			}
		}
		break;

		case BattleState::SwapRoles:
		{
			// Returns BattleState::ProcessTurn
			curBattleState = SwapRoles();
		}
		break;

		case BattleState::PendingMidTurnSwitch:
		{
			// Returns either BattleState::SwapRoles or BattleState::PendingMidTurnSwitch
			curBattleState = CheckMidTurnPendingSwitch();

			if (curBattleState == BattleState::SwapRoles)
			{
				playEvents = true;
			}
		}
		break;

		case BattleState::ProcessPostTurn:
		{
			// Returns either BattleState::CheckActivePokemonFaints or BattleState::Victory
			curBattleState = ProcessPostTurn();

			playEvents = true;
		}
		break;

		case BattleState::CheckActivePokemonFaints:
		{
			// Returns either BattleState::PromptUsersForSwitch or BattleState::Cleanup
			curBattleState = CheckActivePokemonFaints();

			if (curBattleState == BattleState::PromptUsersForSwitch)
			{
				playEvents = true;
			}
		}
		break;

		case BattleState::PromptUsersForSwitch:
		{
			// Returns BattleState::WaitForSwitchInput
			curBattleState = PromptUsersForSwitch();
		}
		break;

		case BattleState::WaitForSwitchInput:
		{
			// Returns either BattleState::WaitForSwitchInput or BattleState::Cleanup
			curBattleState = ProcessSwitches();

			if (curBattleState == BattleState::Cleanup)
			{
				playEvents = true;
			}
		}
		break;

		case BattleState::Cleanup:
		{
			// Returns BattleState::DisplayFightingPokemon
			curBattleState = Cleanup();
		}
		break;

		case BattleState::Victory:
		{

		}
	}

	return { curBattleState, playEvents };
}

void BattleManager::AssignFirstPokemon()
{
	for (auto& pokemon : m_context.playerOne->GetBeltArray())
	{
		if (pokemon.HasPokemon())
		{
			m_context.playerOneCurrentPokemon = &pokemon;
			break;
		}
	}

	for (auto& pokemon : m_context.playerTwo->GetBeltArray())
	{
		if (pokemon.HasPokemon())
		{
			m_context.playerTwoCurrentPokemon = &pokemon;
			break;
		}
	}
}

BattleState BattleManager::StartBattle()
{
	AssignFirstPokemon();

	BattleAIUpdateRoutines::InitAIPlayers(m_context);

	m_battleAnnouncerUI.ThrowOutFirstPokemon(m_context);

	return BattleState::DisplayFightingPokemon;
}

BattleState BattleManager::DisplayFightingPokemon()
{
	++m_context.battleTurn;

	m_battleAnnouncerUI.DisplayTurnNumber(m_context.battleTurn);

	m_battleAnnouncerUI.DisplayFightingPokemon(m_context);

	return BattleState::BeginChooseAction;
}

BattleState BattleManager::BeginChooseAction()
{
	m_context.playerOne->UpdateTurnState(*m_context.playerOneCurrentPokemon);
	m_context.playerTwo->UpdateTurnState(*m_context.playerTwoCurrentPokemon);

	if (m_context.playerOneCurrentPokemon->IsCharging() || m_context.playerOneCurrentPokemon->IsRecharging() ||
		m_context.playerOneCurrentPokemon->IsRampaging() || m_context.playerOneCurrentPokemon->IsBiding())
	{
		m_context.playerOne->GetController().SkipChooseAction();
	}
	else
	{
		m_context.playerOne->GetController().ChooseAction(*m_context.playerOne, *m_context.playerTwo, *m_context.playerOneCurrentPokemon, *m_context.playerTwoCurrentPokemon, m_rng);
	}
	
	if (m_context.playerTwoCurrentPokemon->IsCharging() || m_context.playerTwoCurrentPokemon->IsRecharging() ||
		m_context.playerTwoCurrentPokemon->IsRampaging() || m_context.playerTwoCurrentPokemon->IsBiding())
	{
		m_context.playerTwo->GetController().SkipChooseAction();
	}
	else
	{
		m_context.playerTwo->GetController().ChooseAction(*m_context.playerTwo, *m_context.playerOne, *m_context.playerTwoCurrentPokemon, *m_context.playerOneCurrentPokemon, m_rng);
	}
	
	return BattleState::WaitForPlayerInput;
}

BattleState BattleManager::ApplyPlayerDecisions()
{
	if (!m_context.playerOne->GetController().HasDecision())
	{
		return BattleState::WaitForPlayerInput;
	}

	if (!m_context.playerTwo->GetController().HasDecision())
	{
		return BattleState::WaitForPlayerInput;
	}

	PlayerDecisionOutcome playerOneDecision = m_context.playerOne->GetController().TakeDecision();
	PlayerDecisionOutcome playerTwoDecision = m_context.playerTwo->GetController().TakeDecision();

	switch (playerOneDecision.action)
	{
	case BattleAction::Fight:
		m_context.playerOneCurrentMove = playerOneDecision.chosenMove;
		break;
		
	case BattleAction::SwitchPokemon:
		m_context.playerOneCurrentMove = nullptr;
		m_context.playerOne->SetIsSwitching(true);
		m_context.playerOne->SetPokemonToSwitchTo(playerOneDecision.chosenPokemon);
		break;

	case BattleAction::Forfeit:
		m_context.playerOne->SetForfeit(true);
		m_context.vec_outOfPokemon.emplace_back(m_context.playerOne);
		break;
	}

	switch (playerTwoDecision.action)
	{
	case BattleAction::Fight:
		m_context.playerTwoCurrentMove = playerTwoDecision.chosenMove;
		break;

	case BattleAction::SwitchPokemon:
		m_context.playerTwoCurrentMove = nullptr;
		m_context.playerTwo->SetIsSwitching(true);
		m_context.playerTwo->SetPokemonToSwitchTo(playerTwoDecision.chosenPokemon);
		break;

	case BattleAction::Forfeit:
		m_context.playerTwo->SetForfeit(true);
		m_context.vec_outOfPokemon.emplace_back(m_context.playerTwo);
		break;
	}

	return BattleState::DetermineTurnOrder;
}

void BattleManager::ApplyPlayerOneAction()
{
	if (m_context.playerOneCurrentPokemon->IsCharging() || m_context.playerOneCurrentPokemon->IsRecharging() ||
		m_context.playerOneCurrentPokemon->IsRampaging() || m_context.playerOneCurrentPokemon->IsBiding())
	{
		return;
	}

	PlayerDecisionOutcome decision{};

	decision = m_context.playerOne->GetController().ChooseAction(*m_context.playerOne, *m_context.playerTwo, *m_context.playerOneCurrentPokemon, *m_context.playerTwoCurrentPokemon, m_rng);

	switch (decision.action)
	{
	case BattleAction::Fight:
		m_context.playerOneCurrentMove = decision.chosenMove;
		break;

	case BattleAction::SwitchPokemon:
		m_context.playerOneCurrentMove = nullptr;
		m_context.playerOne->SetIsSwitching(true);
		m_context.playerOne->SetPokemonToSwitchTo(decision.chosenPokemon);
		break;

	case BattleAction::Forfeit:
		m_context.playerOne->SetForfeit(true);
		m_context.vec_outOfPokemon.emplace_back(m_context.playerOne);
		break;
	}
}

void BattleManager::ApplyPlayerTwoAction()
{
	if (m_context.playerTwoCurrentPokemon->IsCharging() || m_context.playerTwoCurrentPokemon->IsRecharging() ||
		m_context.playerTwoCurrentPokemon->IsRampaging() || m_context.playerTwoCurrentPokemon->IsBiding())
	{
		return;
	}

	PlayerDecisionOutcome decision{};

	decision = m_context.playerTwo->GetController().ChooseAction(*m_context.playerTwo, *m_context.playerOne, *m_context.playerTwoCurrentPokemon, *m_context.playerOneCurrentPokemon, m_rng);

	switch (decision.action)
	{
	case BattleAction::Fight:
		m_context.playerTwoCurrentMove = decision.chosenMove;
		break;

	case BattleAction::SwitchPokemon:
		m_context.playerTwoCurrentMove = nullptr;
		m_context.playerTwo->SetIsSwitching(true);
		m_context.playerTwo->SetPokemonToSwitchTo(decision.chosenPokemon);
		break;

	case BattleAction::Forfeit:
		m_context.playerTwo->SetForfeit(true);
		m_context.vec_outOfPokemon.emplace_back(m_context.playerTwo);
		break;
	}
}

BattleState BattleManager::DetermineTurnOrder()
{
	if (m_context.playerOne->HasForfeited() && m_context.playerTwo->HasForfeited())
	{
		return BattleState::Victory;
	}

	if (m_context.playerOne->HasForfeited())
	{
		m_winChecker.CheckWinCondition(*m_context.playerTwo, *m_context.playerOne);
		return BattleState::Victory;
	}

	if (m_context.playerTwo->HasForfeited())
	{
		m_winChecker.CheckWinCondition(*m_context.playerOne, *m_context.playerTwo);
		return BattleState::Victory;
	}

	m_turnProcessor.DetermineTurnOrder();

	curActor = CurrentRoundActor::First;

	return BattleState::ProcessTurn;
}

BattleState BattleManager::ProcessTurn()
{
	TurnSwitchState curTurnState{};

	curTurnState = m_turnProcessor.ExecuteTurn();

	if (m_context.flags.moveWasUsed)
	{
		BattleAIUpdateRoutines::RefineEnemyModel(m_context);
	}
	
	if (curTurnState == TurnSwitchState::Victory)
	{ 
		return BattleState::Victory;
	}

	if (curTurnState == TurnSwitchState::PromptUserForSwitch)
	{
		return BattleState::PendingMidTurnSwitch;
	}
	else if (curTurnState == TurnSwitchState::ContinueRound)
	{
		if (curActor == CurrentRoundActor::First)
		{
			if (!m_context.defendingPokemon->IsFainted())
			{
				return BattleState::SwapRoles;
			}
			else
			{
				return BattleState::ProcessPostTurn;
			}
		}
		else if (curActor == CurrentRoundActor::Second)
		{
			return BattleState::ProcessPostTurn;
		}
	}

	std::unreachable();
}

BattleState BattleManager::CheckMidTurnPendingSwitch()
{
	TurnSwitchState curTurnState = m_turnProcessor.CheckPendingSwitch();

	if (curTurnState == TurnSwitchState::PromptUserForSwitch || curTurnState == TurnSwitchState::WaitForSwitchInput)
	{
		return BattleState::PendingMidTurnSwitch;
	}
	else if (curTurnState == TurnSwitchState::ContinueRound)
	{
		if (curActor == CurrentRoundActor::First)
		{
			return BattleState::SwapRoles;
		}
		else if (curActor == CurrentRoundActor::Second)
		{
			return BattleState::ProcessPostTurn;
		}
	}

	std::unreachable();
}

BattleState BattleManager::SwapRoles()
{
	m_context.ResetTurnState();

	m_turnProcessor.SwapRoles();

	curActor = CurrentRoundActor::Second;

	if (!m_context.attackingPokemon->IsFainted())
	{
		m_statusEffectUI.NewLine();
	}

	return BattleState::ProcessTurn;
}

BattleState BattleManager::ProcessPostTurn()
{
	const bool attackerHasPendingEffect =
		(m_context.attackingPokemon->HasPendingPostTurnEffect() &&
		 !m_context.attackingPokemon->IsFainted()) ||
		m_context.attackingPlayer->HasPendingPostTurnEffect();

	const bool defenderHasPendingEffect = 
		(m_context.defendingPokemon->HasPendingPostTurnEffect() &&
		 !m_context.defendingPokemon->IsFainted()) ||
		m_context.defendingPlayer->HasPendingPostTurnEffect();

	if (attackerHasPendingEffect || defenderHasPendingEffect)
	{
		m_statusEffectUI.NewLine();
	}

	if (m_postTurnProcessor.ProcessAllPostTurnEffects())
	{ 
		return BattleState::Victory;
	}

	return BattleState::CheckActivePokemonFaints;
}

BattleState BattleManager::CheckActivePokemonFaints()
{
	if (m_context.attackingPokemon->IsFainted() || m_context.defendingPokemon->IsFainted())
	{
		return BattleState::PromptUsersForSwitch;
	}

	return BattleState::Cleanup;
}

BattleState BattleManager::PromptUsersForSwitch()
{
	if (m_context.playerOneCurrentPokemon->IsFainted())
	{
		m_context.playerOne->GetController().PromptForSwitch(*m_context.playerOne, *m_context.playerTwo, *m_context.playerOneCurrentPokemon, *m_context.playerTwoCurrentPokemon);
	}

	if (m_context.playerTwoCurrentPokemon->IsFainted())
	{
		m_context.playerTwo->GetController().PromptForSwitch(*m_context.playerTwo, *m_context.playerOne, *m_context.playerTwoCurrentPokemon, *m_context.playerOneCurrentPokemon);
	}

	return BattleState::WaitForSwitchInput;
}

BattleState BattleManager::ProcessSwitches()
{
	const bool playerOneNeedsSwitch = m_context.playerOneCurrentPokemon->IsFainted();

	const bool playerTwoNeedsSwitch = m_context.playerTwoCurrentPokemon->IsFainted();

	if (playerOneNeedsSwitch &&	!m_context.playerOne->GetController().HasDecision())
	{
		return BattleState::WaitForSwitchInput;
	}

	if (playerTwoNeedsSwitch &&	!m_context.playerTwo->GetController().HasDecision())
	{
		return BattleState::WaitForSwitchInput;
	}

	if (playerOneNeedsSwitch)
	{
		PlayerDecisionOutcome decision = m_context.playerOne->GetController().TakeDecision();

		m_context.playerOne->SetPokemonToSwitchTo(decision.chosenPokemon);
	}

	if (playerTwoNeedsSwitch)
	{
		PlayerDecisionOutcome decision = m_context.playerTwo->GetController().TakeDecision();

		m_context.playerTwo->SetPokemonToSwitchTo(decision.chosenPokemon);
	}

	ResolveSwitchDecisions(playerOneNeedsSwitch, playerTwoNeedsSwitch);

	return BattleState::Cleanup;
}

void BattleManager::ResolveSwitchDecisions(bool playerOneNeedsSwitch, bool playerTwoNeedsSwitch)
{
	if (playerOneNeedsSwitch && playerTwoNeedsSwitch)
	{
		m_postTurnProcessor.DeterminePostFaintSwitchOrder();

		m_switchExecutor.ExecuteSwitch(*m_context.attackingPlayer, m_context.attackingPokemon);

		m_switchExecutor.ExecuteSwitch(*m_context.defendingPlayer, m_context.defendingPokemon);
	}
	else if (playerOneNeedsSwitch)
	{
		m_switchExecutor.ExecuteSwitch( *m_context.playerOne, m_context.playerOneCurrentPokemon);
	}
	else if (playerTwoNeedsSwitch)
	{
		m_switchExecutor.ExecuteSwitch(*m_context.playerTwo, m_context.playerTwoCurrentPokemon);
	}
}

BattleState BattleManager::Cleanup()
{
	m_context.damageTaken = 0;
	m_context.damageTakenCategory = Category::None;

	m_context.ResetTurnState();

	m_battleAnnouncerUI.NewLine();

	return BattleState::DisplayFightingPokemon;
}

bool BattleManager::RunBattleSimulation()
{
	m_context.battleTurn = 0;

	AssignFirstPokemon();

	BattleAIUpdateRoutines::InitAIPlayers(m_context);

	while (true)
	{
		++m_context.battleTurn;

		m_battleAnnouncerUI.DisplayTurnNumber(m_context.battleTurn);

		m_context.playerOne->UpdateTurnState(*m_context.playerOneCurrentPokemon);
		m_context.playerTwo->UpdateTurnState(*m_context.playerTwoCurrentPokemon);

		ApplyPlayerOneAction();

		ApplyPlayerTwoAction();

		m_turnProcessor.DetermineTurnOrder();

		TurnSwitchState curTurnState = TurnSwitchState::ContinueRound;

		curTurnState = m_turnProcessor.ExecuteTurn();
		if (curTurnState == TurnSwitchState::Victory)
		{
			return true;
		}

		if (m_context.flags.moveWasUsed)
		{
			BattleAIUpdateRoutines::RefineEnemyModel(m_context);
		}

		if (m_context.attackingPlayer->IsPendingSwitch())
		{
			BattlePokemon* newPokemon = m_context.attackingPlayer->GetController().PromptForSwitch(*m_context.attackingPlayer, *m_context.defendingPlayer, *m_context.attackingPokemon, *m_context.defendingPokemon);
			m_context.attackingPlayer->SetPokemonToSwitchTo(newPokemon);

			m_switchExecutor.ExecuteSwitch(*m_context.attackingPlayer, m_context.attackingPokemon);
			m_context.attackingPlayer->SetPendingSwitch(false);
		}

		if (!m_context.defendingPokemon->IsFainted())
		{
			m_context.ResetTurnState();

			m_battleAnnouncerUI.NewLine();

			m_turnProcessor.SwapRoles();
		
			curTurnState = m_turnProcessor.ExecuteTurn();
			if (curTurnState == TurnSwitchState::Victory)
			{
				return true;
			}

			if (m_context.flags.moveWasUsed)
			{
				BattleAIUpdateRoutines::RefineEnemyModel(m_context);
			}

			if (m_context.attackingPlayer->IsPendingSwitch())
			{
				BattlePokemon* newPokemon = m_context.attackingPlayer->GetController().PromptForSwitch(*m_context.attackingPlayer, *m_context.defendingPlayer, *m_context.attackingPokemon, *m_context.defendingPokemon);
				m_context.attackingPlayer->SetPokemonToSwitchTo(newPokemon);

				m_switchExecutor.ExecuteSwitch(*m_context.attackingPlayer, m_context.attackingPokemon);
				m_context.attackingPlayer->SetPendingSwitch(false);
			}
		}

		m_battleAnnouncerUI.NewLine();

		if (m_postTurnProcessor.ProcessAllPostTurnEffects())
		{
			return true;
		}

		m_postTurnProcessor.ProcessPostKOSwitches();

		m_context.damageTaken = 0;
		m_context.damageTakenCategory = Category::None;

		m_context.ResetTurnState();
	}

	return true;
}

void BattleManager::ResetValues()
{
	m_context.ResetBattleState();

	m_context.playerOne->ResetValues();
	m_context.playerTwo->ResetValues();

	for (auto& pokemon : m_context.playerOne->GetBeltArray())
	{
		if (!pokemon.HasPokemon())
		{
			continue;
		}
		pokemon.ResetValues();
	}

	for (auto& pokemon : m_context.playerTwo->GetBeltArray())
	{
		if (!pokemon.HasPokemon())
		{
			continue;
		}
		pokemon.ResetValues();
	}

	BattleAIUpdateRoutines::ResetAIObservedMoves(m_context);
}