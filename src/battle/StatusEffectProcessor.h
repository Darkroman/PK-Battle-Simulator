#pragma once

struct BattleContext;
class RandomEngine;
class IStatusEffectUI;
class Player;
class BattlePokemon;

class StatusEffectProcessor
{
public:
	StatusEffectProcessor(BattleContext&, RandomEngine&, IStatusEffectUI&);

	bool CheckPerformativeStatus();
	bool SleepStatus();
	bool FrozenStatus();
	bool FlinchStatus();
	bool ConfusedStatus();
	bool ParalysisStatus();

	void ResetRampageState();
	void RampageConfuse();

	void ResetBideState();

	void CheckSubstituteCondition(Player*, BattlePokemon*);

	void CheckFaintCondition(Player& sourcePlayer, Player& targetPlayer, BattlePokemon& sourcePokemon, BattlePokemon& targetPokemon);

private:
	BattleContext& m_context;
	RandomEngine& m_rng;
	IStatusEffectUI& m_statusEffectUI;
};