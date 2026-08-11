#include <array>
#include <algorithm>

#include "HardAIScoring.h"

#include "AIScoreTag.h"
#include "AIMoveScoring.h"
#include "ScoringResultsStruct.h"
#include "../AIController.h"
#include "../../Player.h"
#include "../../pokemonMove.h"
#include "../../BattlePokemon.h"
#include "../../../data/MoveID.h"
#include "../../../data/StringToTypes.h"
#include "../../../battle/RandomEngine.h"
#include "../../../moves/MoveEffectEnums.h"

// Largely based on Da Squyd's reverse-engineered Gen 5 Expert AI scripts in his flag2.ais file
// https://docs.google.com/document/d/1AziiMPsY1TcABKIwl92677A4nYGtByvjFOR7p6PAXY0

namespace HardAIMoveScoring
{
	bool MirrorMoveIDFound(MoveID id)
	{
		switch (id)
		{
			case MoveID::Guillotine:
			case MoveID::SandAttack:
			case MoveID::HornDrill:
			case MoveID::Sing:
			case MoveID::HyperBeam:
			case MoveID::PoisonPowder:
			case MoveID::SleepPowder:
			case MoveID::ThunderWave:
			case MoveID::Fissure:
			case MoveID::Toxic:
			case MoveID::Hypnosis:
			case MoveID::Screech:
			case MoveID::Smokescreen:
			case MoveID::ConfuseRay:
			case MoveID::Glare:
			case MoveID::LovelyKiss:
			case MoveID::Spore:
				return true;
			default:
				return false;
		}
	}

	bool SpeedUpMoveEffectFound(MoveEffect effect)
	{
		switch (effect)
		{
			case MoveEffect::Stomp:
			case MoveEffect::FlinchHit:
			case MoveEffect::HealHalfHP:
			case MoveEffect::Rest:
			case MoveEffect::Substitute:
				return true;
			default:
				return false;
		}
	}

	ScoringResults RunExpertScoringRoutine(ScoringResults& result, std::span<ScoringResults>& results, const Player& self, const Player& targetPlayer, const pokemonMove& move, const BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng)
	{
		int delta{};

		auto tags = result.tag;

		switch (tags)
		{
			case AIScoreTag::Sleep:
			{
				delta += SleepMove(results, rng); // if user has Dream Eater, roll for 50% chance to add 1 to move score
			}
			break;

			case AIScoreTag::SelfFaintingDamage:
			{
				delta += SelfFaintingDamage(rng, selfMon, targetMon);
			}
			break;

			case AIScoreTag::DreamEater:
			{
				delta += DreamEater(rng, targetMon);
			}
			break;

			case AIScoreTag::MirrorMove:
			{
				delta += MirrorMove(rng, selfMon, targetMon);
			}
			break;

			case AIScoreTag::SelfAttackBoost:
			{
				delta += SelfAttackBoost(rng, selfMon);
			}
			break;

			case AIScoreTag::SelfDefenseBoost:
			{
				delta += SelfDefenseBoost(rng, selfMon, targetMon);
			}
			break;

			case AIScoreTag::SelfSpeedBoost:
			{
				delta += SelfSpeedBoost(rng, selfMon, targetMon);
			}
			break;

			case AIScoreTag::SelfSpABoost:
			{
				delta += SelfSpABoost(rng, selfMon);
			}
			break;


		}

		result.score += delta;

		return result;
		
	}

	int SleepMove(std::span<ScoringResults>& results, RandomEngine& rng)
	{
		int delta{};

		for (auto& result : results)
		{
			if (result.tag != AIScoreTag::DreamEater)
			{
				continue;
			}

			if (!rng.RandomLT(128)) // 50% chance to add 1 to move score
			{
				delta += 1;
			}

			break;

		}

		return delta;
	}

	int SelfFaintingDamage(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		int targetEvasionStage{ targetMon.GetEvasionStage() };

		if (targetEvasionStage >= 7)
		{
			delta -= 1;

			if (targetEvasionStage >= 10 && !rng.RandomLT(128))
			{
				delta -= 1;
			}
		}

		unsigned int currentHPPercent{ selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP() };

		if (currentHPPercent >= 80 && AIMoveScoring::CalculateSpeed(selfMon) > AIMoveScoring::CalculateSpeed(targetMon))
		{
			if (!rng.RandomLT(50)) // 80.46875%
			{
				delta -= 3;
			}

			return delta;
		}

		if (currentHPPercent >= 50)
		{
			if (!rng.RandomLT(50)) // 80.46875%
			{
				delta -= 1;
			}

			return delta;
		}

		if (rng.RandomLT(128)) // 50%
		{
			delta += 1;
		}

		if (currentHPPercent >= 30)
		{
			return delta;
		}


		if (rng.RandomLT(128)) // 50%
		{
			delta += 1;
		}
		
		return delta;
	}

	int DreamEater(RandomEngine& rng, const BattlePokemon& targetMon)
	{
		int delta{};

		if (targetMon.GetStatus() == Status::Sleeping && !rng.RandomLT(51)) // 80.078125%
		{
			delta += 3;
		}

		return delta;
	}

	int MirrorMove(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		pokemonMove* targetLastUsedMove{ targetMon.GetLastUsedMove() };
		MoveID targetLastUsedMoveID{};
		if (targetLastUsedMove)
		{
			targetLastUsedMoveID = targetMon.GetLastUsedMove()->GetMoveID();
		}

		bool moveFound = MirrorMoveIDFound(targetLastUsedMoveID);

		int delta{};

		if (!moveFound)
		{
			if (!rng.RandomLT(80)) // 68.75%
			{
				delta -= 1;
			}

			return delta;
		}

		bool userIsFaster{ AIMoveScoring::CalculateSpeed(selfMon) > AIMoveScoring::CalculateSpeed(targetMon) };

		if (moveFound && userIsFaster)
		{
			if (!rng.RandomLT(128)) // 50%
			{
				delta += 2;
			}

			return delta;
		}

		return delta;
	}

	int SelfAttackBoost(RandomEngine& rng, const BattlePokemon& selfMon)
	{
		int delta{};
		
		int currentAttackStage{ selfMon.GetAttackStage() };
		unsigned int currentHPPercent{ selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP() };

		if (currentAttackStage >= 9)
		{
			if (!rng.RandomLT(100)) // 60.9375%
			{ 
				delta -= 1;
			}
		}

		else if (currentHPPercent == 100 && !rng.RandomLT(128)) // 50%
		{
			delta += 2;
		}

		if (currentHPPercent >= 70)
		{
			return delta;
		}

		if (currentHPPercent < 40)
		{
			delta -= 2;

			return delta;
		}


		if (!rng.RandomLT(40)) // 84.375%
		{ 
			delta -= 2;
		}

		return delta;
	}

	int SelfDefenseBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		int currentDefenseStage{ selfMon.GetDefenseStage() };
		unsigned int currentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();


		if (currentDefenseStage >= 9)
		{
			if (!rng.RandomLT(100)) // 60.9375% chance
			{ 
				delta -= 1;
			}

			// In the OG Gen 5 assembly this is a bug.
			// I believe the jump labels are wrong and instead should jump to label
			// 0x095A insteaad of 0x0954 in the 0x0906 block
			//delta += 2;
		}
		// Like SpD Boost, this should only happen by fall through or baton pass check passes
		else if (currentHPPercent == 100 && !rng.RandomLT(128)) // 50% chance
		{
			delta += 2;
		}

		if (currentHPPercent >= 70 && !rng.RandomLT(200))
		{
			delta -= 2;
			
			return delta;
		}

		if (currentHPPercent < 40)
		{
			delta -= 2;

			return delta;
		}

		const pokemonMove* targetLastMove = targetMon.GetLastUsedMove();

		if (targetLastMove != nullptr)
		{
			unsigned int power{ targetLastMove->GetPower() };
			Category category{ targetLastMove->GetCategoryEnum() };

			// JumpIfStoredEQ(0, &Label_0x09A8)
			if (power == 0 && /* Label 0x09A8-> */ !rng.RandomLT(60)) // 76.5625%
			{
				delta -= 2;

				return delta;
			}

			if (power > 0 && category == Category::Special)
			{
				delta -= 2;

				return delta;
			}

			if (power > 0 && category == Category::Physical)
			{
				if (!rng.RandomLT(60)) // 76.5625%
				{
					if (!rng.RandomLT(60)) // 76.5625%
					{
						delta -= 2; // 58.6181640625% -2 score if hp% greater than or equal to 40% and less than 70% and if target used a damaging physical move

						return delta;
					}
				}
			}
		}

		// Label_0x09B8
		return delta;
	}

	int SelfSpeedBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		if (AIMoveScoring::CalculateSpeed(selfMon) > AIMoveScoring::CalculateSpeed(targetMon))
		{
			delta -= 3;
			
			return delta;
		}

		bool moveFound{};
		for (const auto& move : selfMon.GetMoveArray())
		{
			if (SpeedUpMoveEffectFound(move.GetMoveEffectEnum()))
			{
				if (!move.HasMove())
				{
					continue;
				}

				moveFound = true;
				break;
			}
		}

		if (moveFound && !rng.RandomLT(70)) // 72.65625%
		{
			delta += 2;
		}

		if (!rng.RandomLT(70)) // 72.65625%
		{
			delta += 2;
		}

		return delta;
	}

	int SelfSpABoost(RandomEngine& rng, const BattlePokemon& selfMon)
	{
		int delta{};

		if (selfMon.GetSpecialAttackStage() >= 9)
		{
			if (!rng.RandomLT(100)) // 60.9375%
			{
				delta -= 1;
			}
		}

		unsigned int currentHPPercent{ selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP() };

		if (currentHPPercent == 100 && selfMon.GetSpecialAttackStage() < 9)
		{
			if (!rng.RandomLT(128)) // 50%
			{
				delta += 2;
			}
		}

		if (currentHPPercent >= 70)
		{
			return delta;
		}

		if (currentHPPercent < 40)
		{
			delta -= 2;
			
			return delta;
		}

		if (!rng.RandomLT(70)) // 72.65625%
		{
			delta -= 2;
		}
		
		return delta;
	}

	int SelfSpDBoost(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		int userSpDStage{ selfMon.GetSpecialDefenseStage() };
		unsigned int currentHPPercent{ selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP() };

		if (userSpDStage >= 9)
		{
			if (!rng.RandomLT(100))
			{
				delta -= 1;
			}
		}
		else if (currentHPPercent == 100 && !rng.RandomLT(128))
		{
			delta += 2;
		}

		if (currentHPPercent >= 70 && !rng.RandomLT(200))
		{
			return delta;
		}

		if (currentHPPercent < 40)
		{
			delta -= 2;

			return delta;
		}

		pokemonMove* targetLastMove = targetMon.GetLastUsedMove();

		if (targetLastMove)
		{
			unsigned int power{ targetLastMove->GetPower() };
			Category category{ targetLastMove->GetCategoryEnum() };

			if (power == 0 && !rng.RandomLT(60)) // 76.5625
			{
				delta -= 2;

				return delta;
			}

			if (power > 0 && category == Category::Special)
			{
				delta -= 2;

				return delta;
			}

			if (power > 0 && category == Category::Physical)
			{
				if (!rng.RandomLT(60)) // 76.5625%
				{
					if (!rng.RandomLT(60)) // 76.5625%
					{
						delta -= 2; // 58.6181640625% -2 score if hp% greater than or equal to 40% and less than 70% and if target used a damaging physical move

						return delta;
					}
				}
			}
		}

		return delta;
	}


}