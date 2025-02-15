#pragma once

#include <string>
#include <map>

//enum class PokemonType;

enum class PokemonType // Used in Moves, Pokemon, and BattlePokemon
{
    Normal,
    Fire,
    Water,
    Electric,
    Grass,
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
    None
};

using mapOfStringsToPokemonTypes = std::map<std::string_view, PokemonType>;

PokemonType ConvertStringToPokemonType(std::string_view);