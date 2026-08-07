#include <algorithm>
#include <utility>
#include <memory>
#include <span>

#include "AIController.h"

#include "IPlayerController.h"

#include "../../common/EnumUtils.h"

#include "move scoring/AIMoveScoring.h"
#include "switch logic/AISwitchLogic.h"
#include "../PlayerDecisionOutcome.h"
#include "../pokemonMove.h"
#include "../BattlePokemon.h"
#include "../Player.h"
#include "../../battle/BattleAction.h"
#include "../../battle/BattleContext.h"
#include "../../battle/Typechart.h"
#include "../../battle/StageRatios.h"
#include "../../moves/MoveEffectEnums.h"
#include "../../data/StringToTypes.h"
#include "../../data/Pokemon.h"

constexpr unsigned int FixedPointBase = 4096;

constexpr unsigned int HalfMultiplier = FixedPointBase / 2;
constexpr unsigned int NormalMultiplier = FixedPointBase;
constexpr unsigned int OneAndHalfMultiplier = FixedPointBase + FixedPointBase / 2;
constexpr unsigned int DoubleMultiplier = FixedPointBase * 2;

AIController::AIController(Difficulty difficulty)
	: m_difficulty(difficulty)
 {}

std::unique_ptr<IPlayerController> AIController::clone() const
{
	return std::make_unique<AIController>(*this);
}

PlayerDecisionOutcome AIController::ChooseAction(Player& player, const Player& targetPlayer, BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng)
{
	if (player.GetAIController().GetDifficulty() >= Difficulty::Medium)
	{
		if (AISwitchLogic::WantsToSwitch(player, targetPlayer, selfMon, targetMon, rng))
		{
			m_decisionOutcome.action = BattleAction::SwitchPokemon;
			m_decisionOutcome.chosenPokemon = SwitchAction(player, targetPlayer, selfMon, targetMon);

			if (m_decisionOutcome.chosenPokemon != nullptr)
			{
				return m_decisionOutcome;
			}
		}
	}

	m_decisionOutcome.chosenMove = FightAction(player, targetPlayer, selfMon, targetMon, rng);

	/*
	if (m_decisionOutcome.chosenMove == &GetStruggle())
	{
		m_decisionOutcome.action = BattleAction::Struggle;
	}
	else
	{
		m_decisionOutcome.action = BattleAction::Fight;
	}
	*/

	m_decisionOutcome.action = BattleAction::Fight;

	return m_decisionOutcome;
}

void AIController::SkipChooseAction()
{
	m_decisionOutcome.action = BattleAction::Skip;
	b_hasDecision = true;
}

BattlePokemon* AIController::PromptForSwitch(Player& player, const Player& targetPlayer, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
{
	m_decisionOutcome.chosenPokemon = SwitchActionPostKO(player, targetPlayer, selfMon, targetMon);
	return m_decisionOutcome.chosenPokemon;
}

bool AIController::HasDecision()
{
	return b_hasDecision;
}

PlayerDecisionOutcome AIController::TakeDecision()
{
	b_hasDecision = false;
	return std::exchange(m_decisionOutcome, {});
}

Difficulty AIController::GetDifficulty() const
{
	return m_difficulty;
}

pokemonMove* AIController::FightAction(const Player& player, const Player& targetPlayer, BattlePokemon& selfMon, const BattlePokemon& targetMon, RandomEngine& rng)
{
	if (selfMon.WillPerformStruggle())
	{
		b_hasDecision = true;
		return &GetStruggle();
	}

	pokemonMove* selectedMove = AIMoveScoring::GetWinningMove(player, targetPlayer, selfMon, targetMon, rng);
	b_hasDecision = true;
    return selectedMove;
}

BattlePokemon* AIController::SwitchAction(Player& player, const Player& targetPlayer, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
{
	BattlePokemon* selectedPokemon = AISwitchLogic::ChooseSwitch(player, targetPlayer, selfMon, targetMon);
	b_hasDecision = true;
	return selectedPokemon;
}

BattlePokemon* AIController::SwitchActionPostKO(Player& player, const Player& targetPlayer, const BattlePokemon& selfMon, const BattlePokemon& targetMon)
{
	BattlePokemon* selectedPokemon = AISwitchLogic::ChoosePostKOSwitch(player, targetPlayer, selfMon, targetMon);
	b_hasDecision = true;
	return selectedPokemon;
}

BattleAction AIController::ForfeitAction(const Player&)
{
	b_hasDecision = true;
	return BattleAction::Forfeit;
}

void AIController::OnBattleStart(const Player& self, BattleContext& context)
{
	if (&self == context.playerOne)
	{
		memory.selfPlayer = context.playerOne;
		memory.opponentPlayer = context.playerTwo;
	}
	else if (&self == context.playerTwo)
	{
		memory.selfPlayer = context.playerTwo;
		memory.opponentPlayer = context.playerOne;
	}

	GetOpponentParty(*memory.opponentPlayer);
}

void AIController::OnActivePokemonChanged(const BattleContext& context)
{
	if (memory.selfPlayer == context.playerOne)
	{
		UpdateOpponentActivePokemon(*context.playerTwoCurrentPokemon);
	}
	else if (memory.selfPlayer == context.playerTwo)
	{
		UpdateOpponentActivePokemon(*context.playerOneCurrentPokemon);
	}
}

void AIController::GetOpponentParty(const Player& opponent)
{
    for (size_t i = 0; i < memory.opponentMemory.size(); ++i)
    {
		memory.opponentMemory[i].pokemon = &(opponent.GetBelt(i + 1));
    }
}

std::span<const pokemonMove*> AIController::GetObservedMoves() const
{
	auto activePokemon = memory.slotOfActivePokemon;

	if (activePokemon == nullptr || activePokemon->pokemon->IsFainted())
	{
		return std::span<const pokemonMove*>{};
	}

	return activePokemon->observedMoves.moves;
}

void AIController::UpdateObservedMoves(const pokemonMove& currentMove)
{
	auto* activePokemon = memory.slotOfActivePokemon;

	if (activePokemon == nullptr || activePokemon->pokemon->IsFainted())
	{
		return;
	}

	memory.activeOpponent.opponentLastUsedMove = &currentMove;

	auto& observed = activePokemon->observedMoves;

	for (size_t moveSlot = 0; moveSlot < observed.moves.size(); ++moveSlot)
	{
		if (observed.moves[moveSlot] != nullptr && observed.moves[moveSlot]->GetMoveID() == currentMove.GetMoveID())
		{
			return;
		}

		if (observed.moves[moveSlot] == nullptr)
		{
			observed.moves[moveSlot] = &currentMove;
			observed.revealed[moveSlot] = true;
			return;
		}
	}
}

void AIController::ResetObservedMoves()
{
	for (auto& pokemon : memory.opponentMemory)
	{
		for (auto& move : pokemon.observedMoves.moves)
		{
			move = nullptr;
		}
		for (auto& move : pokemon.observedMoves.revealed)
		{
			move = false;
		}
	}
}

void AIController::UpdateOpponentActivePokemon(const BattlePokemon& activeOpponentMon)
{
	if (!(&activeOpponentMon == memory.activeOpponent.opponentActivePokemon))
	{
		memory.activeOpponent.opponentActivePokemon = &activeOpponentMon;
		memory.slotOfActivePokemon = FindActivePokemonSlot();
	}
}

void AIController::OnMoveResolved(const BattleContext& context)
{
	if (!memory.selfPlayer || !memory.opponentPlayer)
	{
		return;
	}

	// if switch happened
	if (context.currentMove == nullptr)
	{
		return;
	}

	bool amIDefender = (memory.selfPlayer == context.defendingPlayer);

	const pokemonMove& moveUsed = *context.currentMove;

	if (amIDefender)
	{
		UpdateObservedMoves(moveUsed);
	}
}

unsigned int AIController::AICalculatePokemonTypeEffectiveness(const BattlePokemon& source, const BattlePokemon& target) const
{
	unsigned int atk1 = EnumIndex(source.GetTypeOneEnum());
	unsigned int atk2 = EnumIndex(source.GetTypeTwoEnum());
	unsigned int def1 = EnumIndex(target.GetTypeOneEnum());
	unsigned int def2 = EnumIndex(target.GetTypeTwoEnum());

	bool atk2Exists = (atk2 != 18);

	unsigned int score1 = typeChart[atk1][def1];
	if (def2 != 18)
		score1 = (score1 * typeChart[atk1][def2]) / FixedPointBase;

	unsigned int score2 = 0;
	if (atk2Exists)
	{
		score2 = typeChart[atk2][def1];
		if (def2 != 18)
			score2 = (score2 * typeChart[atk2][def2]) / FixedPointBase;
	}

	return std::max(score1, score2);
}

unsigned int AIController::AICalculateMoveTypeEffectiveness(const pokemonMove& currentMove, const BattlePokemon& target) const
{
	if (currentMove.GetCategoryEnum() == Category::Status)
	{
		return 0;
	}

	unsigned int moveType = EnumIndex(currentMove.GetMoveTypeEnum());
	unsigned int defensiveTypeOne = EnumIndex(target.GetTypeOneEnum());
	unsigned int defensiveTypeTwo = EnumIndex(target.GetTypeTwoEnum());

	unsigned int effect1 = typeChart[moveType][defensiveTypeOne];
	unsigned int effect2 = (defensiveTypeTwo == 18) ? NormalMultiplier : typeChart[moveType][defensiveTypeTwo];

	if (effect1 == 0 || effect2 == 0)
	{
		return 0;
	}

	unsigned int product = effect1 * effect2;
	return (product / FixedPointBase);
}

unsigned int AIController::AICalculateDamage(const pokemonMove& currentMove, const Player& targetPlayer, const BattlePokemon& source, const BattlePokemon& target) const
{
	unsigned int baseDamage{ 0 };

	unsigned int effectiveness = AICalculateMoveTypeEffectiveness(currentMove, target);

	if (effectiveness <= 0)
	{
		return 0;
	}

	if ((currentMove.GetMoveEffectEnum() == MoveEffect::OHKO) && effectiveness != 0)
	{
		baseDamage = target.GetCurrentHP();
		return baseDamage;
	}

	// START: Calculate total attack and defense values of attacker and defender
	bool isPhysical{ currentMove.GetCategoryEnum() == Category::Physical };

	unsigned int baseSourceAttack{ isPhysical ? source.GetAttack() : source.GetSpecialAttack() };
	unsigned int baseTargetDefense{ isPhysical ? target.GetDefense() : target.GetSpecialDefense() };

	int sourceStage{ isPhysical ? source.GetAttackStage() : source.GetSpecialAttackStage() };
	int targetStage{ isPhysical ? target.GetDefenseStage() : target.GetSpecialDefenseStage() };

	auto [atkNumerator, atkDenominator] = GetStageRatio(sourceStage);
	unsigned int sourceAttack{ baseSourceAttack * atkNumerator / atkDenominator };

	auto [defNumerator, defDenominator] = GetStageRatio(targetStage);
	unsigned int targetDefense{ baseTargetDefense * defNumerator / defDenominator };
	// END:

	unsigned int currentMovePower{ currentMove.GetPower() };

	auto CalculateLowKickPower = [](const BattlePokemon& target) -> unsigned int
		{
			unsigned int pokemonWeight = target.GetPokemonDatabasePointer()->GetPokemonWeightHg();

			if (pokemonWeight <= 0)
			{
				return 0;
			}

			if (pokemonWeight < 100)
			{
				return 20;
			}

			if (pokemonWeight < 250)
			{
				return 40;
			}

			if (pokemonWeight < 500)
			{
				return 60;
			}

			if (pokemonWeight < 1000)
			{
				return 80;
			}

			if (pokemonWeight < 2000)
			{
				return 100;
			}

			return 120;
		};

	if (currentMove.GetMoveEffectEnum() == MoveEffect::LowKick)
	{
		currentMovePower = CalculateLowKickPower(target);
	}

	unsigned int level = source.GetLevel();

	// Damage formula: (((((2 * level / 5) + 2) * currentMovePower * sourceAttack) / targetDefense) / 50) + 2
	// Truncates int after every division
	unsigned int step1 = (2 * level / 5) + 2;
	unsigned int step2 = step1 * currentMovePower;
	unsigned int step3 = step2 * sourceAttack;
	unsigned int step4 = step3 / targetDefense;
	baseDamage = step4 / 50 + 2;

	unsigned int interimDamage = baseDamage;

	bool hasStab = (currentMove.GetMoveTypeEnum() == source.GetTypeOneEnum() ||
		currentMove.GetMoveTypeEnum() == source.GetTypeTwoEnum())
		&& currentMove.GetMoveEffectEnum() != MoveEffect::Struggle;

	if (hasStab)
	{
		interimDamage = interimDamage * OneAndHalfMultiplier / FixedPointBase;
	}

	interimDamage = interimDamage * effectiveness / FixedPointBase;

	if (source.GetStatus() == Status::Burned && isPhysical)
	{
		interimDamage = interimDamage * HalfMultiplier / FixedPointBase;
	}

	unsigned int other{ FixedPointBase };

	if ((currentMove.GetMoveEffectEnum() == MoveEffect::Stomp || currentMove.GetMoveEffectEnum() == MoveEffect::BodySlam) && target.HasUsedMinimize())
	{
		other = (other * DoubleMultiplier + HalfMultiplier) / FixedPointBase;
	}

	if (currentMove.GetMoveEffectEnum() == MoveEffect::Earthquake && target.IsSemiInvulnerableFromDig())
	{
		other = (other * DoubleMultiplier + HalfMultiplier) / FixedPointBase;
	}

	if (targetPlayer.HasReflect() && isPhysical)
	{
		other = (other * HalfMultiplier + HalfMultiplier) / FixedPointBase;
	}

	if (targetPlayer.HasLightScreen() && !isPhysical)
	{
		other = (other * HalfMultiplier + HalfMultiplier) / FixedPointBase;
	}

	unsigned int finalDamage = interimDamage * other / FixedPointBase;

	if (effectiveness != 0)
	{
		finalDamage = std::max(1u, finalDamage);
	}

	return finalDamage;
}

bool AIController::CalculateStatusMoveEffectiveness(const pokemonMove& currentMove, const Player& targetPlayer, const BattlePokemon& source, const BattlePokemon& target) const
{
	if (target.GetStatus() != Status::Normal)
	{
		return false;
	}

	bool hasMist = targetPlayer.HasMist();

	bool isGrassImmune = (currentMove.GetMoveEffectEnum() == MoveEffect::PoisonPowder
		|| currentMove.GetMoveEffectEnum() == MoveEffect::StunSpore
		|| currentMove.GetMoveEffectEnum() == MoveEffect::SleepPowder
		|| currentMove.GetMoveEffectEnum() == MoveEffect::LeechSeed)
		&& (target.GetTypeOneEnum() == PokemonType::Grass || target.GetTypeTwoEnum() == PokemonType::Grass);

	bool isElectricImmune = (currentMove.GetMoveEffectEnum() == MoveEffect::Paralyze || currentMove.GetMoveEffectEnum() == MoveEffect::StunSpore)
		&& (target.GetTypeOneEnum() == PokemonType::Electric || target.GetTypeTwoEnum() == PokemonType::Electric);

	bool isThunderWaveImmune = (currentMove.GetMoveTypeEnum() == PokemonType::Electric
		&& (target.GetTypeOneEnum() == PokemonType::Ground || target.GetTypeTwoEnum() == PokemonType::Ground));

	bool isPoisonImmune = (currentMove.GetMoveTypeEnum() == PokemonType::Poison)
		&& ((target.GetTypeOneEnum() == PokemonType::Poison || target.GetTypeTwoEnum() == PokemonType::Poison)
			|| (target.GetTypeOneEnum() == PokemonType::Steel || target.GetTypeTwoEnum() == PokemonType::Steel));

	if (hasMist || isGrassImmune || isElectricImmune || isThunderWaveImmune || isPoisonImmune)
	{
		return false;
	}
	else
	{
		return true;
	}
}

PersistentMemory* AIController::FindActivePokemonSlot()
{
	auto it = std::find_if(
		memory.opponentMemory.begin(),
		memory.opponentMemory.end(),
		[this](const PersistentMemory& mem)
		{
			return memory.activeOpponent.opponentActivePokemon == mem.pokemon;
		});

	return (it == memory.opponentMemory.end()) ? nullptr : std::to_address(it);
}