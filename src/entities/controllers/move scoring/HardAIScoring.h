#pragma once

#include "ScoringResultsStruct.h"

#include <span>

enum class MoveEffect;
enum class MoveID;
class AIController;
class BattlePokemon;
class Player;
class RandomEngine;
struct PokemonMoveSlot;

namespace HardAIMoveScoring
{
	bool MirrorMoveIDFound(MoveID id);

	bool SpeedUpMoveEffectFound(MoveEffect effect);

	void RunExpertScoringRoutine(ScoringResults& result, std::span<ScoringResults>& results, const Player& self, const Player& targetPlayer, const PokemonMoveSlot& move, const BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng);

	int SleepMove(std::span<ScoringResults>& results, RandomEngine& rng);

	int SelfFaintingDamage(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int DreamEater(RandomEngine& rng, const BattlePokemon& targetMon);

	int MirrorMove(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int SelfAttackBoost(RandomEngine& rng, const BattlePokemon& selfMon);

	int SelfDefenseBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int SelfSpeedBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	//int SelfSpABoost(RandomEngine& rng, const BattlePokemon& selfMon);

	int SelfSpDBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	//int SelfAccuracyBoost(RandomEngine& rng, const BattlePokemon& selfMon);

	int SelfEvasionBoost(RandomEngine& rng, AIController& self, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int Growth(RandomEngine& rng, const BattlePokemon& selfMon);

	int AlwaysHit(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int TargetAttackDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int TargetDefenseDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int TargetSpeedDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	//int TargetSpecialAttackDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	//int TargetSpecialDefenseDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	// future gens will require ingrain, aqua ring and curse
	int TargetAccuracyDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	//int TargetEvasionDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);
}