#pragma once

#include <span>

class Player;
class BattlePokemon;
struct pokemonMove;
class RandomEngine;
enum class MoveID;
enum class MoveEffect;

#include "ScoringResultsStruct.h"

namespace HardAIMoveScoring
{
	bool MirrorMoveIDFound(MoveID id);

	bool SpeedUpMoveEffectFound(MoveEffect effect);

	ScoringResults RunExpertScoringRoutine(ScoringResults& result, std::span<ScoringResults>& results, const Player& self, const Player& targetPlayer, const pokemonMove& move, const BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng);

	int SleepMove(std::span<ScoringResults>& results, RandomEngine& rng);

	int SelfFaintingDamage(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int DreamEater(RandomEngine& rng, const BattlePokemon& targetMon);

	int MirrorMove(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int SelfAttackBoost(RandomEngine& rng, const BattlePokemon& selfMon);

	int SelfDefenseBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int SelfSpeedBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);

	int SelfSpABoost(RandomEngine& rng, const BattlePokemon& selfMon);

	int SelfSpDBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon);


}