#include <string_view>

#include "pokemonMove.h"

#include "../data/MoveID.h"
#include "../data/Move.h"
#include "../data/Database.h"
#include "../data/StringToTypes.h"
#include "../moves/MoveEffectEnums.h"

pokemonMove::pokemonMove() {}

pokemonMove::pokemonMove(MoveID id) :
    mp_move(Database::GetPointerToBaseMoveByID(id)),
    m_currentPP(1),
    m_maxPP(1)
{

}

bool pokemonMove::HasMove() const
{
    return mp_move != nullptr;
}

bool pokemonMove::IsActive() const
{
    return mp_move != nullptr &&
        m_currentPP > 0 &&
        !b_isDisabled;
}

void pokemonMove::SetMovePointer(const Move* move)
{
    mp_move = move;
}

const Move* pokemonMove::GetMovePointer() const
{
    return mp_move;
}

void pokemonMove::ResetMove()
{
    mp_move = nullptr;
    m_currentPP = 0;
    m_maxPP = 0;
    b_isDisabled = false;
    b_isMimicked = false;
}

void pokemonMove::DeductPP()
{
    m_currentPP -= 1;
}

MoveID pokemonMove::GetMoveID() const
{
    return mp_move->GetMoveID();
}

size_t pokemonMove::GetMovedexNumber() const
{
    return mp_move->GetMovedexNumber();
}

size_t pokemonMove::GetMoveIndex() const
{
    return mp_move->GetMoveIndex();
}

std::string_view pokemonMove::GetName() const
{
    return mp_move->GetName();
}

std::string_view pokemonMove::GetCategory() const
{
    return mp_move->GetCategory();
}

Category pokemonMove::GetCategoryEnum() const
{
    return mp_move->GetCategoryEnum();
}

std::string_view pokemonMove::GetMoveType() const
{
    return mp_move->GetMoveType();
}

PokemonType pokemonMove::GetMoveTypeEnum() const
{
    return mp_move->GetMoveTypeEnum();
}

int pokemonMove::GetPriority() const
{
    return mp_move->GetPriority();
}

MoveEffect pokemonMove::GetMoveEffectEnum() const
{
    return mp_move->GetMoveEffectEnum();
}

int pokemonMove::GetEffectChance() const
{
    return mp_move->GetEffectChance();
}

int pokemonMove::GetPP() const
{
    return mp_move->GetPP();
}

unsigned int pokemonMove::GetPower() const
{
    return mp_move->GetPower();
}

int pokemonMove::GetAccuracy() const
{
    return mp_move->GetAccuracy();
}

bool pokemonMove::DoesMakeContact() const
{
    return mp_move->DoesMakeContact();
}

bool pokemonMove::IsAffectedByProtect() const
{
    return mp_move->IsAffectedByProtect();
}

bool pokemonMove::IsAffectedByMagicCoat() const
{
    return mp_move->IsAffectedByMagicCoat();
}

bool pokemonMove::IsAffectedBySnatch() const
{
    return mp_move->IsAffectedBySnatch();
}

bool pokemonMove::IsAffectedByMirrorMove() const
{
    return mp_move->IsAffectedByMirrorMove();
}

bool pokemonMove::IsAffectedByKingRock() const
{
    return mp_move->IsAffectedByKingRock();
}

bool pokemonMove::IsSoundBased() const
{
    return mp_move->IsSoundBased();
}

bool pokemonMove::CanBypassSubstitute() const
{
    return mp_move->CanBypassSubstitute();
}