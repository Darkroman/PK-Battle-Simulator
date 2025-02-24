#include "../include/MoveEffects.h"

std::unique_ptr<IMoveEffects> MoveEffectsFactory::Call(int ID)
{
	switch (ID)
	{
	case 0:
		return std::make_unique<NormalHit>();

	case 1:
		return std::make_unique<IncreasedCritical>();

	case 2:
		return std::make_unique<MultiAttack>();

	case 3:
		return std::make_unique<BurnHit>();

	case 4:
		return std::make_unique<FreezeHit>();

	case 5:
		return std::make_unique<ParalyzeHit10>();

	case 6:
		return std::make_unique<OneHitKOHit>();

	case 7:
		return std::make_unique<RazorWind>();

	case 8:
		return std::make_unique<AttackUp2>();

	case 9:
		return std::make_unique<Gust>();

	case 10:
		return std::make_unique<MakeEnemySwitch>();

	case 11:
		return std::make_unique<Fly>();

	case 12:
		return std::make_unique<Bound>();

	case 13:
		return std::make_unique<Stomp>();

	case 14:
		return std::make_unique<DoubleHit>();

	case 15:
		return std::make_unique<JumpKick>();

	case 16:
		return std::make_unique<FlinchHit>();

	case 17:
		return std::make_unique<AccuracyDown>();

	case 18:
		return std::make_unique<BodySlam>();

	case 19:
		return std::make_unique<RecoilQuarter>();

	case 20:
		return std::make_unique<Thrash>();

	case 21:
		return std::make_unique<RecoilThird>();

	case 22:
		return std::make_unique<DefenseDown>();

	case 23:
		return std::make_unique<PoisonHit>();

	case 24:
		return std::make_unique<Twineedle>();

	case 25:
		return std::make_unique<AttackDown>();

	case 26:
		return std::make_unique<BypassSubSleep>();

	case 27:
		return std::make_unique<Confuse>();

	case 28:
		return std::make_unique<SonicBoom>();

	case 29:
		return std::make_unique<Disable>();

	case 30:
		return std::make_unique<SpecialDefenseDownHit>();

	case 31:
		return std::make_unique<Mist>();

	case 32:
		return std::make_unique<ConfuseHit>();

	case 33:
		return std::make_unique<SpeedDownHit>();

	case 34:
		return std::make_unique<AttackDownHit>();

	case 35:
		return std::make_unique<RechargeAttack>();

	case 36:
		return std::make_unique<LowKick>();

	case 37:
		return std::make_unique<Counter>();

	case 38:
		return std::make_unique<SeismicToss>();

	case 39:
		return std::make_unique<Leech>();

	case 40:
		return std::make_unique<LeechSeed>();

	case 41:
		return std::make_unique<Growth>();

	case 42:
		return std::make_unique<SolarBeam>();

	case 43:
		return std::make_unique<PoisonPowder>();

	case 44:
		return std::make_unique<StunSpore>();

	case 45:
		return std::make_unique<SleepPowder>();

	case 46:
		return std::make_unique<SpeedDown2>();

	case 47:
		return std::make_unique<DragonRage>();

	case 48:
		return std::make_unique<Paralyze>();

	case 49:
		return std::make_unique<ParalyzeHit30>();

	case 50:
		return std::make_unique<Earthquake>();

	case 51:
		return std::make_unique<Dig>();

	case 52:
		return std::make_unique<Toxic>();

	case 53:
		return std::make_unique<SleepMove>();

	case 54:
		return std::make_unique<AttackUp>();

	case 55:
		return std::make_unique<SpeedUp2>();

	case 56:
		return std::make_unique<Rage>();

	case 57:
		return std::make_unique<Teleport>();

	case 58:
		return std::make_unique<NightShade>();

	case 59:
		return std::make_unique<Mimic>();

	case 60:
		return std::make_unique<DefenseDown2>();

	case 61:
		return std::make_unique<EvasionUp>();

	case 62:
		return std::make_unique<Heal50>();

	case 63:
		return std::make_unique<DefenseUp>();

	case 64:
		return std::make_unique<Minimize>();

	case 65:
		return std::make_unique<DefenseUp2>();

	case 66:
		return std::make_unique<LightScreen>();

	case 67:
		return std::make_unique<Haze>();

	case 68:
		return std::make_unique<Reflect>();

	case 69:
		return std::make_unique<FocusEnergy>();

	case 70:
		return std::make_unique<Bide>();

	case 71:
		return std::make_unique<Metronome>();

	case 72:
		return std::make_unique<MirrorMove>();

	case 73:
		return std::make_unique<Explosion>();

	case 74:
		return std::make_unique<PoisonHit40>();

	case 75:
		return std::make_unique<FlinchHit10>();

	case 76:
		return std::make_unique<FlinchHit20>();

	case 77:
		return std::make_unique<Swift>();

	case 78:
		return std::make_unique<SkullBash>();

	case 79:
		return std::make_unique<SpecialDefenseUp2>();

	case 80:
		return std::make_unique<DreamEater>();

	case 81:
		return std::make_unique<PoisonGas>();

	case 82:
		return std::make_unique<SkyAttack>();

	case 83:
		return std::make_unique<Transform>();

	case 84:
		return std::make_unique<ConfuseHit20>();

	case 85:
		return std::make_unique<Psywave>();

	case 86:
		return std::make_unique<Splash>();

	case 87:
		return std::make_unique<Rest>();

	case 88:
		return std::make_unique<Conversion>();

	case 89:
		return std::make_unique<TriAttack>();

	case 90:
		return std::make_unique<SuperFang>();

	case 91:
		return std::make_unique<Substitute>();

	case 92:
		return std::make_unique<Struggle>();

	default:
		return std::make_unique<Noop>();

	}
	return std::make_unique<Noop>();
}

void Noop::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	std::cout << "This isn't implemented yet!\n\n";

	sourcePokemon->SetLastUsedMove(currentMove);
}

void NormalHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void IncreasedCritical::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	int oldcritstage = sourcePokemon->GetCriticalHitStage();
	int newcritstage = sourcePokemon->GetCriticalHitStage() + 1;

	sourcePokemon->SetCriticalHitStage(newcritstage);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetCriticalHitStage(oldcritstage);

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void MultiAttack::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	std::uniform_int_distribution<int> rngDist(1, 100);

	int randomNumber{ rngDist(generator) };

	int turnCount{ 0 };

	if (randomNumber <= 35)
	{
		turnCount = 2;
	}
	else if (randomNumber > 35 && randomNumber <= 70)
	{
		turnCount = 3;
	}
	else if (randomNumber > 70 && randomNumber <= 85)
	{
		turnCount = 4;
	}
	else if (randomNumber > 85)
	{
		turnCount = 5;
	}

	if (hit)
	{
		int timesHit{ 0 };
		while (turnCount != 0 && targetPokemon->GetCurrentHP() > 0)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);

			if (currentEffectiveness == Effectiveness::No)
			{
				DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
				return;
			}

			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

			++timesHit;

			--turnCount;
		}
		std::cout << targetPokemon->GetNameView() << " was hit " << timesHit << " times!\n";
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void BurnHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Fire && targetPokemon->GetTypeTwoEnum() != PokemonType::Fire)
			&& !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 10)
			{
				targetPokemon->ChangeStatus(Status::Burned);
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is burned!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void FreezeHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Ice && targetPokemon->GetTypeTwoEnum() != PokemonType::Ice)
			&& !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 10)
			{
				targetPokemon->ChangeStatus(Status::Frozen);
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is frozen solid!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void ParalyzeHit10::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Electric && targetPokemon->GetTypeTwoEnum() != PokemonType::Electric)
			&& !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 10)
			{
				targetPokemon->ChangeStatus(Status::Paralyzed);
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is paralyzed! It may be unable to move!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void OneHitKOHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon); // damage done for this move is calculated in the function CalculateDamage
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void RazorWind::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (sourcePokemon->IsCharging())
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

		if (hit)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}

		else
		{
			DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
		}

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetCharging(false);
		sourcePlayer->SetCanSwitch(true);
		sourcePokemon->SetLastUsedMove(currentMove);
		currentMove->m_currentPP -= 1;
	}
	else
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " made a whirlwind!\n";
		sourcePokemon->SetCharging(true);
		sourcePlayer->SetCanSwitch(false);
	}
}

void AttackUp2::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int attackStage = sourcePokemon->GetAttackStage();

	if (sourcePokemon->GetAttackStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " can't raise its attack any higher!\n";
	}
	else if (attackStage == 5)
	{
		++attackStage;
		sourcePokemon->SetAttackStage(attackStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s attack rose!\n";
	}
	else if (attackStage < 5)
	{
		attackStage += 2;
		sourcePokemon->SetAttackStage(attackStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s attack rose sharply!\n";
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Gust::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon); // power of move is doubled but is done already in CalculateDamage function
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void MakeEnemySwitch::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	currentMove->m_currentPP -= 1;

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (targetPlayer->GetPokemonCount() == 1 || (targetPlayer == bs.GetSecondTurnPlayer()) || targetPokemon->IsSemiInvulnerable())
	{
		DisplayFailedTextDialog();
		return;
	}

	hit = true;

	std::deque<BattlePokemon*> enemyPokemonList{};
	int numberOfPokemon{ 0 };

	if (hit)
	{
		for (size_t i = 1; i <= 6; ++i)
		{
			if (targetPlayer->GetBelt(i)->HasPokemon() && targetPlayer->GetBelt(i) != targetPokemon)
			{
				enemyPokemonList.push_back(targetPlayer->GetBelt(i));
				++numberOfPokemon;
			}
		}

		std::uniform_int_distribution<size_t> randomModDistributor(1, numberOfPokemon);
		size_t randomMod{ randomModDistributor(generator) };

		ResetStatsOnSwitch(targetPokemon);
		if (sourcePokemon->IsBound())
		{
			sourcePokemon->SetBound(false);
			sourcePokemon->ResetBoundCounter();
			sourcePokemon->SetBoundTurnCount(0);
		}

		if (targetPokemon->HasSubstitute())
		{
			targetPokemon->SetSubstitute(false);
			targetPokemon->SetSubstituteHP(0);
		}

		if (targetPlayer == bs.GetPlayerOne())
		{
			bs.SetPlayerOneCurrentPokemon(enemyPokemonList.at(randomMod - 1));
		}

		if (targetPlayer == bs.GetPlayerTwo())
		{
			bs.SetPlayerTwoCurrentPokemon(enemyPokemonList.at(randomMod - 1));
		}

		std::cout << "the opposing " << enemyPokemonList.at(randomMod - 1)->GetNameView() << " was dragged out!\n";
	}

	else
	{
		DisplayFailedTextDialog();
	}

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Fly::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (sourcePokemon->IsCharging())
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

		if (hit)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}

		else
		{
			DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
		}

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetCharging(false);
		sourcePokemon->SetSemiInvulnerableFly(false);
		sourcePlayer->SetCanSwitch(true);
		sourcePokemon->SetLastUsedMove(currentMove);
		currentMove->m_currentPP -= 1;
	}
	else
	{
		std::cout << sourcePokemon->GetNameView() << " flew up high in the sky!\n";
		sourcePokemon->SetCharging(true);
		sourcePokemon->SetSemiInvulnerableFly(true);
		sourcePlayer->SetCanSwitch(false);
	}
}

void Bound::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	bool isGhost = targetPokemon->GetTypeOneEnum() == PokemonType::Ghost || targetPokemon->GetTypeTwoEnum() == PokemonType::Ghost;

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (!targetPokemon->IsBound() && currentEffectiveness != Effectiveness::No && !targetPokemon->HasSubstitute())
		{
			targetPokemon->SetBound(true);
			if (!isGhost)
			{
				targetPlayer->SetCanSwitch(false);
			}

			std::uniform_int_distribution<int> randomModDistributor(4,5);
			int randomMod(randomModDistributor(generator));
			targetPokemon->SetBoundTurnCount(randomMod);
			targetPokemon->ResetBoundCounter();
			targetPokemon->SetBoundMoveName(currentMove->mp_move->GetMoveIndex());
			BoundMoveText(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon, currentMove);
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Stomp::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (targetPokemon->HasUsedMinimize() && !targetPokemon->IsSemiInvulnerable())
	{
		hit = true;
	}
	else
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);
	}

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon); // will do double damage if opponent pokemon has used minimized once, calculated in function already
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	std::uniform_int_distribution<int> randomModDistributor(1, 101);
	int randomMod{ randomModDistributor(generator) };

	if (randomMod < 30 && targetPlayer == bs.GetSecondTurnPlayer() && currentEffectiveness != Effectiveness::No && targetPokemon->GetCurrentHP() != 0)
	{
		targetPokemon->SetIsFlinched(true);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void DoubleHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		int turnCount = 2;
		int timesHit{ 0 };
		while (turnCount != 0 && targetPokemon->GetCurrentHP() > 0)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);

			if (currentEffectiveness == Effectiveness::No)
			{
				DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
				return;
			}

			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

			++timesHit;

			--turnCount;
		}
		std::cout << targetPokemon->GetNameView() << " was hit " << timesHit << " times!\n";
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void JumpKick::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);

		double crashDamage{ floor(sourcePokemon->GetMaxHP() / 2) };
		sourcePokemon->DamageCurrentHP(static_cast<int>(crashDamage));

		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " kept going and crashed!\n";
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void FlinchHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		std::uniform_int_distribution<int> randomModDistributor(1, 101);
		int randomMod{ randomModDistributor(generator) };

		if (randomMod < 30 && targetPlayer == bs.GetSecondTurnPlayer() && currentEffectiveness != Effectiveness::No && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			targetPokemon->SetIsFlinched(true);
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void AccuracyDown::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	if (targetPlayer->HasMist() && hit)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is protected by the mist!\n";

		currentMove->m_currentPP -= 1;

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetLastUsedMove(currentMove);

		return;
	}

	if (hit && (targetPokemon->HasSubstitute() && !currentMove->mp_move->CanBypassSubstitute()))
	{
		DisplayFailedTextDialog();
	}

	else if (hit && !targetPokemon->HasSubstitute())
	{
		if (targetPokemon->GetAccuracyStage() > -6)
		{	
			int lowerAccuracy{ targetPokemon->GetAccuracyStage() - 1 };
			targetPokemon->SetAccuracyStage(lowerAccuracy);

			DisplayAccuracyLoweredTextDialog(targetPlayer, targetPokemon);
		}
		else
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s accuracy won't go any lower!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void BodySlam::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (targetPokemon->HasUsedMinimize() && !targetPokemon->IsSemiInvulnerable())
	{
		hit = true;
	}
	else
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);
	}

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon); // will do double damage if opponent pokemon has used minimized once, calculated in function already
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Electric && targetPokemon->GetTypeTwoEnum() != PokemonType::Electric)
			&& !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 30 && currentEffectiveness != Effectiveness::No)
			{
				targetPokemon->ChangeStatus(Status::Paralyzed);
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is paralyzed, so it may be unable to move!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void RecoilQuarter::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	double recoilDamage{ 0 };

	if (hit && !targetPokemon->HasSubstitute())
	{
		double targetHPBegin = targetPokemon->GetCurrentHP();

		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		double targetHPEnd = targetPokemon->GetCurrentHP();

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		recoilDamage = floor((targetHPBegin - targetHPEnd) / 4);
		sourcePokemon->DamageCurrentHP(static_cast<int>(recoilDamage));

		if (currentEffectiveness != Effectiveness::No)
		{
			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was damaged by the recoil!\n";

			CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);
		}
	}

	else if (hit && targetPokemon->HasSubstitute())
	{
		double targetHPBegin = targetPokemon->GetSubstituteHP();

		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		double targetHPEnd = targetPokemon->GetSubstituteHP();

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		recoilDamage = floor((targetHPBegin - targetHPEnd) / 4);
		sourcePokemon->DamageCurrentHP(static_cast<int>(recoilDamage));

		if (currentEffectiveness != Effectiveness::No)
		{
			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was damaged by the recoil!\n";

			CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Thrash::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (!currentMove->b_isDisabled)
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

		if (hit)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

			if (!sourcePokemon->IsThrashing())
			{
				sourcePokemon->SetThrashing(true);
				sourcePlayer->SetCanSwitch(false);

				std::uniform_int_distribution<int> randomModDistributor(2, 3);
				int randomMod(randomModDistributor(generator));
				sourcePokemon->SetThrashTurnCount(randomMod);
				sourcePokemon->ResetThrashCounter();

				currentMove->m_currentPP -= 1;
			}
		}

		else
		{
			DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
		}
	}

	else
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s Thrash is disabled!\n";
	}

	sourcePokemon->IncrementThrashCounter();

	if (sourcePokemon->GetThrashCounter() == sourcePokemon->GetThrashTurnCount() && !sourcePokemon->IsConfused())
	{
		ThrashConfuse(sourcePlayer, sourcePokemon);
	}

	if ((sourcePokemon->GetThrashCounter() == sourcePokemon->GetThrashTurnCount() || currentEffectiveness == Effectiveness::No || !hit || currentMove->b_isDisabled) && sourcePokemon->IsThrashing())
	{
		ThrashStop(sourcePlayer, sourcePokemon);
		ThrashReset(sourcePlayer, sourcePokemon);
	}

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void RecoilThird::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	double recoilDamage{ 0 };

	if (hit && !targetPokemon->HasSubstitute())
	{
		double targetHPBegin = targetPokemon->GetCurrentHP();

		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		double targetHPEnd = targetPokemon->GetCurrentHP();

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		recoilDamage = floor((targetHPBegin - targetHPEnd) / 3);
		sourcePokemon->DamageCurrentHP(static_cast<int>(recoilDamage));

		if (currentEffectiveness != Effectiveness::No)
		{
			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was damaged by the recoil!\n";

			CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);
		}
	}

	else if (hit && targetPokemon->HasSubstitute())
	{
		double targetHPBegin = targetPokemon->GetSubstituteHP();

		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		double targetHPEnd = targetPokemon->GetSubstituteHP();

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		recoilDamage = floor((targetHPBegin - targetHPEnd) / 3);
		sourcePokemon->DamageCurrentHP(static_cast<int>(recoilDamage));

		if (currentEffectiveness != Effectiveness::No)
		{
			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was damaged by the recoil!\n";

			CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void DefenseDown::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	if (targetPlayer->HasMist() && hit)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is protected by the mist!\n";

		currentMove->m_currentPP -= 1;

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetLastUsedMove(currentMove);

		return;
	}

	if (hit && targetPokemon->HasSubstitute())
	{
		DisplayFailedTextDialog();
	}

	else if (hit && !targetPokemon->HasSubstitute())
	{
		if (targetPokemon->GetDefenseStage() > -6)
		{
			int lowerDefense{ targetPokemon->GetDefenseStage() - 1 };
			targetPokemon->SetDefenseStage(lowerDefense);

			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s defense fell!\n";
		}
		else
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s defense won't go any lower!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void PoisonHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Poison && targetPokemon->GetTypeTwoEnum() != PokemonType::Poison)
			&& (targetPokemon->GetTypeOneEnum() != PokemonType::Steel && targetPokemon->GetTypeTwoEnum() != PokemonType::Steel) && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 30)
			{
				targetPokemon->ChangeStatus(Status::Poisoned);
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is poisoned!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Twineedle::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		int turnCount = 2;
		int timesHit{ 0 };
		while (turnCount != 0 && targetPokemon->GetCurrentHP() > 0)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);

			if (currentEffectiveness == Effectiveness::No)
			{
				DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
				return;
			}

			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

			if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Poison && targetPokemon->GetTypeTwoEnum() != PokemonType::Poison)
				&& (targetPokemon->GetTypeOneEnum() != PokemonType::Steel && targetPokemon->GetTypeTwoEnum() != PokemonType::Steel) && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
			{
				std::uniform_int_distribution<int> rngDist(1, 101);
				int randomNumber{ rngDist(generator) };

				if (randomNumber <= 20)
				{
					targetPokemon->ChangeStatus(Status::Poisoned);
					std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is poisoned!\n";
				}
			}

			++timesHit;

			--turnCount;
		}
		std::cout << targetPokemon->GetNameView() << " was hit " << timesHit << " times!\n";
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void AttackDown::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	if (targetPlayer->HasMist() && hit)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is protected by the mist!\n";

		currentMove->m_currentPP -= 1;

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetLastUsedMove(currentMove);

		return;
	}

	if (hit && targetPokemon->HasSubstitute())
	{
		DisplayFailedTextDialog();
	}

	else if (hit && !targetPokemon->HasSubstitute())
	{
		if (targetPokemon->GetAttackStage() > -6)
		{
			int lowerAttack{ targetPokemon->GetAttackStage() - 1 };
			targetPokemon->SetAttackStage(lowerAttack);

			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s attack fell!\n";
		}
		else
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s attack won't go any lower!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void BypassSubSleep::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	if (hit)
	{
		if (targetPokemon->GetStatus() == Status::Normal)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " fell asleep!\n";

			targetPokemon->ChangeStatus(Status::Sleeping);

			std::uniform_int_distribution<int> randomModDistributor(1, 3);
			int randomMod(randomModDistributor(generator));
			targetPokemon->SetSleepTurnCount(randomMod);
			targetPokemon->ResetSleepCounter();
		}

		else if (targetPokemon->GetStatus() == Status::Sleeping)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is already asleep!\n";
		}

		else 
		{
			DisplayFailedTextDialog();
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Confuse::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	if (hit)
	{
		if (!targetPokemon->IsConfused() && currentMove->mp_move->CanBypassSubstitute())
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " became confused!\n";

			targetPokemon->SetConfusedStatus(true);
			
			std::uniform_int_distribution<int> randomModDistributor(2, 4);
			int randomMod(randomModDistributor(generator));
			targetPokemon->SetConfusedTurnCount(randomMod);
			targetPokemon->ResetConfusedCounter();
		}

		else
		{
			DisplayFailedTextDialog();
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SonicBoom::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	CalculateTypeEffectiveness(currentMove, targetPokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	double sonicBoomDamage = 20;

	if (hit)
	{
		if (targetPokemon->GetTypeOneEnum() == PokemonType::Ghost || targetPokemon->GetTypeTwoEnum() == PokemonType::Ghost)
		{
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			sonicBoomDamage = 0;
		}

		if (targetPokemon->HasSubstitute())
		{
			if (sonicBoomDamage > targetPokemon->GetSubstituteHP())
			{
				sonicBoomDamage = targetPokemon->GetSubstituteHP();
			}
			targetPokemon->DamageSubstitute(static_cast<int>(sonicBoomDamage));
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}

		else
		{
			if (sonicBoomDamage > targetPokemon->GetCurrentHP())
			{
				sonicBoomDamage = targetPokemon->GetCurrentHP();
			}

			targetPokemon->DamageCurrentHP(static_cast<int>(sonicBoomDamage));
		}
		std::cout << sonicBoomDamage << " damage inflicted.\n";
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	damageTaken = sonicBoomDamage;

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Disable::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		if (targetPokemon->GetLastUsedMove() == nullptr)
		{
			DisplayFailedTextDialog();
		}
		else if (targetPokemon->MoveIsDisabled() || targetPokemon->GetLastUsedMove()->m_currentPP == 0 || targetPokemon->GetLastUsedMove()->mp_move->GetSecondaryFlag() == 92)
		{
			DisplayFailedTextDialog();
		}
		else
		{
			targetPokemon->SetDisabledStatus(true);
			targetPokemon->ResetDisabledCounter();

			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s " << targetPokemon->GetLastUsedMove()->mp_move->GetName() << " was disabled!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SpecialDefenseDownHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		std::uniform_int_distribution<int> rngDist(1, 101);
		int randomNumber{ rngDist(generator) };

		if (randomNumber <= 10 && !targetPlayer->HasMist() && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			if (targetPokemon->GetSpecialDefenseStage() > -6)
			{
				int lowerSpecialDefense{ targetPokemon->GetSpecialDefenseStage() - 1 };
				targetPokemon->SetSpecialDefenseStage(lowerSpecialDefense);

				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s special defense fell!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Mist::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (!sourcePlayer->HasMist())
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s team became shrouded in mist!\n";
		sourcePlayer->SetMist(true);
	}

	else
	{
		DisplayFailedTextDialog();
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void ConfuseHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (!targetPokemon->IsConfused())
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 10 && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
			{
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " became confused!\n";

				targetPokemon->SetConfusedStatus(true);

				std::uniform_int_distribution<int> randomModDistributor(2, 4);
				int randomMod(randomModDistributor(generator));
				targetPokemon->SetConfusedTurnCount(randomMod);
				targetPokemon->ResetConfusedCounter();
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SpeedDownHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		std::uniform_int_distribution<int> rngDist(1, 101);
		int randomNumber{ rngDist(generator) };

		if (randomNumber <= 10 && !targetPlayer->HasMist() && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			if (targetPokemon->GetSpeedStage() > -6)
			{
				int lowerSpeed{ targetPokemon->GetSpeedStage() - 1 };
				targetPokemon->SetSpeedStage(lowerSpeed);

				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s speed fell!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void AttackDownHit::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		std::uniform_int_distribution<int> rngDist(1, 101);
		int randomNumber{ rngDist(generator) };

		if (randomNumber <= 10 && !targetPlayer->HasMist() && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			if (targetPokemon->GetAttackStage() > -6)
			{
				int lowerAttack{ targetPokemon->GetAttackStage() - 1 };
				targetPokemon->SetAttackStage(lowerAttack);

				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s attack fell!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void RechargeAttack::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (!sourcePokemon->IsRecharging())
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

		if (hit)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

			if (currentEffectiveness != Effectiveness::No)
			{
				sourcePokemon->SetRecharging(true);
				sourcePlayer->SetCanSwitch(false);
			}
		}

		else
		{
			DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
		}

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetLastUsedMove(currentMove);
		currentMove->m_currentPP -= 1;
	}
	else
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " must recharge!\n";
		sourcePokemon->SetRecharging(false);
		sourcePlayer->SetCanSwitch(true);
	}
}

void LowKick::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon); // Low Kick's power is calculated in function
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Counter::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	double counterDamage = damageTaken * 2;

	CalculateTypeEffectiveness(currentMove, targetPokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		if (counterDamage < 1 || sourcePlayer == bs.GetFirstTurnPlayer())
		{
			DisplayFailedTextDialog();
		}

		else
		{
			if (currentEffectiveness == Effectiveness::No && targetPokemon->GetLastUsedMove()->mp_move->GetCategoryEnum() != Category::Physical)
			{
				DisplayFailedTextDialog();
				counterDamage = 0;
			}

			else if (currentEffectiveness != Effectiveness::No && targetPokemon->GetLastUsedMove()->mp_move->GetCategoryEnum() != Category::Physical)
			{
				DisplayFailedTextDialog();
				counterDamage = 0;
			}

			else if (currentEffectiveness == Effectiveness::No && targetPokemon->GetLastUsedMove()->mp_move->GetCategoryEnum() == Category::Physical)
			{
				DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
				counterDamage = 0;
			}

			if (targetPokemon->HasSubstitute())
			{
				if (counterDamage > targetPokemon->GetSubstituteHP())
				{
					counterDamage = targetPokemon->GetSubstituteHP();
				}
				targetPokemon->DamageSubstitute(static_cast<int>(counterDamage));
				DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
			}

			else
			{
				if (counterDamage > targetPokemon->GetCurrentHP())
				{
					counterDamage = targetPokemon->GetCurrentHP();
				}

				targetPokemon->DamageCurrentHP(static_cast<int>(counterDamage));
			}
			std::cout << counterDamage << " damage inflicted.\n";
		}
		
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	damageTaken = counterDamage;

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SeismicToss::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	CalculateTypeEffectiveness(currentMove, targetPokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	double seismicTossDamage = sourcePokemon->GetLevel();

	if (hit)
	{
		if (targetPokemon->GetTypeOneEnum() == PokemonType::Ghost || targetPokemon->GetTypeTwoEnum() == PokemonType::Ghost)
		{
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			seismicTossDamage = 0;
		}

		if (targetPokemon->HasSubstitute())
		{
			if (seismicTossDamage > targetPokemon->GetSubstituteHP())
			{
				seismicTossDamage = targetPokemon->GetSubstituteHP();
			}
			targetPokemon->DamageSubstitute(static_cast<int>(seismicTossDamage));
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}

		else
		{
			if (seismicTossDamage > targetPokemon->GetCurrentHP())
			{
				seismicTossDamage = targetPokemon->GetCurrentHP();
			}

			targetPokemon->DamageCurrentHP(static_cast<int>(seismicTossDamage));
		}
		std::cout << seismicTossDamage << " damage inflicted.\n";
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	damageTaken = seismicTossDamage;

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Leech::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		double leechedHealth{};

		if (damageTaken <= 0)
		{
			leechedHealth = 0;
		}
		else if (damageTaken == 1)
		{
			leechedHealth = 1;
		}
		else
		{
			leechedHealth = floor(damageTaken / 2);
		}

		if (leechedHealth > (sourcePokemon->GetMaxHP() - sourcePokemon->GetCurrentHP()))
		{
			leechedHealth = (sourcePokemon->GetMaxHP() - sourcePokemon->GetCurrentHP());
		}

		sourcePokemon->HealCurrentHP(static_cast<int>(leechedHealth));

		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " had its energy drained!\n";
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void LeechSeed::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		if (targetPokemon->GetTypeOneEnum() == PokemonType::Grass || targetPokemon->GetTypeTwoEnum() == PokemonType::Grass)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << '\n';
		}
		else if (targetPokemon->IsSeeded() || targetPokemon->HasSubstitute())
		{
			DisplayFailedTextDialog();
		}
		else
		{
			targetPokemon->SetSeededStatus(true);

			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " was seeded!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Growth::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int attackStage = sourcePokemon->GetAttackStage();
	int specialAttackStage = sourcePokemon->GetSpecialAttackStage();

	if (sourcePokemon->GetAttackStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " can't raise its attack any higher!\n";
	}
	else
	{
		++attackStage;
		sourcePokemon->SetAttackStage(attackStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s attack rose!\n";
	}

	if (sourcePokemon->GetSpecialAttackStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " can't raise its special attack any higher!\n";
	}
	else
	{
		++specialAttackStage;
		sourcePokemon->SetSpecialAttackStage(specialAttackStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s special attack rose!\n";
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SolarBeam::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (sourcePokemon->IsCharging())
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

		if (hit)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}

		else
		{
			DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
		}

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetCharging(false);
		sourcePlayer->SetCanSwitch(true);
		sourcePokemon->SetLastUsedMove(currentMove);
	}
	else
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " absorbed light!\n";
		sourcePokemon->SetCharging(true);
		sourcePlayer->SetCanSwitch(false);
		currentMove->m_currentPP -= 1;
	}
}

void PoisonPowder::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	bool isImmune = ((targetPokemon->GetTypeOneEnum() == PokemonType::Grass || targetPokemon->GetTypeTwoEnum() == PokemonType::Grass) ||
		(targetPokemon->GetTypeOneEnum() == PokemonType::Poison || targetPokemon->GetTypeTwoEnum() == PokemonType::Poison) ||
		(targetPokemon->GetTypeOneEnum() == PokemonType::Steel || targetPokemon->GetTypeTwoEnum() == PokemonType::Steel));

	if (hit)
	{
		if (targetPokemon->GetStatus() != Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Poisoned)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is already poisoned!\n";
		}
		else if ((targetPokemon->GetStatus() != Status::Poisoned && targetPokemon->GetStatus() != Status::Normal) || targetPokemon->HasSubstitute())
		{
			DisplayFailedTextDialog();
		}
		else if (targetPokemon->GetStatus() == Status::Normal && !isImmune)
		{
			targetPokemon->ChangeStatus(Status::Poisoned);
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " was poisoned!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void StunSpore::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	bool isImmune = ((targetPokemon->GetTypeOneEnum() == PokemonType::Grass || targetPokemon->GetTypeTwoEnum() == PokemonType::Grass) ||
		(targetPokemon->GetTypeOneEnum() == PokemonType::Electric || targetPokemon->GetTypeTwoEnum() == PokemonType::Electric));

	if (hit)
	{
		if (targetPokemon->GetStatus() != Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Paralyzed)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is already paralyzed!\n";
		}
		else if ((targetPokemon->GetStatus() != Status::Paralyzed && targetPokemon->GetStatus() != Status::Normal) || targetPokemon->HasSubstitute())
		{
			DisplayFailedTextDialog();
		}
		else if (targetPokemon->GetStatus() == Status::Normal && !isImmune)
		{
			targetPokemon->ChangeStatus(Status::Paralyzed);
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is paralyzed! It may be unable to move!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SleepPowder::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	bool isImmune = (targetPokemon->GetTypeOneEnum() == PokemonType::Grass || targetPokemon->GetTypeTwoEnum() == PokemonType::Grass);

	if (hit)
	{
		if (targetPokemon->GetStatus() != Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Sleeping)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is already asleep!\n";
		}
		else if ((targetPokemon->GetStatus() != Status::Sleeping && targetPokemon->GetStatus() != Status::Normal) || targetPokemon->HasSubstitute())
		{
			DisplayFailedTextDialog();
		}
		else if (targetPokemon->GetStatus() == Status::Normal && !isImmune)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " fell asleep!\n";

			targetPokemon->ChangeStatus(Status::Sleeping);

			std::uniform_int_distribution<int> randomModDistributor(1, 3);
			int randomMod(randomModDistributor(generator));
			targetPokemon->SetSleepTurnCount(randomMod);
			targetPokemon->ResetSleepCounter();
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SpeedDown2::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	if (targetPlayer->HasMist() && hit)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is protected by the mist!\n";

		currentMove->m_currentPP -= 1;

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetLastUsedMove(currentMove);

		return;
	}

	if (hit && targetPokemon->HasSubstitute())
	{
		DisplayFailedTextDialog();
	}

	else if (hit && !targetPokemon->HasSubstitute())
	{
		if (targetPokemon->GetSpeedStage() == -5)
		{
			int lowerSpeed{ targetPokemon->GetSpeedStage() - 1 };
			targetPokemon->SetSpeedStage(lowerSpeed);

			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s speed fell!\n";
		}
		else if (targetPokemon->GetSpeedStage() > -5)
		{
			int lowerSpeed{ targetPokemon->GetSpeedStage() - 2 };
			targetPokemon->SetSpeedStage(lowerSpeed);

			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s speed fell harshly!\n";
		}
		else if (targetPokemon->GetSpeedStage() < -5)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s speed won't go any lower!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void DragonRage::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	CalculateTypeEffectiveness(currentMove, targetPokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int dragonRageDamage{ 40 };

	if (hit)
	{
		if (targetPokemon->GetTypeOneEnum() == PokemonType::Fairy || targetPokemon->GetTypeTwoEnum() == PokemonType::Fairy)
		{
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			dragonRageDamage = 0;
		}

		if (targetPokemon->HasSubstitute())
		{
			if (dragonRageDamage > targetPokemon->GetSubstituteHP())
			{
				dragonRageDamage = targetPokemon->GetSubstituteHP();
			}
			targetPokemon->DamageSubstitute(dragonRageDamage);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}

		else
		{
			if (dragonRageDamage > targetPokemon->GetCurrentHP())
			{
				dragonRageDamage = targetPokemon->GetCurrentHP();
			}

			targetPokemon->DamageCurrentHP(dragonRageDamage);
		}
		std::cout << dragonRageDamage << " damage inflicted.\n";
	}
	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	damageTaken = dragonRageDamage;

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Paralyze::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	CalculateTypeEffectiveness(currentMove, targetPokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	bool isImmune{ false };

	isImmune = (targetPokemon->GetTypeOneEnum() == PokemonType::Electric || targetPokemon->GetTypeTwoEnum() == PokemonType::Electric || currentEffectiveness == Effectiveness::No);

	if (currentMove->mp_move->GetName() == "Glare")
	{
		if ((targetPokemon->GetTypeOneEnum() == PokemonType::Ghost || targetPokemon->GetTypeTwoEnum() == PokemonType::Ghost)
		 && !(targetPokemon->GetTypeOneEnum() == PokemonType::Electric || targetPokemon->GetTypeTwoEnum() == PokemonType::Electric))
		{
			isImmune = false;
		}
	}

	if (hit)
	{
		if (targetPokemon->GetStatus() != Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Paralyzed)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is already paralyzed!\n";
		}
		else if ((targetPokemon->GetStatus() != Status::Paralyzed && targetPokemon->GetStatus() != Status::Normal) || targetPokemon->HasSubstitute())
		{
			DisplayFailedTextDialog();
		}
		else if (targetPokemon->GetStatus() == Status::Normal && !isImmune)
		{
			targetPokemon->ChangeStatus(Status::Paralyzed);
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is paralyzed! It may be unable to move!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void ParalyzeHit30::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Electric && targetPokemon->GetTypeTwoEnum() != PokemonType::Electric)
			&& !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 30)
			{
				targetPokemon->ChangeStatus(Status::Paralyzed);
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is paralyzed! It may be unable to move!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Earthquake::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon); // Will do double damage if enemy used dig. Calculated in function already
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Dig::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (sourcePokemon->IsCharging())
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

		if (hit)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}

		else
		{
			DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
		}

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetCharging(false);
		sourcePokemon->SetSemiInvulnerableDig(false);
		sourcePlayer->SetCanSwitch(true);
		sourcePokemon->SetLastUsedMove(currentMove);
		currentMove->m_currentPP -= 1;
	}
	else
	{
		std::cout << sourcePokemon->GetNameView() << " burrowed its way under the ground!\n";
		sourcePokemon->SetCharging(true);
		sourcePokemon->SetSemiInvulnerableDig(true);
		sourcePlayer->SetCanSwitch(false);
	}
}

void Toxic::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	bool isImmune = ((targetPokemon->GetTypeOneEnum() == PokemonType::Grass || targetPokemon->GetTypeTwoEnum() == PokemonType::Grass) ||
		(targetPokemon->GetTypeOneEnum() == PokemonType::Poison || targetPokemon->GetTypeTwoEnum() == PokemonType::Poison) ||
		(targetPokemon->GetTypeOneEnum() == PokemonType::Steel || targetPokemon->GetTypeTwoEnum() == PokemonType::Steel));

	if (hit)
	{
		if (targetPokemon->GetStatus() != Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Poisoned)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is already poisoned!\n";
		}
		else if ((targetPokemon->GetStatus() != Status::Poisoned && targetPokemon->GetStatus() != Status::Normal) || targetPokemon->HasSubstitute())
		{
			DisplayFailedTextDialog();
		}
		else if (targetPokemon->GetStatus() == Status::Normal && !isImmune)
		{
			targetPokemon->ChangeStatus(Status::Badly_Poisoned);
			targetPokemon->ResetBadlyPoisonCounter();
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " was badly poisoned!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SleepMove::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	if (hit)
	{
		if (targetPokemon->GetStatus() == Status::Normal)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " fell asleep!\n";

			targetPokemon->ChangeStatus(Status::Sleeping);

			std::uniform_int_distribution<int> randomModDistributor(1, 3);
			int randomMod(randomModDistributor(generator));
			targetPokemon->SetSleepTurnCount(randomMod);
			targetPokemon->ResetSleepCounter();
		}

		else if (targetPokemon->GetStatus() == Status::Sleeping)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is already asleep!\n";
		}

		else if (targetPokemon->HasSubstitute())
		{
			DisplayFailedTextDialog();
		}
		else
		{
			DisplayFailedTextDialog();
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void AttackUp::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int attackStage = sourcePokemon->GetAttackStage();

	if (sourcePokemon->GetAttackStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " can't raise its attack any higher!\n";
	}
	else
	{
		++attackStage;
		sourcePokemon->SetAttackStage(attackStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s attack rose!\n";
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SpeedUp2::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int speedStage = sourcePokemon->GetSpeedStage();

	if (sourcePokemon->GetSpeedStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " can't raise its speed any higher!\n";
	}
	else if (speedStage == 5)
	{
		++speedStage;
		sourcePokemon->SetSpeedStage(speedStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s speed rose!\n";
	}
	else if (speedStage < 5)
	{
		speedStage += 2;
		sourcePokemon->SetSpeedStage(speedStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s speed rose sharply!\n";
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Rage::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		sourcePokemon->SetRaging(true);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Teleport::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	currentMove->m_currentPP -= 1;

	if (sourcePlayer->GetPokemonCount() == 1)
	{
		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);
		DisplayFailedTextDialog();
		return;
	}

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	bs.SwitchPokemonOption(sourcePlayer, sourcePokemon);

	bs.PerformSwitch(sourcePlayer, sourcePokemon);

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void NightShade::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	CalculateTypeEffectiveness(currentMove, targetPokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int nightShadeDamage = sourcePokemon->GetLevel();

	if (hit)
	{
		if (targetPokemon->GetTypeOneEnum() == PokemonType::Normal || targetPokemon->GetTypeTwoEnum() == PokemonType::Normal)
		{
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			nightShadeDamage = 0;
		}

		if (targetPokemon->HasSubstitute())
		{
			if (nightShadeDamage > targetPokemon->GetSubstituteHP())
			{
				nightShadeDamage = targetPokemon->GetSubstituteHP();
			}
			targetPokemon->DamageSubstitute(nightShadeDamage);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}
		else
		{
			if (nightShadeDamage > targetPokemon->GetCurrentHP())
			{
				nightShadeDamage = targetPokemon->GetCurrentHP();
			}
			targetPokemon->DamageCurrentHP(nightShadeDamage);
		}

		std::cout << nightShadeDamage << " damage inflicted.\n";
	}
	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	damageTaken = nightShadeDamage;

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Mimic::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	// Copies target's Pokemon last used move and replaces Mimic slot with the copied move with a max PP of 8.
	// Cannot copy transform, sketch, struggle, metronome, or any move the user already knows.
	// Will always succeed unless enemy pokemon is in semi invulnerable state.
	// Copies the base PP amount of move (doesn't take into account PP Ups on moves).

	currentMove->m_currentPP -= 1;

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (targetPokemon->GetLastUsedMove() == nullptr)
	{
		DisplayFailedTextDialog();
		return;
	}

	if (targetPokemon->GetLastUsedMove()->mp_move->GetName() == "Transform" || targetPokemon->GetLastUsedMove()->mp_move->GetName() == "Struggle" || targetPokemon->GetLastUsedMove()->mp_move->GetName() == "Metronome")
	{
		DisplayFailedTextDialog();
		return;
	}

	if (targetPokemon->IsSemiInvulnerable())
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
		return;
	}

	sourcePokemon->SetUsedMimic(true);
	sourcePokemon->SetMimicPP(currentMove->m_currentPP);

	BattlePokemon::pokemonMove* targetLastUsedMove = targetPokemon->GetLastUsedMove();

	std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " learned " << targetLastUsedMove->mp_move->GetName() << "!\n";

	currentMove->mp_move = targetPokemon->GetDatabasePointer()->GetPointerToMovedexNumber(targetLastUsedMove->mp_move->GetMoveIndex() - 1);
	currentMove->m_currentPP = targetLastUsedMove->mp_move->GetPP();
	currentMove->m_maxPP = targetLastUsedMove->mp_move->GetPP();
	currentMove->b_isMimicked = true;
}

void DefenseDown2::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	if (targetPlayer->HasMist() && hit)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is protected by the mist!\n";

		currentMove->m_currentPP -= 1;

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetLastUsedMove(currentMove);

		return;
	}

	if (hit)
	{

		if (targetPokemon->GetDefenseStage() <= -6)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s defense won't go any lower!\n";
		}
		else if (targetPokemon->GetDefenseStage() == -5)
		{
			int lowerDefense{ targetPokemon->GetDefenseStage() - 1 };
			targetPokemon->SetDefenseStage(lowerDefense);

			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s defense fell!\n";
		}
		else if (targetPokemon->GetDefenseStage() > -5)
		{
			int lowerDefense{ targetPokemon->GetDefenseStage() - 2 };
			targetPokemon->SetDefenseStage(lowerDefense);

			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s defense fell harshly!\n";
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void EvasionUp::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int evasionStage = sourcePokemon->GetEvasionStage();

	if (sourcePokemon->GetEvasionStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " evasiveness won't go any higher!\n";
	}
	else
	{
		++evasionStage;
		sourcePokemon->SetEvasionStage(evasionStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s evasiveness rose!\n";
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Heal50::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (sourcePokemon->GetCurrentHP() < sourcePokemon->GetMaxHP())
	{
		double healAmount{};

		healAmount = ceil((double)sourcePokemon->GetMaxHP() / 2);

		sourcePokemon->HealCurrentHP(static_cast<int>(healAmount));

		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " had its HP restored!\n";
		std::cout << "Amount healed: " << healAmount << '\n';
	}

	else
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " HP is full!\n";
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void DefenseUp::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int defenseStage = sourcePokemon->GetEvasionStage();

	if (sourcePokemon->GetDefenseStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " defense won't go any higher!\n";
	}
	else
	{
		++defenseStage;
		sourcePokemon->SetDefenseStage(defenseStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s defense rose!\n";
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Minimize::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int evasionStage = sourcePokemon->GetEvasionStage();

	if (sourcePokemon->GetEvasionStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " evasiveness won't go any higher!\n";
	}
	else if (sourcePokemon->GetEvasionStage() == 5)
	{
		++evasionStage;
		sourcePokemon->SetEvasionStage(evasionStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s evasiveness rose!\n";
		sourcePokemon->SetUsedMinimize(true);
	}
	else if (sourcePokemon->GetEvasionStage() < 5)
	{
		evasionStage += 2;
		sourcePokemon->SetEvasionStage(evasionStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s evasiveness rose sharply!\n";
		sourcePokemon->SetUsedMinimize(true);
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void DefenseUp2::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int defenseStage = sourcePokemon->GetDefenseStage();

	if (sourcePokemon->GetDefenseStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " can't raise its defense any higher!\n";
	}
	else if (defenseStage == 5)
	{
		++defenseStage;
		sourcePokemon->SetDefenseStage(defenseStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s defense rose!\n";
	}
	else if (defenseStage < 5)
	{
		defenseStage += 2;
		sourcePokemon->SetDefenseStage(defenseStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s defense rose sharply!\n";
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void LightScreen::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (sourcePlayer->HasLightScreen())
	{
		DisplayFailedTextDialog();
	}

	else
	{
		sourcePlayer->SetLightScreen(true);
		std::cout << "Light screen made " << sourcePlayer->GetPlayerNameView() << "'s team stronger against special moves!\n";
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Haze::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	sourcePokemon->SetAttackStage(0);
	sourcePokemon->SetDefenseStage(0);
	sourcePokemon->SetSpecialAttackStage(0);
	sourcePokemon->SetSpecialDefenseStage(0);
	sourcePokemon->SetSpeedStage(0);
	sourcePokemon->SetEvasionStage(0);
	sourcePokemon->SetAccuracyStage(0);

	targetPokemon->SetAttackStage(0);
	targetPokemon->SetDefenseStage(0);
	targetPokemon->SetSpecialAttackStage(0);
	targetPokemon->SetSpecialDefenseStage(0);
	targetPokemon->SetSpeedStage(0);
	targetPokemon->SetEvasionStage(0);
	targetPokemon->SetAccuracyStage(0);

	std::cout << "All stat changes were eliminated!\n";

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Reflect::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (sourcePlayer->HasReflect())
	{
		DisplayFailedTextDialog();
	}

	else
	{
		sourcePlayer->SetReflect(true);
		std::cout << "Reflect made " << sourcePlayer->GetPlayerNameView() << "'s team stronger against physical moves!\n";
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void FocusEnergy::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (sourcePokemon->HasFocusEnergy())
	{
		DisplayFailedTextDialog();
	}
	else 
	{
		sourcePokemon->SetFocusEnergy(true);
		sourcePokemon->SetCriticalHitStage(2);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " is getting pumped!\n";
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Bide::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (!currentMove->b_isDisabled)
	{
		if (!sourcePokemon->IsBiding())
		{
			UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

			sourcePokemon->SetBide(true);
			sourcePlayer->SetCanSwitch(false);

			sourcePokemon->SetBideTurnCount(2);
			sourcePokemon->ResetBideCounter();

			currentMove->m_currentPP -= 1;
		}

		if (sourcePokemon->GetBideCounter() >= sourcePokemon->GetBideTurnCount())
		{
			hit = (targetPokemon->IsSemiInvulnerable()) ? false : true;

			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " unleashed its energy!\n";

			int bideDamage = sourcePokemon->GetBideDamage() * 2;

			if (hit)
			{
				if (targetPokemon->GetTypeOneEnum() == PokemonType::Ghost || targetPokemon->GetTypeTwoEnum() == PokemonType::Ghost)
				{
					DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
					bideDamage = 0;
				}

				if (targetPokemon->HasSubstitute())
				{
					if (bideDamage >= targetPokemon->GetSubstituteHP())
					{
						bideDamage = targetPokemon->GetSubstituteHP();
					}

					targetPokemon->DamageSubstitute(bideDamage);
					DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
					damageTaken = bideDamage;
				}

				else
				{
					if (bideDamage >= targetPokemon->GetCurrentHP())
					{
						bideDamage = targetPokemon->GetCurrentHP();
					}

					targetPokemon->DamageCurrentHP(bideDamage);
					damageTaken = bideDamage;
				}

				std::cout << bideDamage << " damage inflicted!\n";
			}

			else
			{
				DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
			}

			BideStop(sourcePlayer, sourcePokemon);
			BideReset(sourcePlayer, sourcePokemon);
		}
		else
		{
			sourcePokemon->IncrementBideCounter();
			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " is storing energy!\n";
		}
	}

	else
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s Bide is disabled!\n";

		BideStop(sourcePlayer, sourcePokemon);
		BideReset(sourcePlayer, sourcePokemon);
	}

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Metronome::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	size_t randomMod{ 67 };

	while (randomMod == 67 || randomMod == 101 || randomMod == 117 || randomMod == 118 || randomMod == 143)
	{
		std::uniform_int_distribution<size_t> randomModDistributor(0, 163);
		size_t randomModResult(randomModDistributor(generator));
		randomMod = randomModResult;
	}

	Move* selectedMove = Database::GetInstance()->GetPointerToMovedexNumber(randomMod);
	sourcePokemon->metronomeMove.mp_move = selectedMove;
	sourcePokemon->metronomeMove.m_currentPP = 1;
	sourcePokemon->metronomeMove.m_maxPP = 1;

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	std::cout << "Waggling its finger let " << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " use " << selectedMove->GetName() << "!\n";

	currentMove->m_currentPP -= 1;

	MoveEffectsFactory factory;

	{
		std::unique_ptr<IMoveEffects> moveEffect = factory.Call(selectedMove->GetSecondaryFlag());
		moveEffect->DoMove(sourcePlayer, targetPlayer, &sourcePokemon->metronomeMove, sourcePokemon, targetPokemon, bs);
	}

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void MirrorMove::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (targetPokemon->GetLastUsedMove() == nullptr)
	{
		DisplayFailedTextDialog();
		currentMove->m_currentPP -= 1;
		return;
	}

	BattlePokemon::pokemonMove* targetLastUsedMove = targetPokemon->GetLastUsedMove();

	if (targetLastUsedMove->mp_move->IsAffectedByMirrorMove())
	{
		Move* selectedMove = Database::GetInstance()->GetPointerToMovedexNumber(targetLastUsedMove->mp_move->GetMoveIndex() - 1);
		sourcePokemon->mirrorMove.mp_move = selectedMove;
		sourcePokemon->mirrorMove.m_currentPP = 1;
		sourcePokemon->mirrorMove.m_maxPP = 1;

		MoveEffectsFactory factory;

 		std::unique_ptr<IMoveEffects> moveEffect = factory.Call(selectedMove->GetSecondaryFlag());
		moveEffect->DoMove(sourcePlayer, targetPlayer, &sourcePokemon->mirrorMove, sourcePokemon, targetPokemon, bs);
	}
	else
	{
		DisplayFailedTextDialog();
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Explosion::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	sourcePokemon->DamageCurrentHP(sourcePokemon->GetCurrentHP());

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void PoisonHit40::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Poison && targetPokemon->GetTypeTwoEnum() != PokemonType::Poison)
			&& (targetPokemon->GetTypeOneEnum() != PokemonType::Steel && targetPokemon->GetTypeTwoEnum() != PokemonType::Steel) && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 40)
			{
				targetPokemon->ChangeStatus(Status::Poisoned);
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is poisoned!\n";
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void FlinchHit10::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		std::uniform_int_distribution<int> randomModDistributor(1, 101);
		int randomMod{ randomModDistributor(generator) };

		if (randomMod < 10 && targetPlayer == bs.GetSecondTurnPlayer() && currentEffectiveness != Effectiveness::No && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			targetPokemon->SetIsFlinched(true);
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void FlinchHit20::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		std::uniform_int_distribution<int> randomModDistributor(1, 101);
		int randomMod{ randomModDistributor(generator) };

		if (randomMod < 20 && targetPlayer == bs.GetSecondTurnPlayer() && currentEffectiveness != Effectiveness::No && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			targetPokemon->SetIsFlinched(true);
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Swift::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	hit = true;

	if (targetPokemon->IsSemiInvulnerable())
	{
		hit = false;
	}

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SkullBash::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (sourcePokemon->IsCharging())
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

		if (hit)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
		}

		else
		{
			DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
		}

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetCharging(false);
		sourcePlayer->SetCanSwitch(true);

		currentMove->m_currentPP -= 1;

		sourcePokemon->SetLastUsedMove(currentMove);
	}
	else
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " tucked in its head!\n";

		int defenseStage = sourcePokemon->GetEvasionStage();

		if (sourcePokemon->GetDefenseStage() >= 6)
		{
			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " defense won't go any higher!\n";
		}
		else
		{
			++defenseStage;
			sourcePokemon->SetDefenseStage(defenseStage);
			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s defense rose!\n";
		}

		sourcePokemon->SetCharging(true);
		sourcePlayer->SetCanSwitch(false);
	}
}

void SpecialDefenseUp2::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	int specialDefenseStage = sourcePokemon->GetSpecialDefenseStage();

	if (sourcePokemon->GetSpecialDefenseStage() >= 6)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " can't raise its special defense any higher!\n";
	}
	else if (specialDefenseStage == 5)
	{
		++specialDefenseStage;
		sourcePokemon->SetSpecialDefenseStage(specialDefenseStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s special defense rose!\n";
	}
	else if (specialDefenseStage < 5)
	{
		specialDefenseStage += 2;
		sourcePokemon->SetSpecialDefenseStage(specialDefenseStage);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s special defense rose sharply!\n";
	}

	currentMove->m_currentPP -= 1;

	sourcePokemon->SetLastUsedMove(currentMove);
}

void DreamEater::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (targetPokemon->GetStatus() != Status::Sleeping)
	{
		std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		currentMove->m_currentPP -= 1;
		sourcePokemon->SetLastUsedMove(currentMove);

		return;
	}

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		double leechedHealth{};

		if (damageTaken <= 0)
		{
			leechedHealth = 0;
		}
		else if (damageTaken == 1)
		{
			leechedHealth = 1;
		}
		else
		{
			leechedHealth = floor(damageTaken / 2);
		}

		if (leechedHealth > (sourcePokemon->GetMaxHP() - sourcePokemon->GetCurrentHP()))
		{
			leechedHealth = (sourcePokemon->GetMaxHP() - sourcePokemon->GetCurrentHP());
		}

		sourcePokemon->HealCurrentHP(static_cast<int>(leechedHealth));

		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " had its energy drained!\n";
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void PoisonGas::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	bool isImmune = ((targetPokemon->GetTypeOneEnum() == PokemonType::Poison || targetPokemon->GetTypeTwoEnum() == PokemonType::Poison) ||
		(targetPokemon->GetTypeOneEnum() == PokemonType::Steel || targetPokemon->GetTypeTwoEnum() == PokemonType::Steel));

	if (hit)
	{
		if (targetPokemon->GetStatus() != Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Normal && isImmune)
		{
			std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
		}
		else if (targetPokemon->GetStatus() == Status::Poisoned)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is already poisoned!\n";
		}
		else if (targetPokemon->GetStatus() != Status::Poisoned && targetPokemon->GetStatus() != Status::Normal)
		{
			DisplayFailedTextDialog();
		}
		else if (targetPokemon->GetStatus() == Status::Normal && !isImmune)
		{
			targetPokemon->ChangeStatus(Status::Poisoned);
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " was poisoned!\n";
		}
		else if (targetPokemon->HasSubstitute())
		{
			DisplayFailedTextDialog();
		}
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SkyAttack::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	if (sourcePokemon->IsCharging())
	{
		hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

		UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

		if (hit)
		{
			CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
			DisplayCritTextDialog();
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

			std::uniform_int_distribution<int> randomModDistributor(1, 101);
			int randomMod{ randomModDistributor(generator) };

			if (randomMod < 30 && targetPlayer == bs.GetSecondTurnPlayer() && currentEffectiveness != Effectiveness::No && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
			{
				targetPokemon->SetIsFlinched(true);
			}
		}

		else
		{
			DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
		}

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetCharging(false);
		sourcePlayer->SetCanSwitch(true);
		sourcePokemon->SetLastUsedMove(currentMove);
		currentMove->m_currentPP -= 1;
	}
	else
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " became cloaked in a harsh light!\n";
		sourcePokemon->SetCharging(true);
		sourcePlayer->SetCanSwitch(false);
	}
}

void Transform::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (sourcePokemon->IsTransformed() || targetPokemon->IsTransformed() || targetPokemon->HasSubstitute())
	{
		std::cout << "But it failed!\n";
		return;
	}

	hit = true;

	if (targetPokemon->IsSemiInvulnerable())
	{
		hit = false;
	}

	if (hit)
	{
		sourcePokemon->SetTransformation(targetPokemon);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " transformed into " << targetPokemon->GetNameView() << "!\n";
	}

	else
	{
		DisplayAttackAvoidedTextDialog(targetPlayer, targetPokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void ConfuseHit20::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		if (!targetPokemon->IsConfused())
		{
			std::uniform_int_distribution<int> rngDist(1, 101);
			int randomNumber{ rngDist(generator) };

			if (randomNumber <= 20 && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
			{
				std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " became confused!\n";

				targetPokemon->SetConfusedStatus(true);

				std::uniform_int_distribution<int> randomModDistributor(2, 4);
				int randomMod(randomModDistributor(generator));
				targetPokemon->SetConfusedTurnCount(randomMod);
				targetPokemon->ResetConfusedCounter();
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Psywave::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	CalculateTypeEffectiveness(currentMove, targetPokemon);

	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	double psywaveDamage{};

	if (hit)
	{
		if (targetPokemon->GetTypeOneEnum() == PokemonType::Dark || targetPokemon->GetTypeTwoEnum() == PokemonType::Dark)
		{
			DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
			psywaveDamage = 0;
		}

		else
		{
			std::uniform_int_distribution<int> rngDist(0, 100);
			int randomNumber{ rngDist(generator) };

			double psywaveDamage = floor(sourcePokemon->GetLevel() * (randomNumber + 50) / 100);

			if (psywaveDamage == 0)
			{
				psywaveDamage = 1;
			}

			if (targetPokemon->HasSubstitute())
			{
				targetPokemon->DamageSubstitute(static_cast<int>(psywaveDamage));
				DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
			}
			else
			{
				targetPokemon->DamageCurrentHP(static_cast<int>(psywaveDamage));
			}
			std::cout << psywaveDamage << " damage inflicted.\n";
		}

	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	damageTaken = psywaveDamage;

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Splash::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	std::cout << "But nothing happened!\n";

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Rest::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (sourcePokemon->GetStatus() != Status::Sleeping && sourcePokemon->GetCurrentHP() < sourcePokemon->GetMaxHP())
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " slept and became healthy!\n";

		sourcePokemon->ChangeStatus(Status::Sleeping);

		sourcePokemon->SetSleepTurnCount(2);
		sourcePokemon->ResetSleepCounter();
	}

	else if (sourcePokemon->GetCurrentHP() >= sourcePokemon->GetMaxHP())
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " HP is full!\n";
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Conversion::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (sourcePokemon->GetTypeOneEnum() == currentMove->mp_move->GetMoveTypeEnum() || sourcePokemon->GetTypeTwoEnum() == currentMove->mp_move->GetMoveTypeEnum() || sourcePokemon->IsConverted())
	{
		DisplayFailedTextDialog();
	}
	else
	{
		sourcePokemon->SetConversion(currentMove);

		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s type changed to " << sourcePokemon->GetTypeOne() << "!\n";
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void TriAttack::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = CalculateHitChance(currentMove, sourcePokemon, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		std::uniform_int_distribution<int> rngDist(1, 101);
		int randomNumber{ rngDist(generator) };

		if (randomNumber <= 20 && currentEffectiveness != Effectiveness::No && !targetPokemon->HasSubstitute() && targetPokemon->GetCurrentHP() != 0)
		{
			std::uniform_int_distribution<int> rngDist(1, 3);
			int randomStatus{ rngDist(generator) };

			switch (randomStatus)
			{
			case 1:
				if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Fire && targetPokemon->GetTypeTwoEnum() != PokemonType::Fire))
				{
					targetPokemon->ChangeStatus(Status::Burned);
					std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is burned!\n";

				}
				break;

			case 2:
				if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Ice && targetPokemon->GetTypeTwoEnum() != PokemonType::Ice))
				{
					targetPokemon->ChangeStatus(Status::Frozen);
					std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is frozen solid!\n";
				}
				break;

			case 3:
				if (targetPokemon->GetStatus() == Status::Normal && (targetPokemon->GetTypeOneEnum() != PokemonType::Electric && targetPokemon->GetTypeTwoEnum() != PokemonType::Electric))
				{
					targetPokemon->ChangeStatus(Status::Paralyzed);
					std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " is paralyzed! It may be unable to move!\n";
				}
				break;

			default:
				break;
			}
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void SuperFang::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	CalculateTypeEffectiveness(currentMove, targetPokemon);

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	double superFangDamage{};

	if (targetPokemon->HasSubstitute())
	{
		superFangDamage = floor(targetPokemon->GetSubstituteHP() / 2);
	}
	else
	{
		superFangDamage = floor(targetPokemon->GetCurrentHP() / 2);
	}

	if (superFangDamage <= 0)
	{
		superFangDamage = 1;
	}

	if (currentEffectiveness == Effectiveness::No)
	{
		DisplayEffectivenessTextDialog(targetPlayer, targetPokemon);
		superFangDamage = 0;
	}

	if (targetPokemon->HasSubstitute())
	{
		targetPokemon->DamageSubstitute(static_cast<int>(superFangDamage));
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);
	}
	else
	{
		targetPokemon->DamageCurrentHP(static_cast<int>(superFangDamage));
	}

	std::cout << superFangDamage << " damage inflicted\n";

	damageTaken = superFangDamage;

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Substitute::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	if (sourcePokemon->HasSubstitute())
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " already has a substitute!\n";

		currentMove->m_currentPP -= 1;

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		sourcePokemon->SetLastUsedMove(currentMove);

		return;
	}

	double substituteHP = floor(sourcePokemon->GetMaxHP() / 4);

	if (substituteHP >= sourcePokemon->GetCurrentHP())
	{
		std::cout << "But it does not have enough HP left to make a substitute!\n";
	}
	else 
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " put in a substitute!\n";
		sourcePokemon->SetSubstitute(true);
		sourcePokemon->SetSubstituteHP(static_cast<int>(substituteHP));
		sourcePokemon->DamageCurrentHP(static_cast<int>(substituteHP));
		sourcePokemon->SetBound(false);
		sourcePokemon->ResetBoundCounter();
		sourcePokemon->SetBoundTurnCount(0);
	}

	currentMove->m_currentPP -= 1;

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	sourcePokemon->SetLastUsedMove(currentMove);
}

void Struggle::DoMove(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattleSystem& bs)
{
	hit = true;

	if (targetPokemon->IsSemiInvulnerable())
	{
		hit = false;
	}

	std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " has no moves left!\n";

	UsedTextDialog(sourcePlayer, currentMove, sourcePokemon);

	double recoilDamage{ 0 };

	if (hit)
	{
		CalculateDamage(targetPlayer, currentMove, sourcePokemon, targetPokemon);
		DisplayCritTextDialog();
		DisplaySubstituteDamageTextDialog(targetPlayer, targetPokemon);

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

		recoilDamage = round(sourcePokemon->GetMaxHP() / 4);
		sourcePokemon->DamageCurrentHP(static_cast<int>(recoilDamage));

		if (currentEffectiveness != Effectiveness::No)
		{
			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was damaged by the recoil!\n";

			CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);
		}
	}

	else
	{
		DisplayAttackMissedTextDialog(sourcePlayer, sourcePokemon);
	}

	sourcePokemon->SetLastUsedMove(currentMove);
}
