#pragma once

#include <vector>
#include <memory>

#include "../data/StringToTypes.h"

class Player;
class BattlePokemon;
struct pokemonMove;
enum class MoveEffect;

struct BattleStateFlags
{
    void ResetBattleFlags();

    enum class Effectiveness { No, Less, Normal, Super };

    Effectiveness currentEffectiveness{ Effectiveness::Normal };

    bool hit{ false };
    bool hitSubstitute{ false };
    bool isCriticalHit{ false };
};

struct BattleContext
{
    BattleContext(std::vector<std::unique_ptr<Player>>& vec_players);

    void ResetTurnState();
    void ResetBattleState();

    std::vector<Player*> vec_aiPlayers;

    std::vector<Player*> vec_outOfPokemon;

    BattleStateFlags flags;

    Player* playerOne;
    Player* playerTwo;

    BattlePokemon* playerOneCurrentPokemon{ nullptr };
    BattlePokemon* playerTwoCurrentPokemon{ nullptr };

    pokemonMove* playerOneCurrentMove{ nullptr };
    pokemonMove* playerTwoCurrentMove{ nullptr };

    PokemonType playerOneCurrentMoveType{ PokemonType::None };
    PokemonType playerTwoCurrentMoveType{ PokemonType::None };

    Player* attackingPlayer{ nullptr };
    Player* defendingPlayer{ nullptr };

    BattlePokemon* attackingPokemon{ nullptr };
    BattlePokemon* defendingPokemon{ nullptr };

    pokemonMove* currentMove{ nullptr };
    PokemonType currentMoveType{ PokemonType::None };

    const int HP_BAR_WIDTH{ 400 };

    int battleTurn{ 0 };

    unsigned int lastDamageApplied{};

    unsigned int damageTaken{};
    Category damageTakenCategory{ Category::None };

    unsigned int pixelsLost{};
    unsigned int prevPixels{ 400 };
    unsigned int damageInPixels{};

    unsigned int initialPowerMultiplier{ 10 };
    unsigned int effectiveness{ 4096 };
};