#include <algorithm>
#include <vector>

#include "StatusEffectProcessor.h"

#include "BattleContext.h"
#include "RandomEngine.h"
#include "StageRatios.h"
#include "../data/Move.h"
#include "../moves/MoveEffectEnums.h"
#include "../ui/interfaces/IStatusEffectUI.h"
#include "../entities/pokemonMove.h"
#include "../entities/BattlePokemon.h"
#include "../entities/Player.h"

constexpr int ConfusionTurnChance{ 33 };
constexpr int ThawTurnChance{ 20 };
constexpr int ParalysisTurnChance{ 25 };

StatusEffectProcessor::StatusEffectProcessor(BattleContext& context, RandomEngine& rng, IStatusEffectUI& statusEffectUI)
	: m_context(context), m_rng(rng), m_statusEffectUI(statusEffectUI) {}

bool StatusEffectProcessor::CheckPerformativeStatus()
{
	bool canPerform{ true };

	if (m_context.attackingPokemon->IsRecharging())
	{
		m_statusEffectUI.DisplayRechargeMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView());
		m_context.attackingPokemon->SetRecharging(false);
		m_context.attackingPlayer->SetCanSwitch(true);

		return false;
	}

	if (m_context.attackingPokemon->IsRampaging() || m_context.attackingPokemon->IsBiding())
	{
		m_context.attackingPokemon->IncrementLockedCounter();
	}

	switch (m_context.attackingPokemon->GetStatus())
	{
	case Status::Sleeping:
		canPerform = SleepStatus();
		break;

	case Status::Frozen:
		canPerform = FrozenStatus();
		break;
	}

	if (m_context.attackingPokemon->IsFlinched() && canPerform)
	{
		canPerform = FlinchStatus();
	}

	if (m_context.attackingPokemon->IsConfused() && canPerform)
	{
		canPerform = ConfusedStatus();
	}

	if (m_context.attackingPokemon->GetStatus() == Status::Paralyzed && canPerform)
	{
		canPerform = ParalysisStatus();
	}

	if (m_context.attackingPokemon->MoveIsDisabled() && canPerform)
	{
		canPerform = CheckDisabled();
	}

	if (m_context.attackingPokemon->IsCharging() && !canPerform)
	{
		m_context.attackingPokemon->SetCharging(false);
		m_context.attackingPlayer->SetCanSwitch(true);

		if (m_context.attackingPokemon->IsSemiInvulnerable())
		{
			m_context.attackingPokemon->SetSemiInvulnerableDig(false);
			m_context.attackingPokemon->SetSemiInvulnerableFly(false);
		}
	}

	if (m_context.attackingPokemon->IsRampaging() && !canPerform)
	{
		if (m_context.attackingPokemon->GetLockedCounter() >= m_context.attackingPokemon->GetLockedTurnCount() && !m_context.attackingPokemon->IsConfused())
		{
			RampageConfuse();
		}

		ResetRampageState();
	}

	if (m_context.attackingPokemon->IsBiding())
	{
		if (!canPerform)
		{
			ResetBideState();
		}

		else if (canPerform && !(m_context.attackingPokemon->GetLockedCounter() >= m_context.attackingPokemon->GetLockedTurnCount()))
		{
			m_statusEffectUI.DisplayBideStoringEnergyMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView());

			return !canPerform;
		}
	}

	return canPerform;
}

bool StatusEffectProcessor::SleepStatus()
{
	if (m_context.attackingPokemon->GetSleepCounter() >= m_context.attackingPokemon->GetSleepTurnCount())
	{
		m_context.attackingPokemon->ChangeStatus(Status::Normal);
		m_context.attackingPokemon->ResetSleepCounter();
		m_context.attackingPokemon->SetSleepTurnCount(0);

		m_statusEffectUI.DisplayWokenUpMsg(m_context.attackingPokemon->GetNameView());
		return true;
	}
	else
	{
		m_context.attackingPokemon->IncrementSleepCounter();
		m_statusEffectUI.DisplayIsAsleepMsg(m_context.attackingPokemon->GetNameView());
		return false;
	}
}

bool StatusEffectProcessor::FrozenStatus()
{
	int randomMod{ m_rng.GetPercentRoll() };

	if (randomMod > ThawTurnChance)
	{
		m_statusEffectUI.DisplayFrozenSolidMsg(m_context.attackingPokemon->GetNameView());
		return false;
	}
	else
	{
		m_context.attackingPokemon->ChangeStatus(Status::Normal);
		m_statusEffectUI.DisplayThawedMsg(m_context.attackingPokemon->GetNameView());
		return true;
	}
}

bool StatusEffectProcessor::FlinchStatus()
{
	m_statusEffectUI.DisplayFlinchMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView());
	m_context.attackingPokemon->SetIsFlinched(false);

	return false;
}

bool StatusEffectProcessor::ConfusedStatus()
{
	if (m_context.attackingPokemon->GetConfusedCounter() >= m_context.attackingPokemon->GetConfusedTurnCount())
	{
		m_context.attackingPokemon->SetConfusedStatus(false);
		m_context.attackingPokemon->ResetConfusedCounter();
		m_context.attackingPokemon->SetConfusedTurnCount(0);

		m_statusEffectUI.DisplayNoLongerConfusedMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView());
		return true;
	}
	else
	{
		m_context.attackingPokemon->IncrementConfusedCounter();
		m_statusEffectUI.DisplayIsConfusedMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView());

		int randomMod{ m_rng.GetPercentRoll() };

		if (randomMod > ConfusionTurnChance)
		{
			return true;
		}
		else
		{
			// Confusion damage is a typeless 40-power physical attack.
			// It uses the user's Attack and Defense stages, but does not
			// receive STAB, critical hits, or the burn damage penalty.
			unsigned int level{ m_context.attackingPokemon->GetLevel() };
			constexpr unsigned int confusePower{ 40 };

			int attackStage = m_context.attackingPokemon->GetAttackStage();
			int defenseStage = m_context.attackingPokemon->GetDefenseStage();

			auto [atkNumerator, atkDenominator] = GetStageRatio(attackStage);
			auto [defNumerator, defDenominator] = GetStageRatio(defenseStage);

			unsigned int sourceAttack =	m_context.attackingPokemon->GetAttack() * atkNumerator / atkDenominator;
			unsigned int targetDefense = m_context.attackingPokemon->GetDefense() *	defNumerator / defDenominator;

			unsigned int baseDamage = (((((2 * level / 5) + 2) * confusePower * sourceAttack) / targetDefense) / 50) + 2;

			unsigned int damageMod{ m_rng.GetDamageRoll() };
			unsigned int finalDamage = baseDamage * damageMod / 100;

			m_context.attackingPokemon->DamageCurrentHP(finalDamage);

			m_statusEffectUI.DisplayHurtItselfConfuseMsg();

			CheckFaintCondition(*m_context.defendingPlayer, *m_context.attackingPlayer, *m_context.defendingPokemon, *m_context.attackingPokemon);

			return false;
		}
	}
}

bool StatusEffectProcessor::ParalysisStatus()
{
	int randomMod{ m_rng.GetPercentRoll() };

	if (randomMod <= ParalysisTurnChance)
	{
		m_statusEffectUI.DisplayCantMoveParalysisMsg(m_context.attackingPokemon->GetNameView());

		return false;
		
	}
	else
	{
		return true;
	}

}

bool StatusEffectProcessor::CheckDisabled()
{
	bool canPerform{ true };

	bool isLocked = m_context.attackingPokemon->IsCharging() || m_context.attackingPokemon->IsRecharging() ||
		m_context.attackingPokemon->IsRampaging() || m_context.attackingPokemon->IsBiding();

	const bool isCalledMoveContinuation = isLocked &&
		(m_context.currentMove->GetMoveEffectEnum() == MoveEffect::Metronome ||
			m_context.currentMove->GetMoveEffectEnum() == MoveEffect::MirrorMove);

	const Move* disabledMove =
		m_context.attackingPokemon->GetDisabledMove();

	bool disabled = false;

	if (isCalledMoveContinuation)
	{
		const pokemonMove* calledMove = m_context.attackingPokemon->GetCalledMove();

		disabled = calledMove->HasMove() && calledMove->GetMoveID() == disabledMove->GetMoveID();
	}
	else if (isLocked)
	{
		const pokemonMove* lastUsed = m_context.attackingPokemon->GetLastUsedMove();

		disabled = lastUsed != nullptr && lastUsed->GetMoveID() == disabledMove->GetMoveID();
	}
	else
	{
		disabled = m_context.currentMove->GetMoveID() == disabledMove->GetMoveID();
	}

	if (disabled)
	{
		canPerform = false;

		m_statusEffectUI.DisplayMoveIsDisabledMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView(), disabledMove->GetName());
	}
	
	return canPerform;
}

void StatusEffectProcessor::ResetRampageState()
{
	m_context.attackingPokemon->SetRampaging(false);
	m_context.attackingPokemon->ResetLockedCounter();
	m_context.attackingPokemon->SetLockedTurnCount(0);
	m_context.attackingPlayer->SetCanSwitch(true);
}

void StatusEffectProcessor::RampageConfuse()
{
	m_statusEffectUI.DisplayRampageConfusionMsg(m_context.attackingPlayer->GetPlayerNameView(), m_context.attackingPokemon->GetNameView());

	m_context.attackingPokemon->SetConfusedStatus(true);

	unsigned int randomMod{ m_rng.GetConfusionTurnRoll() };
	m_context.attackingPokemon->SetConfusedTurnCount(randomMod);
	m_context.attackingPokemon->ResetConfusedCounter();
}

void StatusEffectProcessor::ResetBideState()
{
	m_context.attackingPokemon->SetBide(false);
	m_context.attackingPokemon->ResetLockedCounter();
	m_context.attackingPokemon->SetLockedTurnCount(0);
	m_context.attackingPokemon->ResetBideDamage();
	m_context.attackingPlayer->SetCanSwitch(true);
}

void StatusEffectProcessor::CheckSubstituteCondition(Player* targetPlayer, BattlePokemon* targetPokemon)
{
	if (targetPokemon->GetSubstituteHP() <= 0 && targetPokemon->HasSubstitute())
	{
		targetPokemon->SetSubstitute(false);
		m_statusEffectUI.DisplaySubstituteFadedMsg(targetPlayer->GetPlayerNameView(), targetPokemon->GetNameView());
	}
}

void StatusEffectProcessor::CheckFaintCondition(Player& sourcePlayer, Player& targetPlayer, BattlePokemon& source, BattlePokemon& target)
{
	if (target.GetCurrentHP() <= 0 && !target.IsFainted())
	{
		target.SetFainted(true);
		target.ChangeStatus(Status::Normal);
		m_statusEffectUI.DisplayFaintedMsg(targetPlayer.GetPlayerNameView(), target.GetNameView());
		targetPlayer.IncrementFaintedCount();

		if (source.IsBound())
		{
			source.SetBound(false);
			sourcePlayer.SetCanSwitch(true);
			source.ResetBoundCounter();
			source.SetBoundTurnCount(0);

			m_statusEffectUI.DisplayFreedFromBoundMsg(sourcePlayer.GetPlayerNameView(), source.GetNameView(), source.GetBoundMoveName());
		}

		if (targetPlayer.GetPokemonCount() == targetPlayer.GetFaintedCount())
		{
			if (std::find(m_context.vec_outOfPokemon.begin(), m_context.vec_outOfPokemon.end(), &targetPlayer) == m_context.vec_outOfPokemon.end())
			{
				m_context.vec_outOfPokemon.emplace_back(&targetPlayer);
			}
		}

		targetPlayer.SetCanSwitch(true);
	}
}