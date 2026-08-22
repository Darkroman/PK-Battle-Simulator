#include "PokemonMoveSlot.h"

#include "../data/Database.h"
#include "../data/Move.h"
#include "../data/MoveID.h"
#include "../data/StringToTypes.h"

#include "../moves/MoveEffectEnums.h"

#include <string_view>

PokemonMoveSlot::PokemonMoveSlot() {}

PokemonMoveSlot::PokemonMoveSlot(MoveID id) :
    mp_move(Database::GetPointerToBaseMoveByID(id)),
    m_currentPP(1),
    m_maxPP(1)
{

}

bool PokemonMoveSlot::HasMove() const
{
    return mp_move != nullptr;
}

bool PokemonMoveSlot::IsActive() const
{
    return mp_move != nullptr &&
        m_currentPP > 0 &&
        !b_isDisabled;
}

void PokemonMoveSlot::SetMovePointer(const Move* move)
{
    mp_move = move;
}

const Move* PokemonMoveSlot::GetMovePointer() const
{
    return mp_move;
}

void PokemonMoveSlot::ResetMove()
{
    mp_move = nullptr;
    m_currentPP = 0;
    m_maxPP = 0;
    b_isDisabled = false;
    b_isMimicked = false;
}

void PokemonMoveSlot::DeductPP()
{
    m_currentPP -= 1;
}

MoveID PokemonMoveSlot::GetMoveID() const
{
    return mp_move->GetMoveID();
}

size_t PokemonMoveSlot::GetMovedexNumber() const
{
    return mp_move->GetMovedexNumber();
}

size_t PokemonMoveSlot::GetMoveIndex() const
{
    return mp_move->GetMoveIndex();
}

std::string_view PokemonMoveSlot::GetName() const
{
    return mp_move->GetName();
}

std::string_view PokemonMoveSlot::GetCategory() const
{
    return mp_move->GetCategory();
}

Category PokemonMoveSlot::GetCategoryEnum() const
{
    return mp_move->GetCategoryEnum();
}

std::string_view PokemonMoveSlot::GetMoveType() const
{
    return mp_move->GetMoveType();
}

PokemonType PokemonMoveSlot::GetMoveTypeEnum() const
{
    return mp_move->GetMoveTypeEnum();
}

int PokemonMoveSlot::GetPriority() const
{
    return mp_move->GetPriority();
}

MoveEffect PokemonMoveSlot::GetMoveEffectEnum() const
{
    return mp_move->GetMoveEffectEnum();
}

int PokemonMoveSlot::GetEffectChance() const
{
    return mp_move->GetEffectChance();
}

int PokemonMoveSlot::GetPP() const
{
    return mp_move->GetPP();
}

unsigned int PokemonMoveSlot::GetPower() const
{
    return mp_move->GetPower();
}

int PokemonMoveSlot::GetAccuracy() const
{
    return mp_move->GetAccuracy();
}

bool PokemonMoveSlot::DoesMakeContact() const
{
    return mp_move->DoesMakeContact();
}

bool PokemonMoveSlot::IsAffectedByProtect() const
{
    return mp_move->IsAffectedByProtect();
}

bool PokemonMoveSlot::IsAffectedByMagicCoat() const
{
    return mp_move->IsAffectedByMagicCoat();
}

bool PokemonMoveSlot::IsAffectedBySnatch() const
{
    return mp_move->IsAffectedBySnatch();
}

bool PokemonMoveSlot::IsAffectedByMirrorMove() const
{
    return mp_move->IsAffectedByMirrorMove();
}

bool PokemonMoveSlot::IsAffectedByKingRock() const
{
    return mp_move->IsAffectedByKingRock();
}

bool PokemonMoveSlot::IsSoundBased() const
{
    return mp_move->IsSoundBased();
}

bool PokemonMoveSlot::CanBypassSubstitute() const
{
    return mp_move->CanBypassSubstitute();
}