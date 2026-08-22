#pragma once

#include "../common/EnumUtils.h"

#include <array>
#include <string_view>
#include <utility>

enum class Category // Used in Moves
{
    Physical = 0,
    Special,
    Status,
    None,
    Count
};

constexpr auto NumCategories = std::to_underlying(Category::Count);

constexpr std::array<std::string_view, NumCategories> kCategoryNames{
    "Physical", "Special", "Status", "None" };

constexpr std::string_view CategoryToString(Category category)
{
    return kCategoryNames[EnumIndex(category)];
}

enum class PokemonType // Used in Moves, Pokemon, and BattlePokemon
{
    Normal = 0,
    Fire,
    Water,
    Grass,
    Electric,
    Ice,
    Fighting,
    Poison,
    Ground,
    Flying,
    Psychic,
    Bug,
    Rock,
    Ghost,
    Dragon,
    Dark,
    Steel,
    Fairy,
    None,
    Count
};

constexpr auto NumTypes = std::to_underlying(PokemonType::Count);

constexpr std::array<std::string_view, NumTypes> kTypeNames{
    "Normal", "Fire", "Water", "Grass", "Electric", "Ice",
    "Fighting", "Poison", "Ground", "Flying", "Psychic", "Bug",
    "Rock", "Ghost", "Dragon", "Dark", "Steel", "Fairy", "None"
};

constexpr std::string_view TypeToString(PokemonType type)
{
    return kTypeNames[EnumIndex(type)];
}