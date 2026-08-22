#pragma once

#include "IPlayerController.h"

#include <array>
#include <memory>
#include <span>

enum class BattleAction;
class BattlePokemon;
class Move;
class Player;
class RandomEngine;
struct BattleContext;
struct PlayerDecisionOutcome;
struct PokemonMoveSlot;

enum class Difficulty { Easy, Medium, Hard };

struct ObservedPokemonMoves
{
	std::array<const PokemonMoveSlot*, 4> moves{};
	int count{};
};

struct PersistentMemory
{
	const BattlePokemon* pokemon{};
	ObservedPokemonMoves observedMoves{};
};

struct AIMemory
{
	const Player* selfPlayer{};
	const Player* opponentPlayer{};
	std::array<PersistentMemory, 6> opponentMemory{};
	int opponentMemoryCount{};

	PersistentMemory* activeOpponentMemory{};
};

class AIController : public IPlayerController
{
public:

	explicit AIController(Difficulty);
	AIController(const AIController& other) = default;
	std::unique_ptr<IPlayerController> clone() const override;

	PlayerDecisionOutcome ChooseAction(Player&, const Player&, BattlePokemon&, const BattlePokemon&, RandomEngine&) override;
	void SkipChooseAction() override;
	BattlePokemon* PromptForSwitch(Player&, const Player&, const BattlePokemon&, const BattlePokemon&) override;
	bool HasDecision() override;
	PlayerDecisionOutcome TakeDecision() override;

	Difficulty GetDifficulty() const;

	void OnBattleStart(const Player&, BattleContext&);
	void OnActivePokemonChanged(const BattleContext&);

	std::span<const PokemonMoveSlot*> GetObservedMoves() const;
	void ResetObservedMoves();

	void OnMoveResolved(const BattleContext&);
	unsigned int AICalculatePokemonTypeEffectiveness(const BattlePokemon& source, const BattlePokemon& target) const;
	unsigned int AICalculateMoveTypeEffectiveness(const PokemonMoveSlot& currentMove, const BattlePokemon& target) const;
	unsigned int AICalculateDamage(const PokemonMoveSlot&, const Player&, const BattlePokemon&, const BattlePokemon&) const;
	unsigned int AICalculateDamage(const PokemonMoveSlot&, const Player&, const BattlePokemon&, const BattlePokemon&, unsigned int) const;
	bool CalculateStatusMoveEffectiveness(const PokemonMoveSlot& currentMove, const Player&, const Player& targetPlayer, const BattlePokemon& source, const BattlePokemon& target) const;

private:
	PokemonMoveSlot* FightAction(const Player&, const Player&, BattlePokemon&, const BattlePokemon&, RandomEngine&);

	BattlePokemon* SwitchAction(Player&, const Player&, const BattlePokemon&, const BattlePokemon&);
	BattlePokemon* SwitchActionPostKO(Player&, const Player&, const BattlePokemon&, const BattlePokemon&);

	BattleAction ForfeitAction(const Player&);

	void UpdateObservedMoves(const PokemonMoveSlot&);
	void UpdateOpponentActivePokemon(const BattlePokemon&);

	PersistentMemory* FindPokemonMemory(const BattlePokemon& pokemon);

public:
	AIMemory memory;

private:
	Difficulty m_difficulty{};
};