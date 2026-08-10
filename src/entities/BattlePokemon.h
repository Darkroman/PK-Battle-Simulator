#pragma once

#include <array>
#include <string>
#include <string_view>
#include <span>

enum class PokemonType;
enum class MoveID;
class Pokemon;
class Move;

#include "pokemonMove.h"

#include "../common/PartyEditResults.h"

enum struct Status { Normal = 0, Burned, Frozen, Paralyzed, Poisoned, Badly_Poisoned, Sleeping };

class BattlePokemon
{
public:
    struct DetransformData
    {
        DetransformData();

        void BackupOriginalPokemonData(BattlePokemon*);

        std::array<pokemonMove, 4> m_array_moves{};

        const Pokemon* mp_pokemon{ nullptr };

        PokemonType m_type1e{};
        PokemonType m_type2e{};

        unsigned int m_attackstage{ 0 };
        unsigned int m_defensestage{ 0 };
        unsigned int m_specialattackstage{ 0 };
        unsigned int m_specialdefensestage{ 0 };
        unsigned int m_speedstage{ 0 };
        unsigned int m_evasionstage{ 0 };
        unsigned int m_accuracystage{ 0 };
        unsigned int m_criticalhitstage{ 0 };

        unsigned int m_attack{ 0 };
        unsigned int m_defense{ 0 };
        unsigned int m_specialAttack{ 0 };
        unsigned int m_specialDefense{ 0 };
        unsigned int m_speed{ 0 };

        bool b_hasFocusEnergy{ false };

        unsigned int m_moveCount{ 0 };
    };

public:

    const Pokemon* GetPokemonDatabasePointer() const;

    SetPokemonOutcome SetPokemon(std::string_view);
    void ReleasePokemon();

    SetMoveOutcome SetMove(size_t, std::string_view);
    std::span<pokemonMove> GetMoveArray();
    std::span<const pokemonMove> GetMoveArray() const;

    void SetNickname(std::string_view);
    bool HasNickname() const;

    void SetLevel(unsigned int);

    void SetHPIV(unsigned int);
    void SetAttackIV(unsigned int);
    void SetDefenseIV(unsigned int);
    void SetSpecialAttackIV(unsigned int);
    void SetSpecialDefenseIV(unsigned int);
    void SetSpeedIV(unsigned int);

    SetEVResult SetHPEV(unsigned int);
    SetEVResult SetAttackEV(unsigned int);
    SetEVResult SetDefenseEV(unsigned int);
    SetEVResult SetSpecialAttackEV(unsigned int);
    SetEVResult SetSpecialDefenseEV(unsigned int);
    SetEVResult SetSpeedEV(unsigned int);

    unsigned int GetHPEV() const;
    unsigned int GetAttackEV() const;
    unsigned int GetDefenseEV() const;
    unsigned int GetSpecialAttackEV() const;
    unsigned int GetSpecialDefenseEV() const;
    unsigned int GetSpeedEV() const;

    bool ExceedsMaxAllowedEVs(unsigned int);

    unsigned int GetHPIV() const;
    unsigned int GetAttackIV() const;
    unsigned int GetDefenseIV() const;
    unsigned int GetSpecialAttackIV() const;
    unsigned int GetSpecialDefenseIV() const;
    unsigned int GetSpeedIV() const;

private:
    void UpdateStats();

public:

    const std::string& GetPokemonName() const;
    std::string_view GetPokemonNameView() const;
    const std::string& GetNickname() const;
    std::string_view GetNicknameView() const;

    const std::string& GetName() const;
    std::string_view GetNameView() const;

    unsigned int GetLevel() const;

    pokemonMove& GetMove(size_t);
    const pokemonMove& GetMove(size_t) const;
    void DeleteMove(size_t);
    void SwapMoves(size_t, size_t);
    void ReorderMoves(size_t, size_t);
    unsigned int GetPP(size_t) const;

    bool WillPerformStruggle() const;

    bool HasPokemon() const;
    bool HasMove(size_t);

    void IncrementMoveCount();
    void DecrementMoveCount();

    unsigned int GetMoveCount() const;

    std::string_view GetMoveName(size_t) const;
    MoveID GetMoveID(size_t) const;

    pokemonMove* GetLastUsedMove() const;
    void SetLastUsedMove(pokemonMove*);

    unsigned int GetTotalEVs() const;

    unsigned int GetCurrentHP() const;
    unsigned int GetMaxHP() const;
    unsigned int GetAttack() const;
    unsigned int GetDefense() const;
    unsigned int GetSpecialAttack() const;
    unsigned int GetSpecialDefense() const;
    unsigned int GetSpeed() const;

    void DamageCurrentHP(unsigned int);
    void HealCurrentHP(unsigned int);

    bool IsFainted() const;
    void SetFainted(bool);

    std::string_view GetTypeOne() const;
    PokemonType GetTypeOneEnum() const;
    std::string_view GetTypeTwo() const;
    PokemonType GetTypeTwoEnum() const;

    int GetAttackStage() const;
    int GetDefenseStage() const;
    int GetSpecialAttackStage() const;
    int GetSpecialDefenseStage() const;
    int GetSpeedStage() const;
    int GetEvasionStage() const;
    int GetAccuracyStage() const;
    int GetCriticalHitStage() const;

    void SetAttackStage(int);
    void SetDefenseStage(int);
    void SetSpecialAttackStage(int);
    void SetSpecialDefenseStage(int);
    void SetSpeedStage(int);
    void SetEvasionStage(int);
    void SetAccuracyStage(int);
    void SetCriticalHitStage(int);

    bool IsConfused() const;
    void SetConfusedStatus(bool);
    void SetConfusedTurnCount(unsigned int);
    unsigned int GetConfusedTurnCount() const;
    void IncrementConfusedCounter();
    unsigned int GetConfusedCounter() const;
    void ResetConfusedCounter();

    bool IsSeeded() const;
    void SetSeededStatus(bool);

    bool IsBound() const;
    void SetBound(bool);
    void SetBoundMoveName(MoveID);
    std::string_view GetBoundMoveName() const;
    void SetBoundTurnCount(unsigned int);
    unsigned int GetBoundTurnCount() const;
    void IncrementBoundCounter();
    unsigned int GetBoundCounter() const;
    void ResetBoundCounter();

    bool IsSemiInvulnerable() const;
    bool IsSemiInvulnerableFromDig() const;
    bool IsSemiInvulnerableFromFly() const;
    void SetSemiInvulnerableDig(bool);
    void SetSemiInvulnerableFly(bool);

    void ResetLockInState();

    bool IsCharging() const;
    void SetCharging(bool);

    bool IsRecharging() const;
    void SetRecharging(bool);

    void SetSleepTurnCount(unsigned int);
    unsigned int GetSleepTurnCount() const;
    void IncrementSleepCounter();
    unsigned int GetSleepCounter() const;
    void ResetSleepCounter();

    bool IsRampaging() const;
    void SetRampaging(bool);
    void SetRampageTurnCount(unsigned int);
    unsigned int GetRampageTurnCount() const;
    void IncrementRampageCounter();
    unsigned int GetRampageCounter() const;
    void ResetRampageCounter();

    void SetDisabledStatus(bool);
    void IncrementDisabledCounter();
    unsigned int GetDisabledCounter() const;
    void ResetDisabledCounter();
    bool MoveIsDisabled() const;
    void SetDisabledMoveID(MoveID);
    MoveID GetDisabledMoveID() const;

    bool HasPendingPostTurnEffect() const;

    unsigned int GetBadlyPoisonCounter() const;
    void ResetBadlyPoisonCounter();
    void IncrementBadlyPoisonCounter();

    bool IsFlinched() const;
    void SetIsFlinched(bool);

    bool HasUsedMinimize() const;
    void SetUsedMinimize(bool);

    bool IsRaging() const;
    void SetRaging(bool);

    bool HasUsedMimic() const;
    void SetUsedMimic(bool);
    int GetMimicPP() const;
    void SetMimicPP(int);

    bool HasFocusEnergy() const;
    void SetFocusEnergy(bool);

    Status GetStatus() const;
    void ChangeStatus(Status);

    bool IsBiding() const;
    void SetBide(bool);
    void SetBideTurnCount(unsigned int);
    unsigned int GetBideTurnCount() const;
    void IncrementBideCounter();
    unsigned int GetBideCounter() const;
    void ResetBideCounter();
    unsigned int GetBideDamage() const;
    void AddBideDamage(unsigned int);
    void ResetBideDamage();

    bool IsTransformed() const;
    void SetTransformation(BattlePokemon*);
    void Detransform();

    bool IsConverted() const;
    void SetConversion(PokemonType);
    void Deconvert();

    bool HasSubstitute() const;
    void SetSubstitute(bool);
    void SetSubstituteHP(unsigned int);
    unsigned int GetSubstituteHP() const;
    void DamageSubstitute(unsigned int);

    void SetCalledMove(const Move& move);
    pokemonMove* GetCalledMove();

private:
    void ResetStatsAndMoves();

public:
    void ResetStatsOnSwitch();
    void ResetValues();

private:
    std::array<pokemonMove, 4> m_array_moves{};

    std::string m_name{};
    std::string m_nickname{};
    std::string m_boundMove{};

    pokemonMove calledMove;

    pokemonMove* lastUsedMove{ nullptr };

    const Pokemon* mp_pokemon{ nullptr };

    unsigned int m_currentHP{ 0 };

    PokemonType m_type1e{};
    PokemonType m_type2e{};

    Status currentStatus{ Status::Normal };

    unsigned int m_level{ 50 };

    int m_attackstage{ 6 };
    int m_defensestage{ 6 };
    int m_specialattackstage{ 6 };
    int m_specialdefensestage{ 6 };
    int m_speedstage{ 6 };
    int m_evasionstage{ 6 };
    int m_accuracystage{ 6 };
    int m_criticalhitstage{ 0 };
    
    unsigned int m_maxHP{};
    unsigned int m_attack{};
    unsigned int m_defense{};
    unsigned int m_specialAttack{};
    unsigned int m_specialDefense{};
    unsigned int m_speed{};
    
    unsigned int m_hp_iv{ 31 };
    unsigned int m_attack_iv{ 31 };
    unsigned int m_defense_iv{ 31 };
    unsigned int m_specialattack_iv{ 31 };
    unsigned int m_specialdefense_iv{ 31 };
    unsigned int m_speed_iv{ 31 };

    unsigned int m_hp_ev{ 0 };
    unsigned int m_attack_ev{ 0 };
    unsigned int m_defense_ev{ 0 };
    unsigned int m_specialattack_ev{ 0 };
    unsigned int m_specialdefense_ev{ 0 };
    unsigned int m_speed_ev{ 0 };

    unsigned int m_sleepCounter{ 0 };
    unsigned int m_sleepTurnCount{ 0 };

    unsigned int m_substituteHealth{ 0 };

    unsigned int m_badlyPoisonCounter{ 0 };

    unsigned int m_disabledCounter{ 0 };

    unsigned int m_boundCounter{ 0 };
    unsigned int m_boundTurnCount{ 0 };

    unsigned int m_confusedCounter{ 0 };
    unsigned int m_confusedTurnCount{ 0 };

    unsigned int m_rampageCounter{ 0 };
    unsigned int m_rampageTurnCount{ 0 };

    unsigned int m_bideDamageTaken{ 0 };
    unsigned int m_bideCounter{ 0 };
    unsigned int m_bideTurnCount{ 0 };

    unsigned int m_moveCount{ 0 };

    int m_mimicPP{ 0 };

    unsigned int m_ev_total{ 0 };

    PokemonType m_beforeConversionType1_e{};
    PokemonType m_beforeConversionType2_e{};

    MoveID m_disabledMoveID{};

    bool b_hasNickname{ false };

    bool b_isFainted{ false };

    bool b_isCharging{ false };
    bool b_isRecharging{ false };
    bool b_isFlinched{ false };

    bool b_hasSubstitute{ false };

    bool b_isSemiInvulnerableFly{ false };
    bool b_isSemiInvulnerableDig{ false };

    bool b_hasUsedMinimize{ false };

    bool b_isSeeded{ false };

    bool b_moveIsDisabled{ false };

    bool b_isBound{ false };

    bool b_isConfused{ false };

    bool b_isRampaging{ false };

    bool b_hasFocusEnergy{ false };

    bool b_isRaging{ false };

    bool b_isBiding{ false };

    bool b_isConverted{ false };

    bool b_usedMimic{ false };

    bool b_isTransformed{ false };

    DetransformData m_detransformData;
};