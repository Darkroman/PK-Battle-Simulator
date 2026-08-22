#include "Pokemon.h"

#include "../common/EnumUtils.h"

#include "PokemonID.h"
#include "StringToTypes.h"

#include <span>
#include <string_view>

PokemonID Pokemon::GetPokemonID() const
{
    return e_id;
}

unsigned int Pokemon::GetNationalDexNumber() const
{
    return EnumIndex(e_id);
}

size_t Pokemon::GetPokemonIndex() const
{
    return IDToIndex(e_id);
}

std::string_view Pokemon::GetName() const
{
    return m_name;
}

unsigned int Pokemon::GetBaseHP() const
{
    return m_basehp;
}

unsigned int Pokemon::GetBaseAttack() const
{
    return m_baseattack;
}

unsigned int Pokemon::GetBaseDefense() const
{
    return m_basedefense;
}

unsigned int Pokemon::GetBaseSpecialAttack() const
{
    return m_basespecialattack;
}

unsigned int Pokemon::GetBaseSpecialDefense() const
{
    return m_basespecialdefense;
}

unsigned int Pokemon::GetBaseSpeed() const
{
    return m_basespeed;
}

std::string_view Pokemon::GetFirstType() const
{
    return TypeToString(e_type1);
}

PokemonType Pokemon::GetFirstTypeEnum() const
{
    return e_type1;
}

std::string_view Pokemon::GetSecondType() const
{
    return TypeToString(e_type2);
}

PokemonType Pokemon::GetSecondTypeEnum() const
{
    return e_type2;
}

int Pokemon::GetPokemonWeightHg() const
{
    return m_weight;
}

double Pokemon::GetPokemonWeightKg() const
{
    return static_cast<double>(m_weight) / 10;
}

std::span<const size_t> Pokemon::GetMoveList() const
{
    return m_movelist;
}

bool Pokemon::CheckPokemonMoveList(size_t movenum) const
{
    ++movenum;

    for (auto index = m_movelist.begin(); index != m_movelist.end(); ++index)
    {
        if (movenum == *index)
            return true;
    }
    return false;
}

size_t Pokemon::FetchMoveNumber(size_t index) const
{
    return index - 1;
}