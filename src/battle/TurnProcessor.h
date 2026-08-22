#pragma once

class BattleCalculations;
class MoveExecutor;
class StatusEffectProcessor;
class SwitchExecutor;
class WinChecker;
struct BattleContext;

enum class TurnSwitchState
{
	None,
	ContinueRound,
	Victory,
	PromptUserForSwitch,
	WaitForSwitchInput
};

class TurnProcessor
{
public:
	TurnProcessor(BattleContext&, BattleCalculations&, StatusEffectProcessor&, WinChecker&, SwitchExecutor&, MoveExecutor&);

	void DetermineTurnOrder();
	TurnSwitchState ExecuteTurn();
	void SwapRoles();
	TurnSwitchState CheckPendingSwitch();

private:
	TurnSwitchState PromptUserForSwitch();
	TurnSwitchState ProcessSwitch();
	void ResolveSwitch(bool playerNeedsSwitch);

	BattleContext& m_context;
	BattleCalculations& m_calculations;
	StatusEffectProcessor& m_statusProcessor;
	WinChecker& m_winChecker;
	SwitchExecutor& m_switchExecutor;
	MoveExecutor& m_moveExecutor;

	TurnSwitchState curTurnState{ TurnSwitchState::None };
};