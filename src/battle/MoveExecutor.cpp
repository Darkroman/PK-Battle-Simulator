#include "MoveExecutor.h"

#include "../data/StringToTypes.h"

#include "../entities/BattlePokemon.h"
#include "../entities/NonVolatileStatuses.h"
#include "../entities/PokemonMoveSlot.h"

#include "../moves/MoveRoutineDeps.h"
#include "../moves/MoveRoutines.h"

#include "../ui/interfaces/IStatusEffectUI.h"

#include "BattleContext.h"

MoveExecutor::MoveExecutor(
    BattleContext& context,
    RandomEngine& rng,
    BattleCalculations& calculations,
    StatusEffectProcessor& statusProcessor,
    IMoveResultsUI& resultsUI,
    IStatusEffectUI& statusEffectUI
)
    : m_deps(context, rng, calculations, statusProcessor, resultsUI, statusEffectUI)
{}

void MoveExecutor::ExecuteMove()
{
    MoveRoutines::Execute(m_deps.context.currentMove->GetMoveEffectEnum(), m_deps);

    TryPostMoveReactions();
}

void MoveExecutor::TryPostMoveReactions()
{
    if (m_deps.context.defendingPokemon->GetStatus() == Status::Frozen &&
        m_deps.context.lastDamagingMove != nullptr &&
        m_deps.context.lastDamagingMove->GetMoveTypeEnum() == PokemonType::Fire &&
        m_deps.context.lastDamageApplied > 0 &&
        !m_deps.context.flags.hitSubstitute)
    {
        m_deps.context.defendingPokemon->ChangeStatus(Status::Normal);
        m_deps.statusEffectUI.DisplayThawedMsg(m_deps.context.defendingPokemon->GetNameView());
    }
}