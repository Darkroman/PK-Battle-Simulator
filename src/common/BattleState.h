#pragma once

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