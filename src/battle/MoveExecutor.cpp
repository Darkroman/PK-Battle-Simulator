#include "MoveExecutor.h"

#include "BattleContext.h"
#include "../entities/pokemonMove.h"
#include "../entities/BattlePokemon.h"
#include "../data/StringToTypes.h"
#include "../moves/MoveRoutines.h"
#include "../ui/interfaces/IStatusEffectUI.h"

MoveExecutor::MoveExecutor(
    BattleContext& context,
    BattleCalculations& calculations,
    StatusEffectProcessor& statusProcessor,
    IMoveResultsUI& resultsUI,
    IStatusEffectUI& statusEffectUI,
    RandomEngine& rng
)
    : m_deps(context, calculations, statusProcessor, resultsUI, statusEffectUI, rng)
{}

void MoveExecutor::ExecuteMove()
{
    MoveRoutines::Execute(m_deps.context.currentMoveEffect, m_deps);

    TryPostMoveReactions();
}

void MoveExecutor::TryPostMoveReactions()
{
    if (m_deps.context.defendingPokemon->GetStatus() == Status::Frozen &&
        m_deps.context.currentMoveType == PokemonType::Fire &&
        m_deps.context.lastDamageApplied > 0 &&
        !m_deps.context.flags.hitSubstitute)
    {
        m_deps.context.defendingPokemon->ChangeStatus(Status::Normal);
        m_deps.statusEffectUI.DisplayThawedMsg(m_deps.context.defendingPokemon->GetNameView());
    }
}