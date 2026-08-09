#pragma once

struct BattleContext;
class BattleCalculations;
class StatusEffectProcessor;
class IMoveResultsUI;
class IStatusEffectUI;
class RandomEngine;

#include "../moves/MoveRoutineDeps.h"

class MoveExecutor
{
public:
    MoveExecutor(BattleContext& context, BattleCalculations& calculations, StatusEffectProcessor& statusProcessor, IMoveResultsUI& resultsUI, IStatusEffectUI& statusEffectUI, RandomEngine& rng);

    void ExecuteMove();

    void TryPostMoveReactions();

private:
    MoveRoutineDeps m_deps;
};