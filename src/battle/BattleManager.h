#pragma once

#include "../common/BattleState.h"

#include "BattleAction.h"
#include "BattleCalculations.h"
#include "BattleContext.h"
#include "MoveExecutor.h"
#include "PostTurnEffectProcessor.h"
#include "StatusEffectProcessor.h"
#include "SwitchExecutor.h"
#include "TurnProcessor.h"
#include "WinChecker.h"

#include <memory>
#include <vector>

class Player;
class IBattleAnnouncerUI;
class IMoveResultsUI;
class IStatusEffectUI;
class RandomEngine;

class BattleManager
{
public:
	BattleManager(std::vector<std::unique_ptr<Player>>& players, RandomEngine& rng, IBattleAnnouncerUI& battleAnnouncerUI, IMoveResultsUI& moveResultsUI, IStatusEffectUI& statusEffectUI);

	void PresetupBattle();
	BattleRunResult RunBattle();
	void EndBattle();
	bool RunBattleSimulation();
	void ResetBattleState();
	unsigned int GetTotalTurns() const;

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
	std::vector<std::unique_ptr<Player>>& m_players;
	RandomEngine& m_rng;
	IBattleAnnouncerUI& m_battleAnnouncerUI;
	IMoveResultsUI& m_moveResultsUI;
	IStatusEffectUI& m_statusEffectUI;

	BattleContext m_context;
	BattleCalculations m_calculations;
	StatusEffectProcessor m_statusEffectProcessor;
	WinChecker m_winChecker;
	SwitchExecutor m_switchExecutor;
	MoveExecutor m_moveExecutor;
	TurnProcessor m_turnProcessor;
	PostTurnEffectProcessor m_postTurnProcessor;

	BattleAction e_battleAction{};
	BattleState curBattleState = BattleState::PresetupBattle;
	CurrentRoundActor curActor{};
};