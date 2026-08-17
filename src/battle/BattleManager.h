#pragma once

struct BattleContext;
class RandomEngine;
class IBattleAnnouncerUI;
class IMoveResultsUI;
class IStatusEffectUI;

#include "BattleCalculations.h"
#include "SwitchExecutor.h"
#include "WinChecker.h"
#include "StatusEffectProcessor.h"
#include "MoveExecutor.h"
#include "TurnProcessor.h"
#include "PostTurnEffectProcessor.h"
#include "BattleAction.h"
#include "../common/BattleState.h"

class BattleManager
{
public:
	BattleManager(BattleContext& context, RandomEngine& rng, IBattleAnnouncerUI& battleAnnouncerUI, IMoveResultsUI& moveResultsUI, IStatusEffectUI& statusEffectUI);

	BattleRunResult RunBattle();
	bool RunBattleSimulation();
	void ResetValues();

private:
	void AssignFirstPokemon();
	BattleState StartBattle();
	BattleState DisplayFightingPokemon();
	BattleState BeginChooseAction();
	BattleState ApplyPlayerDecisions();
	void ApplyPlayerOneAction();
	void ApplyPlayerTwoAction();
	BattleState DetermineTurnOrder();
	BattleState ProcessTurn();
	BattleState CheckMidTurnPendingSwitch();
	BattleState SwapRoles();
	BattleState ProcessPostTurn();
	BattleState CheckActivePokemonFaints();
	BattleState PromptUsersForSwitch();
	BattleState ProcessSwitches();
	BattleState Cleanup();
	void ResolveSwitchDecisions(bool playerOneNeedsSwitch, bool playerTwoNeedsSwitch);

private:
	BattleContext& m_context;
	RandomEngine& m_rng;
	IBattleAnnouncerUI& m_battleAnnouncerUI;
	IMoveResultsUI& m_moveResultsUI;
	IStatusEffectUI& m_statusEffectUI;

	BattleCalculations m_calculations;
	SwitchExecutor m_switchExecutor;
	WinChecker m_winChecker;
	StatusEffectProcessor m_statusEffectProcessor;
	MoveExecutor m_moveExecutor;
	TurnProcessor m_turnProcessor;
	PostTurnEffectProcessor m_postTurnProcessor;

	BattleAction e_battleAction{};
	BattleState curBattleState = BattleState::StartBattle;
	CurrentRoundActor curActor{};
};