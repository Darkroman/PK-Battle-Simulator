#pragma once

#include <string_view>

#include "BattleEvents.h"

namespace BattleText
{
    // --- NO ARGUMENTS ---
    inline constexpr std::string_view Noop = "This isn't implemented yet!";

    inline constexpr std::string_view CriticalHit = "Critical hit!";

    inline constexpr std::string_view OHKO = "It was a one-hit KO!";

    inline constexpr std::string_view Failed = "But it failed!";

    inline constexpr std::string_view Splash = "But nothing happened!";

    inline constexpr std::string_view NotEnoughHPSubstitute = "But it does not have enough HP left to make a substitute!";

    inline constexpr std::string_view Haze = "All stat changes were eliminated!";

    inline constexpr std::string_view HurtItselfConfusion = "It hurt itself in its confusion!";

    inline constexpr std::string_view NewLine = "";

    inline constexpr std::string_view NotVery = "It was not very effective...";
    inline constexpr std::string_view Super = "It was super effective!";

    // --- SINGLE UNSIGNED INT ARGUMENTS ---
    inline constexpr std::string_view DirectDamage = "{} damage inflicted.";
    
    // --- SINGLE SIZE_T ARGUMENTS ---
    inline constexpr std::string_view BoundNotFound = "Text not found for move index number {}";

    // --- SINGLE STRING ARGUMENTS ---
    inline constexpr std::string_view EnemySwitch = "{} was dragged out!";

    inline constexpr std::string_view Mist = "{}'s team became shrouded in mist!";
    inline constexpr std::string_view LightScreen = "Light screen made {}'s team stronger against special moves!";
    inline constexpr std::string_view Reflect = "Reflect made {}'s team stronger against physical moves!";

    inline constexpr std::string_view WokenUp = "{} has woken up!";
    inline constexpr std::string_view IsAsleep = "{} is sleeping.";

    inline constexpr std::string_view FrozenSolid = "{} is frozen solid!";
    inline constexpr std::string_view Thawed = "{} thawed out!";

    inline constexpr std::string_view CantMoveParalysis = "{} couldn't move because it's paralyzed!";

    inline constexpr std::string_view NoLongerProtectedMist = "{}'s team is no longer protected by mist!";

    inline constexpr std::string_view FlyCharge = "{} flew up high in the sky!";
    inline constexpr std::string_view DigCharge = "{} burrowed its way under the ground!";

    // --- TWO STRING ARGUMENTS ---
    inline constexpr std::string_view No = "It doesn't affect {}'s {}...";
    inline constexpr std::string_view AttackMissed = "{}'s {}'s attack missed!";
    inline constexpr std::string_view AttackAvoided = "{}'s {} avoided the attack!";

    inline constexpr std::string_view SubstituteDamage = "The substitute took damage for {}'s {}!";

    inline constexpr std::string_view NoMovesLeftStruggle = "{}'s {} has no moves left!";

    inline constexpr std::string_view RazorWindCharge = "{}'s {} made a whirlwind!";
    inline constexpr std::string_view SolarBeamCharge = "{}'s {} absorbed light!";
    inline constexpr std::string_view SkullBashCharge = "{}'s {} tucked in its head!";
    inline constexpr std::string_view SkyAttackCharge = "{}'s {} became cloaked in a harsh light!";

    inline constexpr std::string_view JumpKickCrash = "{}'s {} kept going and crashed!";
    inline constexpr std::string_view Recoil = "{}'s {} was damaged by the recoil!";

    inline constexpr std::string_view EnergyDrained = "{}'s {} had its energy drained!";
    inline constexpr std::string_view RestoredHP = "{}'s {} had its HP restored!";
    inline constexpr std::string_view HPFull = "{}'s {}'s HP is full!";
    inline constexpr std::string_view Rest = "{}'s {} slept and became healthy!";

    inline constexpr std::string_view BurnSuccess = "{}'s {} was burned!";
    inline constexpr std::string_view FreezeSuccess = "{}'s {} was frozen solid!";
    inline constexpr std::string_view ParalyzeSuccess = "{}'s {} is paralyzed! It may be unable to move!";
    inline constexpr std::string_view PoisonSuccess = "{}'s {} was poisoned!";
    inline constexpr std::string_view BadlyPoisonSuccess = "{}'s {} was badly poisoned!";
    inline constexpr std::string_view SleepSuccess = "{}'s {} fell asleep!";

    inline constexpr std::string_view BecameConfused = "{}'s {} became confused!";
    inline constexpr std::string_view AlreadyPoisoned = "{}'s {} is already poisoned!";
    inline constexpr std::string_view AlreadyParalyzed = "{}'s {} is already paralyzed!";
    inline constexpr std::string_view AlreadyAsleep = "{}'s {} is already asleep!";
    inline constexpr std::string_view StatusImmune = "It doesn't affect {}'s {}...";

    inline constexpr std::string_view AlreadyHasSubstitute = "{}'s {} already has a substitute!";
    inline constexpr std::string_view PutInSubstitute = "{}'s {} put in a substitute!";

    inline constexpr std::string_view FocusEnergy = "{}'s {} is getting pumped!";

    inline constexpr std::string_view ProtectedByMist = "{}'s {} is protected by the mist!";

    inline constexpr std::string_view BideUnleashed = "{}'s {} unleashed its energy!";
    inline constexpr std::string_view BideStoringEnergy = "{}'s {} is storing energy!";

    inline constexpr std::string_view SwitchOutNoFaint = "{} switches out {}.";
    inline constexpr std::string_view SwitchOut = "\n{} switches out {}.";
    inline constexpr std::string_view PlayerChooses = "{} chooses {}.";

    inline constexpr std::string_view FellAsleep = "{}'s {} fell asleep!";
    inline constexpr std::string_view NoLongerConfused = "{}'s {} is no longer confused!";
    inline constexpr std::string_view IsConfused = "{}'s {} is confused!";
    inline constexpr std::string_view Flinch = "{}'s {} flinched and couldn't move!";
    inline constexpr std::string_view Recharge = "{}'s {} must recharge!";

    inline constexpr std::string_view Seeded = "{}'s {} was seeded!";
    inline constexpr std::string_view LeechSeedSapped = "{}'s {}'s health is sapped by Leech Seed.";

    inline constexpr std::string_view RampageConfusion = "{}'s {} became confused due to fatigue!";
    inline constexpr std::string_view RageStarted = "(Rage started on {}'s {})";

    inline constexpr std::string_view SubstituteFaded = "{}'s {}'s substitute faded!";
    inline constexpr std::string_view Fainted = "{}'s {} has fainted!";

    inline constexpr std::string_view FieldEffectFaded = "{}'s team's {} wore off!";

    // --- TEXT MIXED TYPE ARGUMENTS ---
    inline constexpr std::string_view MultiHit = "{} was hit {} times!";

    // --- THREE STRING ARGUMENTS ---
    inline constexpr std::string_view UsedMove = "{}'s {} used {}";

    inline constexpr std::string_view StatRaised2 = "{}'s {}'s {} rose sharply!";
    inline constexpr std::string_view StatRaised1 = "{}'s {}'s {} rose!";
    inline constexpr std::string_view StatRaiseFail = "{}'s {} can't raise its {} any higher!";

    inline constexpr std::string_view StatLowered2 = "{}'s {}'s {} fell harshly!";
    inline constexpr std::string_view StatLowered1 = "{}'s {}'s {} fell!";
    inline constexpr std::string_view StatLoweredFail = "{}'s {}'s {} won't go any lower!";

    inline constexpr std::string_view LearnedMimicMove = "{}'s {} learned {}!";

    inline constexpr std::string_view Transform = "{}'s {} transformed into {}!";

    inline constexpr std::string_view Metronome = "Waggling its finger let {}'s {} use {}";

    inline constexpr std::string_view Conversion = "{}'s {}'s type changed to {}!";

    inline constexpr std::string_view MoveDisabled = "{}'s {}'s {} was disabled!";

    inline constexpr std::string_view DamagedByStatusPostTurn = "{}'s {} was damaged by {}.";

    inline constexpr std::string_view HurtByBound = "{}'s {} was hurt by {}!";
    inline constexpr std::string_view FreedFromBound = "{}'s {} was freed from {}!";

    inline constexpr std::string_view MoveIsDisabled = "{}'s {}'s {} is disabled!";
    inline constexpr std::string_view MoveNoLongerDisabled = "{}'s {}'s {} is no longer disabled!";

    // --- FOUR STRING ARGUMENTS ---
    inline constexpr std::string_view Bind = "{}'s {} was squeezed by {}'s {}!";
    inline constexpr std::string_view Wrap = "{}'s {} was wrapped by {}'s {}!";
    inline constexpr std::string_view FireSpin = "{}'s {} became trapped in the fiery vortex!";
    inline constexpr std::string_view Clamp = "{}'s {} clamped down on {}'s {}!";

    constexpr std::string_view GetFormat(BattleEvents ev)
    {
        switch (ev)
        {
            case BattleEvents::Noop:                    return Noop;
            case BattleEvents::CriticalHit:             return CriticalHit;
            case BattleEvents::OHKO:                    return OHKO;
            case BattleEvents::Failed:                  return Failed;
            case BattleEvents::BoundNotFound:           return BoundNotFound;
            case BattleEvents::Splash:                  return Splash;
            case BattleEvents::NotEnoughHPSubstitute:   return NotEnoughHPSubstitute;
            case BattleEvents::Haze:                    return Haze;
            case BattleEvents::HurtItselfConfusion:     return HurtItselfConfusion;
            case BattleEvents::NewLine:                 return NewLine;
            case BattleEvents::NotVery:                 return NotVery;
            case BattleEvents::Super:                   return Super;
            case BattleEvents::DirectDamage:            return DirectDamage;
            case BattleEvents::EnemySwitch:             return EnemySwitch;
            case BattleEvents::Mist:                    return Mist;
            case BattleEvents::LightScreen:             return LightScreen;
            case BattleEvents::Reflect:                 return Reflect;
            case BattleEvents::WokenUp:                 return WokenUp;
            case BattleEvents::IsAsleep:                return IsAsleep;
            case BattleEvents::FrozenSolid:             return FrozenSolid;
            case BattleEvents::Thawed:                  return Thawed;
            case BattleEvents::CantMoveParalysis:       return CantMoveParalysis;
            case BattleEvents::NoLongerProtectedMist:   return NoLongerProtectedMist;
            case BattleEvents::FlyCharge:               return FlyCharge;
            case BattleEvents::DigCharge:               return DigCharge;
            case BattleEvents::No:                      return No;
            case BattleEvents::AttackMissed:            return AttackMissed;
            case BattleEvents::AttackAvoided:           return AttackAvoided;
            case BattleEvents::SubstituteDamage:        return SubstituteDamage;
            case BattleEvents::NoMovesLeftStruggle:     return NoMovesLeftStruggle;
            case BattleEvents::RazorWindCharge:         return RazorWindCharge;
            case BattleEvents::SolarBeamCharge:         return SolarBeamCharge;
            case BattleEvents::SkullBashCharge:         return SkullBashCharge;
            case BattleEvents::SkyAttackCharge:         return SkyAttackCharge;
            case BattleEvents::JumpKickCrash:           return JumpKickCrash;
            case BattleEvents::Recoil:                  return Recoil;
            case BattleEvents::EnergyDrained:           return EnergyDrained;
            case BattleEvents::RestoredHP:              return RestoredHP;
            case BattleEvents::HPFull:                  return HPFull;
            case BattleEvents::Rest:                    return Rest;
            case BattleEvents::BurnSuccess:             return BurnSuccess;
            case BattleEvents::FreezeSuccess:           return FreezeSuccess;
            case BattleEvents::ParalyzeSuccess:         return ParalyzeSuccess;
            case BattleEvents::PoisonSuccess:           return PoisonSuccess;
            case BattleEvents::BadlyPoisonSuccess:      return BadlyPoisonSuccess;
            case BattleEvents::SleepSuccess:            return SleepSuccess;
            case BattleEvents::BecameConfused:          return BecameConfused;
            case BattleEvents::AlreadyPoisoned:         return AlreadyPoisoned;
            case BattleEvents::AlreadyParalyzed:        return AlreadyParalyzed;
            case BattleEvents::AlreadyAsleep:           return AlreadyAsleep;
            case BattleEvents::StatusImmune:            return StatusImmune;
            case BattleEvents::AlreadyHasSubstitute:    return AlreadyHasSubstitute;
            case BattleEvents::PutInSubstitute:         return PutInSubstitute;
            case BattleEvents::FocusEnergy:             return FocusEnergy;
            case BattleEvents::ProtectedByMist:         return ProtectedByMist;
            case BattleEvents::BideUnleashed:           return BideUnleashed;
            case BattleEvents::BideStoringEnergy:       return BideStoringEnergy;
            case BattleEvents::SwitchOutNoFaint:        return SwitchOutNoFaint;
            case BattleEvents::SwitchOut:               return SwitchOut;
            case BattleEvents::PlayerChooses:           return PlayerChooses;
            case BattleEvents::FellAsleep:              return FellAsleep;
            case BattleEvents::NoLongerConfused:        return NoLongerConfused;
            case BattleEvents::IsConfused:              return IsConfused;
            case BattleEvents::Flinch:                  return Flinch;
            case BattleEvents::Recharge:                return Recharge;
            case BattleEvents::Seeded:                  return Seeded;
            case BattleEvents::LeechSeedSapped:         return LeechSeedSapped;
            case BattleEvents::RampageConfusion:        return RampageConfusion;
            case BattleEvents::RageStarted:             return RageStarted;
            case BattleEvents::SubstituteFaded:         return SubstituteFaded;
            case BattleEvents::Fainted:                 return Fainted;
            case BattleEvents::FieldEffectFaded:        return FieldEffectFaded;
            case BattleEvents::MultiHit:                return MultiHit;
            case BattleEvents::UsedMove:                return UsedMove;
            case BattleEvents::StatRaised2:             return StatRaised2;
            case BattleEvents::StatRaised1:             return StatRaised1;
            case BattleEvents::StatRaiseFail:           return StatRaiseFail;
            case BattleEvents::StatLowered2:            return StatLowered2;
            case BattleEvents::StatLowered1:            return StatLowered1;
            case BattleEvents::StatLoweredFail:         return StatLoweredFail;
            case BattleEvents::LearnedMimicMove:        return LearnedMimicMove;
            case BattleEvents::Transform:               return Transform;
            case BattleEvents::Metronome:               return Metronome;
            case BattleEvents::Conversion:              return Conversion;
            case BattleEvents::MoveDisabled:            return MoveDisabled;
            case BattleEvents::DamagedByStatusPostTurn: return DamagedByStatusPostTurn;
            case BattleEvents::HurtByBound:             return HurtByBound;
            case BattleEvents::FreedFromBound:          return FreedFromBound;
            case BattleEvents::MoveIsDisabled:          return MoveIsDisabled;
            case BattleEvents::MoveNoLongerDisabled:    return MoveNoLongerDisabled;
            case BattleEvents::Bind:                    return Bind;
            case BattleEvents::Wrap:                    return Wrap;
            case BattleEvents::FireSpin:                return FireSpin;
            case BattleEvents::Clamp:                   return Clamp;
        
            default:                                    return "";
        }
    }
}