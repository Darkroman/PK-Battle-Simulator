#pragma once

#include "../battle/BattleAction.h"

class BattlePokemon;
struct PokemonMoveSlot;

struct PlayerDecisionOutcome
{
    BattleAction action{ BattleAction::None };
    PokemonMoveSlot* chosenMove{ nullptr };
    BattlePokemon* chosenPokemon{ nullptr };
};