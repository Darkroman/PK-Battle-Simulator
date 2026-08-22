#pragma once

#include <array>

class BattlePokemon;
class Player;
class RandomEngine;
struct BattleContext;
struct PokemonMoveSlot;

class BattleCalculations
{
public:
	BattleCalculations(BattleContext&, RandomEngine&);

	unsigned int CalculatePokemonSpeed(const BattlePokemon&);

	void RandomizeTurnOrder();

	void RandomizePostTurnOrder();

	void SetFirst(Player&, Player&);

	bool CalculateCriticalHit(BattleContext&, const BattlePokemon&);

	unsigned int MultiplyEffectiveness(unsigned int, unsigned int);

	void CalculateTypeEffectiveness(BattleContext&, const PokemonMoveSlot&, const BattlePokemon&);

	bool CalculateHitChance(const PokemonMoveSlot&, const BattlePokemon&, const BattlePokemon&);

	unsigned int CalculateDamage(BattleContext&, const Player&, const PokemonMoveSlot&, const BattlePokemon&, BattlePokemon&);

	void ApplyDamage(const PokemonMoveSlot&, BattlePokemon&, unsigned int);

	unsigned int CalculateLowKickPower(const BattlePokemon&);

private:
	RandomEngine& m_rng;
	BattleContext& m_context;

public:
	const std::array<int, 4> m_arr_CriticalHitStageThresholds{ 1, 3, 12, 24 }; // For critical hit

};