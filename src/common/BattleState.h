#pragma once

enum class BattleState;

struct BattleRunResult
{
	BattleState state{};
	bool playEvents{};
};

enum class BattleState
{
	None,
	StartBattle,
	DisplayFightingPokemon,
	BeginChooseAction,
	WaitForPlayerInput,
	DetermineTurnOrder,
	ProcessTurn,
	PendingMidTurnSwitch,
	SwapRoles,
	ProcessPostTurn,
	CheckActivePokemonFaints,
	PromptUsersForSwitch,
	WaitForSwitchInput,
	ProcessSwitches,
	Cleanup,
	Victory
};

enum class CurrentRoundActor
{
	First,
	Second
};