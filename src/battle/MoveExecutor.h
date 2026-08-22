#pragma once

#include "../moves/MoveRoutineDeps.h"

class BattleCalculations;
class IMoveResultsUI;
class IStatusEffectUI;
class RandomEngine;
class StatusEffectProcessor;
struct BattleContext;

class MoveExecutor
{
public:
    MoveExecutor(BattleContext& context, RandomEngine& rng, BattleCalculations& calculations, StatusEffectProcessor& statusProcessor, IMoveResultsUI& resultsUI, IStatusEffectUI& statusEffectUI);

    void ExecuteMove();

private:
    void TryPostMoveReactions();

    MoveRoutineDeps m_deps;
};