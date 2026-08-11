#include <algorithm>
#include <string_view>

#include "PostTurnEffectProcessor.h"

#include "BattleContext.h"
#include "BattleCalculations.h"
#include "StatusEffectProcessor.h"
#include "WinChecker.h"
#include "SwitchExecutor.h"
#include "../ui/interfaces/IStatusEffectUI.h"
#include "../data/MoveID.h"
#include "../entities/BattlePokemon.h"
#include "../entities/Player.h"
#include "../entities/controllers/IPlayerController.h"

constexpr unsigned int SeedDivisor{ 8 };
constexpr unsigned int BurnDivisor{ 16 };
constexpr unsigned int PoisonDivisor{ 8 };
constexpr unsigned int BadPoisonDivisor{ 16 };
constexpr unsigned int BoundDivisor{ 8 };
constexpr int DisableTurnCount{ 4 };
constexpr int ReflectTurnCount{ 4 };
constexpr int LightScreenTurnCount{ 4 };
constexpr int MistTurnCount{ 4 };

PostTurnEffectProcessor::PostTurnEffectProcessor(BattleContext& context, BattleCalculations& calculations, IStatusEffectUI& statusEffectUI, StatusEffectProcessor& statusProcessor, WinChecker& winChecker, SwitchExecutor& switchExecutor)
    : m_context(context)
    , m_calculations(calculations)
    , m_statusEffectUI(statusEffectUI)
    , m_statusProcessor(statusProcessor)
    , m_winChecker(winChecker)
    , m_switchExecutor(switchExecutor)
{}

void PostTurnEffectProcessor::DeterminePostFaintSwitchOrder()
{
    if (!m_context.vec_outOfPokemon.empty())
    {
        return;
    }

    int playerOneSpeed = m_calculations.CalculatePokemonSpeed(*m_context.playerOneCurrentPokemon);
    int playerTwoSpeed = m_calculations.CalculatePokemonSpeed(*m_context.playerTwoCurrentPokemon);

    if (playerOneSpeed > playerTwoSpeed)
    {
        m_context.attackingPlayer = m_context.playerOne;
        m_context.defendingPlayer = m_context.playerTwo;
        m_context.attackingPokemon = m_context.playerOneCurrentPokemon;
        m_context.defendingPokemon = m_context.playerTwoCurrentPokemon;
    }
    else if (playerTwoSpeed > playerOneSpeed)
    {
        m_context.attackingPlayer = m_context.playerTwo;
        m_context.defendingPlayer = m_context.playerOne;
        m_context.attackingPokemon = m_context.playerTwoCurrentPokemon;
        m_context.defendingPokemon = m_context.playerOneCurrentPokemon;
    }
    else
    {
        m_calculations.RandomizePostTurnOrder();
    }
}

bool PostTurnEffectProcessor::ProcessAllPostTurnEffects()
{
    if (CheckSeededStatuses())
    { 
        return true;
    }

    if (CheckDamagingStatuses())
    {
        return true;
    }

    if (CheckBoundStatuses())
    {
        return true;
    }

    CheckDisabledStatus();

    CheckFieldEffects();

    return false;
}

// This is only used in BattleManager::RunBattleSimulation for fast evaluation
void PostTurnEffectProcessor::ProcessPostKOSwitches()
{
    if (!m_context.attackingPokemon->IsFainted() && !m_context.defendingPokemon->IsFainted())
    {
        return;
    }

    if (m_context.attackingPokemon->IsFainted() && m_context.defendingPokemon->IsFainted())
    {
        DeterminePostFaintSwitchOrder();
    }

    ProcessPostKOSwitch(*m_context.defendingPlayer, *m_context.attackingPlayer, *m_context.defendingPokemon, *m_context.attackingPokemon);

    ProcessPostKOSwitch(*m_context.attackingPlayer, *m_context.defendingPlayer, *m_context.attackingPokemon, *m_context.defendingPokemon);
}

// Only for use in PostTurnEffectProcessor::ProcessPostKOSwitches()
void PostTurnEffectProcessor::ProcessPostKOSwitch(Player& sourcePlayer, Player& targetPlayer, const BattlePokemon& sourcePokemon, const BattlePokemon& targetPokemon)
{
    if (!targetPokemon.IsFainted())
    {
        return;
    }

    BattlePokemon* newPokemon = targetPlayer.GetController().PromptForSwitch(targetPlayer, sourcePlayer, targetPokemon, sourcePokemon);
    targetPlayer.SetPokemonToSwitchTo(newPokemon);

    if (&targetPokemon == m_context.playerOneCurrentPokemon)
    {
        m_switchExecutor.ExecuteSwitch(*m_context.playerOne, m_context.playerOneCurrentPokemon);
        return;
    }

    if (&targetPokemon == m_context.playerTwoCurrentPokemon)
    {
        m_switchExecutor.ExecuteSwitch(*m_context.playerTwo, m_context.playerTwoCurrentPokemon);
        return;
    }
}

bool PostTurnEffectProcessor::CheckSeededStatuses()
{
    if (!m_context.vec_outOfPokemon.empty())
    {
        return true;
    }

    if (!m_context.attackingPokemon->IsSeeded() && !m_context.defendingPokemon->IsSeeded())
    {
        return false;
    }

    if (m_context.attackingPokemon->IsSeeded() && m_context.defendingPokemon->IsSeeded())
    {   
        m_calculations.RandomizePostTurnOrder();
    }

    if (m_context.attackingPokemon->IsSeeded() && !m_context.attackingPokemon->IsFainted() && !m_context.defendingPokemon->IsFainted())
    {
        unsigned int damage = std::max(1u, m_context.attackingPokemon->GetMaxHP() / SeedDivisor);

        unsigned int before = m_context.attackingPokemon->GetCurrentHP();
        m_context.attackingPokemon->DamageCurrentHP(damage);

        unsigned int drained = before - m_context.attackingPokemon->GetCurrentHP();

        m_context.defendingPokemon->HealCurrentHP(drained);

        m_statusEffectUI.DisplayLeechSeedSappedMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView());

        m_statusProcessor.CheckFaintCondition(*m_context.defendingPlayer, *m_context.attackingPlayer, *m_context.defendingPokemon, *m_context.attackingPokemon);

        if (m_winChecker.CheckWinCondition(*m_context.defendingPlayer, *m_context.attackingPlayer))
        {
            return true;
        }
    }

    if (m_context.defendingPokemon->IsSeeded() && !m_context.defendingPokemon->IsFainted() && !m_context.attackingPokemon->IsFainted())
    {
        unsigned int damage = std::max(1u, m_context.defendingPokemon->GetMaxHP() / SeedDivisor);

        unsigned int before = m_context.defendingPokemon->GetCurrentHP();
        m_context.defendingPokemon->DamageCurrentHP(damage);

        unsigned int drained = before - m_context.defendingPokemon->GetCurrentHP();

        m_context.attackingPokemon->HealCurrentHP(drained);

        m_statusEffectUI.DisplayLeechSeedSappedMsg(m_context.defendingPlayer->GetPlayerNameView(), m_context.defendingPokemon->GetNameView());

        m_statusProcessor.CheckFaintCondition(*m_context.attackingPlayer, *m_context.defendingPlayer, *m_context.attackingPokemon, *m_context.defendingPokemon);

        if (m_winChecker.CheckWinCondition(*m_context.attackingPlayer, *m_context.defendingPlayer))
        {
            return true;
        }
    }

    return false;
}

bool PostTurnEffectProcessor::CheckDamagingStatuses()
{
    if (!m_context.vec_outOfPokemon.empty())
    {
        return true;
    }

    bool atkPkmnHasDmgStatus = m_context.attackingPokemon->GetStatus() == Status::Badly_Poisoned ||
        m_context.attackingPokemon->GetStatus() == Status::Burned ||
        m_context.attackingPokemon->GetStatus() == Status::Poisoned;

    bool defPkmnHasDmgStatus = m_context.defendingPokemon->GetStatus() == Status::Badly_Poisoned ||
        m_context.defendingPokemon->GetStatus() == Status::Burned ||
        m_context.defendingPokemon->GetStatus() == Status::Poisoned;

    if (!atkPkmnHasDmgStatus && !defPkmnHasDmgStatus)
    {
        return false;
    }

    if (atkPkmnHasDmgStatus && defPkmnHasDmgStatus)
    {
        m_calculations.RandomizePostTurnOrder();
    }

    if (!m_context.attackingPokemon->IsFainted())
    {
        switch (m_context.attackingPokemon->GetStatus())
        {
        case Status::Burned:
            BurnedStatus(*m_context.attackingPlayer, *m_context.attackingPokemon);
            break;

        case Status::Poisoned:
            PoisonedStatus(*m_context.attackingPlayer, *m_context.attackingPokemon);
            break;

        case Status::Badly_Poisoned:
            BadlyPoisonedStatus(*m_context.attackingPlayer, *m_context.attackingPokemon);
            break;

        default:
            break;
        }
    }

    m_statusProcessor.CheckFaintCondition(*m_context.defendingPlayer, *m_context.attackingPlayer, *m_context.defendingPokemon, *m_context.attackingPokemon);

    if (m_winChecker.CheckWinCondition(*m_context.defendingPlayer, *m_context.attackingPlayer))
    {
        return true;
    }

    if (!m_context.defendingPokemon->IsFainted())
    {
        switch (m_context.defendingPokemon->GetStatus())
        {
        case Status::Burned:
            BurnedStatus(*m_context.defendingPlayer, *m_context.defendingPokemon);
            break;

        case Status::Poisoned:
            PoisonedStatus(*m_context.defendingPlayer, *m_context.defendingPokemon);
            break;

        case Status::Badly_Poisoned:
            BadlyPoisonedStatus(*m_context.defendingPlayer, *m_context.defendingPokemon);
            break;

        default:
            break;
        }
    }
    m_statusProcessor.CheckFaintCondition(*m_context.attackingPlayer, *m_context.defendingPlayer, *m_context.attackingPokemon, *m_context.defendingPokemon);

    if (m_winChecker.CheckWinCondition(*m_context.attackingPlayer, *m_context.defendingPlayer))
    {
        return true;
    }

    return false;
}

void PostTurnEffectProcessor::BurnedStatus(const Player& player, BattlePokemon& pokemon)
{
    unsigned int maxHP{ pokemon.GetMaxHP() };
    unsigned int burnDamage{ std::max(1u, maxHP / BurnDivisor) };

    pokemon.DamageCurrentHP(burnDamage);

    m_statusEffectUI.DisplayDamagedByStatusPostTurn(player.GetPlayerNameView(), pokemon.GetNameView(), "burn");
}

void PostTurnEffectProcessor::PoisonedStatus(const Player& player, BattlePokemon& pokemon)
{
    unsigned int maxHP{ pokemon.GetMaxHP() };
    unsigned int poisonDamage{ std::max(1u, maxHP / PoisonDivisor) };

    pokemon.DamageCurrentHP(poisonDamage);

    m_statusEffectUI.DisplayDamagedByStatusPostTurn(player.GetPlayerNameView(), pokemon.GetNameView(), "poison");
}

void PostTurnEffectProcessor::BadlyPoisonedStatus(const Player& player, BattlePokemon& pokemon)
{
    // Badly poison's counter is capped at 15 in the BattlePokemon::IncrementBadlyPoisonCounter() method
    unsigned int counter{ pokemon.GetBadlyPoisonCounter() };

    unsigned int maxHP{ pokemon.GetMaxHP() };
    unsigned int baseDamage{ std::max(1u, maxHP / BadPoisonDivisor) };
    unsigned int poisonDamage{ baseDamage * counter };

    pokemon.DamageCurrentHP(poisonDamage);

    m_statusEffectUI.DisplayDamagedByStatusPostTurn(player.GetPlayerNameView(), pokemon.GetNameView(), "poison");

    pokemon.IncrementBadlyPoisonCounter();
}

bool PostTurnEffectProcessor::CheckBoundStatuses()
{
    if (!m_context.vec_outOfPokemon.empty())
    {
        return true;
    }

    if (!m_context.attackingPokemon->IsBound() && !m_context.defendingPokemon->IsBound())
    {
        return false;
    }

    if (m_context.attackingPokemon->IsBound() && m_context.defendingPokemon->IsBound())
    {
        m_calculations.RandomizePostTurnOrder();
    }

    if (m_context.attackingPokemon->IsBound() && !m_context.attackingPokemon->IsFainted())
    {
        if (m_context.attackingPokemon->GetBoundCounter() >= m_context.attackingPokemon->GetBoundTurnCount())
        {
            m_context.attackingPokemon->SetBound(false);
            m_context.attackingPlayer->SetCanSwitch(true);
            m_context.attackingPokemon->ResetBoundCounter();
            m_context.attackingPokemon->SetBoundTurnCount(0);

            m_statusEffectUI.DisplayFreedFromBoundMsg(m_context.attackingPlayer->GetPlayerNameView(),
                m_context.attackingPokemon->GetNameView(),
                m_context.attackingPokemon->GetBoundMoveName());
        }
        else
        {
            m_context.attackingPokemon->IncrementBoundCounter();
            unsigned int boundDamage{ std::max(1u, m_context.attackingPokemon->GetMaxHP() / BoundDivisor) };

            m_context.attackingPokemon->DamageCurrentHP(boundDamage);

            m_statusEffectUI.DisplayHurtByBoundMsg(m_context.attackingPlayer->GetPlayerNameView(),
                m_context.attackingPokemon->GetNameView(),
                m_context.attackingPokemon->GetBoundMoveName());

            m_statusProcessor.CheckFaintCondition(*m_context.defendingPlayer, *m_context.attackingPlayer,
                *m_context.defendingPokemon, *m_context.attackingPokemon);

            if (m_winChecker.CheckWinCondition(*m_context.defendingPlayer, *m_context.attackingPlayer))
            {
                return true;
            }
        }
    }

    if (m_context.defendingPokemon->IsBound() && !m_context.defendingPokemon->IsFainted())
    {
        if (m_context.defendingPokemon->GetBoundCounter() >= m_context.defendingPokemon->GetBoundTurnCount())
        {

            m_context.defendingPokemon->SetBound(false);
            m_context.defendingPlayer->SetCanSwitch(true);
            m_context.defendingPokemon->ResetBoundCounter();
            m_context.defendingPokemon->SetBoundTurnCount(0);

            m_statusEffectUI.DisplayFreedFromBoundMsg(m_context.defendingPlayer->GetPlayerNameView(),
                m_context.defendingPokemon->GetNameView(),
                m_context.defendingPokemon->GetBoundMoveName());
        }
        else
        {
            m_context.defendingPokemon->IncrementBoundCounter();
            unsigned int boundDamage{ std::max(1u, m_context.defendingPokemon->GetMaxHP() / BoundDivisor) };

            m_context.defendingPokemon->DamageCurrentHP(boundDamage);

            m_statusEffectUI.DisplayHurtByBoundMsg(m_context.defendingPlayer->GetPlayerNameView(),
                m_context.defendingPokemon->GetNameView(),
                m_context.defendingPokemon->GetBoundMoveName());

            m_statusProcessor.CheckFaintCondition(*m_context.attackingPlayer, *m_context.defendingPlayer,
                *m_context.attackingPokemon, *m_context.defendingPokemon);

            if (m_winChecker.CheckWinCondition(*m_context.attackingPlayer, *m_context.defendingPlayer))
            {
                return true;
            }
        }
    } 

    return false;
}

void PostTurnEffectProcessor::CheckDisabledStatus()
{
    if (!m_context.vec_outOfPokemon.empty())
    {
        return;
    }

    if (!m_context.attackingPokemon->MoveIsDisabled() && !m_context.defendingPokemon->MoveIsDisabled())
    {
        return;
    }

    if (m_context.attackingPokemon->MoveIsDisabled() && m_context.defendingPokemon->MoveIsDisabled())
    {
        m_calculations.RandomizePostTurnOrder();
    }

    if (m_context.attackingPokemon->MoveIsDisabled() && !m_context.attackingPokemon->IsFainted())
    {
        if (m_context.attackingPokemon->GetDisabledCounter() >= DisableTurnCount)
        {
            for (auto& move : m_context.attackingPokemon->GetMoveArray())
            {
                if (move.HasMove() && move.GetMoveID() == m_context.attackingPokemon->GetDisabledMove()->GetMoveID())
                {
                    move.b_isDisabled = false;
                    break;
                }
            }

            m_statusEffectUI.DisplayMoveNoLongerDisabledMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView(), m_context.attackingPokemon->GetDisabledMove()->GetName());
            m_context.attackingPokemon->SetDisabledStatus(false);
            m_context.attackingPokemon->SetDisabledMove(nullptr);
            m_context.attackingPokemon->ResetDisabledCounter();
        }
        else
        {
            m_context.attackingPokemon->IncrementDisabledCounter();
        }
    }

    if (m_context.defendingPokemon->MoveIsDisabled() && !m_context.defendingPokemon->IsFainted())
    {
        if (m_context.defendingPokemon->GetDisabledCounter() >= DisableTurnCount)
        {
            for (auto& move : m_context.defendingPokemon->GetMoveArray())
            {
                if (move.HasMove() && move.GetMoveID() == m_context.defendingPokemon->GetDisabledMove()->GetMoveID())
                {
                    move.b_isDisabled = false;
                    break;
                }
            }

            m_statusEffectUI.DisplayMoveNoLongerDisabledMsg(m_context.defendingPlayer->GetPlayerNameView(), m_context.defendingPokemon->GetNameView(), m_context.defendingPokemon->GetDisabledMove()->GetName());
            m_context.defendingPokemon->SetDisabledStatus(false);
            m_context.defendingPokemon->SetDisabledMove(nullptr);
            m_context.defendingPokemon->ResetDisabledCounter();
        }
        else
        {
            m_context.defendingPokemon->IncrementDisabledCounter();
        }
    }
}

void PostTurnEffectProcessor::CheckFieldEffects()
{
    if (!m_context.vec_outOfPokemon.empty())
    {
        return;
    }

    if (!m_context.defendingPlayer->HasReflect() && !m_context.attackingPlayer->HasReflect()
        && !m_context.attackingPlayer->HasLightScreen() && !m_context.defendingPlayer->HasLightScreen()
        && !m_context.attackingPlayer->HasMist() && !m_context.defendingPlayer->HasMist())
    {
        return;
    }

    if (m_context.attackingPlayer->HasReflect() && m_context.defendingPlayer->HasReflect())
    {
        m_calculations.RandomizePostTurnOrder();
    }

    // Reflect
    if (m_context.attackingPlayer->HasReflect())
    {
        if (m_context.attackingPlayer->GetReflectCounter() >= ReflectTurnCount)
        {
            m_statusEffectUI.DisplayFieldEffectFadedMsg(m_context.attackingPlayer->GetPlayerNameView(), "reflect");
            m_context.attackingPlayer->SetReflect(false);
            m_context.attackingPlayer->ResetReflectCounter();
        }
        else
        {
            m_context.attackingPlayer->IncrementReflectCounter();
        }
    }

    if (m_context.defendingPlayer->HasReflect())
    {
        if (m_context.defendingPlayer->GetReflectCounter() >= ReflectTurnCount)
        {
            m_statusEffectUI.DisplayFieldEffectFadedMsg(m_context.defendingPlayer->GetPlayerNameView(), "reflect");
            m_context.defendingPlayer->SetReflect(false);
            m_context.defendingPlayer->ResetReflectCounter();
        }
        else
        {
            m_context.defendingPlayer->IncrementReflectCounter();
        }
    }

    if (m_context.attackingPlayer->HasLightScreen() && m_context.defendingPlayer->HasLightScreen())
    {
        m_calculations.RandomizePostTurnOrder();
    }

    // Light Screen
    if (m_context.attackingPlayer->HasLightScreen())
    {
        if (m_context.attackingPlayer->GetLightScreenCounter() >= LightScreenTurnCount)
        {
            m_statusEffectUI.DisplayFieldEffectFadedMsg(m_context.attackingPlayer->GetPlayerNameView(), "light screen");
            m_context.attackingPlayer->SetLightScreen(false);
            m_context.attackingPlayer->ResetLightScreenCounter();
        }
        else
        {
            m_context.attackingPlayer->IncrementLightScreenCounter();
        }
    }

    if (m_context.defendingPlayer->HasLightScreen())
    {
        if (m_context.defendingPlayer->GetLightScreenCounter() >= LightScreenTurnCount)
        {
            m_statusEffectUI.DisplayFieldEffectFadedMsg(m_context.defendingPlayer->GetPlayerNameView(), "light screen");
            m_context.defendingPlayer->SetLightScreen(false);
            m_context.defendingPlayer->ResetLightScreenCounter();
        }
        else
        {
            m_context.defendingPlayer->IncrementLightScreenCounter();
        }
    }

    if (m_context.attackingPlayer->HasMist() && m_context.defendingPlayer->HasMist())
    {
        m_calculations.RandomizePostTurnOrder();
    }

    // Mist
    if (m_context.attackingPlayer->HasMist())
    {
        if (m_context.attackingPlayer->GetMistCounter() >= MistTurnCount)
        {
            m_statusEffectUI.DisplayNoLongerProtectedMist(m_context.attackingPlayer->GetPlayerNameView());
            m_context.attackingPlayer->SetMist(false);
            m_context.attackingPlayer->ResetMistCounter();
        }
        else
        {
            m_context.attackingPlayer->IncrementMistCounter();
        }
    }

    if (m_context.defendingPlayer->HasMist())
    {
        if (m_context.defendingPlayer->GetMistCounter() >= MistTurnCount)
        {
            m_statusEffectUI.DisplayNoLongerProtectedMist(m_context.defendingPlayer->GetPlayerNameView());
            m_context.defendingPlayer->SetMist(false);
            m_context.defendingPlayer->ResetMistCounter();
        }
        else
        {
            m_context.defendingPlayer->IncrementMistCounter();
        }
    }
}