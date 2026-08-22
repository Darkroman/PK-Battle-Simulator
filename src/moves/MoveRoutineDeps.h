#pragma once

class BattleCalculations;
class IMoveResultsUI;
class IStatusEffectUI;
class RandomEngine;
class StatusEffectProcessor;
struct BattleContext;

struct MoveRoutineDeps
{
	BattleContext& context;
	RandomEngine& rng;
	BattleCalculations& calculations;
	StatusEffectProcessor& statusProcessor;
	IMoveResultsUI& resultsUI;
	IStatusEffectUI& statusEffectUI;

	MoveRoutineDeps(BattleContext& ctx, RandomEngine& randomEngine, BattleCalculations& calc, StatusEffectProcessor& statusProc, IMoveResultsUI& results, IStatusEffectUI& statusEffectUI)
		: context(ctx)
		, rng(randomEngine)
		, calculations(calc)
		, statusProcessor(statusProc)
		, resultsUI(results)
		, statusEffectUI(statusEffectUI)
	{}
};