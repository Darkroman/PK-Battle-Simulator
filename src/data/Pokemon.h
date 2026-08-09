#pragma once

#include <span>
#include <string_view>

enum class PokemonID;
enum class PokemonType;

class Pokemon
{
public:
    constexpr Pokemon
    (PokemonID id, std::string_view name,
        unsigned int basehp, unsigned int baseattack, unsigned int basedefense,
        unsigned int basespecialattack, unsigned int basespecialdefense, unsigned int basespeed,
        PokemonType type1, PokemonType type2, unsigned int weight, std::span<const size_t> moves)
        : e_id{ id }, m_name{ name },
        m_basehp{ basehp }, m_baseattack{ baseattack }, m_basedefense{ basedefense },
        m_basespecialattack{ basespecialattack }, m_basespecialdefense{ basespecialdefense }, m_basespeed{ basespeed },
        e_type1{ type1 }, e_type2{ type2 }, m_weight{ weight }, m_movelist(moves)
    {
    }

    PokemonID                   GetPokemonID() const;
    unsigned int        GetNationalDexNumber() const;
    size_t                   GetPokemonIndex() const;
    std::string_view                 GetName() const;
    unsigned int                   GetBaseHP() const;
    unsigned int               GetBaseAttack() const;
    unsigned int              GetBaseDefense() const;
    unsigned int        GetBaseSpecialAttack() const;
    unsigned int       GetBaseSpecialDefense() const;
    unsigned int                GetBaseSpeed() const;
    std::string_view            GetFirstType() const;
    PokemonType             GetFirstTypeEnum() const;
    std::string_view           GetSecondType() const;
    PokemonType            GetSecondTypeEnum() const;
    std::span<const size_t>      GetMoveList() const;

    int    GetPokemonWeightHg() const;
    double GetPokemonWeightKg() const;

    bool CheckPokemonMoveList(size_t) const;
    size_t    FetchMoveNumber(size_t) const;

private:
    std::span<const size_t> m_movelist;
    std::string_view            m_name;

    PokemonID                     e_id;
    unsigned int              m_basehp;
    unsigned int          m_baseattack;
    unsigned int         m_basedefense;
    unsigned int   m_basespecialattack;
    unsigned int  m_basespecialdefense;
    unsigned int           m_basespeed;
    PokemonType                e_type1;
    PokemonType                e_type2;
    unsigned int              m_weight;
};