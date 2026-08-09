#pragma once

struct BattleContext;
class BattleCalculations;
class StatusEffectProcessor;
class IMoveResultsUI;
class IStatusEffectUI;
class RandomEngine;

struct MoveRoutineDeps
{
	BattleContext& context;
	BattleCalculations& calculations;
	StatusEffectProcessor& statusProcessor;
	IMoveResultsUI& resultsUI;
	IStatusEffectUI& statusEffectUI;
	RandomEngine& rng;

	MoveRoutineDeps(BattleContext& ctx, BattleCalculations& calc, StatusEffectProcessor& statusProc, IMoveResultsUI& results, IStatusEffectUI& statusEffectUI, RandomEngine& randomEngine)
		: context(ctx)
		, calculations(calc)
		, statusProcessor(statusProc)
		, resultsUI(results)
		, statusEffectUI(statusEffectUI)
		, rng(randomEngine)
	{}
};