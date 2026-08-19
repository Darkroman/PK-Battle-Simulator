#include <algorithm>
#include <array>
#include <cassert>
#include <span>
#include <climits>

#include "AIMoveScoring.h"

#include "ScoringResultsStruct.h"
#include "BasicScoring.h"
#include "MediumMoveScoring.h"
#include "HardAIScoring.h"

#include "AIMoveClassifier.h"
#include "../../../battle/StageRatios.h"
#include "../../../battle/RandomEngine.h"
#include "../../../data/StringToTypes.h"
#include "../../pokemonMove.h"
#include "../../BattlePokemon.h"
#include "../../Player.h"
#include "../AIController.h"

namespace AIMoveScoring
{
	pokemonMove* GetWinningMove(const Player& self, const Player& targetPlayer, BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng)
	{
		std::array<ScoringResults, 4> results{};

		auto moveArray = selfMon.GetMoveArray();

		size_t index{};
		for (int i{}; i < 4; ++i)
		{
			if (!moveArray[i].IsActive())
			{
				continue;
			}

			results[index].score = 100;
			results[index].move = &moveArray[i];
			results[index].tag = AIMoveClassifier::Classify(*results[index].move);

			++index;
		}

		std::span<ScoringResults> resultsView{ results.data(), index };

		for (auto& result : resultsView)
		{
			RunScoringRoutine(result, self, targetPlayer, *result.move, selfMon, targetMon);
		}

		if (self.GetAIController().GetDifficulty() >= Difficulty::Medium)
		{
			MediumMoveScoring::EvaluateBestDamageMove(resultsView, targetMon);
		}
		
		if (self.GetAIController().GetDifficulty() == Difficulty::Hard)
		{
			for (auto& result : resultsView)
			{
				HardAIMoveScoring::RunExpertScoringRoutine(result, resultsView, self, targetPlayer, *result.move, selfMon, targetMon, rng);
			}
		}
		
		//pokemonMove* winningMove = EvaluateScoredMoves(results, rng);
		//return winningMove;

		return EvaluateScoredMoves(resultsView, rng);
	}

	pokemonMove* EvaluateScoredMoves(std::span<ScoringResults>& results, RandomEngine& rng)
	{
		int highestScore = INT_MIN;
		for (const auto& result : results)
		{
			highestScore = std::max(highestScore, result.score);
		}

		std::array<ScoringResults*, 4> topScores{};
		size_t count{};
		for (auto& result : results)
		{
			if (result.score == highestScore)
			{
				topScores[count] = &result;
				++count;
			}
		}

		assert(!results.empty());
		assert(count > 0);

		return topScores[rng.RandomRange(0ull, count - 1ull)]->move;
	}

	void RunScoringRoutine(ScoringResults& results, const Player& self, const Player& targetPlayer, const pokemonMove& move, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		if (move.GetCategoryEnum() == Category::Status)
		{
			results.score += BasicScoring::BaseStatusScoring(results, self, targetPlayer, move, selfMon, targetMon);
		}
		else
		{
			AIController& ai = self.GetAIController();
			unsigned int effectiveness = ai.AICalculateMoveTypeEffectiveness(move, targetMon);
			results.score += BasicScoring::BaseDamageScoring(results, self, targetPlayer, selfMon, targetMon, effectiveness);
			results.damage = ai.AICalculateDamage(move, targetPlayer, selfMon, targetMon, effectiveness);
		}
	}

	unsigned int CalculateSpeed(const BattlePokemon& pokemon)
	{
		auto [numerator, denominator] = GetStageRatio(pokemon.GetSpeedStage());

		unsigned int speed = pokemon.GetSpeed() * numerator / denominator;

		if (pokemon.GetStatus() == Status::Paralyzed)
		{
			speed /= 2;
		}

		return speed;
	}
}