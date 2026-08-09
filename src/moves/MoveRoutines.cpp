#include <array>
#include <span>
#include <algorithm>

#include "MoveRoutines.h"

#include "MoveEffectEnums.h"
#include "MoveHelpers.h"
#include "MoveRoutineDeps.h"
#include "../common/EnumUtils.h"
#include "../data/Database.h"
#include "../data/MoveID.h"
#include "../data/Move.h"
#include "../data/StringToTypes.h"
#include "../battle/BattleCalculations.h"
#include "../battle/StatusEffectProcessor.h"
#include "../battle/BattleContext.h"
#include "../battle/RandomEngine.h"
#include "../entities/controllers/AIController.h"
#include "../entities/BattlePokemon.h"
#include "../entities/Player.h"
#include "../entities/pokemonMove.h"
#include "../ui/interfaces/IMoveResultsUI.h"

namespace MoveRoutines
{
	static inline constexpr std::array<RoutineFn, EnumIndex(MoveEffect::COUNT)> JumpTable = []() {
		std::array<RoutineFn, EnumIndex(MoveEffect::COUNT)> table{};

		table.fill(Noop);

		table[EnumIndex(MoveEffect::NormalHit)] = NormalHit;
		table[EnumIndex(MoveEffect::IncreasedCritical)] = IncreasedCritical;
		table[EnumIndex(MoveEffect::MultiHit)] = MultiHit;
		table[EnumIndex(MoveEffect::BurnHit)] = BurnHit;
		table[EnumIndex(MoveEffect::FreezeHit)] = FreezeHit;
		table[EnumIndex(MoveEffect::ParalyzeHit)] = ParalyzeHit;
		table[EnumIndex(MoveEffect::OHKO)] = OHKO;
		table[EnumIndex(MoveEffect::RazorWind)] = RazorWind;
		table[EnumIndex(MoveEffect::AttackUp2)] = AttackUp2;
		table[EnumIndex(MoveEffect::Gust)] = Gust;
		table[EnumIndex(MoveEffect::ForceSwitch)] = ForceSwitch;
		table[EnumIndex(MoveEffect::Fly)] = Fly;
		table[EnumIndex(MoveEffect::PartialTrap)] = PartialTrap;
		table[EnumIndex(MoveEffect::Stomp)] = Stomp;
		table[EnumIndex(MoveEffect::DoubleHit)] = DoubleHit;
		table[EnumIndex(MoveEffect::JumpKick)] = JumpKick;
		table[EnumIndex(MoveEffect::FlinchHit)] = FlinchHit;
		table[EnumIndex(MoveEffect::AccuracyDown)] = AccuracyDown;
		table[EnumIndex(MoveEffect::BodySlam)] = BodySlam;
		table[EnumIndex(MoveEffect::RecoilQuarter)] = RecoilQuarter;
		table[EnumIndex(MoveEffect::Rampage)] = Rampage;
		table[EnumIndex(MoveEffect::RecoilThird)] = RecoilThird;
		table[EnumIndex(MoveEffect::DefenseDown)] = DefenseDown;
		table[EnumIndex(MoveEffect::PoisonHit)] = PoisonHit;
		table[EnumIndex(MoveEffect::Twineedle)] = Twineedle;
		table[EnumIndex(MoveEffect::AttackDown)] = AttackDown;
		table[EnumIndex(MoveEffect::SleepMove)] = SleepMove;
		table[EnumIndex(MoveEffect::Confuse)] = Confuse;
		table[EnumIndex(MoveEffect::SonicBoom)] = SonicBoom;
		table[EnumIndex(MoveEffect::Disable)] = Disable;
		table[EnumIndex(MoveEffect::SpecialDefenseDownHit)] = SpecialDefenseDownHit;
		table[EnumIndex(MoveEffect::Mist)] = Mist;
		table[EnumIndex(MoveEffect::ConfuseHit)] = ConfuseHit;
		table[EnumIndex(MoveEffect::SpeedDownHit)] = SpeedDownHit;
		table[EnumIndex(MoveEffect::AttackDownHit)] = AttackDownHit;
		table[EnumIndex(MoveEffect::RechargeAttack)] = RechargeAttack;
		table[EnumIndex(MoveEffect::LowKick)] = LowKick;
		table[EnumIndex(MoveEffect::Counter)] = Counter;
		table[EnumIndex(MoveEffect::SeismicToss)] = SeismicToss;
		table[EnumIndex(MoveEffect::Leech)] = Leech;
		table[EnumIndex(MoveEffect::LeechSeed)] = LeechSeed;
		table[EnumIndex(MoveEffect::Growth)] = Growth;
		table[EnumIndex(MoveEffect::SolarBeam)] = SolarBeam;
		table[EnumIndex(MoveEffect::PoisonPowder)] = PoisonPowder;
		table[EnumIndex(MoveEffect::StunSpore)] = StunSpore;
		table[EnumIndex(MoveEffect::SleepPowder)] = SleepPowder;
		table[EnumIndex(MoveEffect::SpeedDown2)] = SpeedDown2;
		table[EnumIndex(MoveEffect::DragonRage)] = DragonRage;
		table[EnumIndex(MoveEffect::Paralyze)] = Paralyze;
		table[EnumIndex(MoveEffect::Earthquake)] = Earthquake;
		table[EnumIndex(MoveEffect::Dig)] = Dig;
		table[EnumIndex(MoveEffect::Toxic)] = Toxic;
		table[EnumIndex(MoveEffect::AttackUp)] = AttackUp;
		table[EnumIndex(MoveEffect::SpeedUp2)] = SpeedUp2;
		table[EnumIndex(MoveEffect::Rage)] = Rage;
		table[EnumIndex(MoveEffect::Teleport)] = Teleport;
		table[EnumIndex(MoveEffect::NightShade)] = NightShade;
		table[EnumIndex(MoveEffect::Mimic)] = Mimic;
		table[EnumIndex(MoveEffect::DefenseDown2)] = DefenseDown2;
		table[EnumIndex(MoveEffect::EvasionUp)] = EvasionUp;
		table[EnumIndex(MoveEffect::HealHalfHP)] = HealHalfHP;
		table[EnumIndex(MoveEffect::DefenseUp)] = DefenseUp;
		table[EnumIndex(MoveEffect::Minimize)] = Minimize;
		table[EnumIndex(MoveEffect::DefenseUp2)] = DefenseUp2;
		table[EnumIndex(MoveEffect::LightScreen)] = LightScreen;
		table[EnumIndex(MoveEffect::Haze)] = Haze;
		table[EnumIndex(MoveEffect::Reflect)] = Reflect;
		table[EnumIndex(MoveEffect::FocusEnergy)] = FocusEnergy;
		table[EnumIndex(MoveEffect::Bide)] = Bide;
		table[EnumIndex(MoveEffect::Metronome)] = Metronome;
		table[EnumIndex(MoveEffect::MirrorMove)] = MirrorMove;
		table[EnumIndex(MoveEffect::Explosion)] = Explosion;
		table[EnumIndex(MoveEffect::AlwaysHit)] = AlwaysHit;
		table[EnumIndex(MoveEffect::SkullBash)] = SkullBash;
		table[EnumIndex(MoveEffect::SpecialDefenseUp2)] = SpecialDefenseUp2;
		table[EnumIndex(MoveEffect::DreamEater)] = DreamEater;
		table[EnumIndex(MoveEffect::PoisonGas)] = PoisonGas;
		table[EnumIndex(MoveEffect::SkyAttack)] = SkyAttack;
		table[EnumIndex(MoveEffect::Transform)] = Transform;
		table[EnumIndex(MoveEffect::Psywave)] = Psywave;
		table[EnumIndex(MoveEffect::Splash)] = Splash;
		table[EnumIndex(MoveEffect::Rest)] = Rest;
		table[EnumIndex(MoveEffect::Conversion)] = Conversion;
		table[EnumIndex(MoveEffect::TriAttack)] = TriAttack;
		table[EnumIndex(MoveEffect::SuperFang)] = SuperFang;
		table[EnumIndex(MoveEffect::Substitute)] = Substitute;
		table[EnumIndex(MoveEffect::Struggle)] = Struggle;

		return table;
		}();

	void Execute(MoveEffect ID, MoveRoutineDeps& deps)
	{
		JumpTable[EnumIndex(ID)](deps);
	}

	void Noop(MoveRoutineDeps& deps)
	{
		//auto& ctx = deps.context;

		//deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		//ctx.currentMove->DeductPP();

		//ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		//deps.resultsUI.DisplayNoopMsg();
	}

	void NormalHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void IncreasedCritical(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		unsigned int oldCritStage = ctx.attackingPokemon->GetCriticalHitStage();
		unsigned int newCritStage = oldCritStage + 1;

		ctx.attackingPokemon->SetCriticalHitStage(newCritStage);

		DamageRoutine(deps);

		ctx.attackingPokemon->SetCriticalHitStage(oldCritStage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void MultiHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		ctx.currentMove->DeductPP();

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{ 
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		int randomNumber{ deps.rng.GetPercentRoll() };

		int turnCount{};

		if (randomNumber <= 35)
			turnCount = 2;
		else if (randomNumber <= 70)
			turnCount = 3;
		else if (randomNumber <= 85)
			turnCount = 4;
		else
			turnCount = 5;

		MultiStrikeRoutine(deps, turnCount);

		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void BurnHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		InflictNVStatus(Status::Burned, ctx.currentMove->GetEffectChance(), deps);
	}

	void FreezeHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		InflictNVStatus(Status::Frozen, ctx.currentMove->GetEffectChance(), deps);
	}

	void ParalyzeHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		InflictNVStatus(Status::Paralyzed, ctx.currentMove->GetEffectChance(), deps);
	}

	void OHKO(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		OHKODamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void RazorWind(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		if (HandleCharging(deps, &IMoveResultsUI::DisplayRazorWindChargeMsg))
		{
			return;
		}

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		unsigned int oldCritStage = ctx.attackingPokemon->GetCriticalHitStage();
		unsigned int newCritStage = oldCritStage + 1;

		ctx.attackingPokemon->SetCriticalHitStage(newCritStage);

		DamageRoutine(deps);

		ctx.attackingPokemon->SetCriticalHitStage(oldCritStage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void AttackUp2(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 2, "attack", [](BattlePokemon& p) { return p.GetAttackStage(); }, [](BattlePokemon& p, int val) { p.SetAttackStage(val); });
	}

	void Gust(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		// Specific accuracy check for gust vs SemiInvulnerableFly done in CalculateHitChance()
		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->IsSemiInvulnerableFromFly())
		{
			ctx.initialPowerMultiplier = 20;
		}

		DamageRoutine(deps);
	}

	void ForceSwitch(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		if (ctx.defendingPlayer->GetPokemonLeft() == 1 || !ctx.defendingPlayer->IsFirst())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		ctx.flags.hit = !ctx.defendingPokemon->IsSemiInvulnerable();

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		std::array<BattlePokemon*, 6> enemyPokemonList{};

		size_t count{};
		for (auto& candidateMon : ctx.defendingPlayer->GetBeltArray())
		{
			if (candidateMon.HasPokemon() && &candidateMon != ctx.defendingPokemon && !candidateMon.IsFainted())
			{
				enemyPokemonList[count] = &candidateMon;
				++count;
			}
		}

		std::span<BattlePokemon*> enemyListView{ enemyPokemonList.data(), count };

		BattlePokemon* newMon{ enemyListView[deps.rng.RandomRange(0, count - 1)] };

		// Reset stats for the Pokémon being forced out
		ctx.defendingPokemon->ResetStatsOnSwitch();

		if (ctx.attackingPokemon->IsBound())
		{
			ctx.attackingPokemon->SetBound(false);
			ctx.attackingPokemon->ResetBoundCounter();
			ctx.attackingPokemon->SetBoundTurnCount(0);
		}

		if (ctx.defendingPlayer == ctx.playerOne)
		{
			ctx.playerOneCurrentPokemon = newMon;
		}
		else
		{
			ctx.playerTwoCurrentPokemon = newMon;
		}

		for (auto player : ctx.vec_aiPlayers)
		{
			player->GetAIController().OnActivePokemonChanged(ctx);
		}

		deps.resultsUI.DisplayEnemySwitchMsg(newMon->GetNameView());
	}

	void Fly(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		ChargingMoveHooks hooks;
		hooks.preCharge = [](MoveRoutineDeps& deps) { deps.context.attackingPokemon->SetSemiInvulnerableFly(true); };
		hooks.postCharge = [](MoveRoutineDeps& deps) { deps.context.attackingPokemon->SetSemiInvulnerableFly(false); };

		if (HandleCharging(deps, &IMoveResultsUI::DisplayFlyChargeMsg, hooks))
		{
			return;
		}

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void PartialTrap(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.defendingPokemon->IsFainted() && !ctx.defendingPokemon->IsBound() && ctx.flags.currentEffectiveness != BattleStateFlags::Effectiveness::No && !ctx.flags.hitSubstitute)
		{
			bool isGhost = ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Ghost || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Ghost;

			ctx.defendingPokemon->SetBound(true);

			if (!isGhost)
			{
				ctx.defendingPlayer->SetCanSwitch(false);
			}

			unsigned int randomMod{ deps.rng.GetBoundTurnRoll() };
			ctx.defendingPokemon->SetBoundTurnCount(randomMod);
			ctx.defendingPokemon->ResetBoundCounter();
			ctx.defendingPokemon->SetBoundMoveName(ctx.currentMove->GetMoveID());

			deps.resultsUI.BoundMoveText(ctx.attackingPlayer->GetPlayerNameView(), ctx.defendingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.defendingPokemon->GetNameView(), ctx.currentMove->GetMoveID());
		}
	}

	void Stomp(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		if (ctx.defendingPokemon->HasUsedMinimize() && !ctx.defendingPokemon->IsSemiInvulnerable())
		{
			ctx.flags.hit = true;
		}
		else if (ctx.defendingPokemon->IsSemiInvulnerable())
		{
			ctx.flags.hit = false;
		}
		else
		{
			ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		// Damage multiplier for when defending Pokemon has minimized is in CalculateDamage()
		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		FlinchRoutine(deps);
	}

	void DoubleHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		int turnCount{ 2 };

		MultiStrikeRoutine(deps, turnCount);

		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void JumpKick(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		bool isImmune =	ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No;

		if (isImmune)
		{
			ctx.flags.hit = false;
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
		}
		else
		{
			ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);
		}

		if (isImmune || !ctx.flags.hit)
		{
			if (!isImmune)
			{
				deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			}

			unsigned int crashDamage = std::max(1u, ctx.attackingPokemon->GetMaxHP() / 2);

			ctx.attackingPokemon->DamageCurrentHP(crashDamage);

			deps.resultsUI.DisplayJumpKickCrashMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());

			deps.statusProcessor.CheckFaintCondition(*ctx.defendingPlayer, *ctx.attackingPlayer, *ctx.defendingPokemon, *ctx.attackingPokemon);

			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void FlinchHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		FlinchRoutine(deps);
	}

	void AccuracyDown(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (ctx.flags.hit && ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		if (ctx.defendingPlayer->HasMist() && ctx.flags.hit)
		{
			deps.resultsUI.DisplayProtectedByMistMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		StageDownRoutine(deps, 1, "accuracy", [](BattlePokemon& p) { return p.GetAccuracyStage(); }, [](BattlePokemon& p, int val) { p.SetAccuracyStage(val); });
	}

	void BodySlam(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		if (ctx.defendingPokemon->HasUsedMinimize() && !ctx.defendingPokemon->IsSemiInvulnerable())
		{
			ctx.flags.hit = true;
		}
		else if (ctx.defendingPokemon->IsSemiInvulnerable())
		{
			ctx.flags.hit = false;
		}
		else
		{
			ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		// Damage multiplier for when defending Pokemon has minimized is in CalculateDamage()
		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		InflictNVStatus(Status::Paralyzed, ctx.currentMove->GetEffectChance(), deps);
	}

	void RecoilQuarter(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		RecoilRoutine(deps, 4);
	}

	void Rampage(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		if (!ctx.attackingPokemon->IsRampaging())
		{
			ctx.currentMove->DeductPP();

			ctx.attackingPokemon->SetRampaging(true);
			ctx.attackingPlayer->SetCanSwitch(false);

			unsigned int randomMod{ deps.rng.GetRampageTurnRoll() };
			ctx.attackingPokemon->SetRampageTurnCount(randomMod);
			ctx.attackingPokemon->ResetRampageCounter();
		}

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			if (ctx.attackingPokemon->GetRampageCounter() >= ctx.attackingPokemon->GetRampageTurnCount() && !ctx.attackingPokemon->IsConfused())
			{
				deps.statusProcessor.RampageConfuse();
			}

			deps.statusProcessor.ResetRampageState();

			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		bool isImmune = ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No;

		if (isImmune)
		{
			ctx.flags.hit = false;
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
		}
		else
		{
			ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);
		}

		if (isImmune || !ctx.flags.hit)
		{
			if (!isImmune)
			{
				deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			}
		}

		if (!isImmune && ctx.flags.hit)
		{
			DamageRoutine(deps);

			deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
			deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
		}

		bool reachedEnd = ctx.attackingPokemon->GetRampageCounter() >= ctx.attackingPokemon->GetRampageTurnCount();
		bool moveFailed = !ctx.flags.hit || isImmune;

		if (moveFailed || reachedEnd)
		{
			if (reachedEnd && !ctx.attackingPokemon->IsConfused())
			{
				deps.statusProcessor.RampageConfuse();
			}

			deps.statusProcessor.ResetRampageState();
		}
	}

	void RecoilThird(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		RecoilRoutine(deps, 3);
	}

	void DefenseDown(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (ctx.flags.hit && ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		if (ctx.defendingPlayer->HasMist() && ctx.flags.hit)
		{
			deps.resultsUI.DisplayProtectedByMistMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		StageDownRoutine(deps, 1, "defense", [](BattlePokemon& p) { return p.GetDefenseStage(); }, [](BattlePokemon& p, int val) { p.SetDefenseStage(val); });
	}

	void PoisonHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		InflictNVStatus(Status::Poisoned, ctx.currentMove->GetEffectChance(), deps);
	}

	void Twineedle(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		int turnCount = 2;

		MultiStrikeRoutine(deps, turnCount);

		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void AttackDown(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (ctx.flags.hit && ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		if (ctx.defendingPlayer->HasMist() && ctx.flags.hit)
		{
			deps.resultsUI.DisplayProtectedByMistMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		StageDownRoutine(deps, 1, "attack", [](BattlePokemon& p) { return p.GetAttackStage(); }, [](BattlePokemon& p, int val) { p.SetAttackStage(val); });
	}

	void SleepMove(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() == Status::Sleeping)
		{
			deps.resultsUI.DisplayAlreadyAsleepMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() != Status::Normal || (ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute()))
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		InflictNVStatus(Status::Sleeping, 100, deps);
	}

	void Confuse(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->IsConfused() || (ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute()))
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		ctx.defendingPokemon->SetConfusedStatus(true);

		unsigned int randomMod{ deps.rng.GetConfusionTurnRoll() };
		ctx.defendingPokemon->SetConfusedTurnCount(randomMod);
		ctx.defendingPokemon->ResetConfusedCounter();

		deps.resultsUI.DisplayBecameConfuseMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
	}

	void SonicBoom(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		const int baseDamage = 20;

		FixedDamageRoutine(deps, baseDamage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Disable(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		auto* lastUsed = ctx.defendingPokemon->GetLastUsedMove();

		if (lastUsed ==	nullptr ||
			!ctx.defendingPokemon->MoveIsDisabled() ||
			lastUsed->m_currentPP <= 0 ||
			lastUsed->GetMoveEffectEnum() == MoveEffect::Struggle)
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		ctx.defendingPokemon->SetDisabledStatus(true);
		ctx.defendingPokemon->ResetDisabledCounter();

		deps.resultsUI.DisplayMoveDisabledMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ctx.defendingPokemon->GetLastUsedMove()->GetName());

	}

	void SpecialDefenseDownHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		StageDownDamageRoutine(deps, 1, "special defense", [](BattlePokemon& p) { return p.GetSpecialDefenseStage(); }, [](BattlePokemon& p, int val) { p.SetSpecialDefenseStage(val); });
	}

	void Mist(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (!ctx.attackingPlayer->HasMist())
		{
			deps.resultsUI.DisplayMistMsg(ctx.attackingPlayer->GetPlayerNameView());
			ctx.attackingPlayer->SetMist(true);
		}
		else
		{
			deps.resultsUI.DisplayFailedTextDialog();
		}
	}

	void ConfuseHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.defendingPokemon->IsFainted() && !ctx.defendingPokemon->IsConfused() && !ctx.flags.hitSubstitute)
		{
			int randomNumber{ deps.rng.GetPercentRoll() };

			if (randomNumber <= ctx.currentMove->GetEffectChance())
			{
				deps.resultsUI.DisplayBecameConfuseMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());

				ctx.defendingPokemon->SetConfusedStatus(true);

				unsigned int randomMod{ deps.rng.GetConfusionTurnRoll() };
				ctx.defendingPokemon->SetConfusedTurnCount(randomMod);
				ctx.defendingPokemon->ResetConfusedCounter();
			}
		}
	}

	void SpeedDownHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		StageDownDamageRoutine(deps, 1, "speed", [](BattlePokemon& p) { return p.GetSpeedStage(); }, [](BattlePokemon& p, int val) { p.SetSpeedStage(val); });
	}

	void AttackDownHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		StageDownDamageRoutine(deps, 1, "attack", [](BattlePokemon& p) { return p.GetAttackStage(); }, [](BattlePokemon& p, int val) { p.SetAttackStage(val); });
	}

	void RechargeAttack(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		ctx.attackingPokemon->SetRecharging(true);
		ctx.attackingPlayer->SetCanSwitch(false);
	}

	void LowKick(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		// Low Kick power calculated in CalculateDamage()
		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Counter(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		int counterDamage = ctx.damageTaken * 2;

		const auto* lastMove = ctx.defendingPokemon->GetLastUsedMove();
		const bool lastWasPhysical = lastMove && lastMove->GetCategoryEnum() == Category::Physical;

		bool fail = ctx.attackingPlayer->IsFirst() || counterDamage == 0 || !lastWasPhysical || ctx.flags.hitSubstitute;

		if (fail)
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		FixedDamageRoutine(deps, counterDamage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void SeismicToss(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		const int baseDamage = ctx.attackingPokemon->GetLevel();

		FixedDamageRoutine(deps, baseDamage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Leech(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		unsigned int leechedHealth{ ctx.lastDamageApplied / 2 };

		unsigned int finalLeech = std::min(std::max(1u, leechedHealth), ctx.attackingPokemon->GetMaxHP() - ctx.attackingPokemon->GetCurrentHP());

		ctx.attackingPokemon->HealCurrentHP(finalLeech);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);

		if (finalLeech > 0)
		{
			deps.resultsUI.DisplayEnergyDrainedMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
		}

		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void LeechSeed(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		bool isImmune = ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Grass || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Grass;

		if (isImmune)
		{
			deps.resultsUI.DisplayDoesntAffectMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->IsSeeded() || ctx.defendingPokemon->HasSubstitute())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		ctx.defendingPokemon->SetSeededStatus(true);

		deps.resultsUI.DisplaySeededMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
	}

	void Growth(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 1, "attack", [](BattlePokemon& p) { return p.GetAttackStage(); }, [](BattlePokemon& p, int val) { p.SetAttackStage(val); });
		StageUpRoutine(deps, 1, "special attack", [](BattlePokemon& p) { return p.GetSpecialAttackStage(); }, [](BattlePokemon& p, int val) { p.SetSpecialAttackStage(val); });
	}

	void SolarBeam(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		if (HandleCharging(deps, &IMoveResultsUI::DisplaySolarBeamChargeMsg))
		{
			return;
		}

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void PoisonPowder(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		bool isImmune = ((ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Grass || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Grass) ||
			(ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Poison || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Poison) ||
			(ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Steel || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Steel));

		if (isImmune)
		{
			deps.resultsUI.DisplayDoesntAffectMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() == Status::Poisoned || ctx.defendingPokemon->GetStatus() == Status::Badly_Poisoned)
		{
			deps.resultsUI.DisplayAlreadyPoisonedMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() != Status::Normal || (ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute()))
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		InflictNVStatus(Status::Poisoned, 100, deps);
	}

	void StunSpore(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		bool isImmune = ((ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Grass || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Grass) ||
			(ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Electric || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Electric));

		if (isImmune)
		{
			deps.resultsUI.DisplayDoesntAffectMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() == Status::Paralyzed)
		{
			deps.resultsUI.DisplayAlreadyParalyzedMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if ((ctx.defendingPokemon->GetStatus() != Status::Normal) || (ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute()))
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		InflictNVStatus(Status::Paralyzed, 100, deps);
	}

	void SleepPowder(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		bool isImmune = (ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Grass || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Grass);

		if (isImmune)
		{
			deps.resultsUI.DisplayDoesntAffectMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() == Status::Sleeping)
		{
			deps.resultsUI.DisplayAlreadyAsleepMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if ((ctx.defendingPokemon->GetStatus() != Status::Normal) || (ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute()))
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		InflictNVStatus(Status::Sleeping, 100, deps);
	}

	void SpeedDown2(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (ctx.flags.hit && ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		if (ctx.defendingPlayer->HasMist() && ctx.flags.hit)
		{
			deps.resultsUI.DisplayProtectedByMistMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		StageDownRoutine(deps, 2, "speed", [](BattlePokemon& p) { return p.GetSpeedStage(); }, [](BattlePokemon& p, int val) { p.SetSpeedStage(val); });
	}

	void DragonRage(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		const int baseDamage = 40;

		FixedDamageRoutine(deps, baseDamage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Paralyze(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		bool isElectricType = (ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Electric ||
			ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Electric);

		bool electricVsGround =	ctx.currentMove->GetMoveTypeEnum() == PokemonType::Electric &&
			(ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Ground ||
				ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Ground);

		bool isImmune = (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No || isElectricType || electricVsGround);

		// Special case: Glare affects Ghosts despite being Normal-type
		if (ctx.currentMove->GetMoveID() == MoveID::Glare)
		{
			bool isGhostType = (ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Ghost ||
				ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Ghost);

			if (isGhostType && !isElectricType)
				isImmune = false;
		}

		if (isImmune)
		{
			deps.resultsUI.DisplayDoesntAffectMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() == Status::Paralyzed)
		{
			deps.resultsUI.DisplayAlreadyParalyzedMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() != Status::Normal || (ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute()))
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		InflictNVStatus(Status::Paralyzed, 100, deps);
	}

	void Earthquake(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		// Damage multiplier for when defending Pokemon is SemiInvulnerableDig is in CalculateDamage()
		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Dig(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		ChargingMoveHooks hooks;
		hooks.preCharge = [](MoveRoutineDeps& deps) { deps.context.attackingPokemon->SetSemiInvulnerableDig(true); };
		hooks.postCharge = [](MoveRoutineDeps& deps) { deps.context.attackingPokemon->SetSemiInvulnerableDig(false); };

		if (HandleCharging(deps, &IMoveResultsUI::DisplayDigChargeMsg, hooks))
		{
			return;
		}

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Toxic(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		bool isImmune = ((ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Poison || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Poison) ||
			(ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Steel || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Steel));

		if (isImmune)
		{
			deps.resultsUI.DisplayDoesntAffectMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.attackingPokemon->GetTypeOneEnum() == PokemonType::Poison || ctx.attackingPokemon->GetTypeTwoEnum() == PokemonType::Poison)
		{
			ctx.flags.hit = true;
		}
		else
		{
			ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() == Status::Poisoned || ctx.defendingPokemon->GetStatus() == Status::Badly_Poisoned)
		{
			deps.resultsUI.DisplayAlreadyPoisonedMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() != Status::Normal || (ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute()))
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		InflictNVStatus(Status::Badly_Poisoned, 100, deps);
	}

	void AttackUp(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 1, "attack", [](BattlePokemon& p) { return p.GetAttackStage(); }, [](BattlePokemon& p, int val) { p.SetAttackStage(val); });
	}

	void SpeedUp2(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 2, "speed", [](BattlePokemon& p) { return p.GetSpeedStage(); }, [](BattlePokemon& p, int val) { p.SetSpeedStage(val); });
	}

	void Rage(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		ctx.attackingPokemon->SetRaging(true);

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Teleport(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (ctx.attackingPlayer->GetPokemonLeft() == 1)
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		ctx.attackingPlayer->SetPendingSwitch(true);
	}

	void NightShade(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		const int baseDamage = ctx.attackingPokemon->GetLevel();

		FixedDamageRoutine(deps, baseDamage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Mimic(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		pokemonMove* targetLastUsedMove = ctx.defendingPokemon->GetLastUsedMove();

		if (targetLastUsedMove == nullptr)
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		bool alreadyHasMove{};
		for (const auto& move : ctx.attackingPokemon->GetMoveArray())
		{
			if (move.GetMovePointer() == nullptr)
			{
				continue;
			}

			if (targetLastUsedMove->GetMoveID() == move.GetMoveID())
			{
				alreadyHasMove = true;
				break;
			}
		}

		bool fail =
			alreadyHasMove ||
			targetLastUsedMove->GetMoveID() == MoveID::Transform ||
			targetLastUsedMove->GetMoveID() == MoveID::Struggle ||
			targetLastUsedMove->GetMoveID() == MoveID::Metronome ||
			ctx.attackingPokemon->IsTransformed();
		

		if (fail)
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		ctx.flags.hit = !ctx.defendingPokemon->IsSemiInvulnerable();

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.attackingPokemon->SetUsedMimic(true);
		ctx.attackingPokemon->SetMimicPP(ctx.currentMove->m_currentPP);

		const Move* copiedMove = Database::GetPointerToBaseMoveByIndex(targetLastUsedMove->GetMoveIndex());

		deps.resultsUI.DisplayLearnedMimicMoveMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), targetLastUsedMove->GetName());

		ctx.currentMove->SetMovePointer(copiedMove);

		ctx.currentMove->m_currentPP = ctx.defendingPokemon->GetLastUsedMove()->GetPP();
		ctx.currentMove->m_maxPP = ctx.defendingPokemon->GetLastUsedMove()->GetPP();
		ctx.currentMove->b_isMimicked = true;
	}

	void DefenseDown2(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (ctx.flags.hit && ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		if (ctx.defendingPlayer->HasMist() && ctx.flags.hit)
		{
			deps.resultsUI.DisplayProtectedByMistMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		StageDownRoutine(deps, 2, "defense", [](BattlePokemon& p) { return p.GetDefenseStage(); }, [](BattlePokemon& p, int val) { p.SetDefenseStage(val); });
	}

	void EvasionUp(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 1, "evasion", [](BattlePokemon& p) { return p.GetEvasionStage(); }, [](BattlePokemon& p, int val) { p.SetEvasionStage(val); });
	}	 

	void HealHalfHP(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (ctx.attackingPokemon->GetCurrentHP() < ctx.attackingPokemon->GetMaxHP())
		{
			unsigned int healAmount = (ctx.attackingPokemon->GetMaxHP() + 1) / 2;

			ctx.attackingPokemon->HealCurrentHP(healAmount);

			deps.resultsUI.DisplayRecoveredHPRestoredMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
		}

		else
		{
			deps.resultsUI.DisplayHPFullMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
		}
	}

	void DefenseUp(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 1, "defense", [](BattlePokemon& p) { return p.GetDefenseStage(); }, [](BattlePokemon& p, int val) { p.SetDefenseStage(val); });
	}

	void Minimize(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 2, "evasion", [](BattlePokemon& p) { return p.GetEvasionStage(); }, [](BattlePokemon& p, int val) { p.SetEvasionStage(val); });
	}

	void DefenseUp2(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 2, "defense", [](BattlePokemon& p) { return p.GetDefenseStage(); }, [](BattlePokemon& p, int val) { p.SetDefenseStage(val); });

	}

	void LightScreen(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (ctx.attackingPlayer->HasLightScreen())
		{
			deps.resultsUI.DisplayFailedTextDialog();
		}
		else
		{
			ctx.attackingPlayer->SetLightScreen(true);
			deps.resultsUI.DisplayLightScreenMsg(ctx.attackingPlayer->GetPlayerNameView());
		}
	}

	void Haze(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		ctx.attackingPokemon->SetAttackStage(6);
		ctx.attackingPokemon->SetDefenseStage(6);
		ctx.attackingPokemon->SetSpecialAttackStage(6);
		ctx.attackingPokemon->SetSpecialDefenseStage(6);
		ctx.attackingPokemon->SetSpeedStage(6);
		ctx.attackingPokemon->SetEvasionStage(6);
		ctx.attackingPokemon->SetAccuracyStage(6);

		ctx.defendingPokemon->SetAttackStage(6);
		ctx.defendingPokemon->SetDefenseStage(6);
		ctx.defendingPokemon->SetSpecialAttackStage(6);
		ctx.defendingPokemon->SetSpecialDefenseStage(6);
		ctx.defendingPokemon->SetSpeedStage(6);
		ctx.defendingPokemon->SetEvasionStage(6);
		ctx.defendingPokemon->SetAccuracyStage(6);

		deps.resultsUI.DisplayHazeMsg();
	}

	void Reflect(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (ctx.attackingPlayer->HasReflect())
		{
			deps.resultsUI.DisplayFailedTextDialog();
		}
		else
		{
			ctx.attackingPlayer->SetReflect(true);
			deps.resultsUI.DisplayReflectMsg(ctx.attackingPlayer->GetPlayerNameView());
		}
	}

	void FocusEnergy(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (ctx.attackingPokemon->HasFocusEnergy())
		{
			deps.resultsUI.DisplayFailedTextDialog();
		}
		else
		{
			ctx.attackingPokemon->SetFocusEnergy(true);
			ctx.attackingPokemon->SetCriticalHitStage(2);
			deps.resultsUI.DisplayFocusEnergyMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
		}
	}

	void Bide(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (!ctx.attackingPokemon->IsBiding())
		{
			deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

			ctx.currentMove->DeductPP();

			ctx.attackingPokemon->SetBide(true);
			ctx.attackingPlayer->SetCanSwitch(false);

			ctx.attackingPokemon->SetBideTurnCount(2);
			ctx.attackingPokemon->ResetBideCounter();

			deps.resultsUI.DisplayBideStoringEnergyMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());

			return;
		}

		deps.resultsUI.DisplayBideUnleashedMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());

		int bideDamage = ctx.attackingPokemon->GetBideDamage() * 2;

		deps.statusProcessor.ResetBideState();

		if (bideDamage <= 0)
		{
			deps.resultsUI.DisplayFailedTextDialog();

			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));

			return;
		}

		ctx.flags.hit = !ctx.defendingPokemon->IsSemiInvulnerable();

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}
		
		FixedDamageRoutine(deps, bideDamage);
		
		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Metronome(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		ctx.currentMove->DeductPP();

		/* ---
		Metronome cannot call these moves:
		counter - 68
		mimic - 102
		metronome - 118
		mirror move - 119
		transform - 144
		struggle - 165
		  --- */

		MoveID id = MoveID::Counter;

		do
		{
			id = RandomEnum(deps.rng.GetGenerator(), MoveID::Pound, MoveID::Substitute);
		}
		while (id == MoveID::Counter || id == MoveID::Mimic || id == MoveID::Metronome || id == MoveID::MirrorMove || id == MoveID::Transform);

		const Move& selectedMove = Database::GetBaseMoveByID(id);

		deps.resultsUI.DisplayMetronomeMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), selectedMove.GetName());

		ctx.attackingPokemon->SetMetronomeMove(selectedMove);

		pokemonMove* metronome = ctx.currentMove;

		ctx.currentMove = ctx.attackingPokemon->GetMetronomeMove();
		
		if (ctx.attackingPlayer == ctx.playerOne)
		{
			ctx.playerOneCurrentMoveEffect = selectedMove.GetMoveEffectEnum();
		}
		else
		{
			ctx.playerTwoCurrentMoveEffect = selectedMove.GetMoveEffectEnum();
		}

		ctx.currentMoveEffect = (ctx.attackingPlayer == ctx.playerOne) ? ctx.playerOneCurrentMoveEffect : ctx.playerTwoCurrentMoveEffect;

		{
			Execute(selectedMove.GetMoveEffectEnum(), deps);
		}

		ctx.currentMove = metronome;

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		ctx.attackingPokemon->ResetMetronome();
	}

	void MirrorMove(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);
			return;
		}

		pokemonMove* targetLastUsedMove = ctx.defendingPokemon->GetLastUsedMove();

		if (targetLastUsedMove == nullptr)
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		if (!targetLastUsedMove->IsAffectedByMirrorMove())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		const Move& selectedMove = Database::GetBaseMoveByIndex(targetLastUsedMove->GetMoveIndex());

		ctx.attackingPokemon->SetMirrorMove(selectedMove);

		pokemonMove* mirrorMove = ctx.currentMove;

		ctx.currentMove = ctx.attackingPokemon->GetMirrorMoveCopiedMove();

		if (ctx.attackingPlayer == ctx.playerOne)
		{
			ctx.playerOneCurrentMoveEffect = selectedMove.GetMoveEffectEnum();
		}
		else
		{
			ctx.playerTwoCurrentMoveEffect = selectedMove.GetMoveEffectEnum();
		}


		ctx.currentMoveEffect = (ctx.attackingPlayer == ctx.playerOne) ? ctx.playerOneCurrentMoveEffect : ctx.playerTwoCurrentMoveEffect;

		{
			Execute(selectedMove.GetMoveEffectEnum(), deps);
		}

		ctx.currentMove = mirrorMove;

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		ctx.attackingPokemon->ResetMirrorMove();
	}

	void Explosion(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		ctx.attackingPokemon->DamageCurrentHP(ctx.attackingPokemon->GetCurrentHP());

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			deps.statusProcessor.CheckFaintCondition(*ctx.defendingPlayer, *ctx.attackingPlayer, *ctx.defendingPokemon, *ctx.attackingPokemon);
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));

			deps.statusProcessor.CheckFaintCondition(*ctx.defendingPlayer, *ctx.attackingPlayer, *ctx.defendingPokemon, *ctx.attackingPokemon);

			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());

			deps.statusProcessor.CheckFaintCondition(*ctx.defendingPlayer, *ctx.attackingPlayer, *ctx.defendingPokemon, *ctx.attackingPokemon);

			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckFaintCondition(*ctx.defendingPlayer, *ctx.attackingPlayer, *ctx.defendingPokemon, *ctx.attackingPokemon);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void AlwaysHit(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = !ctx.defendingPokemon->IsSemiInvulnerable();

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void SkullBash(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		ChargingMoveHooks hooks;
		hooks.stageUp = &StageUpRoutine;
		hooks.getStage = [](BattlePokemon& p) { return p.GetDefenseStage(); };
		hooks.setStage = [](BattlePokemon& p, int val) { p.SetDefenseStage(val); };
		hooks.stageIncreaseAmount = 1;
		hooks.stageName = "defense";

		if (HandleCharging(deps, &IMoveResultsUI::DisplaySkullBashChargeMsg, hooks))
		{
			return;
		}

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void SpecialDefenseUp2(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		StageUpRoutine(deps, 2, "special defense", [](BattlePokemon& p) { return p.GetSpecialDefenseStage(); }, [](BattlePokemon& p, int val) { p.SetSpecialDefenseStage(val); });
	}

	void DreamEater(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.defendingPokemon->GetStatus() != Status::Sleeping || ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayDoesntAffectMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		unsigned int leechedHealth{ ctx.damageTaken / 2 };

		unsigned int finalLeech = std::min(std::max(1u, leechedHealth), ctx.attackingPokemon->GetMaxHP() - ctx.attackingPokemon->GetCurrentHP());

		ctx.attackingPokemon->HealCurrentHP(finalLeech);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);

		if (finalLeech > 0)
		{
			deps.resultsUI.DisplayEnergyDrainedMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
		}

		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void PoisonGas(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		bool isImmune = ((ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Poison || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Poison) ||
			(ctx.defendingPokemon->GetTypeOneEnum() == PokemonType::Steel || ctx.defendingPokemon->GetTypeTwoEnum() == PokemonType::Steel));

		if (isImmune)
		{
			deps.resultsUI.DisplayDoesntAffectMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if (ctx.defendingPokemon->GetStatus() == Status::Poisoned || ctx.defendingPokemon->GetStatus() == Status::Badly_Poisoned)
		{
			deps.resultsUI.DisplayAlreadyPoisonedMsg(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		if ((ctx.defendingPokemon->GetStatus() != Status::Poisoned && ctx.defendingPokemon->GetStatus() != Status::Normal) || ctx.defendingPokemon->HasSubstitute())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		InflictNVStatus(Status::Poisoned, 100, deps);
	}

	void SkyAttack(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		if (HandleCharging(deps, &IMoveResultsUI::DisplaySkyAttackChargeMsg))
		{
			return;
		}

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		unsigned int oldCritStage = ctx.attackingPokemon->GetCriticalHitStage();
		unsigned int newCritStage = oldCritStage + 1;

		ctx.attackingPokemon->SetCriticalHitStage(newCritStage);

		DamageRoutine(deps);

		ctx.attackingPokemon->SetCriticalHitStage(oldCritStage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		FlinchRoutine(deps);
	}

	void Transform(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		if (ctx.attackingPokemon->IsTransformed() || ctx.defendingPokemon->IsTransformed() || ctx.defendingPokemon->HasSubstitute())
		{
			deps.resultsUI.DisplayFailedTextDialog();
			return;
		}

		ctx.flags.hit = !ctx.defendingPokemon->IsSemiInvulnerable();

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackAvoidedTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView());
			return;
		}

		ctx.attackingPokemon->SetTransformation(ctx.defendingPokemon);
		deps.resultsUI.DisplayTransformMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.defendingPokemon->GetNameView());
	}

	void Psywave(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		unsigned int psywaveDamage = 0;

		unsigned int randomNumber{ deps.rng.GetPsywaveDamageRoll() };

		psywaveDamage = std::max(1u, ctx.attackingPokemon->GetLevel() * (randomNumber + 50) / 100);

		FixedDamageRoutine(deps, psywaveDamage);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Splash(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		deps.resultsUI.DisplaySplashMsg();
	}

	void Rest(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (ctx.attackingPokemon->GetStatus() != Status::Sleeping &&
			ctx.attackingPokemon->GetCurrentHP() < ctx.attackingPokemon->GetMaxHP())
		{
			deps.resultsUI.DisplayRestMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());

			ctx.attackingPokemon->ChangeStatus(Status::Sleeping);

			ctx.attackingPokemon->SetSleepTurnCount(2);
			ctx.attackingPokemon->ResetSleepCounter();

			unsigned int healAmount = ctx.attackingPokemon->GetMaxHP() - ctx.attackingPokemon->GetCurrentHP();
			ctx.attackingPokemon->HealCurrentHP(healAmount);
		}
		else if (ctx.attackingPokemon->GetCurrentHP() >= ctx.attackingPokemon->GetMaxHP())
		{
			deps.resultsUI.DisplayHPFullMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
		}
	}

	void Conversion(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		PokemonType firstAvailableMoveSlotType{};

		for (const auto& move : ctx.attackingPokemon->GetMoveArray())
		{
			if (move.GetMovePointer() == nullptr)
			{
				continue;
			}
			
			firstAvailableMoveSlotType = move.GetMoveTypeEnum();
			break;
		}

		if ((ctx.attackingPokemon->GetTypeOneEnum() == firstAvailableMoveSlotType &&
			ctx.attackingPokemon->GetTypeTwoEnum() == PokemonType::None) ||
			ctx.attackingPokemon->IsConverted())
		{
			deps.resultsUI.DisplayFailedTextDialog();
		}
		else
		{
			ctx.attackingPokemon->SetConversion(firstAvailableMoveSlotType);

			deps.resultsUI.DisplayConversionMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.attackingPokemon->GetTypeOne());
		}
	}

	void TriAttack(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		int randomNumber{ deps.rng.GetPercentRoll() };

		if (randomNumber <= ctx.currentMove->GetEffectChance() &&
			(!ctx.defendingPokemon->HasSubstitute() || ctx.currentMove->CanBypassSubstitute()) &&
			ctx.defendingPokemon->GetCurrentHP() != 0)
		{
			unsigned int randomStatus{ deps.rng.GetTriAttackStatusRoll() };

			switch (randomStatus)
			{
			case 1:
				InflictNVStatus(Status::Burned, 100, deps);
				break;

			case 2:
				InflictNVStatus(Status::Frozen, 100, deps);
				break;

			case 3:
				InflictNVStatus(Status::Paralyzed, 100, deps);
				break;

			default:
				break;
			}
		}

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void SuperFang(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = deps.calculations.CalculateHitChance(*ctx.currentMove, *ctx.attackingPokemon, *ctx.defendingPokemon);

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		bool hasSubstitute = ctx.defendingPokemon->HasSubstitute() && !ctx.currentMove->CanBypassSubstitute();

		unsigned int hpSource = hasSubstitute ? ctx.defendingPokemon->GetSubstituteHP() : ctx.defendingPokemon->GetCurrentHP();

		unsigned int finalDamage = std::max(1u, hpSource / 2);

		deps.calculations.ApplyDamage(*ctx.currentMove, *ctx.defendingPokemon, finalDamage);
		deps.resultsUI.DisplaySubstituteDamageTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ctx.defendingPokemon->GetSubstituteHP(), ctx.defendingPokemon->HasSubstitute(), ctx.flags.hitSubstitute);

		TryDamageReactions(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);
	}

	void Substitute(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.currentMove->DeductPP();

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (ctx.attackingPokemon->HasSubstitute())
		{
			deps.resultsUI.DisplayAlreadyHasSubstituteMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		unsigned int substituteHP = ctx.attackingPokemon->GetMaxHP() / 4;

		if (substituteHP >= ctx.attackingPokemon->GetCurrentHP())
		{
			deps.resultsUI.DisplayNotEnoughHPSubstituteMsg();
			return;
		}

		unsigned int hpCost = substituteHP;

		deps.resultsUI.DisplayPutInSubstituteMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
		ctx.attackingPokemon->SetSubstitute(true);
		ctx.attackingPokemon->SetSubstituteHP(hpCost);
		ctx.attackingPokemon->DamageCurrentHP(hpCost);
		ctx.attackingPokemon->SetBound(false);
		ctx.attackingPokemon->ResetBoundCounter();
		ctx.attackingPokemon->SetBoundTurnCount(0);
	}

	void Struggle(MoveRoutineDeps& deps)
	{
		auto& ctx = deps.context;

		deps.resultsUI.DisplayNoMovesLeftStruggleMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());

		deps.resultsUI.UsedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView(), ctx.currentMove->GetName());

		ctx.attackingPokemon->SetLastUsedMove(ctx.currentMove);

		if (DefendingPokemonIsFainted(ctx, deps.resultsUI))
		{
			return;
		}

		deps.calculations.CalculateTypeEffectiveness(ctx, *ctx.currentMove, *ctx.defendingPokemon);

		if (ctx.flags.currentEffectiveness == BattleStateFlags::Effectiveness::No)
		{
			deps.resultsUI.DisplayEffectivenessTextDialog(ctx.defendingPlayer->GetPlayerNameView(), ctx.defendingPokemon->GetNameView(), ToEffectivenessText(ctx.flags.currentEffectiveness));
			return;
		}

		ctx.flags.hit = !ctx.defendingPokemon->IsSemiInvulnerable();

		if (!ctx.flags.hit)
		{
			deps.resultsUI.DisplayAttackMissedTextDialog(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());
			return;
		}

		DamageRoutine(deps);

		deps.statusProcessor.CheckSubstituteCondition(ctx.defendingPlayer, ctx.defendingPokemon);
		deps.statusProcessor.CheckFaintCondition(*ctx.attackingPlayer, *ctx.defendingPlayer, *ctx.attackingPokemon, *ctx.defendingPokemon);

		unsigned int recoilDamage = (ctx.attackingPokemon->GetMaxHP() + 2) / 4;

		unsigned int finalDamage = std::max(1u, recoilDamage);

		ctx.attackingPokemon->DamageCurrentHP(finalDamage);

		deps.resultsUI.DisplayRecoilMsg(ctx.attackingPlayer->GetPlayerNameView(), ctx.attackingPokemon->GetNameView());

		deps.statusProcessor.CheckFaintCondition(*ctx.defendingPlayer, *ctx.attackingPlayer, *ctx.defendingPokemon, *ctx.attackingPokemon);
	}
}