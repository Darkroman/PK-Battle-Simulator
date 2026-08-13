#include "AISwitchLogic.h"

#include <array>
#include <span>
#include <algorithm>
#include <tuple>

#include "../AIController.h"
#include "../move scoring/AIMoveScoring.h"
#include "../../pokemonMove.h"
#include "../../BattlePokemon.h"
#include "../../Player.h"
#include "../../../battle/RandomEngine.h"
#include "../../../data/StringToTypes.h"

namespace AISwitchLogic
{
	bool WantsToSwitch(const Player& self, const Player& targetPlayer, const BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng)
	{
		// if on last pokemon, don't switch
		if (self.GetPokemonLeft() < 2)
		{
			return false;
		}

		if (selfMon.WillPerformStruggle())
		{
			int willPerformStruggleCount{ 0 };
			for (const auto& pokemon : self.GetBeltArray())
			{
				if (!pokemon.HasPokemon() || pokemon.IsFainted() || &pokemon == &selfMon)
				{
					continue;
				}

				if (pokemon.WillPerformStruggle())
				{
					++willPerformStruggleCount;
				}
			}

			if (willPerformStruggleCount < self.GetPokemonLeft() - 1)
			{
				return true;
			}
		}

		unsigned int highestDamage{ 0 };
		const pokemonMove* highestDamagingMove{};

		bool canKO{};
		bool priorityCanKO{};

		for (const auto& move : selfMon.GetMoveArray())
		{
			if (move.IsActive() && move.GetCategoryEnum() != Category::Status) 
			{
				unsigned int damage = AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), targetPlayer, move, selfMon, targetMon);

				if (damage > highestDamage)
				{
					highestDamage = damage;
					highestDamagingMove = &move;
				}

				if (highestDamage >= targetMon.GetCurrentHP())
				{
					canKO = true;
				}

				if (move.GetPriority() > 0 && damage >= targetMon.GetCurrentHP())
				{
					priorityCanKO = true;
				}
			}
		}

		// if all moves are immune or all status moves, switch
		if (highestDamage == 0)
		{
			return true;
		}

		unsigned int selfMonSpeed = AIMoveScoring::CalculateSpeed(selfMon);
		unsigned int targetMonSpeed = AIMoveScoring::CalculateSpeed(targetMon);

		bool isFaster{ selfMonSpeed >= targetMonSpeed };

		// if selfMon is faster and has move that can one-hit KO targetMon, don't switch
		if (isFaster && canKO)
		{
			return false;
		}

		// if selfMon has priority move that can KO targetMon, don't switch (and self is hard difficulty)
		if (self.GetAIController().GetDifficulty() == Difficulty::Hard && priorityCanKO)
		{
			return false;
		}

		bool targetCantAttack = (targetMon.GetStatus() == Status::Frozen || targetMon.GetStatus() == Status::Sleeping);

		// if targetMon is asleep or frozen, don't switch
		if (targetCantAttack)
		{
			return false;
		}

		const pokemonMove* targetMonLastUsedMove = targetMon.GetLastUsedMove();
		bool lastUsedMoveAvailable = targetMonLastUsedMove != nullptr &&
			targetMonLastUsedMove->IsActive() &&
			targetMonLastUsedMove->GetCategoryEnum() != Category::Status;

		if (!isFaster && lastUsedMoveAvailable)
		{
			unsigned int lastMoveDamage = AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), self, *targetMonLastUsedMove, targetMon, selfMon);

			if (lastMoveDamage >= selfMon.GetCurrentHP())
			{
				// if last move used by targetMon can KO selfMon and selfMon is slower, switch
				return true;
			}
		}

		if (self.GetAIController().GetDifficulty() == Difficulty::Hard)
		{
			bool selfTypingDisadvantageous{ PokemonTypeEffectiveness(self, targetMon, selfMon) > 4096 };

			// if selfMon is slower and typing is disadvantageous, switch
			if (!isFaster && selfTypingDisadvantageous)
			{
				return true;
			}

			bool isNotVeryEffective{ IsMoveNotVeryEffective(self, *highestDamagingMove, targetMon) };

			// if selfMon's typing is disadvantageous and highest damaging move is not very effective and cannot KO, switch
			if (selfTypingDisadvantageous && isNotVeryEffective && !canKO)
			{
				return true;
			}
			
			// If selfMon is faster, skip the rest of the evaluation
			if (isFaster)
			{
				return false;
			}
			
			const auto& observedMoves = self.GetAIController().GetObservedMoves();

			for (const auto& observedMove : observedMoves)
			{
				if (observedMove == targetMonLastUsedMove)
				{
					continue;
				}

				if (!observedMove->IsActive() || observedMove->GetCategoryEnum() == Category::Status)
				{
					continue;
				}

				unsigned int damageToSelf{ AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), self, *observedMove, targetMon, selfMon) };

				// If selfMon is slower and targetMon has a move that can KO, switch
				if (damageToSelf >= selfMon.GetCurrentHP())
				{
					return true;
				}
			}
		}
		
		return false;
	}

	BattlePokemon* ChooseSwitch(Player& self, const Player& targetPlayer, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		struct CandidatePokemon
		{
			BattlePokemon* pokemon{};
			unsigned int typeEffectiveness{};
			unsigned int highestDamageMove{};
			bool isFaster{};
			bool canKO{};
			bool canSurviveTwoHits{};
			bool canSurviveOneHit{};
		};

		std::array<CandidatePokemon, 6> candidatePkmnPool{};

		auto canAttack = [&](const BattlePokemon& pokemon) -> bool { return pokemon.GetStatus() != Status::Frozen && pokemon.GetStatus() != Status::Sleeping; };

		size_t count{};
		for (auto& pokemon : self.GetBeltArray())
		{
			if (pokemon.HasPokemon() && !pokemon.IsFainted() && canAttack(pokemon))
			{
				candidatePkmnPool[count].pokemon = &pokemon;
				++count;
			}
		}

		// If no candidates found, return without switching.
		if (count == 0)
		{
			return nullptr;
		}

		std::span<CandidatePokemon> candidatePkmn{ candidatePkmnPool.data(), count };

		const auto& observedMoves = self.GetAIController().GetObservedMoves();
		std::array<const pokemonMove*, 4> observedDamagingMoves{};
		size_t observedCount{};

		for (const auto& observedMove : observedMoves)
		{
			if (!observedMove->IsActive() || observedMove->GetCategoryEnum() == Category::Status)
			{
				continue;
			}

			observedDamagingMoves[observedCount] = observedMove;
			++observedCount;
		}

		std::span<const pokemonMove*> validObservedMoves{ observedDamagingMoves.data(), observedCount };

		unsigned int highestDamageToSelf{ 0 };
		const pokemonMove* mostLikelyMove{};
		if (!validObservedMoves.empty())
		{
			mostLikelyMove = validObservedMoves.front();
			// Evaluate most likely observed move AI will do against selfMon
			for (const auto& observedMove : validObservedMoves)
			{
				unsigned int damageToSelf = AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), self, *observedMove, targetMon, selfMon);

				if (damageToSelf > highestDamageToSelf)
				{
					highestDamageToSelf = damageToSelf;
					mostLikelyMove = observedMove;
				}
			}
		}

		unsigned int targetMonSpeed = AIMoveScoring::CalculateSpeed(targetMon);

		for (auto& candidate : candidatePkmn)
		{
			for (const auto& move : candidate.pokemon->GetMoveArray())
			{
				if (move.IsActive() && move.GetCategoryEnum() != Category::Status)
				{
					unsigned int damage = AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), targetPlayer, move, *candidate.pokemon, targetMon);

					if (damage > candidate.highestDamageMove)
					{
						candidate.highestDamageMove = damage;
					}
				}
			}

			candidate.typeEffectiveness = PokemonTypeEffectiveness(self, targetMon, *candidate.pokemon);

			unsigned int candidateMonSpeed = AIMoveScoring::CalculateSpeed(*candidate.pokemon);

			candidate.isFaster = candidateMonSpeed >= targetMonSpeed;

			candidate.canKO = !targetMon.IsFainted() && candidate.highestDamageMove >= targetMon.GetCurrentHP();

			if (mostLikelyMove != nullptr)
			{
				unsigned int firstAttackVsCandidate = AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), self, *mostLikelyMove, targetMon, *candidate.pokemon);
				unsigned int secondAttackVsCandidate{ firstAttackVsCandidate };

				// Evaluate most likely observed move AI will do against candidateMon
				for (const auto& observedMove : validObservedMoves)
				{
					if (observedMove == mostLikelyMove)
					{
						continue;
					}

					unsigned int damageToCandidate = AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), self, *observedMove, targetMon, *candidate.pokemon);
					if (damageToCandidate > secondAttackVsCandidate)
					{
						secondAttackVsCandidate = damageToCandidate;
					}
				}

				candidate.canSurviveOneHit = firstAttackVsCandidate < candidate.pokemon->GetCurrentHP();

				candidate.canSurviveTwoHits = (firstAttackVsCandidate + secondAttackVsCandidate) < candidate.pokemon->GetCurrentHP();
			}
		}

		auto getPriority = [&](const CandidatePokemon& candidate)
			{
				if (!validObservedMoves.empty())
				{
					if (candidate.canKO && candidate.isFaster && candidate.canSurviveOneHit)
					{
						return 2u;
					}

					if (candidate.canKO && candidate.canSurviveTwoHits)
					{
						return 1u;
					}

					return 0u;
				}

				if (candidate.canKO && candidate.typeEffectiveness <= 2048)
				{
					return 3u;
				}

				if (candidate.canKO && candidate.isFaster && candidate.pokemon->GetCurrentHP() == candidate.pokemon->GetMaxHP())
				{
					return 2u;
				}

				if (candidate.typeEffectiveness <= 2048)
				{
					return 1u;
				}

				return 0u;
			};

		auto it = std::max_element(candidatePkmn.begin(), candidatePkmn.end(),
			[&](const CandidatePokemon& a, const CandidatePokemon& b)
			{
				return std::tuple{
					getPriority(a),
					-static_cast<int>(a.typeEffectiveness),
					a.highestDamageMove
				}
				<
					std::tuple{
					getPriority(b),
					-static_cast<int>(b.typeEffectiveness),
					b.highestDamageMove
			};
		});

		if (it == candidatePkmn.end() || getPriority(*it) == 0)
		{
			return nullptr;
		}

		if (it->pokemon == &selfMon)
		{
			return nullptr;
		}

		return it->pokemon;
	}

	BattlePokemon* ChoosePostKOSwitch(Player& self, const Player& targetPlayer, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		struct CandidatePokemon
		{
			BattlePokemon* pokemon{};
			unsigned int typeEffectiveness{};
			unsigned int highestDamageMove{};
			bool isFaster{};
			bool canKO{};
			bool canSurviveOneHit{};
			bool canAttack{ false };
		};

		std::array<CandidatePokemon, 6> candidatePkmnPool{};

		auto canAttack = [&](const BattlePokemon& pokemon) -> bool { return pokemon.GetStatus() != Status::Frozen && pokemon.GetStatus() != Status::Sleeping; };

		size_t count{};
		for (auto& pokemon : self.GetBeltArray())
		{
			if (pokemon.HasPokemon() && !pokemon.IsFainted() && &pokemon != &selfMon)
			{
				candidatePkmnPool[count].pokemon = &pokemon;
				candidatePkmnPool[count].canAttack = canAttack(pokemon);

				++count;
			}
		}

		std::span<CandidatePokemon> candidatePkmn{ candidatePkmnPool.data(), count };

		const auto& observedMoves = self.GetAIController().GetObservedMoves();
		std::array<const pokemonMove*, 4> observedDamagingMoves{};
		size_t observedCount{};

		for (const auto& observedMove : observedMoves)
		{
			if (!observedMove->IsActive() || observedMove->GetCategoryEnum() == Category::Status)
			{
				continue;
			}

			observedDamagingMoves[observedCount] = observedMove;
			++observedCount;
		}

		std::span<const pokemonMove*> validObservedMoves{ observedDamagingMoves.data(), observedCount };

		unsigned int targetMonSpeed = AIMoveScoring::CalculateSpeed(targetMon);

		for (auto& candidate : candidatePkmn)
		{
			for (const auto& move : candidate.pokemon->GetMoveArray())
			{
				if (move.IsActive() && move.GetCategoryEnum() != Category::Status)
				{
					unsigned int damage = AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), targetPlayer, move, *candidate.pokemon, targetMon);

					if (damage > candidate.highestDamageMove)
					{
						candidate.highestDamageMove = damage;
					}
				}
			}

			candidate.typeEffectiveness = PokemonTypeEffectiveness(self, targetMon, *candidate.pokemon);

			unsigned int candidateMonSpeed = AIMoveScoring::CalculateSpeed(*candidate.pokemon);

			candidate.isFaster = candidateMonSpeed >= targetMonSpeed;

			candidate.canKO = !targetMon.IsFainted() && candidate.highestDamageMove >= targetMon.GetCurrentHP();

			if (!validObservedMoves.empty())
			{
				unsigned int highestDamageToCandidate{ 0 };
				for (const auto& observedMove : validObservedMoves)
				{
					unsigned int damageToCandidate = AIMoveScoring::SwitchDamageScoringRoutine(self.GetAIController(), self, *observedMove, targetMon, *candidate.pokemon);

					if (damageToCandidate > highestDamageToCandidate)
					{
						highestDamageToCandidate = damageToCandidate;
					}
				}

				candidate.canSurviveOneHit = highestDamageToCandidate < candidate.pokemon->GetCurrentHP();
			}
		}

		auto getPriority = [&](const CandidatePokemon& candidate)
			{
				if (!validObservedMoves.empty())
				{
					if (candidate.canKO && candidate.isFaster)
					{
						return 5u;
					}

					if (candidate.canKO && candidate.canSurviveOneHit)
					{
						return 4u;
					}

					if (candidate.isFaster && candidate.canSurviveOneHit)
					{
						return 3u;
					}

					if (candidate.canSurviveOneHit)
					{
						return 2u;
					}

					if (candidate.isFaster)
					{
						return 1u;
					}

					return 0u;
				}

				if (candidate.canKO && candidate.isFaster)
				{
					return 2u;
				}

				if (candidate.isFaster)
				{
					return 1u;
				}

				return 0u;
			};

		auto it = std::max_element(candidatePkmn.begin(), candidatePkmn.end(),
			[&](const CandidatePokemon& a, const CandidatePokemon& b)
			{
				return std::tuple{
				a.canAttack, 
				getPriority(a),
				-static_cast<int>(a.typeEffectiveness),
				a.highestDamageMove
				}
				<
				std::tuple{
				b.canAttack,
				getPriority(b),
				-static_cast<int>(b.typeEffectiveness),
				b.highestDamageMove
			};
		});

		return it->pokemon;
	}

	bool IsMoveSuperEffective(const Player& self, const pokemonMove& move, const BattlePokemon& pokemon)
	{
		auto MoveEffectiveness = [&](const pokemonMove& move, const BattlePokemon& targetMon) {
			return self.GetAIController().AICalculateMoveTypeEffectiveness(move, targetMon);
			};

		return MoveEffectiveness(move, pokemon) > 4096 && move.GetPower() > 0 && move.m_currentPP > 0;
	}

	bool IsMoveAtMostEffective(const Player& self, const pokemonMove& move, const BattlePokemon& pokemon)
	{
		auto MoveEffectiveness = [&](const pokemonMove& move, const BattlePokemon& targetMon) {
			return self.GetAIController().AICalculateMoveTypeEffectiveness(move, targetMon);
			};

		return MoveEffectiveness(move, pokemon) <= 4096 && move.GetPower() > 0 && move.m_currentPP > 0;
	}

	bool IsMoveAtLeastEffective(const Player& self, const pokemonMove& move, const BattlePokemon& pokemon)
	{
		auto MoveEffectiveness = [&](const pokemonMove& move, const BattlePokemon& targetMon) {
			return self.GetAIController().AICalculateMoveTypeEffectiveness(move, targetMon);
			};

		return MoveEffectiveness(move, pokemon) >= 4096 && move.GetPower() > 0 && move.m_currentPP > 0;
	}

	bool IsMoveNotEffective(const Player& self, const pokemonMove& move, const BattlePokemon& pokemon)
	{
		auto MoveEffectiveness = [&](const pokemonMove& move, const BattlePokemon& targetMon) {
			return self.GetAIController().AICalculateMoveTypeEffectiveness(move, targetMon);
			};

		return MoveEffectiveness(move, pokemon) == 0 && move.GetPower() > 0 && move.m_currentPP > 0;
	}

	bool IsMoveNotVeryEffective(const Player& self, const pokemonMove& move, const BattlePokemon& pokemon)
	{
		auto MoveEffectiveness = [&](const pokemonMove& move, const BattlePokemon& targetMon) {
			return self.GetAIController().AICalculateMoveTypeEffectiveness(move, targetMon);
			};

		return MoveEffectiveness(move, pokemon) <= 2048 && move.GetPower() > 0 && move.m_currentPP > 0;
	}

	bool IsStatusMoveEffective(const Player& self, const Player& targetPlayer, const pokemonMove& move, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		return self.GetAIController().CalculateStatusMoveEffectiveness(move, self, targetPlayer, selfMon, targetMon) && move.m_currentPP > 0;
	}

	unsigned int PokemonTypeEffectiveness(const Player& self, const BattlePokemon& source, const BattlePokemon& target)
	{
		return self.GetAIController().AICalculatePokemonTypeEffectiveness(source, target);
	}
}