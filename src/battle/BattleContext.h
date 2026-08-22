#pragma once

#include "../data/StringToTypes.h"

#include <memory>
#include <vector>

class BattlePokemon;
class Player;
struct PokemonMoveSlot;

struct BattleStateFlags
{
    void ResetBattleFlags();

    bool hit{ false };
    bool hitSubstitute{ false };
    bool isCriticalHit{ false };
    bool moveWasUsed{ false };
};

struct BattleContext
{
    BattleContext(std::vector<std::unique_ptr<Player>>& vec_players);

    void ResetTurnState();
    void ResetContextState();

    std::vector<Player*> vec_aiPlayers;

    std::vector<Player*> vec_outOfPokemon;

    BattleStateFlags flags;

    Player* playerOne;
    Player* playerTwo;

    BattlePokemon* playerOneCurrentPokemon{ nullptr };
    BattlePokemon* playerTwoCurrentPokemon{ nullptr };

    PokemonMoveSlot* playerOneCurrentMove{ nullptr };
    PokemonMoveSlot* playerTwoCurrentMove{ nullptr };

    Player* attackingPlayer{ nullptr };
    Player* defendingPlayer{ nullptr };

    BattlePokemon* attackingPokemon{ nullptr };
    BattlePokemon* defendingPokemon{ nullptr };

    PokemonMoveSlot* currentMove{ nullptr };
    PokemonMoveSlot* lastDamagingMove{ nullptr };

    const int HP_BAR_WIDTH{ 400 };

    unsigned int battleTurn{ 0 };

    unsigned int lastDamageApplied{};

    unsigned int damageTaken{};
    Category damageTakenCategory{ Category::None };

    unsigned int pixelsLost{};
    unsigned int prevPixels{ 400 };
    unsigned int damageInPixels{};

    unsigned int initialPowerMultiplier{ 10 };
    unsigned int effectiveness{ 4096 };
};