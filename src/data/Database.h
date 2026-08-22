#pragma once

#include "../common/EnumUtils.h"

#include "Move.h"
#include "MoveDex.h"
#include "MoveID.h"
#include "Pokedex.h"
#include "Pokemon.h"
#include "PokemonID.h"

#include <span>

namespace Database
{
    constexpr std::span<const Pokemon> GetPokedexView()
    {
        return global_pokedex;
    }

    constexpr std::span<const Move> GetMovedexView()
    {
        return global_movedex;
    }

    constexpr const Pokemon* GetPointerToBasePokemonByIndex(size_t index)
    {
        return &(global_pokedex[index]);
    }

    constexpr const Pokemon* GetPointerToBasePokemonByID(PokemonID id)
    {
        return &(global_pokedex[IDToIndex(id)]);
    }

    constexpr const Move* GetPointerToBaseMoveByIndex(size_t index)
    {
        return &(global_movedex[index]);
    }

    constexpr const Move* GetPointerToBaseMoveByID(MoveID id)
    {
        return &(global_movedex[IDToIndex(id)]);
    }

    constexpr const Pokemon& GetBasePokemonByID(PokemonID id)
    {
        return global_pokedex[IDToIndex(id)];
    }

    constexpr const Pokemon& GetBasePokemonByIndex(size_t index)
    {
        return global_pokedex[index];
    }

    constexpr const Move& GetBaseMoveByID(MoveID id)
    {
        return global_movedex[IDToIndex(id)];
    }

    constexpr const Move& GetBaseMoveByIndex(size_t index)
    {
        return global_movedex[index];
    }
};