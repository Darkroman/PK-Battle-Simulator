// Move data layout in movedex.txt is as follows:
// Index number, name, type, category, priority, secondary effect flag, secondary effect chance, pp, max pp, power, accuracy.
// Each bool corresponds with whether it:
// Makes contact, affected by Protect, affected by Magic Coat, affected by Snatch, affected by Mirror Move, affected by King's Rock, sound based, bypasses substitute

#pragma once

#include <string_view>

enum class Category;
enum class MoveEffect;
enum class MoveID;
enum class PokemonType;

class Move
{
public:
    constexpr Move
    (MoveID id, std::string_view name,
        PokemonType type, Category category,
        int priority, MoveEffect moveEffectEnum, int effectChance,
        int pp, unsigned int power, int accuracy,
        bool contact, bool protect, bool magicCoat,
        bool snatch, bool mirrorMove, bool kingRock, bool soundBased, bool bypassSubstitute)
        : e_id{ id }, m_name{ name },
        e_type{ type }, e_category{ category },
        m_priority{ priority }, e_moveEffect{ moveEffectEnum }, m_effectChance{ effectChance },
        m_pp{ pp }, m_power{ power }, m_accuracy{ accuracy },
        b_DoesMakeContact{ contact }, b_IsAffectedByProtect{ protect }, b_IsAffectedByMagicCoat{ magicCoat },
        b_IsAffectedBySnatch{ snatch }, b_IsAffectedByMirrorMove{ mirrorMove }, b_IsAffectedByKingRock{ kingRock }, b_isSoundBased{ soundBased }, b_bypassSubstitute{ bypassSubstitute }
    {
    }

    MoveID                  GetMoveID() const;
    unsigned int     GetMovedexNumber() const;
    size_t               GetMoveIndex() const;
    std::string_view          GetName() const;
    
    std::string_view     GetCategory() const;
    Category         GetCategoryEnum() const;
    std::string_view     GetMoveType() const;
    PokemonType      GetMoveTypeEnum() const;
    
    int              GetPriority() const;
    MoveEffect GetMoveEffectEnum() const;
    int          GetEffectChance() const;
    
    int             GetPP() const;
    unsigned int GetPower() const;
    int       GetAccuracy() const;

    bool        DoesMakeContact() const;
    bool    IsAffectedByProtect() const;
    bool  IsAffectedByMagicCoat() const;
    bool     IsAffectedBySnatch() const;
    bool IsAffectedByMirrorMove() const;
    bool   IsAffectedByKingRock() const;
    bool           IsSoundBased() const;
    bool    CanBypassSubstitute() const;

private:
    std::string_view      m_name;

    MoveID                  e_id;
    PokemonType           e_type;
    Category          e_category;
    MoveEffect      e_moveEffect;

    int               m_priority;
    int           m_effectChance;

    int                     m_pp;
    unsigned int         m_power;
    int               m_accuracy;

    bool        b_DoesMakeContact;
    bool    b_IsAffectedByProtect;
    bool  b_IsAffectedByMagicCoat;
    bool     b_IsAffectedBySnatch;
    bool b_IsAffectedByMirrorMove;
    bool   b_IsAffectedByKingRock;
    bool           b_isSoundBased;
    bool       b_bypassSubstitute;
};