//#include <chrono>
#include <random>
//#include <iostream>

#include "RandomEngine.h"

RandomEngine::RandomEngine()
	:
	seed(12345),
	//seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())),
	generator(seed)
{

}

RandomEngine::RandomEngine(int t)
	:
	seed(12345),
	//seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())),
	generator(seed)
{

}
/*
void RandomEngine::Call() const
{
	std::cout << "RNG called.\n";
}


void RandomEngine::GetCallAmount() const
{
	std::cout << "RNG Calls: " << rng_calls << '\n';
}
*/

std::mt19937& RandomEngine::GetGenerator()
{
	//Call();
	//++rng_calls;
	return generator;
}

size_t RandomEngine::RandomRange(size_t min, size_t max)
{
	//Call();
	//++rng_calls;
	reusableDist.param(std::uniform_int_distribution<size_t>::param_type(min, max));

	return reusableDist(generator);
}

unsigned int RandomEngine::GetDamageRoll()
{
	//Call();
	//++rng_calls;
	return distDamage(generator);
}

int RandomEngine::GetPercentRoll()
{
	//Call();
	//++rng_calls;
	return distPercent(generator);
}

int RandomEngine::GetAccuracyRoll()
{
	//Call();
	//++rng_calls;
	return distAccuracy(generator);
}

int RandomEngine::GetCritRoll()
{
	//Call();
	//++rng_calls;
	return distCrit(generator);
}

unsigned int RandomEngine::GetConfusionTurnRoll()
{
	//Call();
	//++rng_calls;
	return distConfusionTurn(generator);
}

unsigned int RandomEngine::GetSleepTurnRoll()
{
	//Call();
	//++rng_calls;
	return distSleepTurn(generator);
}

unsigned int RandomEngine::GetBoundTurnRoll()
{
	//Call();
	//++rng_calls;
	return distBoundTurn(generator);
}

unsigned int RandomEngine::GetRampageTurnRoll()
{
	//Call();
	//++rng_calls;
	return distRampageTurn(generator);
}

unsigned int RandomEngine::GetPsywaveDamageRoll()
{
	//Call();
	//++rng_calls;
	return distPsyWave(generator);
}

unsigned int RandomEngine::GetTriAttackStatusRoll()
{
	//Call();
	//++rng_calls;
	return distTriAttack(generator);
}

bool RandomEngine::RandomLT(unsigned int threshold)
{
	//Call();
	//++rng_calls;
	unsigned int randomNum{ distAI(generator) };

	return randomNum < threshold;
}