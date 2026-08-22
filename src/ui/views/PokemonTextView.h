#pragma once

#include <string_view>

class BattlePokemon;
class Player;
struct PokemonMoveSlot;

namespace PokemonTextView
{
    void DisplayStats(const BattlePokemon&);

    void DisplayIVs(const BattlePokemon&);
    void DisplayEVs(const BattlePokemon&);

    void DisplayLearnableMoves(const BattlePokemon&);
    void DisplayLearnedMoves(const BattlePokemon&);
    void DisplayLearnedMovesExpanded(const BattlePokemon&);
    void DisplayMovesInBattle(const Player&, const Player&, const BattlePokemon&, const BattlePokemon&);

    void DisplayPlayerPokemon(const Player&);
    std::string_view DisplayPokemonStatus(const BattlePokemon&);

    std::string_view CalculateStatusMoveEffectiveness(const Player&, const Player&, const BattlePokemon&, const BattlePokemon&, const PokemonMoveSlot&);
    std::string_view CalculateDamageMoveEffectiveness(const BattlePokemon&, const PokemonMoveSlot&);
}