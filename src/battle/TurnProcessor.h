#pragma once

struct BattleContext;
class BattleCalculations;
class StatusEffectProcessor;
class WinChecker;
class SwitchExecutor;
class MoveExecutor;

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