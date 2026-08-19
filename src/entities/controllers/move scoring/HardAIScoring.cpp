#include <span>

#include "HardAIScoring.h"

#include "AIScoreTag.h"
#include "AIMoveScoring.h"
#include "ScoringResultsStruct.h"
#include "../../Player.h"
#include "../../pokemonMove.h"
#include "../../BattlePokemon.h"
#include "../../../data/MoveID.h"
#include "../../../data/StringToTypes.h"
#include "../../../battle/RandomEngine.h"
#include "../../../moves/MoveEffectEnums.h"
#include "../AIController.h"

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

	void RunExpertScoringRoutine(ScoringResults& result, std::span<ScoringResults>& results, const Player& self, const Player& targetPlayer, const pokemonMove& move, const BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng)
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
				delta += DreamEater(rng, targetMon); // Original script had ability checks
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
			/*
			case AIScoreTag::SelfSpABoost:
			{
				delta += SelfSpABoost(rng, selfMon);
			}
			break;
			*/
			case AIScoreTag::SelfSpDBoost:
			{
				delta += SelfSpDBoost(rng, selfMon, targetMon);
			}
			break;
			/*
			case AIScoreTag::SelfAccuracyBoost:
			{
				delta += SelfAccuracyBoost(rng, selfMon, targetMon);
			}
			*/
			case AIScoreTag::SelfEvasionBoost: // for both -1 and -2 stage decreases
			{
				delta += SelfEvasionBoost(rng, self.GetAIController(), selfMon, targetMon);
			}
			break;

			case AIScoreTag::Growth:
			{
				delta += Growth(rng, selfMon);
			}
			break;

			case AIScoreTag::AlwaysHit:
			{
				delta += AlwaysHit(rng, selfMon, targetMon);
			}
			break;

			case AIScoreTag::TargetAttackDecrease: // for both -1 and -2
			{
				delta += TargetAttackDecrease(rng, selfMon, targetMon);
			}
			break;

			case AIScoreTag::TargetDefenseDecrease: // for both -1, and -2, and -1 atk and def moves (future gens)
			{
				delta += TargetDefenseDecrease(rng, selfMon, targetMon);
			}
			break;

			case AIScoreTag::TargetSpeedDecrease:
			{
				delta += TargetSpeedDecrease(rng, selfMon, targetMon);
			}
			break;
			/*
			case AIScoreTag::TargetSpecialAttackDecrease:
			{
				delta += TargetSpecialAttackDecrease(rng, selfMon, targetMon);
			}
			break;

			case AIScoreTag::TargetSpecialDefenseDecrease:
			{
				delta += TargetSpecialDefenseDecrease(rng, selfMon, targetMon);
			}
			break;
			*/
			case AIScoreTag::TargetAccuracyDecrease:
			{
				delta += TargetAccuracyDecrease(rng, selfMon, targetMon);
			}
			break;
			/*
			case AIScoreTag::TargetEvasionDecrease:
			{
				delta += TargetEvasionDecrease(rng, selfMon, targetMon);
			}
			break;
			*/
		}

		result.score += delta;
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
			// 0x095A instead of 0x0954 in the 0x0906 block
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
	/*
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
	*/
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
	/*
	int SelfAccuracyBoost(RandomEngine& rng, const BattlePokemon& selfMon)
	{
		int delta{};

		int selfAccuracyStage = selfMon.GetAccuracyStage();

		if (selfAccuracyStage >= 9)
		{
			if (!rng.RandomLT(50)) // 80.46875%
			{
				delta -= 2;
			}
		}

		unsigned int currentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();

		if (currentHPPercent < 70)
		{
			return delta -= 2;
		}

		return delta;
	}
	*/
	// Later gens: baton pass, held items, abilities
	int SelfEvasionBoost(RandomEngine& rng, AIController& self, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		const pokemonMove* targetLastMove = targetMon.GetLastUsedMove();

		// Discourage and end if target's last move was an AlwaysHit move.
		if (targetLastMove != nullptr &&
			targetLastMove->GetMoveEffectEnum() == MoveEffect::AlwaysHit)
		{
			return -2;
		}

		bool userHasRecoveryMove{};

		for (const auto& move : selfMon.GetMoveArray())
		{
			if (move.GetMoveEffectEnum() == MoveEffect::HealHalfHP)
			{
				userHasRecoveryMove = true;
				break;
			}
		}

		if (!userHasRecoveryMove &&
			(selfMon.IsSeeded() ||
				selfMon.GetStatus() == Status::Burned ||
				selfMon.GetStatus() == Status::Poisoned ||
				selfMon.GetStatus() == Status::Badly_Poisoned))
		{
			if (!rng.RandomLT(50))
			{
				delta -= 1;
			}
		}

		bool observedTargetHasRecoveryMove{};

		for (const auto* move : self.GetObservedMoves())
		{
			// cancel loop once it hits first null
			if (move == nullptr)
			{
				break;
			}

			// Jump to next entry if move is disabled, 0 pp or null
			if (!move->IsActive())
			{
				continue;
			}

			if (move->GetMoveEffectEnum() == MoveEffect::HealHalfHP)
			{
				observedTargetHasRecoveryMove = true;
				break;
			}
		}

		// No recovery move has yet been observed from the target.
		if (!observedTargetHasRecoveryMove &&
			(targetMon.IsSeeded() ||
				targetMon.GetStatus() == Status::Burned ||
				targetMon.GetStatus() == Status::Poisoned ||
				targetMon.GetStatus() == Status::Badly_Poisoned))
		{
			if (!rng.RandomLT(50))
			{
				delta += 1;
			}
		}

		const unsigned int hpPercent =
			selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();

		if (selfMon.GetEvasionStage() >= 9 && hpPercent < 70)
		{
			if (!rng.RandomLT(50))
			{
				delta -= 1;
			}
		}

		if (hpPercent < 50)
		{
			if (!rng.RandomLT(70))
			{
				delta -= 2;
			}
		}

		return delta;
	}

	int Growth(RandomEngine& rng, const BattlePokemon& selfMon)
	{
		unsigned int selfCurrentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();

		if (selfCurrentHPPercent < 70 && !rng.RandomLT(50)) // 80.46875%
		{
			return -1;
		}

		return 0;
	}

	int AlwaysHit(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		if (targetMon.GetEvasionStage() >= 10 || selfMon.GetAccuracyStage() < 2)
		{
			delta += 1;
		}

		if (targetMon.GetEvasionStage() >= 8 || selfMon.GetAccuracyStage() < 4)
		{
			if (!rng.RandomLT(100)) // 60.9375%
			{
				delta += 1;
			}
		}

		return delta;
	}

	int TargetAttackDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		int targetAttackStage = targetMon.GetAttackStage();

		if (targetAttackStage != 6)
		{
			delta -= 1;
		}

		unsigned int selfCurrentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();

		if (selfCurrentHPPercent < 90)
		{
			delta -= 1;
		}

		if (targetAttackStage < 3 && !rng.RandomLT(50))
		{
			delta -= 2;
		}

		unsigned int targetCurrentHPPercent = targetMon.GetCurrentHP() * 100 / targetMon.GetMaxHP();

		if (targetCurrentHPPercent < 70)
		{
			delta -= 2;
		}

		const pokemonMove* targetLastUsedMove = targetMon.GetLastUsedMove();

		if (targetLastUsedMove == nullptr || targetLastUsedMove->GetCategoryEnum() != Category::Special)
		{
			return delta;
		}

		if (!rng.RandomLT(128))
		{
			delta -= 2;
		}

		return delta;
	}

	int TargetDefenseDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		unsigned int selfCurrentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();
		unsigned int targetCurrentHPPercent = targetMon.GetCurrentHP() * 100 / targetMon.GetMaxHP();
		int targetDefenseStage = targetMon.GetDefenseStage();

		if (selfCurrentHPPercent < 70 || targetDefenseStage < 3)
		{
			if (!rng.RandomLT(50))
			{
				delta -= 2;
			}
		}

		if (targetCurrentHPPercent < 70)
		{
			delta -= 2;
		}

		return delta;
	}

	int TargetSpeedDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		unsigned int targetSpeed = AIMoveScoring::CalculateSpeed(targetMon);
		unsigned int selfSpeed = AIMoveScoring::CalculateSpeed(selfMon);

		if (targetSpeed >= selfSpeed)
		{
			if (!rng.RandomLT(70)) // 72.65625%
			{
				delta += 2;
			}
		}
		else if (targetSpeed < selfSpeed)
		{
			delta -= 3;
		}

		return delta;
	}
	/*
	int TargetSpecialAttackDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		int targetSpecialAttackStage = targetMon.GetSpecialAttackStage();

		if (targetSpecialAttackStage != 6)
		{
			delta -= 1;
		}

		unsigned int selfCurrentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();

		if (selfCurrentHPPercent < 90)
		{
			delta -= 1;
		}

		if (targetSpecialAttackStage < 3 && !rng.RandomLT(50))
		{
			delta -= 2;
		}

		unsigned int targetCurrentHPPercent = targetMon.GetCurrentHP() * 100 / targetMon.GetMaxHP();

		if (targetCurrentHPPercent < 70)
		{
			delta -= 2;
		}

		const pokemonMove* targetLastUsedMove = targetMon.GetLastUsedMove();

		if (targetLastUsedMove == nullptr || targetLastUsedMove->GetCategoryEnum() != Category::Physical)
		{
			return delta;
		}

		if (!rng.RandomLT(128))
		{
			delta -= 2;
		}

		return delta;
	}
	
	int TargetSpecialDefenseDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		unsigned int selfCurrentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();
		unsigned int targetCurrentHPPercent = targetMon.GetCurrentHP() * 100 / targetMon.GetMaxHP();
		int targetSpecialDefenseStage = targetMon.GetSpecialDefenseStage();

		if (selfCurrentHPPercent < 70 || targetSpecialDefenseStage < 3)
		{
			if (!rng.RandomLT(50))
			{
				delta -= 2;
			}
		}

		if (targetCurrentHPPercent < 70)
		{
			delta -= 2;
		}

		return delta;
	}
	*/
	int TargetAccuracyDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		unsigned int selfCurrentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();
		unsigned int targetCurrentHPPercent = targetMon.GetCurrentHP() * 100 / targetMon.GetMaxHP();

		if (selfCurrentHPPercent < 70 || targetCurrentHPPercent < 70)
		{
			if (!rng.RandomLT(100)) // 60.9375%
			{
				delta -= 1;
			}
		}
		
		int selfAccuracyStage = selfMon.GetAccuracyStage();

		if (selfAccuracyStage < 4)
		{
			if (!rng.RandomLT(80)) // 68.75%
			{
				delta -= 2;
			}
		}

		if (targetMon.GetStatus() == Status::Badly_Poisoned)
		{
			if (!rng.RandomLT(70)) // 72.65625%
			{
				delta += 2;
			}
		}

		if (targetMon.IsSeeded())
		{
			if (!rng.RandomLT(70)) // 72.65625%
			{
				delta += 2;
			}
		}

		int targetAccuracyStage = targetMon.GetAccuracyStage();

		if (selfCurrentHPPercent < 70 && targetAccuracyStage != 6)
		{
			if (selfCurrentHPPercent < 40 || targetCurrentHPPercent < 40)
			{
				delta -= 2;
			}
			else if (!rng.RandomLT(70)) // 72.65625%
			{
				delta -= 2;
			}
		}

		return delta;
	}
	/*
	int TargetEvasionDecrease(RandomEngine& rng, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
	{
		int delta{};

		unsigned int selfCurrentHPPercent = selfMon.GetCurrentHP() * 100 / selfMon.GetMaxHP();
		int targetEvasionStage = targetMon.GetEvasionStage();

		if (selfCurrentHPPercent < 70 || targetEvasionStage < 3)
		{
			if (!rng.RandomLT(50)) // 80.46875%
			{
				delta -= 2;
			}
		}

		unsigned int targetCurrentHPPercent = targetMon.GetCurrentHP() * 100 / targetMon.GetMaxHP();

		if (targetCurrentHPPercent < 70)
		{
			delta -= 2;
		}

		return delta;
	}
	*/
}