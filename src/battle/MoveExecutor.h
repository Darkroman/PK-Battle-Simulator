#pragma once

struct BattleContext;
class BattleCalculations;
class StatusEffectProcessor;
class IMoveResultsUI;
class RandomEngine;

#include "../moves/MoveRoutineDeps.h"

class MoveExecutor
{
public:
    MoveExecutor(BattleContext& context, BattleCalculations& calculations, StatusEffectProcessor& statusProcessor, IMoveResultsUI& resultsUI, RandomEngine& rng);

    void ExecuteMove();

private:
    MoveRoutineDeps m_deps;
};