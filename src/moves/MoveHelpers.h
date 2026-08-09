#pragma once

#include <string_view>

#include "../ui/EffectivenessText.h"
#include "../entities/BattlePokemon.h"
#include "../battle/BattleContext.h"

class IMoveResultsUI;
struct MoveRoutineDeps;

EffectivenessText ToEffectivenessText(BattleStateFlags::Effectiveness);

void InflictNVStatus(Status, int effectChance, MoveRoutineDeps&);

bool DefendingPokemonIsFainted(BattleContext&, IMoveResultsUI&);

void DamageRoutine(MoveRoutineDeps&);

void IncreasedCriticalHitRoutine(MoveRoutineDeps&);

void MultiStrikeRoutine(MoveRoutineDeps&, int turnCount);

void OHKODamageRoutine(MoveRoutineDeps&);

void FixedDamageRoutine(MoveRoutineDeps&, unsigned int baseDamage);

void FlinchRoutine(MoveRoutineDeps&);

void RecoilRoutine(MoveRoutineDeps& deps, unsigned int recoilDivisor);

void TryDamageReactions(MoveRoutineDeps& deps);

void ProcessRage(MoveRoutineDeps& deps);

using GetStageFn = int (*)(BattlePokemon&);
using SetStageFn = void (*)(BattlePokemon&, int);

void StageUpRoutine(MoveRoutineDeps& deps, int amount, std::string_view stageName, GetStageFn getStage, SetStageFn setStage);
void StageDownRoutine(MoveRoutineDeps& deps, int amount, std::string_view stageName, GetStageFn getStage, SetStageFn setStage);
void StageDownDamageRoutine(MoveRoutineDeps& deps, int amount, std::string_view stageName, GetStageFn getStage, SetStageFn setStage);
void DisplayStatChange(IMoveResultsUI& ui, int amount, bool isUp, std::string_view playerName, std::string_view pokemonName, std::string_view stageName);

using ChargeMsgMemFn = void (IMoveResultsUI::*)(std::string_view, std::string_view) const;
using ChargeHookFn = void (*)(MoveRoutineDeps& deps);
using ChargeStageUpFn = void (*)(MoveRoutineDeps& deps, int amount, std::string_view stageName, GetStageFn getStage, SetStageFn setStage);

struct ChargingMoveHooks
{
    ChargeHookFn preCharge{ nullptr };
    ChargeHookFn postCharge{ nullptr };
    ChargeStageUpFn stageUp{ nullptr };
    GetStageFn getStage{ nullptr };
    SetStageFn setStage{ nullptr };
    int stageIncreaseAmount{};
    std::string_view stageName{};
};

bool HandleCharging(MoveRoutineDeps&, ChargeMsgMemFn, const ChargingMoveHooks& hooks = {});