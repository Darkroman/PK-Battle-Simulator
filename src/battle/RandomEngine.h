#pragma once

#include <random>

class RandomEngine
{
private:
	unsigned int seed;
	int rng_calls{};
	std::mt19937 generator;

	std::uniform_int_distribution<size_t> reusableDist;
	std::uniform_int_distribution<unsigned int> distDamage{ 85, 100 };
	std::uniform_int_distribution<int> distPercent{ 1, 100 };
	std::uniform_int_distribution<int> distAccuracy{ 0, 99 };
	std::uniform_int_distribution<int> distCrit{ 0, 23 };
	std::uniform_int_distribution<unsigned int> distConfusionTurn{ 1, 4 };
	std::uniform_int_distribution<unsigned int> distSleepTurn{ 1, 3 };
	std::uniform_int_distribution<unsigned int> distBoundTurn{ 4, 5 };
	std::uniform_int_distribution<unsigned int> distRampageTurn{ 1, 2 };
	std::uniform_int_distribution<unsigned int> distPsyWave{ 0, 100 };
	std::uniform_int_distribution<unsigned int> distTriAttack{ 1, 3 };
	std::uniform_int_distribution<unsigned int> distAI{ 0, 255 };

public:
	RandomEngine();
	RandomEngine(int t);

	size_t RandomRange(size_t min, size_t max);
	unsigned int GetDamageRoll();
	int GetPercentRoll();
	int GetAccuracyRoll();
	int GetCritRoll();
	unsigned int GetConfusionTurnRoll();
	unsigned int GetSleepTurnRoll();
	unsigned int GetBoundTurnRoll();
	unsigned int GetRampageTurnRoll();
	unsigned int GetPsywaveDamageRoll();
	unsigned int GetTriAttackStatusRoll();
	void Call();
	void GetCallAmount();

	bool RandomLT(unsigned int value);

	std::mt19937& GetGenerator();
};