#pragma once

#include "IPlayerController.h"

#include <memory>

enum class BattleAction;
class BattlePokemon;
class Player;
class RandomEngine;
struct PlayerDecisionOutcome;
struct PokemonMoveSlot;

class HumanControllerConsole : public IPlayerController
{
public:
	HumanControllerConsole() = default;
	HumanControllerConsole(const HumanControllerConsole& other) = default;

	std::unique_ptr<IPlayerController> clone() const override;

	PlayerDecisionOutcome ChooseAction(Player&, const Player&, BattlePokemon&, const BattlePokemon&, RandomEngine&) override;
	PlayerDecisionOutcome ChooseSwitch();
	void SkipChooseAction();
	BattlePokemon* PromptForSwitch(Player&, const Player&, const BattlePokemon&, const BattlePokemon&) override;
	bool HasDecision() override;
	PlayerDecisionOutcome TakeDecision() override;

private:
	PokemonMoveSlot* FightAction(const Player&, const Player&, BattlePokemon&, const BattlePokemon&);
	BattlePokemon* SwitchAction(Player&, const BattlePokemon&, bool);
	BattleAction ForfeitAction(const Player&);
};