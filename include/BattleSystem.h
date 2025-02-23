#pragma once
#include <random>
#include <chrono>
#include <deque>
#include <memory>

#include "Player.h"

class BattleSystem
{
protected:
	std::array<Player*, 2> players{};
	Player* playerOne{ nullptr };
	Player* playerTwo{ nullptr };

	BattlePokemon* playerOneCurrentPokemon{ nullptr };
	BattlePokemon* playerTwoCurrentPokemon{ nullptr };

	BattlePokemon::pokemonMove* playerOneCurrentMove{ nullptr };
	BattlePokemon::pokemonMove* playerTwoCurrentMove{ nullptr };

	BattlePokemon::pokemonMove* selectedMove{ nullptr };

	Player* firstTurnPlayer{ nullptr };
	Player* secondTurnPlayer{ nullptr };

	BattlePokemon* firstTurnPokemon{ nullptr };
	BattlePokemon* secondTurnPokemon{ nullptr };

	BattlePokemon::pokemonMove* firstTurnMove{ nullptr };
	BattlePokemon::pokemonMove* secondTurnMove{ nullptr };

	BattlePokemon::pokemonMove* lastUsedMoveFirst{ nullptr };
	BattlePokemon::pokemonMove* lastUsedMoveSecond{ nullptr };

	static inline double damageTaken{};

	static inline int seed;
	static inline std::mt19937 generator;

	static inline std::array<double, 13> m_arr_StageMultiplier{ 2.0 / 8.0, 2.0 / 7.0, 2.0 / 6.0, 2.0 / 5.0, 2.0 / 4.0, 2.0 / 3.0, 2.0 / 2.0, 3.0 / 2.0, 4.0 / 2.0, 5.0 / 2.0, 6.0 / 2.0, 7.0 / 2.0, 8.0 / 2.0 }; // For attack, defense, special attack, special defense, and speed (not accuracy, evasion, or crit)
	static inline std::array<double, 13> m_arr_AccuracyStageMultiplier{ 3.0 / 9.0, 3.0 / 8.0, 3.0 / 7.0, 3.0 / 6.0, 3.0 / 5.0, 3.0 / 4.0, 3.0 / 3.0, 4.0 / 3.0, 5.0 / 3.0, 6.0 / 3.0, 7.0 / 3.0, 8.0 / 3.0, 9.0 / 3.0 }; // For accuracy and evasion
	static inline std::array<int, 4> m_arr_CriticalHitStageMultiplier{ 417, 1250, 5000, 10000 }; // For critical hit

	bool hit{ false };
	bool isCriticalHit{ false };

	enum class Effectiveness { Normal, Less, Super, No, OHKO };

	Effectiveness currentEffectiveness{ Effectiveness::Normal };

	static inline std::array<std::array<double, 18>, 18> typeEffectivenessArray
	{{
		{ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0 } },
		{ { 1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0 } },
		{ { 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0, 1.0 } },
		{ { 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0 } },
		{ { 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 1.0 } },
		{ { 1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0 } },
		{ { 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5 } },
		{ { 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0, 2.0 } },
		{ { 1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0 } },
		{ { 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0 } },
		{ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0 } },
		{ { 1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5, 0.5 } },
		{ { 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0 } },
		{ { 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0 } },
		{ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0 } },
		{ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5 } },
		{ { 1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0 } },
		{ { 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.5, 1.0 } }
	}};

public:
	BattleSystem();
	BattleSystem(std::vector<Player>&);

	const Player* GetPlayerOne() const;
	const Player* GetPlayerTwo() const;
	void SetPlayerOne(Player*);
	void SetPlayerTwo(Player*);

	const BattlePokemon* GetPlayerOneCurrentPokemon() const;
	const BattlePokemon* GetPlayerTwoCurrentPokemon() const;
	void SetPlayerOneCurrentPokemon(BattlePokemon*);
	void SetPlayerTwoCurrentPokemon(BattlePokemon*);

	void SetPlayerOneCurrentMove(BattlePokemon::pokemonMove*);
	void SetPlayerTwoCurrentMove(BattlePokemon::pokemonMove*);

	const Player* GetFirstTurnPlayer() const;
	const Player* GetSecondTurnPlayer() const;

	bool CheckPlayerPokemonAvailability();

	void ThrowOutFirstPokemon();

	void DisplayFightingPokemon();

	bool StartBattle();

	bool BattleLoop();

	bool CheckPPCountForStruggle(BattlePokemon*);

	void PlayerOneMakeSelection();
	void PlayerTwoMakeSelection();

	void MakeASelectionLoop(Player*, BattlePokemon*);

	bool Fight(Player*, BattlePokemon*);

	bool SwitchPokemonOption(Player*, BattlePokemon*);

	void Forfeit(Player*);

	BattlePokemon* PerformSwitch(Player*, BattlePokemon*);
	void ResetStatsOnSwitch(BattlePokemon*);

	void DetermineWhoGoesFirst();

	int CalculateCriticalHitStageModifier(size_t);

	double CalculateCriticalHit(BattlePokemon*);

	double CalculateStageModifier(size_t);

	double CalculateTypeEffectiveness(BattlePokemon::pokemonMove*, BattlePokemon*);

	double CalculateAccuracyModifiers(int);

	bool CalculateHitChance(BattlePokemon::pokemonMove* currentMove, BattlePokemon* source, BattlePokemon* target);

	void CalculateDamage(Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*);

	int CalculateLowKickPower(BattlePokemon*);

	void UsedTextDialog(Player*, BattlePokemon::pokemonMove*, BattlePokemon*);
	void DisplayCritTextDialog();
	void DisplayEffectivenessTextDialog(Player*, BattlePokemon*) const;
	void DisplayAccuracyLoweredTextDialog(Player*, BattlePokemon*);
	void DisplayAttackMissedTextDialog(Player*, BattlePokemon*);
	void DisplayAttackAvoidedTextDialog(Player*, BattlePokemon*);
	void DisplayFailedTextDialog();
	void DisplaySubstituteDamageTextDialog(Player*, BattlePokemon*);

	void CheckFaintCondition(Player*, Player*, BattlePokemon*, BattlePokemon*);

	bool CheckWinOrSwitch(Player*, Player*, BattlePokemon*);

	bool CheckWinCondition(Player*, Player*);

	bool AnnounceWinner();

	void ResetValues();

	bool CheckPerformativeStatus(Player*, BattlePokemon*, BattlePokemon::pokemonMove*);
	bool SleepStatus(BattlePokemon*);
	bool FrozenStatus(BattlePokemon*);
	bool FlinchStatus(Player*, BattlePokemon*);
	bool ConfusedStatus(Player*, BattlePokemon*);
	bool ParalysisStatus(Player*, BattlePokemon*);

	void ResetPokemonTurnStatuses(Player*, BattlePokemon*);

	void CheckDamagingStatuses(Player*, Player*, BattlePokemon*, BattlePokemon*);
	void BurnedStatus(Player*, BattlePokemon*);
	void PoisonedStatus(Player*, BattlePokemon*);
	void BadlyPoisonedStatus(Player*, BattlePokemon*);

	void DeterminePostTurnDamageOrder();

	void CheckSeededStatuses(Player*, Player*, BattlePokemon*, BattlePokemon*);
	void CheckBoundStatuses(Player*, Player*, BattlePokemon*, BattlePokemon*);
	void CheckFieldEffects(Player*, Player*);

	void BoundMoveText(Player*, Player*, BattlePokemon*, BattlePokemon*, BattlePokemon::pokemonMove*);

	void ThrashStop(Player*, BattlePokemon*);
	void ThrashConfuse(Player*, BattlePokemon*);
	void ThrashReset(Player*, BattlePokemon*);

	void BideStop(Player*, BattlePokemon*);
	void BideReset(Player*, BattlePokemon*);

	void CheckDisabledStatus(Player*, Player*, BattlePokemon*, BattlePokemon*);

	void RageCheck(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*);

	void ResetHPandPPForTesting();

	void AISelection(Player*, BattlePokemon*);
	void AISwitch(Player*, BattlePokemon*);
};
