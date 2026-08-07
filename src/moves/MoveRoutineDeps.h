#pragma once

struct BattleContext;
class BattleCalculations;
class StatusEffectProcessor;
class IMoveResultsUI;
class RandomEngine;

struct MoveRoutineDeps
{
	BattleContext& context;
	BattleCalculations& calculations;
	StatusEffectProcessor& statusProcessor;
	IMoveResultsUI& resultsUI;
	RandomEngine& rng;

	MoveRoutineDeps(BattleContext& ctx, BattleCalculations& calc, StatusEffectProcessor& statusProc, IMoveResultsUI& results, RandomEngine& randomEngine)
		: context(ctx)
		, calculations(calc)
		, statusProcessor(statusProc)
		, resultsUI(results)
		, rng(randomEngine)
	{}
};