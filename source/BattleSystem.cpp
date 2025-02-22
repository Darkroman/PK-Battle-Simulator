#include "../include/BattleSystem.h"
#include "../include/InputValidation.h"
#include "../include/MoveEffects.h"

BattleSystem::BattleSystem()
{
	//seed = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count());

	//std::mt19937 gen(seed);

	//BattleSystem::generator = gen;
}

BattleSystem::BattleSystem(std::vector<Player>& players)
{
	BattleSystem::players[0] = &(players[0]);
	BattleSystem::players[1] = &(players[1]);

	playerOne = &(players[0]);
	playerTwo = &(players[1]);

	seed = static_cast<int>(std::chrono::system_clock::now().time_since_epoch().count());

	std::mt19937 gen(seed);

	BattleSystem::generator = gen;
}

bool BattleSystem::CheckPlayerPokemonAvailability()
{
	if (!playerOne->GetPokemonCount() && !playerTwo->GetPokemonCount())
	{
		std::cout << "Neither player has pokemon to use!\n\n";
		return true;
	}
	else if (playerOne->GetPokemonCount() && !(playerTwo->GetPokemonCount()))
	{
		std::cout << playerTwo->GetPlayerNameView() << " does not have any Pokemon!\n\n";
		return true;
	}
	else if (playerTwo->GetPokemonCount() && !(playerOne->GetPokemonCount()))
	{
		std::cout << playerOne->GetPlayerNameView() << " does not have any Pokemon!\n\n";
		return true;
	}
	else
	{
		return false;
	}
}

const Player* BattleSystem::GetPlayerOne() const
{
	return playerOne;
}

const Player* BattleSystem::GetPlayerTwo() const
{
	return playerTwo;
}

void BattleSystem::SetPlayerOne(Player* player)
{
	playerOne = player;
}

void BattleSystem::SetPlayerTwo(Player* player)
{
	playerTwo = player;
}

const BattlePokemon* BattleSystem::GetPlayerOneCurrentPokemon() const
{
	return playerOneCurrentPokemon;
}

const BattlePokemon* BattleSystem::GetPlayerTwoCurrentPokemon() const
{
	return playerTwoCurrentPokemon;
}

void BattleSystem::SetPlayerOneCurrentPokemon(BattlePokemon* pokemon)
{
	playerOneCurrentPokemon = pokemon;
}

void BattleSystem::SetPlayerTwoCurrentPokemon(BattlePokemon* pokemon)
{
	playerTwoCurrentPokemon = pokemon;
}

void BattleSystem::SetPlayerOneCurrentMove(BattlePokemon::pokemonMove* move)
{
	playerOneCurrentMove = move;
}

void BattleSystem::SetPlayerTwoCurrentMove(BattlePokemon::pokemonMove* move)
{
	playerTwoCurrentMove = move;
}

const Player* BattleSystem::GetFirstTurnPlayer() const
{
	return firstTurnPlayer;
}

const Player* BattleSystem::GetSecondTurnPlayer() const
{
	return secondTurnPlayer;
}

void BattleSystem::ThrowOutFirstPokemon()
{
	std::cout << playerOne->GetPlayerNameView() << " chose " << playerOne->GetBelt(1)->GetPokemonNameView() << "!\n";
	std::cout << playerTwo->GetPlayerNameView() << " chose " << playerTwo->GetBelt(1)->GetPokemonNameView() << "!\n\n";

	playerOneCurrentPokemon = playerOne->GetBelt(1);
	playerTwoCurrentPokemon = playerTwo->GetBelt(1);
}

void BattleSystem::DisplayFightingPokemon()
{
	std::cout << playerOne->GetPlayerNameView() << "'s Pokemon: " << playerOneCurrentPokemon->GetNameView() << " ("
		<< playerOneCurrentPokemon->GetCurrentHP() << "/" << playerOneCurrentPokemon->GetMaxHP() << ")\n";

	std::cout << playerTwo->GetPlayerNameView() << "'s Pokemon: " << playerTwoCurrentPokemon->GetNameView() << " ("
		<< playerTwoCurrentPokemon->GetCurrentHP() << "/" << playerTwoCurrentPokemon->GetMaxHP() << ")\n\n";
}

bool BattleSystem::StartBattle()
{
	bool exit = false;

	exit = CheckPlayerPokemonAvailability();

	if (exit == true)
	{
		return false;
	}

	ThrowOutFirstPokemon();

	BattleLoop();

	return false;
}

bool BattleSystem::BattleLoop()
{
	int turnCount{ 0 };
	bool winCondition{ false };
	while (winCondition == false)
	{
		++turnCount;
		std::cout << "TURN #" << turnCount << "\n\n";

		DisplayFightingPokemon();

		PlayerOneMakeSelection();

		if (playerOne->HasForfeited())
		{
			winCondition = CheckWinCondition(playerTwo, playerOne);
			return false;
		}

		PlayerTwoMakeSelection();

		if (playerTwo->HasForfeited())
		{
			winCondition = CheckWinCondition(playerOne, playerTwo);
			return false;
		}

		DetermineWhoGoesFirst();

		MoveEffectsFactory factory;

		if (firstTurnPlayer->IsSwitching())
		{
			firstTurnPokemon = PerformSwitch(firstTurnPlayer, firstTurnPokemon);

			if (secondTurnPokemon->IsBound())
			{
				secondTurnPokemon->SetBoundTurnCount(secondTurnPokemon->GetBoundCounter());
			}
		}
		else if (firstTurnPlayer->HasSwitched())
		{
			firstTurnPlayer->SetHasSwitched(false);
			//do nothing, no moves, and keep executing the loop
		}
		else
		{
			if (CheckPerformativeStatus(firstTurnPlayer, firstTurnPokemon, firstTurnMove))
			{
				std::unique_ptr<IMoveEffects> moveEffect = factory.Call(firstTurnMove->mp_move->GetSecondaryFlag());
				moveEffect->DoMove(firstTurnPlayer, secondTurnPlayer, firstTurnMove, firstTurnPokemon, secondTurnPokemon, *this);
			}
			lastUsedMoveFirst = firstTurnMove;
		}

		RageCheck(firstTurnPlayer, secondTurnPlayer, firstTurnMove, firstTurnPokemon, secondTurnPokemon);

		winCondition = CheckWinCondition(firstTurnPlayer, secondTurnPlayer);
		if (winCondition) { continue; }

		std::cout << '\n';

		if (secondTurnPlayer->IsSwitching())
		{
			secondTurnPokemon = PerformSwitch(secondTurnPlayer, secondTurnPokemon);

			if (firstTurnPokemon->IsBound())
			{
				firstTurnPokemon->SetBoundTurnCount(firstTurnPokemon->GetBoundCounter());
			}
		}
		else if (secondTurnPlayer->HasSwitched())
		{
			secondTurnPlayer->SetHasSwitched(false);
			//do nothing, no moves, and keep executing the loop
		}
		else if ((!secondTurnPokemon->IsFainted()) && (!firstTurnPokemon->IsFainted()))
		{
			if (CheckPerformativeStatus(secondTurnPlayer, secondTurnPokemon, secondTurnMove))
			{
				std::unique_ptr<IMoveEffects> moveEffect = factory.Call(secondTurnMove->mp_move->GetSecondaryFlag());
				moveEffect->DoMove(secondTurnPlayer, firstTurnPlayer, secondTurnMove, secondTurnPokemon, firstTurnPokemon, *this);
			}
			lastUsedMoveSecond = secondTurnMove;
		}

		RageCheck(secondTurnPlayer, firstTurnPlayer, secondTurnMove, secondTurnPokemon, firstTurnPokemon);

		winCondition = CheckWinCondition(secondTurnPlayer, firstTurnPlayer);
		if (winCondition) { continue; }

		DeterminePostTurnDamageOrder();

		std::cout << '\n';

		CheckSeededStatuses(firstTurnPlayer, secondTurnPlayer, firstTurnPokemon, secondTurnPokemon); // first turn player/pokemon gets their health sapped if seeded

		winCondition = CheckWinCondition(secondTurnPlayer, firstTurnPlayer);
		if (winCondition) { continue; }

		winCondition = CheckWinCondition(firstTurnPlayer, secondTurnPlayer);
		if (winCondition) { continue; }

		CheckDamagingStatuses(firstTurnPlayer, secondTurnPlayer, firstTurnPokemon, secondTurnPokemon); // first turn player/pokemon are damaged first

		winCondition = CheckWinCondition(secondTurnPlayer, firstTurnPlayer);
		if (winCondition) { continue; }

		winCondition = CheckWinCondition(firstTurnPlayer, secondTurnPlayer);
		if (winCondition) { continue; }

		CheckBoundStatuses(firstTurnPlayer, secondTurnPlayer, firstTurnPokemon, secondTurnPokemon);

		winCondition = CheckWinOrSwitch(secondTurnPlayer, firstTurnPlayer, firstTurnPokemon);
		if (winCondition) { continue; }

		winCondition = CheckWinOrSwitch(firstTurnPlayer, secondTurnPlayer, secondTurnPokemon);
		if (winCondition) { continue; }

		CheckDisabledStatus(firstTurnPlayer, secondTurnPlayer, firstTurnPokemon, secondTurnPokemon);

		CheckFieldEffects(firstTurnPlayer, secondTurnPlayer);

		firstTurnPlayer->SetHasSwitched(false);
		secondTurnPlayer->SetHasSwitched(false);
		damageTaken = 0;

		std::cout << '\n';

#if !defined NDEBUG
			ResetHPandPPForTesting();
#endif
	}

	turnCount = 0;
	return false;
}

bool BattleSystem::CheckPPCountForStruggle(BattlePokemon* pokemon)
{
	int zeroPPCount{ 0 }, disabledCount{ 0 };

	for (size_t i = 0; i < 4; ++i)
	{
		if (pokemon->GetMove(i + 1)->mp_move != nullptr)
		{
			if (pokemon->GetMove(i + 1)->m_currentPP == 0)
			{
				++zeroPPCount;
			}
			if (pokemon->GetMove(i + 1)->b_isDisabled)
			{
				++disabledCount;
			}
		}
	}

	if (zeroPPCount + disabledCount >= pokemon->GetMoveCount())
	{
		return true;
	}
	return false;
}

void BattleSystem::PlayerOneMakeSelection()
{
	if (playerOneCurrentPokemon->IsCharging() || playerOneCurrentPokemon->IsRecharging() || playerOneCurrentPokemon->IsThrashing() || playerOneCurrentPokemon->IsBiding())
	{
		return;
	}

	if (playerOne->IsAI())
	{
		AISelection(playerOne, playerOneCurrentPokemon);
	}
	else
	{
		std::cout << playerOne->GetPlayerNameView() << " choose your action\n";
	
		MakeASelectionLoop(playerOne, playerOneCurrentPokemon);

		if (playerOne->HasForfeited())
		{
			return;
		}
	}
	playerOneCurrentMove = selectedMove;
	selectedMove = nullptr;
}

void BattleSystem::PlayerTwoMakeSelection()
{
	if (playerTwoCurrentPokemon->IsCharging() || playerTwoCurrentPokemon->IsRecharging() || playerTwoCurrentPokemon->IsThrashing())
	{
		return;
	}

	if (playerTwo->IsAI())
	{
		AISelection(playerTwo, playerTwoCurrentPokemon);
	}
	else
	{
		std::cout << playerTwo->GetPlayerNameView() << " choose your action\n";

		MakeASelectionLoop(playerTwo, playerTwoCurrentPokemon);

		if (playerTwo->HasForfeited())
		{
			return;
		}
	}
	playerTwoCurrentMove = selectedMove;
	selectedMove = nullptr;
}

void BattleSystem::MakeASelectionLoop(Player* player, BattlePokemon* currentPokemon)
{
	bool exit = false;

	while (exit == false)
	{
		std::cout << "1. Fight \t";
		std::cout << "2. Switch Pokemon";
		std::cout << ((player->CanSwitch() == true) ? " \t" : "(X) \t");
		std::cout << "3. Forfeit\n";

		std::string input{};
		std::cout << "Option: ";
		std::cin >> input;

		if (!IsDigits(input) || input.size() > 10)
		{
			std::cout << "Invalid input!\n\n";
			continue;
		}

		int choice{ std::stoi(input) };

		switch (choice)
		{
		case 1:
			exit = Fight(player, currentPokemon);
			break;

		case 2:
			if (!player->CanSwitch())
			{
				std::cout << "You aren't able to switch Pokemon right now!\n";
				break;
			}
			exit = SwitchPokemonOption(player, currentPokemon);
			break;

		case 3:
			Forfeit(player);
			exit = true;
			break;

		default:
			std::cout << "Invalid input!\n\n";
		}
	}
}

bool BattleSystem::Fight(Player* player, BattlePokemon* currentPokemon)
{
	bool struggle{ false };

	while (true)
	{
		std::cout << currentPokemon->GetName() << "'s current moves\n";
		currentPokemon->DisplayMovesInBattle();
		
		struggle = CheckPPCountForStruggle(currentPokemon);

		if (struggle)
		{
			std::cout << "You are out of PP for all moves. All you can do is Struggle.\n\n";
			selectedMove = currentPokemon->Struggle();
			return true;
		}

		std::string input{};
		std::cout << "Option (0 to cancel): ";
		std::cin >> input;
		std::cout << '\n';

		if (!IsDigits(input) || input.size() > 10)
		{
			std::cout << "Invalid input!\n\n";
			continue;
		}

		int choice{ std::stoi(input) };

		if (choice == 0)
		{
			return false;
		}

		if (choice > 4)
		{
			std::cout << "Invalid input!\n\n";
			continue;
		}

		if (choice > 0 && struggle)
		{
			selectedMove = currentPokemon->Struggle();
			return true;
		}

		if (currentPokemon->GetMove(choice)->mp_move == nullptr)
		{
			std::cout << "There is no move there!\n\n";
			continue;
		}

		if (currentPokemon->GetMove(choice)->b_isDisabled == true)
		{
			std::cout << "This move is currently disabled!\n\n";
			continue;
		}

		if (currentPokemon->GetPP(choice) <= 0)
		{
			std::cout << "There's no PP left for this move!\n\n";
			continue;
		}

		if (currentPokemon->GetMove(choice)->mp_move != nullptr)
		{
			selectedMove = currentPokemon->GetMove(choice);
			std::cout << player->GetPlayerNameView() << " has chosen " << selectedMove->mp_move->GetName() << "\n\n";
			return true;
		}
	}
}

bool BattleSystem::SwitchPokemonOption(Player* currentPlayer, BattlePokemon* currentPokemon)
{
	std::cout << "Choose Pokemon to switch out! 0 to cancel.\n";
	
	bool exit = false;
	while (exit == false)
	{
		currentPlayer->DisplayPlayerPokemon();

		std::string input{};
		std::cout << "Option: ";
		std::cin >> input;
		std::cout << '\n';

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (!IsDigits(input) || input.size() > 10)
		{
			std::cout << "Invalid input!\n\n";
			continue;
		}

		int choice{ std::stoi(input) };

		if (choice == 0 && currentPokemon->IsFainted())
		{
			std::cout << "Your " << currentPokemon->GetNameView() << " is fainted. You must select another pokemon to take its place!\n\n";
			continue;
		}
		else if (choice == 0)
		{
			return false;
		}

		if (choice > 6)
		{
			std::cout << "Invalid input!\n\n";
			continue;
		}

		if (!currentPlayer->GetBelt(choice)->HasPokemon())
		{
			std::cout << "No Pokemon there!\n\n";
			continue;
		}

		if (currentPlayer->GetBelt(choice)->IsFainted())
		{
			std::cout << "A fainted Pokemon cannot fight!\n\n";
			continue;
		}

		if (currentPlayer->GetBelt(choice) == currentPokemon)
		{
			std::cout << "That pokemon is already in play!\n\n";
			continue;
		}

		if (choice != 0)
		{
			exit = true;

			currentPlayer->SetIsSwitching(true);

			currentPlayer->SetPokemonToSwitchTo(currentPlayer->GetBelt(choice));

			return exit;
		}
	}
	return exit;
}

void BattleSystem::Forfeit(Player* sourcePlayer)
{
	std::cout << sourcePlayer->GetPlayerNameView() << " has forfeited!\n\n";
	sourcePlayer->SetForfeit(true);
}

BattlePokemon* BattleSystem::PerformSwitch(Player* currentPlayer, BattlePokemon* currentPokemon)
{
	std::cout << currentPlayer->GetPlayerNameView() << " switches out " << currentPokemon->GetNameView() << "\n";

	ResetStatsOnSwitch(currentPokemon);
	currentPokemon = currentPlayer->GetPokemonToSwitchTo();

	std::cout << currentPlayer->GetPlayerNameView() << " chooses " << currentPokemon->GetNameView() << "\n\n";

	if (currentPlayer == playerOne)
	{
		playerOneCurrentPokemon = currentPokemon;
		currentPlayer->SetIsSwitching(false);
		return playerOneCurrentPokemon;
	}

	if (currentPlayer == playerTwo)
	{
		playerTwoCurrentPokemon = currentPokemon;
		currentPlayer->SetIsSwitching(false);
		return playerTwoCurrentPokemon;
	}

	return currentPokemon;
}

void BattleSystem::ResetStatsOnSwitch(BattlePokemon* currentPokemon)
{
	if (currentPokemon->IsTransformed())
	{
		currentPokemon->Detransform();
	}

	if (currentPokemon->IsConverted())
	{
		currentPokemon->Deconvert();
	}

	currentPokemon->SetAccuracyStage(0);
	currentPokemon->SetAttackStage(0);
	currentPokemon->SetCriticalHitStage(0);
	currentPokemon->SetDefenseStage(0);
	currentPokemon->SetEvasionStage(0);
	currentPokemon->SetSpecialAttackStage(0);
	currentPokemon->SetSpecialDefenseStage(0);
	currentPokemon->SetSpeedStage(0);

	currentPokemon->SetConfusedStatus(false);
	currentPokemon->SetSemiInvulnerableDig(false);
	currentPokemon->SetSemiInvulnerableFly(false);
	currentPokemon->ResetBadlyPoisonCounter();
	currentPokemon->SetSeededStatus(false);
	currentPokemon->SetBound(false);
	currentPokemon->ResetBoundCounter();
	currentPokemon->SetBoundTurnCount(0);
	currentPokemon->SetUsedMinimize(false);
	currentPokemon->SetFocusEnergy(false);

	if (currentPokemon->HasUsedMimic())
	{
		for (size_t i = 1; i < 5; ++i)
		{
			if (currentPokemon->GetMove(i)->b_isMimicked)
			{
				currentPokemon->GetMove(i)->mp_move = currentPokemon->GetDatabasePointer()->GetPointerToMovedexNumber(101);
				currentPokemon->GetMove(i)->m_currentPP = currentPokemon->GetMimicPP();
				currentPokemon->GetMove(i)->m_maxPP = currentPokemon->GetMove(i)->mp_move->GetPP();

				currentPokemon->SetUsedMimic(false);
				currentPokemon->GetMove(i)->b_isMimicked = false;
				break;
			}
		}
	}

	if (currentPokemon->MoveIsDisabled())
	{
		for (size_t i = 1; i < 5; ++i)
		{
			if (currentPokemon->GetMove(i)->b_isDisabled)
			{
				currentPokemon->GetMove(i)->b_isDisabled = false;
				currentPokemon->SetDisabledStatus(false);
				currentPokemon->ResetDisabledCounter();
			}
		}
	}
}

void BattleSystem::DetermineWhoGoesFirst()
{
	firstTurnPlayer = playerOne;
	secondTurnPlayer = playerTwo;
	firstTurnPokemon = playerOneCurrentPokemon;
	secondTurnPokemon = playerTwoCurrentPokemon;
	firstTurnMove = playerOneCurrentMove;
	secondTurnMove = playerTwoCurrentMove;

	double stageMultiplierOne = CalculateStageModifier(playerOneCurrentPokemon->GetSpeedStage());
	double stageMultiplierTwo = CalculateStageModifier(playerTwoCurrentPokemon->GetSpeedStage());

	double playerOneSpeed = floor(playerOneCurrentPokemon->GetSpeed() * stageMultiplierOne);
	double playerTwoSpeed = floor(playerTwoCurrentPokemon->GetSpeed() * stageMultiplierTwo);

	if (playerOneCurrentPokemon->GetStatus() == Status::Paralyzed)
	{
		playerOneSpeed /= 2;
	}

	if (playerTwoCurrentPokemon->GetStatus() == Status::Paralyzed)
	{
		playerTwoSpeed /= 2;
	}

	if (playerOne->IsSwitching() && !playerTwo->IsSwitching())
	{
		std::cout << playerOne->GetPlayerNameView() << " goes first.\n";
		return;
	}

	if (playerTwo->IsSwitching() && !playerOne->IsSwitching())
	{
		firstTurnPlayer = playerTwo;
		secondTurnPlayer = playerOne;
		firstTurnPokemon = playerTwoCurrentPokemon;
		secondTurnPokemon = playerOneCurrentPokemon;
		firstTurnMove = playerTwoCurrentMove;
		secondTurnMove = playerOneCurrentMove;

		std::cout << playerTwo->GetPlayerNameView() << " goes first.\n";

		return;
	}

	if (playerOne->IsSwitching() && playerTwo->IsSwitching())
	{
		std::cout << playerOne->GetPlayerNameView() << " goes first.\n\n";
		return;
	}

	//if (playerOneCurrentMove == nullptr)
	//{
	//	std::cout << playerOne->GetPlayerNameView() << " goes first.\n\n";
	//	return;
	//}

	//if (playerTwoCurrentMove == nullptr)
	//{
	//	std::cout << playerTwo->GetPlayerNameView() << " goes first.\n\n";
	//	return;
	//}

	if ((playerOneCurrentMove->mp_move->GetPriority() == playerTwoCurrentMove->mp_move->GetPriority()) && (playerOneSpeed == playerTwoSpeed))
	{
		std::uniform_int_distribution<int> firstdist(1, 2);

		int firstmod{ firstdist(generator) };

		if (firstmod == 2)
		{
			firstTurnPlayer = playerTwo;
			secondTurnPlayer = playerOne;
			firstTurnPokemon = playerTwoCurrentPokemon;
			secondTurnPokemon = playerOneCurrentPokemon;
			firstTurnMove = playerTwoCurrentMove;
			secondTurnMove = playerOneCurrentMove;

			std::cout << playerTwo->GetPlayerNameView() << " goes first.\n\n";

			return;
		}

		std::cout << playerOne->GetPlayerNameView() << " goes first.\n\n";

		return;
	}

	if (playerOneCurrentMove->mp_move->GetPriority() < playerTwoCurrentMove->mp_move->GetPriority())
	{
		firstTurnPlayer = playerTwo;
		secondTurnPlayer = playerOne;
		firstTurnPokemon = playerTwoCurrentPokemon;
		secondTurnPokemon = playerOneCurrentPokemon;
		firstTurnMove = playerTwoCurrentMove;
		secondTurnMove = playerOneCurrentMove;

		std::cout << playerTwo->GetPlayerNameView() << " goes first.\n\n";

		return;
	}

	if (playerOneCurrentMove->mp_move->GetPriority() == playerTwoCurrentMove->mp_move->GetPriority())
	{
		if (playerOneSpeed < playerTwoSpeed)
		{
			firstTurnPlayer = playerTwo;
			secondTurnPlayer = playerOne;
			firstTurnPokemon = playerTwoCurrentPokemon;
			secondTurnPokemon = playerOneCurrentPokemon;
			firstTurnMove = playerTwoCurrentMove;
			secondTurnMove = playerOneCurrentMove;

			std::cout << playerTwo->GetPlayerNameView() << " goes first.\n\n";

			return;
		}
	}
	std::cout << playerOne->GetPlayerNameView() << " goes first.\n\n";

}

int BattleSystem::CalculateCriticalHitStageModifier(size_t element)
{
	if (element > 3)
	{
		element = 3;
	}

	return m_arr_CriticalHitStageMultiplier[element];
}

double BattleSystem::CalculateCriticalHit(BattlePokemon* source)
{
	int critModNumber = CalculateCriticalHitStageModifier(source->GetCriticalHitStage());

	std::uniform_int_distribution<int> critmoddistributor(0, 10000);

	double randomNumber{ static_cast<double>(critmoddistributor(generator)) };

	if (randomNumber >= critModNumber)
	{
		isCriticalHit = false;
		return 1;
	}
	else
	{
		isCriticalHit = true;
		return 1.5;
	}
}

double BattleSystem::CalculateStageModifier(size_t element)
{
	element += 6;
	return m_arr_StageMultiplier[element];
}

double BattleSystem::CalculateTypeEffectiveness(BattlePokemon::pokemonMove* currentMove, BattlePokemon* target)
{
	size_t moveType = static_cast<size_t>(currentMove->mp_move->GetMoveTypeEnum());
	size_t defensiveTypeOne = static_cast<size_t>(target->GetTypeOneEnum());
	size_t defensiveTypeTwo = static_cast<size_t>(target->GetTypeTwoEnum());

	double moveEffectiveness{ 1.0 };

	moveEffectiveness = typeEffectivenessArray[moveType][defensiveTypeOne];

	if (defensiveTypeTwo != 18)
	{
		moveEffectiveness *= typeEffectivenessArray[moveType][defensiveTypeTwo];
	}

	if (moveEffectiveness > 1)
	{
		currentEffectiveness = Effectiveness::Super;
	}
	
	if (moveEffectiveness < 1 && moveEffectiveness > 0)
	{
		currentEffectiveness = Effectiveness::Less;
	}

	if (moveEffectiveness == 0)
	{
		currentEffectiveness = Effectiveness::No;
	}

	if (currentMove->mp_move->GetSecondaryFlag() == 6 && moveEffectiveness != 0)
	{
		currentEffectiveness = Effectiveness::OHKO;
	}

	return moveEffectiveness;
}

double BattleSystem::CalculateAccuracyModifiers(int element)
{
	element += 6;
	return m_arr_AccuracyStageMultiplier[element];
}

bool BattleSystem::CalculateHitChance(BattlePokemon::pokemonMove* currentMove, BattlePokemon* source, BattlePokemon* target)
{
	if (
		(target->IsSemiInvulnerableFromFly() && (currentMove->mp_move->GetSecondaryFlag() != 9 && currentMove->mp_move->GetName() != "Thunder")) ||
		(target->IsSemiInvulnerableFromDig() && (currentMove->mp_move->GetSecondaryFlag() != 50 && currentMove->mp_move->GetName() != "Fissure"))
	   )
	{
		return false;
	}

	int adjustedStages = (source->GetAccuracyStage() - target->GetEvasionStage());

	if (adjustedStages < -6)
	{
		adjustedStages = -6;
	}
	else if (adjustedStages > 6)
	{
		adjustedStages = 6;
	}

	double moveAccuracy = static_cast<double>(currentMove->mp_move->GetAccuracy());

	double accuracyMod{ 0 };

	if (currentMove->mp_move->GetSecondaryFlag() != 6)
	{
		accuracyMod = moveAccuracy * CalculateAccuracyModifiers(adjustedStages);
	}
	else
	{
		accuracyMod = (source->GetLevel() - target->GetLevel()) + 30; // for one-hit KO moves
	}

	double randomMod{ 0.0 };
	double finalMod{ 0.0 };

	if (accuracyMod >= 100.0)
	{
		return true;
	}
	else
	{
		std::uniform_int_distribution<int> randomModDistributor(1, 100);
		double randomMod{ static_cast<double>(randomModDistributor(generator)) };
		finalMod = 100.0 - randomMod;		

		if (finalMod < accuracyMod)
		{
			return true;
		}

		return false;
	}
}

void BattleSystem::CalculateDamage(Player* targetPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* source, BattlePokemon* target)
{
	double damage{ 0 };

	damageTaken = 0;

	double effectiveness = CalculateTypeEffectiveness(currentMove, target);

	if (currentMove->mp_move->GetSecondaryFlag() == 92)
	{
		effectiveness = 1;
	}

	if ((currentMove->mp_move->GetSecondaryFlag() == 6) && effectiveness != 0)
	{
		damage = target->GetCurrentHP();
		target->DamageCurrentHP(static_cast<int>(damage));
		damageTaken = damage;
		return;
	}

	if (effectiveness == 0)
	{
		return;
	}

	double critical = CalculateCriticalHit(source);

	double sourceAttack{ 0.0 };
	double targetDefense{ 0.0 };

	double stagemultiplier{ 0.0 };

	if (currentMove->mp_move->GetCategoryEnum() == Category::Physical)
	{
		if (isCriticalHit && (source->GetAttackStage() < 0))
		{
			stagemultiplier = CalculateStageModifier(0);
			sourceAttack = source->GetAttack() * stagemultiplier;
		}
		else
		{
			stagemultiplier = CalculateStageModifier(source->GetAttackStage());
			sourceAttack = source->GetAttack() * stagemultiplier;
		}

		if (isCriticalHit && (source->GetDefenseStage() > 0))
		{
			stagemultiplier = CalculateStageModifier(0);
			targetDefense = target->GetDefense() * stagemultiplier;
		}
		else
		{
			stagemultiplier = CalculateStageModifier(target->GetDefenseStage());
			targetDefense = target->GetDefense() * stagemultiplier;
		}
	}

	else if (currentMove->mp_move->GetCategoryEnum() == Category::Special)
	{
		if (isCriticalHit && (source->GetSpecialAttackStage() < 0))
		{
			stagemultiplier = CalculateStageModifier(0);
			sourceAttack = source->GetSpecialAttack() * stagemultiplier;
		}
		else
		{
			stagemultiplier = CalculateStageModifier(source->GetSpecialAttackStage());
			sourceAttack = source->GetSpecialAttack() * stagemultiplier;
		}

		if (isCriticalHit && (source->GetSpecialDefenseStage() > 0))
		{
			stagemultiplier = CalculateStageModifier(0);
			targetDefense = target->GetSpecialDefense() * stagemultiplier;
		}
		else
		{
			stagemultiplier = CalculateStageModifier(target->GetSpecialDefenseStage());
			targetDefense = target->GetSpecialDefense() * stagemultiplier;
		}
	}

	double stab{};

	if ((currentMove->mp_move->GetMoveTypeEnum() == source->GetTypeOneEnum()) || (currentMove->mp_move->GetMoveTypeEnum() == source->GetTypeTwoEnum())
		&& currentMove->mp_move->GetSecondaryFlag() != 92)
	{
		stab = 1.5;
	}
	else
	{
		stab = 1;
	}

	double burn{ 1 };

	if (source->GetStatus() == Status::Burned)
	{
		burn = 0.5;
	}

	std::uniform_int_distribution<int> damagemoddistributor(85, 100);
	double damagemod{ static_cast<double>(damagemoddistributor(generator)) };

	double random{ (damagemod / 100.0) };

	double powerModifier{ 1 };

	if (target->IsSemiInvulnerableFromFly() && (currentMove->mp_move->GetSecondaryFlag() == 9)) // For Gust if target is in first turn of fly
	{
		powerModifier = 2;
	}

	int currentMovePower{ currentMove->mp_move->GetPower() };

	if (currentMove->mp_move->GetSecondaryFlag() == 36)
	{
		currentMovePower = CalculateLowKickPower(target);
	}

	damage = floor(floor(floor(floor(floor(floor(floor(floor(floor(2 * source->GetLevel() / 5 + 2) * (currentMovePower * powerModifier) * (static_cast<double>(sourceAttack) / static_cast<double>(targetDefense)) / 50) + 2) * critical) * random) * stab) * effectiveness) * burn));

	if ((currentMove->mp_move->GetSecondaryFlag() == 13 || currentMove->mp_move->GetSecondaryFlag() == 18) && target->HasUsedMinimize())
	{
		damage *= 2;
	}

	if (currentMove->mp_move->GetSecondaryFlag() == 50 && target->IsSemiInvulnerableFromDig())
	{
		damage *= 2;
	}

	if (damage == 0 && effectiveness != 0)
	{
		damage = 1;
	}

	if (targetPlayer->HasReflect() && !isCriticalHit && currentMove->mp_move->GetCategoryEnum() == Category::Physical)
	{
		damage = floor(damage / 2);
	}

	if (targetPlayer->HasLightScreen() && !isCriticalHit && currentMove->mp_move->GetCategoryEnum() == Category::Special)
	{
		damage = floor(damage / 2);
	}

	if (target->HasSubstitute() && !currentMove->mp_move->CanBypassSubstitute())
	{
		target->DamageSubstitute(static_cast<int>(damage));
		damageTaken = damage;
	}

	else
	{
		target->DamageCurrentHP(static_cast<int>(damage));
		damageTaken = damage;
	}

	if (target->IsBiding())
	{
		target->AddBideDamage(static_cast<int>(damage));
	}

	if (damage > target->GetCurrentHP())
	{
		damage = target->GetCurrentHP();
	}

	std::cout << damage << " damage inflicted.\n";
}

// Calculate power of low kick based on target Pokemon's weight (in kg)
int BattleSystem::CalculateLowKickPower(BattlePokemon* target)
{
	double pokemonWeight = target->GetPokemonDatabasePointer()->GetPokemonWeight();

	if (pokemonWeight >= 0.1 && pokemonWeight <= 9.9)
	{
		return 20;
	}

	if (pokemonWeight >= 10 && pokemonWeight <= 24.9)
	{
		return 40;
	}

	if (pokemonWeight >= 25 && pokemonWeight <= 49.9)
	{
		return 60;
	}

	if (pokemonWeight >= 50 && pokemonWeight <= 99.9)
	{
		return 80;
	}

	if (pokemonWeight >= 100 && pokemonWeight <= 199.9)
	{
		return 100;
	}

	if (pokemonWeight >= 200)
	{
		return 120;
	}

	return 0;
}

void BattleSystem::UsedTextDialog(Player* currentPlayer, BattlePokemon::pokemonMove* currentMove, BattlePokemon* source)
{
	std::cout << currentPlayer->GetPlayerNameView() << "'s " << source->GetNameView() << " used " << currentMove->mp_move->GetName() << "\n";
}

void BattleSystem::DisplayCritTextDialog()
{
	if (isCriticalHit && hit)
	{
		std::cout << "Critical hit!\n";
	}

	isCriticalHit = false;
}

void BattleSystem::DisplayEffectivenessTextDialog(Player* targetPlayer, BattlePokemon* targetPokemon) const
{
	if (currentEffectiveness == Effectiveness::Less && hit)
	{
		std::cout << "It was not very effective...\n";
	}

	if (currentEffectiveness == Effectiveness::Super && hit)
	{
		std::cout << "It was super effective!\n";
	}

	if (currentEffectiveness == Effectiveness::No && hit)
	{
		std::cout << "It doesn't affect " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "...\n";
	}

	if (currentEffectiveness == Effectiveness::OHKO && hit)
	{
		std::cout << "It was a one-hit KO!\n";
	}

//	currentEffectiveness = Effectiveness::Normal;
}

void BattleSystem::DisplayAccuracyLoweredTextDialog(Player* player, BattlePokemon* pokemon)
{
	std::cout << player->GetPlayerNameView() << "'s " << pokemon->GetNameView() << "'s accuracy fell!\n";
}

void BattleSystem::DisplayAttackMissedTextDialog(Player* player, BattlePokemon* pokemon)
{
	std::cout << player->GetPlayerNameView() << "'s " << pokemon->GetNameView() << "'s attack missed!\n";
}

void BattleSystem::DisplayAttackAvoidedTextDialog(Player* player, BattlePokemon* pokemon)
{
	std::cout << player->GetPlayerNameView() << "'s " << pokemon->GetNameView() << " avoided the attack!\n";
}

void BattleSystem::DisplayFailedTextDialog()
{
	std::cout << "But it failed!\n";
}

void BattleSystem::DisplaySubstituteDamageTextDialog(Player* player, BattlePokemon* pokemon)
{
	if (!pokemon->HasSubstitute() || damageTaken == 0)
	{
		return;
	}

	if (pokemon->GetSubstituteHP() > 0)
	{
		std::cout << "The substitute took damage for " << player->GetPlayerNameView() << "'s " << pokemon->GetNameView() << '!\n';
	}
	else
	{
		std::cout << player->GetPlayerNameView() << "'s " << pokemon->GetNameView() << " substitute faded!\n";
		pokemon->SetSubstitute(false);
	}
	
}

void BattleSystem::CheckFaintCondition(Player* sourcePlayer, Player* targetPlayer, BattlePokemon* source, BattlePokemon* target)
{
	if ((target->GetCurrentHP() <= 0) && (!target->IsFainted()))
	{
		target->SetFainted(true);
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << target->GetNameView() << " has fainted!\n\n";
		targetPlayer->IncrementFaintedCount();
	}

	if ((source->GetCurrentHP() <= 0) && (!source->IsFainted()))
	{
		source->SetFainted(true);
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << source->GetNameView() << " has fainted!\n\n";
		sourcePlayer->IncrementFaintedCount();
	}
}

bool BattleSystem::CheckWinOrSwitch(Player* sourcePlayer, Player* targetPlayer, BattlePokemon* targetPokemon)
{
	bool winCondition{ false };

	if (!targetPokemon->IsFainted())
	{
		return false;
	}

	else
	{
		winCondition = CheckWinCondition(sourcePlayer, targetPlayer);

		if (!winCondition)
		{
			if (targetPlayer->IsAI())
			{
				AISwitch(targetPlayer, targetPokemon);
			}
			else
			{
				SwitchPokemonOption(targetPlayer, targetPokemon);
			}

			if (targetPokemon == firstTurnPokemon)
			{
				firstTurnPokemon = PerformSwitch(targetPlayer, targetPokemon);
				targetPlayer->SetHasSwitched(true);
				return false;
			}

			if (targetPokemon == secondTurnPokemon)
			{
				secondTurnPokemon = PerformSwitch(targetPlayer, targetPokemon);
				targetPlayer->SetHasSwitched(true);
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}

bool BattleSystem::CheckWinCondition(Player* sourcePlayer, Player* targetPlayer)
{
	//if ((sourcePlayer->GetFaintedCount() == sourcePlayer->GetPokemonCount()) && (targetPlayer->GetFaintedCount() == targetPlayer->GetPokemonCount()))
	//{
	//	sourcePlayer->SetWinCondition(true);
	//	targetPlayer->SetWinCondition(true);
	//	return true;
	//}

	if (targetPlayer->GetFaintedCount() == targetPlayer->GetPokemonCount() || targetPlayer->HasForfeited())
	{
		sourcePlayer->SetWinCondition(true);
		return true;
	}

	if (sourcePlayer->GetFaintedCount() == sourcePlayer->GetPokemonCount() || sourcePlayer->HasForfeited())
	{
		targetPlayer->SetWinCondition(true);
		return true;
	}

	return false;
}

bool BattleSystem::AnnounceWinner()
{
	if (playerOne->HasWon() && playerTwo->HasWon())
	{
		std::cout << "Both players Pokemon have fainted in the same turn!\n";
		std::cout << "It is a tie game!\n\n";
		ResetValues();
		return false;
	}

	if (playerOne->HasWon())
	{
		std::cout << playerOne->GetPlayerNameView() << " wins!\n\n";
		ResetValues();
		return false;
	}

	if (playerTwo->HasWon())
	{
		std::cout << playerTwo->GetPlayerNameView() << " wins!\n\n";
		ResetValues();
		return false;
	}

	return false;
}

void BattleSystem::ResetValues()
{
	playerOne->ResetValues();
	playerTwo->ResetValues();

	for (size_t i = 1; i <= playerOne->GetPokemonCount(); ++i)
	{
		if (playerOne->GetBelt(i) != nullptr)
		{
			playerOne->GetBelt(i)->ResetValues();
		}
		
	}

	for (size_t i = 1; i <= playerTwo->GetPokemonCount(); ++i)
	{
		if (playerTwo->GetBelt(i) != nullptr)
		{
			playerTwo->GetBelt(i)->ResetValues();
		}

	}
}

bool BattleSystem::CheckPerformativeStatus(Player* sourcePlayer, BattlePokemon* sourcePokemon, BattlePokemon::pokemonMove* currentMove)
{
	bool canPerform{ true };

	switch (sourcePokemon->currentStatus)
	{
	case Status::Sleeping:
		canPerform = SleepStatus(sourcePokemon);
		break;

	case Status::Frozen:
		canPerform = FrozenStatus(sourcePokemon);
		break;
	}

	if (sourcePokemon->IsFlinched() && canPerform == true)
	{
		canPerform = FlinchStatus(sourcePlayer, sourcePokemon);
	}

	if (sourcePokemon->IsConfused() && canPerform == true)
	{
		canPerform = ConfusedStatus(sourcePlayer, sourcePokemon);
	}

	if (sourcePokemon->currentStatus == Status::Paralyzed && canPerform == true)
	{
		canPerform = ParalysisStatus(sourcePlayer, sourcePokemon);
	}

	if (currentMove->b_isDisabled && canPerform == true)
	{
		canPerform = false;
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s " << currentMove->mp_move->GetName() << " is disabled!\n";
	}

	if (canPerform == false)
	{
		sourcePokemon->SetCharging(false);
	}

	if (sourcePokemon->IsThrashing() && canPerform == false)
	{
		sourcePokemon->IncrementThrashCounter();

		if (sourcePokemon->GetThrashCounter() == sourcePokemon->GetThrashTurnCount() && !sourcePokemon->IsConfused())
		{
			ThrashConfuse(sourcePlayer, sourcePokemon);
		}

		ThrashStop(sourcePlayer, sourcePokemon);
		ThrashReset(sourcePlayer, sourcePokemon);
	}

	// Bulbapedia mentions only sleep fully disrupts bide, however on Showdown bide is fully disrupted after flinch, and a full paralysis as well
	// If someone could test on a Gen 7 cart how bide interacts with certain status effects that would be greatly appreciated
	if (sourcePokemon->IsBiding() && sourcePokemon->currentStatus == Status::Sleeping && canPerform == false)
	{
		BideStop(sourcePlayer, sourcePokemon);
		BideReset(sourcePlayer, sourcePokemon);
	}

	return canPerform;
}

bool BattleSystem::SleepStatus(BattlePokemon* source)
{
	if (source->GetSleepCounter() >= source->GetSleepTurnCount())
	{
		source->ChangeStatus(Status::Normal);
		source->ResetSleepCounter();
		source->SetSleepTurnCount(0);

		std::cout << source->GetNameView() << " has woken up!\n";
		return true;
	}
	else
	{
		source->IncrementSleepCounter();
		std::cout << source->GetNameView() << " is sleeping\n";
		return false;
	}
}

bool BattleSystem::FrozenStatus(BattlePokemon* source)
{
	std::uniform_int_distribution<int> randomModDistributor(1, 101);
	int randomMod(randomModDistributor(generator));

	if (randomMod <= 80)
	{
		std::cout << source->GetNameView() << " is frozen solid!\n";
		return false;
	}
	else
	{
		source->ChangeStatus(Status::Normal);
		std::cout << source->GetNameView() << " thawed out!\n";
		return true;
	}
}

bool BattleSystem::FlinchStatus(Player* sourcePlayer, BattlePokemon* sourcePokemon)
{
	std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " flinched and couldn't move!\n";
	sourcePokemon->SetIsFlinched(false);

	return false;
}

bool BattleSystem::ConfusedStatus(Player* sourcePlayer, BattlePokemon* sourcePokemon)
{
	if (sourcePokemon->GetConfusedCounter() >= sourcePokemon->GetConfusedTurnCount())
	{
		sourcePokemon->SetConfusedStatus(false);
		sourcePokemon->ResetConfusedCounter();
		sourcePokemon->SetConfusedTurnCount(0);

		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " is no longer confused!\n";
		return true;
	}
	else
	{
		sourcePokemon->IncrementConfusedCounter();
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " is confused!\n";

		std::uniform_int_distribution<int> randomModDistributor(1, 101);
		int randomMod(randomModDistributor(generator));

		if (randomMod > 33)
		{
			return true;
		}
		else
		{
			std::cout << "It hurt itself in its confusion!\n";

			std::uniform_int_distribution<int> damagemoddistributor(85, 100);
			double damagemod{ static_cast<double>(damagemoddistributor(generator)) };
			double random{ (damagemod / 100.0) };

			// Confused damage does not take into account Pokemon's stat boosts, burn status, stab, nor critical, and is a typeless physical move
			double damage = floor(floor(floor(floor(2 * sourcePokemon->GetLevel() / 5 + 2) * 40 * (static_cast<double>(sourcePokemon->GetAttack()) / static_cast<double>(sourcePokemon->GetDefense())) / 50) + 2) * random);

			sourcePokemon->DamageCurrentHP(static_cast<int>(damage));

			if (sourcePokemon->IsBiding())
			{
				sourcePokemon->AddBideDamage(static_cast<int>(damage));
			}

			ResetPokemonTurnStatuses(sourcePlayer, sourcePokemon);

			return false;
		}
	}
}

bool BattleSystem::ParalysisStatus(Player* sourcePlayer, BattlePokemon* sourcePokemon)
{
	std::uniform_int_distribution<int> randomModDistributor(1, 101);
	int randomMod(randomModDistributor(generator));

	if (randomMod <= 25)
	{
		std::cout << sourcePokemon->GetNameView() << " couldn't move because it's paralyzed!\n";
		ResetPokemonTurnStatuses(sourcePlayer, sourcePokemon);
		return false;
	}
	else
	{
		return true;
	}
}

// If paralyze or confusion disrupts their charge (hyper beam, fly, dig, solar beam etc)
void BattleSystem::ResetPokemonTurnStatuses(Player* sourcePlayer, BattlePokemon* sourcePokemon)
{
	if (sourcePlayer->CanSwitch() == true || sourcePokemon->IsCharging() == false || sourcePokemon->IsRecharging() == false || sourcePokemon->IsSemiInvulnerable() == false)
	{
		return;
	}

	sourcePlayer->SetCanSwitch(true);

	sourcePokemon->SetCharging(false);
	sourcePokemon->SetRecharging(false);
	sourcePokemon->SetSemiInvulnerableDig(false);
	sourcePokemon->SetSemiInvulnerableFly(false);
}

void BattleSystem::CheckDamagingStatuses(Player* sourcePlayer, Player* targetPlayer, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon)
{
	if (!sourcePokemon->IsFainted())
	{
		switch (sourcePokemon->currentStatus)
		{
		case Status::Burned:
			BurnedStatus(sourcePlayer, sourcePokemon);
			break;

		case Status::Poisoned:
			PoisonedStatus(sourcePlayer, sourcePokemon);
			break;

		case Status::Badly_Poisoned:
			BadlyPoisonedStatus(sourcePlayer, sourcePokemon);
			break;

		default:
			break;
		}
	}

	CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);

	if (!targetPokemon->IsFainted())
	{
		switch (targetPokemon->currentStatus)
		{
		case Status::Burned:
			BurnedStatus(targetPlayer, targetPokemon);
			break;

		case Status::Poisoned:
			PoisonedStatus(targetPlayer, targetPokemon);
			break;

		case Status::Badly_Poisoned:
			BadlyPoisonedStatus(targetPlayer, targetPokemon);
			break;

		default:
			return;
		}
	}
	CheckFaintCondition(targetPlayer, sourcePlayer, targetPokemon, sourcePokemon);
}

void BattleSystem::BurnedStatus(Player* sourcePlayer, BattlePokemon* sourcePokemon)
{
	double burnDamage = floor(sourcePokemon->GetMaxHP() / 16);

	sourcePokemon->DamageCurrentHP(static_cast<int>(burnDamage));

	std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was damaged by burn.\n";
}

void BattleSystem::PoisonedStatus(Player* sourcePlayer, BattlePokemon* sourcePokemon)
{
	double poisonDamage = floor(sourcePokemon->GetMaxHP() / 8);

	sourcePokemon->DamageCurrentHP(static_cast<int>(poisonDamage));

	std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was damaged by poison.\n";
}

void BattleSystem::BadlyPoisonedStatus(Player* sourcePlayer, BattlePokemon* sourcePokemon)
{
	double poisonDamage = floor(sourcePokemon->GetMaxHP() / 16) * sourcePokemon->GetBadlyPoisonCounter();

	sourcePokemon->DamageCurrentHP(static_cast<int>(poisonDamage));

	std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was damaged by poison.\n";

	sourcePokemon->IncrementBadlyPoisonCounter();

	std::cout << "Poison damage: " << poisonDamage << '\n';
}

void BattleSystem::DeterminePostTurnDamageOrder()
{
	double stageMultiplierOne = CalculateStageModifier(playerOneCurrentPokemon->GetSpeedStage());
	double stageMultiplierTwo = CalculateStageModifier(playerTwoCurrentPokemon->GetSpeedStage());

	double playerOneSpeed = floor(playerOneCurrentPokemon->GetSpeed() * stageMultiplierOne);
	double playerTwoSpeed = floor(playerTwoCurrentPokemon->GetSpeed() * stageMultiplierTwo);

	if (playerOneCurrentPokemon->GetStatus() == Status::Paralyzed)
	{
		playerOneSpeed /= 2;
	}

	if (playerTwoCurrentPokemon->GetStatus() == Status::Paralyzed)
	{
		playerTwoSpeed /= 2;
	}

	if ((playerOneSpeed > playerTwoSpeed) && (firstTurnPlayer != playerOne))
	{
		firstTurnPlayer = playerOne;
		secondTurnPlayer = playerTwo;
		firstTurnPokemon = playerOneCurrentPokemon;
		secondTurnPokemon = playerTwoCurrentPokemon;
	}
	else if ((playerTwoSpeed > playerOneSpeed) && (firstTurnPlayer == playerOne))
	{
		firstTurnPlayer = playerTwo;
		secondTurnPlayer = playerOne;
		firstTurnPokemon = playerTwoCurrentPokemon;
		secondTurnPokemon = playerOneCurrentPokemon;
	}
}

void BattleSystem::CheckSeededStatuses(Player* sourcePlayer, Player* targetPlayer, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon)
{
	if (sourcePokemon->IsSeeded() == false && targetPokemon->IsSeeded() == false)
	{
		return;
	}

	double leechedHealth{ 0 };
	
	if (sourcePokemon->IsSeeded() == true && (!sourcePokemon->IsFainted()))
	{
		leechedHealth = floor(sourcePokemon->GetMaxHP() / 8);

		sourcePokemon->DamageCurrentHP(static_cast<int>(leechedHealth));
		targetPokemon->HealCurrentHP(static_cast<int>(leechedHealth));

		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s health is sapped by Leech Seed.\n";

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);
	}
	
	if (targetPokemon->IsSeeded() == false || (targetPokemon->IsFainted()))
	{
		return;
	}

	leechedHealth = floor(targetPokemon->GetMaxHP() / 8);

	targetPokemon->DamageCurrentHP(static_cast<int>(leechedHealth));
	sourcePokemon->HealCurrentHP(static_cast<int>(leechedHealth));

	std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s health is sapped by Leech Seed.\n";

	CheckFaintCondition(targetPlayer, sourcePlayer, targetPokemon, sourcePokemon);
}

void BattleSystem::CheckBoundStatuses(Player* sourcePlayer, Player* targetPlayer, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon)
{
	if (sourcePokemon->IsBound() == false && targetPokemon->IsBound() == false)
	{
		return;
	}

	double boundDamage{};

	if (sourcePokemon->IsBound() == true && (!sourcePokemon->IsFainted()))
	{
		if (sourcePokemon->GetBoundCounter() >= sourcePokemon->GetBoundTurnCount() && !sourcePokemon->IsFainted())
		{
			sourcePokemon->SetBound(false);
			sourcePlayer->SetCanSwitch(true);
			sourcePokemon->ResetBoundCounter();
			sourcePokemon->SetBoundTurnCount(0);

			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was freed from " << sourcePokemon->GetBoundMoveName() << "!\n";
		}
		else if (sourcePokemon->GetBoundCounter() < sourcePokemon->GetBoundTurnCount() && !sourcePokemon->IsFainted())
		{
			sourcePokemon->IncrementBoundCounter();
			boundDamage = floor(sourcePokemon->GetMaxHP() / 8);

			sourcePokemon->DamageCurrentHP(static_cast<int>(boundDamage));

			std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " was hurt by " << sourcePokemon->GetBoundMoveName() << "!\n";
			std::cout << "Damage from " << sourcePokemon->GetBoundMoveName() << ": " << boundDamage << "\n\n";

			CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);
		}

	}

	if (targetPokemon->IsBound() == false || (targetPokemon->IsFainted()))
	{
		return;
	}

	if (targetPokemon->GetBoundCounter() >= targetPokemon->GetBoundTurnCount() && !targetPokemon->IsFainted())
	{
		targetPokemon->SetBound(false);
		targetPlayer->SetCanSwitch(true);
		targetPokemon->ResetBoundCounter();
		targetPokemon->SetBoundTurnCount(0);

		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " was freed from " << targetPokemon->GetBoundMoveName() << "!\n\n";
	}
	else if (targetPokemon->GetBoundCounter() < targetPokemon->GetBoundTurnCount() && !targetPokemon->IsFainted())
	{
		targetPokemon->IncrementBoundCounter();
		if (targetPokemon->GetBoundCounter() == targetPokemon->GetBoundTurnCount())
		{
			boundDamage = floor(targetPokemon->GetMaxHP() / 8);
		}

		targetPokemon->DamageCurrentHP(static_cast<int>(boundDamage));

		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " was hurt by " << targetPokemon->GetBoundMoveName() << "!\n\n";
		std::cout << "Damage from " << targetPokemon->GetBoundMoveName() << ": " << boundDamage << "\n\n";

		CheckFaintCondition(sourcePlayer, targetPlayer, sourcePokemon, targetPokemon);
	}
}

void BattleSystem::BoundMoveText(Player* sourcePlayer, Player* targetPlayer, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon, BattlePokemon::pokemonMove* currentMove)
{
	if (currentMove->mp_move->GetMoveIndex() == 20)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " was squeezed by " << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "!\n";
	}

	else if (currentMove->mp_move->GetMoveIndex() == 35)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " was wrapped by " << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "!\n";
	}

	else if (currentMove->mp_move->GetMoveIndex() == 83)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " became trapped in the fiery vortex!\n";
	}

	else if (currentMove->mp_move->GetMoveIndex() == 128)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << " clamped down on " << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "!\n";
	}
}

void BattleSystem::ThrashStop(Player* player, BattlePokemon* pokemon)
{
	pokemon->SetThrashing(false);
	player->SetCanSwitch(true);
}

void BattleSystem::ThrashConfuse(Player* player, BattlePokemon* pokemon)
{
	std::cout << player->GetPlayerNameView() << "'s " << pokemon->GetNameView() << " became confused due to fatigue!\n";

	pokemon->SetConfusedStatus(true);

	std::uniform_int_distribution<int> randomModDistributor(2, 4);
	int randomMod(randomModDistributor(generator));
	pokemon->SetConfusedTurnCount(randomMod);
	pokemon->ResetConfusedCounter();
}

void BattleSystem::ThrashReset(Player* player, BattlePokemon* pokemon)
{
	pokemon->ResetThrashCounter();
	pokemon->SetThrashTurnCount(0);
}

void BattleSystem::BideStop(Player* player, BattlePokemon* pokemon)
{
	pokemon->SetBide(false);
	player->SetCanSwitch(true);
}

void BattleSystem::BideReset(Player* player, BattlePokemon* pokemon)
{
	pokemon->ResetBideCounter();
	pokemon->SetBideTurnCount(0);
	pokemon->ResetBideDamage();
}

void BattleSystem::CheckDisabledStatus(Player* sourcePlayer, Player* targetPlayer, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon)
{
	if (!sourcePokemon->MoveIsDisabled() && !targetPokemon->MoveIsDisabled())
	{
		return;
	}

	if (sourcePokemon->MoveIsDisabled())
	{
		sourcePokemon->IncrementDisabledCounter();
	}

	if (sourcePokemon->GetDisabledCounter() == 4)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << "'s " << sourcePokemon->GetDisabledMove()->mp_move->GetName() << " is no longer disabled!\n";
		sourcePokemon->SetDisabledStatus(false);
	}

	if (targetPokemon->MoveIsDisabled())
	{
		targetPokemon->IncrementDisabledCounter();
	}

	if (targetPokemon->GetDisabledCounter() == 4)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s " << targetPokemon->GetDisabledMove()->mp_move->GetName() << " is no longer disabled!\n";
		targetPokemon->SetDisabledStatus(false);
	}
}

void BattleSystem::CheckFieldEffects(Player* sourcePlayer, Player* targetPlayer)
{
	const int reflectTurnCount = 4;
	const int lightscreenTurnCount = 4;
	const int mistTurnCount = 4;

	if (
		   !targetPlayer->HasReflect() && !sourcePlayer->HasReflect()
		&& !sourcePlayer->HasLightScreen() && !targetPlayer->HasLightScreen()
		&& !sourcePlayer->HasMist() && !targetPlayer->HasMist()
		)
	{
		return;
	}

	if (targetPlayer->HasReflect() && targetPlayer->GetReflectCounter() >= reflectTurnCount)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s team's Reflect wore off!\n";
		targetPlayer->SetReflect(false);
		targetPlayer->ResetReflectCounter();
	}

	else if (targetPlayer->HasReflect() && targetPlayer->GetReflectCounter() < reflectTurnCount)
	{
		targetPlayer->IncrementReflectCounter();
	}

	if (sourcePlayer->HasReflect() && sourcePlayer->GetReflectCounter() >= reflectTurnCount)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s team's Reflect wore off!\n";
		sourcePlayer->SetReflect(false);
		sourcePlayer->ResetReflectCounter();
	}

	else if (sourcePlayer->HasReflect() && sourcePlayer->GetReflectCounter() < reflectTurnCount)
	{
		sourcePlayer->IncrementReflectCounter();
	}

	if (sourcePlayer->HasLightScreen() && sourcePlayer->GetLightScreenCounter() >= lightscreenTurnCount)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s team's Light Screen wore off!\n";
		sourcePlayer->SetLightScreen(false);
		sourcePlayer->ResetLightScreenCounter();
	}

	else if (sourcePlayer->HasLightScreen() && sourcePlayer->GetLightScreenCounter() < lightscreenTurnCount)
	{
		sourcePlayer->IncrementLightScreenCounter();
	}

	if (targetPlayer->HasLightScreen() && targetPlayer->GetLightScreenCounter() >= lightscreenTurnCount)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s team's Light Screen wore off!\n";
		targetPlayer->SetLightScreen(false);
		targetPlayer->ResetLightScreenCounter();
	}

	else if (targetPlayer->HasLightScreen() && targetPlayer->GetLightScreenCounter() < lightscreenTurnCount)
	{
		targetPlayer->IncrementLightScreenCounter();
	}

	if (sourcePlayer->HasMist() && sourcePlayer->GetMistCounter() >= mistTurnCount)
	{
		std::cout << sourcePlayer->GetPlayerNameView() << "'s team is no longer protected by mist!\n";
		sourcePlayer->SetMist(false);
		sourcePlayer->ResetMistCounter();
	}

	else if (sourcePlayer->HasMist() && sourcePlayer->GetMistCounter() < mistTurnCount)
	{
		sourcePlayer->IncrementMistCounter();
	}

	if (targetPlayer->HasMist() && targetPlayer->GetMistCounter() >= mistTurnCount)
	{
		std::cout << targetPlayer->GetPlayerNameView() << "'s team is no longer protected by mist!\n";
		targetPlayer->SetMist(false);
		targetPlayer->ResetMistCounter();
	}

	else if (targetPlayer->HasMist() && targetPlayer->GetMistCounter() < mistTurnCount)
	{
		targetPlayer->IncrementMistCounter();
	}
}

void BattleSystem::RageCheck(Player* sourcePlayer, Player* targetPlayer, BattlePokemon::pokemonMove* move, BattlePokemon* sourcePokemon, BattlePokemon* targetPokemon)
{
	if (!sourcePokemon->IsRaging() && !targetPokemon->IsRaging())
	{
		return;
	}

	if (targetPokemon->IsRaging() && (damageTaken > 0 || move->mp_move->GetSecondaryFlag() == 29)) // If target took damage or was targeted by disable while rage is up
	{
		int attackStage = targetPokemon->GetAttackStage();

		if (targetPokemon->GetAttackStage() >= 6)
		{
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << " can't raise its attack any higher!\n";
		}
		else
		{
			++attackStage;
			targetPokemon->SetAttackStage(attackStage);
			std::cout << targetPlayer->GetPlayerNameView() << "'s " << targetPokemon->GetNameView() << "'s attack rose!\n";
		}
	}

	if (sourcePokemon->IsRaging() && move->mp_move->GetSecondaryFlag() != 56)
	{
		sourcePokemon->SetRaging(false);
	}
	else if (sourcePokemon->IsRaging() && move->mp_move->GetSecondaryFlag() == 56 && move->b_isDisabled)
	{
		sourcePokemon->SetRaging(false);
	}
	else if (sourcePokemon->IsRaging() && move->mp_move->GetSecondaryFlag() == 56 && !move->b_isDisabled)
	{
		std::cout << "(" << "Rage started on " << sourcePlayer->GetPlayerNameView() << "'s " << sourcePokemon->GetNameView() << ")" <<  '\n';
	}
}

void BattleSystem::ResetHPandPPForTesting()
{
	playerOneCurrentPokemon->HealCurrentHP(999);
	playerTwoCurrentPokemon->HealCurrentHP(999);

	if (playerOneCurrentMove != nullptr)
	{
		playerOneCurrentMove->m_currentPP = playerOneCurrentMove->m_maxPP;
	}

	if (playerTwoCurrentMove != nullptr)
	{
		playerTwoCurrentMove->m_currentPP = playerTwoCurrentMove->m_maxPP;
	}
}

double BattleSystem::GetDamageTaken()
{
	return damageTaken;
}

void BattleSystem::AISelection(Player* player, BattlePokemon* currentPokemon)
{
	std::deque<BattlePokemon::pokemonMove*> viableMoves{};

	for (size_t i = 1; i <= 4; ++i)
	{
		if (currentPokemon->GetMove(i)->mp_move != nullptr)
		{
			if (!currentPokemon->GetMove(i)->b_isDisabled && currentPokemon->GetMove(i)->m_currentPP != 0)
			{
				viableMoves.push_back(currentPokemon->GetMove(i));
			}
		}
	}

	if (viableMoves.size() == 0)
	{
		selectedMove = currentPokemon->Struggle();
		return;
	}

	size_t numberOfMoves = viableMoves.size();

	std::uniform_int_distribution<int> rngDist(1, static_cast<int>(numberOfMoves));
	int choice{ rngDist(generator) };

	choice--;

	selectedMove = viableMoves.at(choice);
}

void BattleSystem::AISwitch(Player* player, BattlePokemon* currentPokemon)
{
	std::deque<BattlePokemon*> viablePokemon{};

	for (size_t i = 1; i <= 6; ++i)
	{
		if (player->GetBelt(i) != nullptr)
		{
			if (!player->GetBelt(i)->IsFainted() && player->GetBelt(i) != currentPokemon)
			viablePokemon.push_back(player->GetBelt(i));
		}
	}

	player->SetIsSwitching(true);

	player->SetPokemonToSwitchTo(viablePokemon.at(0));
}
