#pragma once

class Player;
class BattlePokemon;
struct pokemonMove;
class RandomEngine;
class AIController;

namespace AISwitchLogic
{
	bool WantsToSwitch(const Player&, const Player&, const BattlePokemon&, const BattlePokemon&, RandomEngine&);

	BattlePokemon* ChooseSwitch(Player&, const Player&, const BattlePokemon&, const BattlePokemon&);

	BattlePokemon* ChoosePostKOSwitch(Player&, const Player&, const BattlePokemon&, const BattlePokemon&);

	bool IsMoveSuperEffective(const AIController&, const pokemonMove&, const BattlePokemon&);

	bool IsMoveAtMostEffective(const AIController&, const pokemonMove&, const BattlePokemon&);

	bool IsMoveAtLeastEffective(const AIController&, const pokemonMove&, const BattlePokemon&);

	bool IsMoveNotEffective(const AIController&, const pokemonMove&, const BattlePokemon&);

	bool IsMoveNotVeryEffective(const AIController&, const pokemonMove&, const BattlePokemon&);

	bool IsStatusMoveEffective(const AIController&, const Player&, const Player&, const pokemonMove&, const BattlePokemon&, const BattlePokemon&);

	unsigned int PokemonTypeEffectiveness(const AIController&, const BattlePokemon& source, const BattlePokemon& target);
}