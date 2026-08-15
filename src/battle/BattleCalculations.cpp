#include <array>
#include <algorithm>
#include <utility>

#include "BattleCalculations.h"

#include "RandomEngine.h"
#include "BattleContext.h"
#include "Typechart.h"
#include "StageRatios.h"

#include "../common/EnumUtils.h"

#include "../data/Pokemon.h"
#include "../data/StringToTypes.h"
#include "../moves/MoveEffectEnums.h"
#include "../entities/pokemonMove.h"
#include "../entities/Player.h"
#include "../entities/BattlePokemon.h"

constexpr unsigned int FixedPointBase = 4096;

constexpr unsigned int HalfMultiplier = FixedPointBase / 2;
constexpr unsigned int NormalMultiplier = FixedPointBase;
constexpr unsigned int OneAndHalfMultiplier = FixedPointBase + FixedPointBase / 2;
constexpr unsigned int DoubleMultiplier = FixedPointBase * 2;

constexpr int MinStage{ 0 };
constexpr int MaxStage{ 12 };
constexpr int DefaultStage{ 6 };
constexpr int MaxCritStage{ 3 };

BattleCalculations::BattleCalculations(BattleContext& context, RandomEngine& rng) : m_context(context), m_rng(rng) {}

unsigned int BattleCalculations::CalculatePokemonSpeed(const BattlePokemon& pokemon)
{
	auto [numerator, denominator] = GetStageRatio(pokemon.GetSpeedStage());

	unsigned int speed = pokemon.GetSpeed() * numerator / denominator;

	if (pokemon.GetStatus() == Status::Paralyzed)
	{
		speed /= 2;
	}

	return speed;
}

void BattleCalculations::RandomizeTurnOrder()
{
	std::array<Player*, 2> activePlayers{ m_context.playerOne, m_context.playerTwo };
	std::shuffle(activePlayers.begin(), activePlayers.end(), m_rng.GetGenerator());

	SetFirst(*activePlayers[0], *activePlayers[1]);
}

void BattleCalculations::RandomizePostTurnOrder()
{
	std::array<BattlePokemon*, 2> activePokemon{ m_context.attackingPokemon, m_context.defendingPokemon };
	std::shuffle(activePokemon.begin(), activePokemon.end(), m_rng.GetGenerator());

	if (activePokemon[0] != m_context.attackingPokemon) {
		std::swap(m_context.attackingPlayer, m_context.defendingPlayer);
		std::swap(m_context.attackingPokemon, m_context.defendingPokemon);
	}
}

void BattleCalculations::SetFirst(Player& first, Player& second)
{
	first.SetFirst(true);
	second.SetFirst(false);
	m_context.attackingPlayer = &first;
	m_context.defendingPlayer = &second;
	m_context.attackingPokemon = (&first == m_context.playerOne) ? m_context.playerOneCurrentPokemon : m_context.playerTwoCurrentPokemon;
	m_context.defendingPokemon = (&second == m_context.playerOne) ? m_context.playerOneCurrentPokemon : m_context.playerTwoCurrentPokemon;
	m_context.currentMove = (&first == m_context.playerOne) ? m_context.playerOneCurrentMove : m_context.playerTwoCurrentMove;
}

bool BattleCalculations::CalculateCriticalHit(BattleContext& ctx, const BattlePokemon& source)
{
	int stage = source.GetCriticalHitStage();

	if (stage >= 3)
	{
		ctx.flags.isCriticalHit = true;
	}
	else
	{
		int threshold = m_arr_CriticalHitStageThresholds[stage];
		int roll{ m_rng.GetCritRoll() };
		ctx.flags.isCriticalHit = (roll < threshold);
	}

	return ctx.flags.isCriticalHit;
}

unsigned int BattleCalculations::MultiplyEffectiveness(unsigned int effect1, unsigned int effect2)
{
	if (effect1 == 0 || effect2 == 0)
	{
		return 0;
	}

	unsigned int product = effect1 * effect2;
	return (product / FixedPointBase);
}

void BattleCalculations::CalculateTypeEffectiveness(BattleContext& ctx, const pokemonMove& currentMove, const BattlePokemon& target)
{
	using Effectiveness = BattleStateFlags::Effectiveness;

	ctx.effectiveness = FixedPointBase;
	ctx.flags.currentEffectiveness = Effectiveness::Normal;

	if (currentMove.GetMoveEffectEnum() == MoveEffect::Struggle)
	{
		return;
	}

	unsigned int moveType = EnumIndex(currentMove.GetMoveTypeEnum());
	unsigned int defensiveTypeOne = EnumIndex(target.GetTypeOneEnum());
	unsigned int defensiveTypeTwo = EnumIndex(target.GetTypeTwoEnum());

	unsigned int effect1 = typeChart[moveType][defensiveTypeOne];
	unsigned int effect2 = (defensiveTypeTwo == 18) ? NormalMultiplier : typeChart[moveType][defensiveTypeTwo];

	ctx.effectiveness = MultiplyEffectiveness(effect1, effect2);

	int moveEffectiveness = ctx.effectiveness;
	
	if (moveEffectiveness == 0)
	{
		ctx.flags.currentEffectiveness = Effectiveness::No;
	}
	else if (moveEffectiveness < FixedPointBase)
	{
		ctx.flags.currentEffectiveness = Effectiveness::Less;
	}
	else if (moveEffectiveness == FixedPointBase)
	{
		ctx.flags.currentEffectiveness = Effectiveness::Normal;
	}
	else
	{
		ctx.flags.currentEffectiveness = Effectiveness::Super;
	}
}

bool BattleCalculations::CalculateHitChance(const pokemonMove& currentMove, const BattlePokemon& source, const BattlePokemon& target)
{
	int sourceAccuracy = source.GetAccuracyStage();
	int targetEvasion = target.GetEvasionStage();

	int netStage{ sourceAccuracy - targetEvasion };
	int targetIndex = netStage + DefaultStage;
	int adjustedStages = std::clamp(targetIndex, MinStage, MaxStage);

	const auto& [numerator, denominator] = GetAccuracyStageRatio(adjustedStages);

	int moveAccuracy = currentMove.GetAccuracy();

	int accuracyMod{};

	if (currentMove.GetMoveEffectEnum() == MoveEffect::OHKO)
	{
		if (source.GetLevel() < target.GetLevel())
		{
			return false;
		}

		accuracyMod = 30 + source.GetLevel() - target.GetLevel();
	}
	else
	{
		accuracyMod = (moveAccuracy * numerator) / denominator;
	}

	if (accuracyMod >= 100)
	{
		return true;
	}

	int rollOutcome{ m_rng.GetAccuracyRoll() };

	return rollOutcome < accuracyMod;
}

unsigned int BattleCalculations::CalculateDamage(BattleContext& ctx, const Player& targetPlayer, const pokemonMove& currentMove, const BattlePokemon& source, BattlePokemon& target)
{
	bool isCritical{ CalculateCriticalHit(ctx, source) };

	// START: Calculate total attack and defense values of attacker and defender
	bool isPhysical{ currentMove.GetCategoryEnum() == Category::Physical };

	unsigned int baseSourceAttack{ isPhysical ? source.GetAttack() : source.GetSpecialAttack() };
	unsigned int baseTargetDefense{ isPhysical ? target.GetDefense() : target.GetSpecialDefense() };

	int sourceStage{ isPhysical ? source.GetAttackStage() : source.GetSpecialAttackStage() };
	int targetStage{ isPhysical ? target.GetDefenseStage() : target.GetSpecialDefenseStage() };

	if (isCritical)
	{
		// If attacker's attack stage is less than 6, clamp to 6
		sourceStage = std::max(sourceStage, DefaultStage);
		
		// If defender's defense stage is greater than 6, clamp to 6
		targetStage = std::min(targetStage, DefaultStage);
	}

	auto [atkNumerator, atkDenominator] = GetStageRatio(sourceStage);
	unsigned int sourceAttack{ baseSourceAttack * atkNumerator / atkDenominator };
	
	auto [defNumerator, defDenominator] = GetStageRatio(targetStage);
	unsigned int targetDefense{ baseTargetDefense * defNumerator / defDenominator };
	// END:

	unsigned int currentMovePower{ currentMove.GetPower() };

	if (currentMove.GetMoveEffectEnum() == MoveEffect::LowKick)
	{
		currentMovePower = CalculateLowKickPower(target);
	}

	unsigned int powerModifier{ ctx.initialPowerMultiplier };

	if (powerModifier > 10)
	{
		currentMovePower = currentMovePower * powerModifier / 10;
	}

	unsigned int level{ source.GetLevel() };

	unsigned int baseDamage{ 0 };

	// Damage formula: (((((2 * level / 5) + 2) * currentMovePower * sourceAttack) / targetDefense) / 50) + 2
	// Truncates int after every division
	unsigned int step1 = (2 * level / 5) + 2;
	unsigned int step2 = step1 * currentMovePower;
	unsigned int step3 = step2 * sourceAttack;
	unsigned int step4 = step3 / targetDefense;
	baseDamage = step4 / 50 + 2;
	
	unsigned int interimDamage = baseDamage;

	if (isCritical)
	{
		interimDamage = interimDamage * OneAndHalfMultiplier / FixedPointBase;
	}

	unsigned int randDmgMultiplier{ m_rng.GetDamageRoll() };

	interimDamage = interimDamage * randDmgMultiplier / 100;

	bool hasStab = (currentMove.GetMoveTypeEnum() == source.GetTypeOneEnum() ||
		currentMove.GetMoveTypeEnum() == source.GetTypeTwoEnum())
		&& currentMove.GetMoveEffectEnum() != MoveEffect::Struggle;

	if (hasStab)
	{
		interimDamage = interimDamage * OneAndHalfMultiplier / FixedPointBase;
	}

	unsigned int effectiveness{ ctx.effectiveness };

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

	if (targetPlayer.HasReflect() && !isCritical && isPhysical)
	{
		other = (other * HalfMultiplier + HalfMultiplier) / FixedPointBase;
	}

	if (targetPlayer.HasLightScreen() && !isCritical && !isPhysical)
	{
		other = (other * HalfMultiplier + HalfMultiplier) / FixedPointBase;
	}

	unsigned int finalDamage = interimDamage * other / FixedPointBase;

	if (effectiveness != 0)
	{
		finalDamage = std::max(1u, finalDamage);
	}

	/*
	if (finalDamage > target.GetCurrentHP())
	{
		finalDamage = target.GetCurrentHP();
	}
	*/
	
	return finalDamage;
}

void BattleCalculations::ApplyDamage(const pokemonMove& currentMove, BattlePokemon& target, unsigned int damage)
{
	const unsigned int HP_BAR_WIDTH = m_context.HP_BAR_WIDTH;

	bool hitSubstitute = target.HasSubstitute() && !currentMove.CanBypassSubstitute();
	m_context.flags.hitSubstitute = hitSubstitute;
	damage = (hitSubstitute ? std::min(damage, target.GetSubstituteHP()) : std::min(damage, target.GetCurrentHP()));
	m_context.lastDamageApplied = damage;
	m_context.lastDamagingMove = m_context.currentMove;

	unsigned int currentPixel = target.GetCurrentHP() * HP_BAR_WIDTH / target.GetMaxHP();
	m_context.prevPixels = currentPixel;

	if (hitSubstitute)
	{
		target.DamageSubstitute(damage);
	}
	else
	{
		target.DamageCurrentHP(damage);
		m_context.damageTaken = damage;
		m_context.damageTakenCategory = currentMove.GetCategoryEnum();
		unsigned int newPixel = target.GetCurrentHP() * HP_BAR_WIDTH / target.GetMaxHP();
		m_context.pixelsLost = currentPixel - newPixel;
		m_context.damageInPixels = m_context.prevPixels - newPixel;
	}

	if (target.IsBiding() && !hitSubstitute)
	{
		target.AddBideDamage(damage);
	}
}

// Calculate power of low kick based on target Pokemon's weight (in hectograms)
unsigned int BattleCalculations::CalculateLowKickPower(const BattlePokemon& target)
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
}