#pragma once

class AIController;
class BattlePokemon;
class Player;
class RandomEngine;
struct PokemonMoveSlot;

namespace AISwitchLogic
{
	bool WantsToSwitch(const Player&, const Player&, const BattlePokemon&, const BattlePokemon&, RandomEngine&);

	BattlePokemon* ChooseSwitch(Player&, const Player&, const BattlePokemon&, const BattlePokemon&);

	BattlePokemon* ChoosePostKOSwitch(Player&, const Player&, const BattlePokemon&, const BattlePokemon&);

	bool IsMoveSuperEffective(const AIController&, const PokemonMoveSlot&, const BattlePokemon&);

	bool IsMoveAtMostEffective(const AIController&, const PokemonMoveSlot&, const BattlePokemon&);

	bool IsMoveAtLeastEffective(const AIController&, const PokemonMoveSlot&, const BattlePokemon&);

	bool IsMoveNotEffective(const AIController&, const PokemonMoveSlot&, const BattlePokemon&);

	bool IsMoveNotVeryEffective(const AIController&, const PokemonMoveSlot&, const BattlePokemon&);

	bool IsStatusMoveEffective(const AIController&, const Player&, const Player&, const PokemonMoveSlot&, const BattlePokemon&, const BattlePokemon&);

	unsigned int PokemonTypeEffectiveness(const AIController&, const BattlePokemon& source, const BattlePokemon& target);
}