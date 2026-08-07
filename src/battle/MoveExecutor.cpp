#include "MoveExecutor.h"

#include "BattleContext.h"
#include "../entities/pokemonMove.h"
#include "../moves/MoveRoutines.h"

MoveExecutor::MoveExecutor(
    BattleContext& context,
    BattleCalculations& calculations,
    StatusEffectProcessor& statusProcessor,
    IMoveResultsUI& resultsUI,
    RandomEngine& rng
)
    : m_deps(context, calculations, statusProcessor, resultsUI, rng)
{}

void MoveExecutor::ExecuteMove()
{
    MoveRoutines::Execute(m_deps.context.currentMoveEffect, m_deps);
}