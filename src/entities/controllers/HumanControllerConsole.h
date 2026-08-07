#pragma once

#include <memory>

#include "IPlayerController.h"

struct pokemonMove;
struct PlayerDecisionOutcome;
class Player;
class BattlePokemon;
class RandomEngine;
enum class BattleAction;

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
	pokemonMove* FightAction(const Player&, BattlePokemon&, const BattlePokemon&);
	BattlePokemon* SwitchAction(Player&, const BattlePokemon&);
	BattleAction ForfeitAction(const Player&);
};