#pragma once
#include "BattleSystem.h"

class IMoveEffects : public BattleSystem
{
public:
	virtual void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) = 0;
};

class MoveEffectsFactory
{
public:
	std::unique_ptr<IMoveEffects> Call(MoveEffect);
};

class Noop : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class NormalHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class IncreasedCritical : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class MultiAttack : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class BurnHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class FreezeHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class ParalyzeHit10 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class OHKO : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class RazorWind : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class AttackUp2 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Gust : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class MakeEnemySwitch : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Fly : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Bound : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Stomp : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class DoubleHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class JumpKick : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class FlinchHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class AccuracyDown : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class BodySlam : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class RecoilQuarter : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Thrash : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class RecoilThird : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class DefenseDown : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class PoisonHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Twineedle : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class AttackDown : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class BypassSubSleep : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Confuse : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SonicBoom : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Disable : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SpecialDefenseDownHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Mist : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class ConfuseHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SpeedDownHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class AttackDownHit : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class RechargeAttack : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class LowKick : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Counter : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SeismicToss : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Leech : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class LeechSeed : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Growth : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SolarBeam : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class PoisonPowder : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class StunSpore : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SleepPowder : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SpeedDown2 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class DragonRage : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Paralyze : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class ParalyzeHit30 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Earthquake : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Dig : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Toxic : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SleepMove : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class AttackUp : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SpeedUp2 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Rage : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Teleport : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class NightShade : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Mimic : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class DefenseDown2 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class EvasionUp : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class HealHalfHP : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class DefenseUp : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Minimize : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class DefenseUp2 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class LightScreen : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Haze : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Reflect : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class FocusEnergy : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Bide : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Metronome : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class MirrorMove : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Explosion : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class PoisonHit40 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class FlinchHit10 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class FlinchHit20 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Swift : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SkullBash : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SpecialDefenseUp2 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class DreamEater : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class PoisonGas : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SkyAttack : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Transform : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class ConfuseHit20 : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Psywave : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Splash : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Rest : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Conversion : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class TriAttack : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class SuperFang : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Substitute : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};

class Struggle : public IMoveEffects
{
public:
	void DoMove(Player*, Player*, BattlePokemon::pokemonMove*, BattlePokemon*, BattlePokemon*, BattleSystem&) override;
};
