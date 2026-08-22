#include "Move.h"

#include "../common/EnumUtils.h"

#include "MoveID.h"
#include "StringToTypes.h"

#include <string_view>

MoveID Move::GetMoveID() const
{
    return e_id;
}

unsigned int Move::GetMovedexNumber() const
{
    return EnumIndex(e_id);
}

size_t Move::GetMoveIndex() const
{
    return IDToIndex(e_id);
}

std::string_view Move::GetName() const
{
    return m_name;
}

std::string_view Move::GetCategory() const
{
    return CategoryToString(e_category);
}

Category Move::GetCategoryEnum() const
{
    return e_category;
}

std::string_view Move::GetMoveType() const
{
    return TypeToString(e_type);
}

PokemonType Move::GetMoveTypeEnum() const
{
    return e_type;
}

int Move::GetPriority() const
{
    return m_priority;
}

MoveEffect Move::GetMoveEffectEnum() const
{
    return e_moveEffect;
}

int Move::GetEffectChance() const
{
    return m_effectChance;
}

int Move::GetPP() const
{
    return m_pp;
}

unsigned int Move::GetPower() const
{
    return m_power;
}

int Move::GetAccuracy() const
{
    return m_accuracy;
}

bool Move::DoesMakeContact() const
{
    return b_DoesMakeContact;
}

bool Move::IsAffectedByProtect() const
{
    return b_IsAffectedByProtect;
}

bool Move::IsAffectedByMagicCoat() const
{
    return b_IsAffectedByMagicCoat;
}

bool Move::IsAffectedBySnatch() const
{
    return b_IsAffectedBySnatch;
}

bool Move::IsAffectedByMirrorMove() const
{
    return b_IsAffectedByMirrorMove;
}

bool Move::IsAffectedByKingRock() const
{
    return b_IsAffectedByKingRock;
}

bool Move::IsSoundBased() const
{
    return b_isSoundBased;
}

bool Move::CanBypassSubstitute() const
{
    return b_bypassSubstitute;
}