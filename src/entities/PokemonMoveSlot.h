#pragma once

#include <string_view>

enum class Category;
enum class MoveEffect;
enum class MoveID;
enum class PokemonType;
class Move;


struct PokemonMoveSlot
{
public:
    PokemonMoveSlot();
    PokemonMoveSlot(MoveID);

    bool HasMove() const;
    bool IsActive() const;

    void SetMovePointer(const Move*);
    const Move* GetMovePointer() const;
    void ResetMove();

    void DeductPP();

    MoveID            GetMoveID() const;
    size_t     GetMovedexNumber() const;
    size_t         GetMoveIndex() const;
    std::string_view    GetName() const;

    std::string_view GetCategory() const;
    Category     GetCategoryEnum() const;
    std::string_view GetMoveType() const;
    PokemonType  GetMoveTypeEnum() const;

    int              GetPriority() const;
    MoveEffect GetMoveEffectEnum() const;
    int          GetEffectChance() const;

    int                GetPP() const;
    unsigned int    GetPower() const;
    int          GetAccuracy() const;

    bool        DoesMakeContact() const;
    bool    IsAffectedByProtect() const;
    bool  IsAffectedByMagicCoat() const;
    bool     IsAffectedBySnatch() const;
    bool IsAffectedByMirrorMove() const;
    bool   IsAffectedByKingRock() const;
    bool           IsSoundBased() const;
    bool    CanBypassSubstitute() const;

private:
    const Move* mp_move{ nullptr };

public:
    int m_currentPP{ 0 };
    int m_maxPP{ 0 };

    bool b_isDisabled{ false };
    bool b_isMimicked{ false };
};