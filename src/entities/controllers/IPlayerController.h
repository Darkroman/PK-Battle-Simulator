#pragma once

#include <memory>

#include "../../data/MoveID.h"
#include "../PlayerDecisionOutcome.h"
#include "../../entities/pokemonMove.h"

class Player;
class BattlePokemon;
class RandomEngine;

class IPlayerController
{
public:
	virtual std::unique_ptr<IPlayerController> clone() const = 0;

	virtual ~IPlayerController() = default;
	virtual PlayerDecisionOutcome ChooseAction(Player&, const Player&, BattlePokemon&, const BattlePokemon&, RandomEngine&) = 0;
	virtual void SkipChooseAction() = 0;
	virtual BattlePokemon* PromptForSwitch(Player&, const Player&, const BattlePokemon&, const BattlePokemon&) = 0;
	virtual bool HasDecision() = 0;
	virtual PlayerDecisionOutcome TakeDecision() = 0;

protected:
	static pokemonMove& GetStruggle()
	{
		static pokemonMove struggleInstance{ MoveID::Struggle };
		return struggleInstance;
	}

	bool b_hasDecision{ false };
	PlayerDecisionOutcome m_decisionOutcome{};
};