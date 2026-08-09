#include <algorithm>
#include <string_view>

#include "MoveHelpers.h"

#include "../ui/EffectivenessText.h"
#include "MoveRoutineDeps.h"
#include "MoveEffectEnums.h"
#include "../entities/BattlePokemon.h"
#include "../entities/Player.h"
#include "../data/StringToTypes.h"
#include "../battle/RandomEngine.h"
#include "../battle/BattleContext.h"
#include "../ui/interfaces/IMoveResultsUI.h"
#include "../battle/BattleCalculations.h"
#include "../battle/StatusEffectProcessor.h"

EffectivenessText ToEffectivenessText(BattleStateFlags::Effectiveness e)
{
	using E = BattleStateFlags::Effectiveness;

	switch (e)
	{
	case E::Normal: return EffectivenessText::Normal;
	case E::Super:  return EffectivenessText::Super;
	case E::Less:   return EffectivenessText::Less;
	case E::No:	    return EffectivenessText::No;
	default:	    return EffectivenessText::Normal;
	}
}

void InflictNVStatus(Status status, int effectChance, MoveRoutineDeps& deps)
{
	auto& ctx = deps.context;

	if (ctx.flags.hitSubstitute || ctx.defendingPokemon->GetCurrentHP() <= 0 || ctx.defendingPokemon->GetStatus() != Status::Normal || ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
	{
		return;
	}

	if (status == Status::Burned && (ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Fire || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Fire))
	{
		return;
	}

	else if (status == Status::Frozen && (ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Ice || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Ice))
	{
		return;
	}

	else if (status == Status::Paralyzed && (ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Electric || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Electric))
	{
		return;
	}

	else if ((status == Status::Poisoned || status == Status::Badly_Poisoned) && ((ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Poison || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Poison)
		|| (ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Steel || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Steel)))
	{
		return;
	}

	if (effectChance < 100 && deps.rng.GetPercentRoll() > effectChance)
	{
		return;
	}

	switch (status)
	{
		case Status::Burned:
			deps.resultsUI.DisplayBurnSuccess(ctx.defendingPlayer->GetPlayerName(), ctx.defendingPokemon->GetNameView());
			break;

		case Status::Frozen:
			deps.resultsUI.DisplayFreezeSuccess(ctx.defendingPlayer->GetPlayerName(), ctx.defendingPokemon->GetNameView());
			break;

		case Status::Paralyzed:
			deps.resultsUI.DisplayParalyzeSuccess(ctx.defendingPlayer->GetPlayerName(), ctx.defendingPokemon->GetNameView());
			break;

		case Status::Poisoned:
			deps.resultsUI.DisplayPoisonSuccess(ctx.defendingPlayer->GetPlayerName(), ctx.defendingPokemon->GetNameView());
			break;

		case Status::Badly_Poisoned:
			deps.resultsUI.DisplayBadlyPoisonSuccess(ctx.defendingPlayer->GetPlayerName(), ctx.defendingPokemon->GetNameView());
			break;

		case Status::Sleeping:
			deps.resultsUI.DisplaySleepSuccess(ctx.defendingPlayer->GetPlayerName(), ctx.defendingPokemon->GetNameView());
			break;

		default:
			deps.resultsUI.DisplayNoopMsg();
	}

	ctx.defendingPokemon->ChangeStatus(status);
	if (status == Status::Badly_Poisoned)
	{
		ctx.defendingPokemon->ResetBadlyPoisonCounter();
	}

	if (status == Status::Sleeping)
	{
		unsigned int randomMod{ deps.rng.GetSleepTurnRoll() };
		ctx.defendingPokemon->SetSleepTurnCount(randomMod);
		ctx.defendingPokemon->ResetSleepCounter();
	}
}

bool DefendingPokemonIsFainted(BattleContext& context, IMoveResultsUI& resultsUI)
{
	if (context.defendingPokemon->IsFainted())
	{
		resultsUI.DisplayFailedTextDialog();
		return true;
	}
	return false;
}

void DamageRoutine(MoveRoutineDeps& deps)
{
	auto& ctx = deps.context;
	auto& calc = deps.calculations;
	auto& resultsUI = deps.resultsUI;

	unsigned int damage = calc.CalculateDamage(ctx, *ctx.defendingPlayer, *ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);
	calc.ApplyDamage(*ctx.currentMove, *ctx.defendingPokemon, damage);
	resultsUI.DisplayDirectDamageInflictedMsg(damage);
	resultsUI.DisplayCritTextDialog(ctx.flags.isCriticalHit);
	resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
	resultsUI.DisplaySubstituteDamageTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ctx.defendingPokemon->GetSubstituteHP(), ctx.defendingPokemon->HasSubstitute(), ctx.flags.hitSubstitute);

	TryDamageReactions(deps);
}

void IncreasedCriticalHitRoutine(MoveRoutineDeps& deps)
{
	auto& ctx = deps.context;

	int oldCritStage = ctx.attackingPokemon->GetCriticalHitStage();
	int newCritStage = oldCritStage + 1;

	ctx.attackingPokemon->SetCriticalHitStage(newCritStage);

	DamageRoutine(deps);

	ctx.attackingPokemon->SetCriticalHitStage(oldCritStage);
}

void MultiStrikeRoutine(MoveRoutineDeps& deps, int turnCount)
{
	auto& ctx = deps.context;

	int timesHit{};

	unsigned int totalDamage{};
	for (int i = 0; i < turnCount; ++i)
	{
		unsigned int damage = deps.calculations.CalculateDamage(ctx, *ctx.defendingPlayer, *ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);
		deps.calculations.ApplyDamage(*ctx.currentMove, *ctx.defendingPokemon, damage);

		totalDamage += damage;
		deps.resultsUI.DisplayCritTextDialog(ctx.flags.isCriticalHit);
		deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
		deps.resultsUI.DisplaySubstituteDamageTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ctx.defendingPokemon->GetSubstituteHP(), ctx.defendingPokemon->HasSubstitute(), ctx.flags.hitSubstitute);

		TryDamageReactions(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);

		++timesHit;

		if (ctx.defendingPokemon->GetCurrentHP() <= 0)
		{
			break;
		}

		if (ctx.currentMove->GetMoveEffectEnum() == MoveEffect::Twineedle)
		{
			InflictNVStatus(Status::Poisoned, ctx.currentMove->GetEffectChance(), deps);
		}
	}

	if (timesHit > 1)
	{
		deps.resultsUI.DisplayMultiAttackMsg(ctx.defendingPokemon->GetNameView(), timesHit);
	}

	deps.resultsUI.DisplayDirectDamageInflictedMsg(totalDamage);
}

void OHKODamageRoutine(MoveRoutineDeps& deps)
{
	auto& ctx = deps.context;
	auto& calc = deps.calculations;
	auto& resultsUI = deps.resultsUI;

	bool hitSubstitute = ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute();

	unsigned int damage = hitSubstitute ? ctx.defendingPokemon->GetSubstituteHP() : ctx.defendingPokemon->GetCurrentHP();

	calc.ApplyDamage(*ctx.currentMove, *ctx.defendingPokemon, damage);

	if (ctx.flags.hitSubstitute)
	{
		resultsUI.DisplaySubstituteDamageTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ctx.defendingPokemon->GetSubstituteHP(), ctx.defendingPokemon->HasSubstitute(), ctx.flags.hitSubstitute);
	}
	else
	{
		resultsUI.DisplayOHKOTextDialog();

		TryDamageReactions(deps);
	}
}

void FixedDamageRoutine(MoveRoutineDeps& deps, unsigned int fixedDamage)
{
	auto& ctx = deps.context;

	bool hasSubstitute = ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute();

	unsigned int maxDamage = hasSubstitute ? ctx.defendingPokemon->GetSubstituteHP() : ctx.defendingPokemon->GetCurrentHP();

	unsigned int finalDamage = std::min(fixedDamage, maxDamage);

	deps.calculations.ApplyDamage(*ctx.currentMove, *ctx.defendingPokemon, finalDamage);
	deps.resultsUI.DisplayDirectDamageInflictedMsg(fixedDamage);
	deps.resultsUI.DisplaySubstituteDamageTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ctx.defendingPokemon->GetSubstituteHP(), ctx.defendingPokemon->HasSubstitute(), ctx.flags.hitSubstitute);

	TryDamageReactions(deps);
}

void FlinchRoutine(MoveRoutineDeps& deps)
{
	auto& ctx = deps.context;

	if (ctx.defendingPokemon->GetCurrentHP() > 0 && !ctx.flags.hitSubstitute && !ctx.defendingPlayer->IsFirst())
	{
		int randomMod{ deps.rng.GetPercentRoll() };

		if (randomMod <= ctx.currentMove->GetEffectChance())
		{
			ctx.defendingPokemon->SetIsFlinched(true);
		}
	}
}

void RecoilRoutine(MoveRoutineDeps& deps, unsigned int recoilDivisor)
{
	auto& ctx = deps.context;

	unsigned int recoilDamage = ctx.lastDamageApplied / recoilDivisor;

	unsigned int finalDamage = std::max(1u, recoilDamage);

	ctx.attackingPokemon->DamageCurrentHP(finalDamage);

	deps.resultsUI.DisplayRecoilMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());

	deps.statusProcessor.CheckFaintCondition(*ctx.defendingPlayer, *ctx.attackingPlayer, *ctx.defendingPokemon, *ctx.attackingPokemon);
}

bool HandleCharging(MoveRoutineDeps& deps, ChargeMsgMemFn chargeMsg, const ChargingMoveHooks& hooks)
{
	auto& ctx = deps.context;
	auto* atkPlayer = ctx.attackingPlayer;
	auto* atkPkmn = ctx.attackingPokemon;

	if (!atkPkmn->IsCharging())
	{
		(deps.resultsUI.*chargeMsg)(atkPlayer->GetPlayerNameView(), atkPkmn->GetNameView());

		if (hooks.preCharge)
		{
			hooks.preCharge(deps);
		}

		if (hooks.stageUp)
		{
			unsigned int amount = hooks.stageIncreaseAmount;
			std::string_view stageName = hooks.stageName;

			hooks.stageUp(deps, amount, stageName, hooks.getStage, hooks.setStage);
		}

		atkPkmn->SetCharging(true);
		ctx.attackingPlayer->SetCanSwitch(false);

		return true;
	}

	atkPkmn->SetCharging(false);
	atkPlayer->SetCanSwitch(true);

	if (hooks.postCharge)
	{
		hooks.postCharge(deps);
	}

	return false;
}

void StageUpRoutine(MoveRoutineDeps& deps, int amount, std::string_view stageName, GetStageFn getStage, SetStageFn setStage)
{
	auto& ctx = deps.context;
	auto& atkPlayer = *ctx.attackingPlayer;
	auto& atkPkmn = *ctx.attackingPokemon;
	auto playerName = atkPlayer.GetPlayerNameView();
	auto pokemonName = atkPkmn.GetNameView();

	int stage{ getStage(atkPkmn) };

	int max{ 12 };
	int rise{ std::min(amount, max - stage) };

	if (rise <= 0)
	{
		deps.resultsUI.DisplayStatRaiseFailMsg(playerName, pokemonName, stageName);
		return;
	}

	setStage(atkPkmn, stage + rise);
	DisplayStatChange(deps.resultsUI, rise, true, playerName, pokemonName, stageName);
}

void StageDownRoutine(MoveRoutineDeps& deps, int amount, std::string_view stageName, GetStageFn getStage, SetStageFn setStage)
{
	auto& ctx = deps.context;
	auto& defPlayer = *ctx.defendingPlayer;
	auto& defPkmn = *ctx.defendingPokemon;
	auto playerName = defPlayer.GetPlayerNameView();
	auto pokemonName = defPkmn.GetNameView();

	int stage{ getStage(defPkmn) };

	int drop{ std::min(amount, stage) };

	if (drop <= 0)
	{
		deps.resultsUI.DisplayStatLoweredFailMsg(playerName, pokemonName, stageName);
		return;
	}

	setStage(defPkmn, stage - drop);

	DisplayStatChange(deps.resultsUI, drop, false, playerName, pokemonName, stageName);
}

void StageDownDamageRoutine(MoveRoutineDeps& deps, int amount, std::string_view stageName, GetStageFn getStage, SetStageFn setStage)
{
	auto& ctx = deps.context;
	auto& defPlayer = *ctx.defendingPlayer;
	auto& defPkmn = *ctx.defendingPokemon;
	auto playerName = defPlayer.GetPlayerNameView();
	auto pokemonName = defPkmn.GetNameView();

	if (defPkmn.GetCurrentHP() <= 0 || ctx.flags.hitSubstitute || defPlayer.HasMist())
	{
		return;
	}

	int stage = getStage(defPkmn);

	int drop{ std::min(amount, stage) };

	if (drop <= 0)
	{
		return;
	}

	int roll{ deps.rng.GetPercentRoll() };

	if (roll <= ctx.currentMove->GetEffectChance())
	{
		setStage(defPkmn, stage - drop);

		DisplayStatChange(deps.resultsUI, drop, false, playerName, pokemonName, stageName);
	}
}

void DisplayStatChange(IMoveResultsUI& ui, int amount, bool isUp, std::string_view playerName, std::string_view pokemonName, std::string_view stageName)
{
	if (amount == 1)
	{
		isUp ? ui.DisplayStatRaised1Msg(playerName, pokemonName, stageName)
			: ui.DisplayStatLowered1Msg(playerName, pokemonName, stageName);
	}
	else if (amount == 2)
	{
		isUp ? ui.DisplayStatRaised2Msg(playerName, pokemonName, stageName)
			: ui.DisplayStatLowered2Msg(playerName, pokemonName, stageName);
	}
}

void TryDamageReactions(MoveRoutineDeps& deps)
{
	ProcessRage(deps);
}

void ProcessRage(MoveRoutineDeps& deps)
{
	auto& ctx = deps.context;
	auto& resultsUI = deps.resultsUI;

	if (!ctx.attackingPokemon->IsRaging() && !ctx.defendingPokemon->IsRaging())
	{
		return;
	}

	if (ctx.defendingPokemon->IsRaging() &&
		((ctx.lastDamageApplied > 0 && !ctx.flags.hitSubstitute) ||
		ctx.currentMove->GetMoveEffectEnum() == MoveEffect::Disable)) // Target took damage or was targeted by Disable while raging
	{
		unsigned int attackStage = ctx.defendingPokemon->GetAttackStage();

		if (attackStage >= 12)
		{
			resultsUI.DisplayStatRaiseFailMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), "attack");
		}
		else
		{
			++attackStage;
			ctx.defendingPokemon->SetAttackStage(attackStage);
			resultsUI.DisplayStatRaised1Msg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), "attack");
		}
	}

	if (ctx.currentMove->GetMoveEffectEnum() == MoveEffect::Rage && !ctx.currentMove->b_isDisabled)
	{
		resultsUI.DisplayRageStartedMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
	}
}