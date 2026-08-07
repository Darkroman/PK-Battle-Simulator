#pragma once

#include <string_view>

#include "../EffectivenessText.h"

enum class MoveID : unsigned int;

class IMoveResultsUI
{
public:
	virtual ~IMoveResultsUI() = default;

	// Basic Move Results
	virtual void DisplayNoopMsg() const = 0;

	virtual void UsedTextDialog(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayCritTextDialog(bool) const = 0;

	virtual void DisplayOHKOTextDialog() const = 0;

	virtual void DisplayEffectivenessTextDialog(std::string_view, std::string_view, EffectivenessText) const = 0;

	virtual void DisplayAttackMissedTextDialog(std::string_view, std::string_view) const = 0;

	virtual void DisplayAttackAvoidedTextDialog(std::string_view, std::string_view) const = 0;

	virtual void DisplayFailedTextDialog() const = 0;

	virtual void DisplayDirectDamageInflictedMsg(unsigned int) const = 0;

	virtual void DisplaySubstituteDamageTextDialog(std::string_view, std::string_view, int, bool, bool) const = 0;

	// Specialized Results
	virtual void DisplayMultiAttackMsg(std::string_view, int) const = 0;

	virtual void DisplayEnemySwitchMsg(std::string_view) const = 0;

	virtual void BoundMoveText(std::string_view, std::string_view, std::string_view, std::string_view, MoveID) const = 0;

	virtual void DisplaySplashMsg() const = 0;

	virtual void DisplayNoMovesLeftStruggleMsg(std::string_view, std::string_view) const = 0;

	// Charging
	virtual void DisplayRazorWindChargeMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayFlyChargeMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplaySolarBeamChargeMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayDigChargeMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplaySkullBashChargeMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplaySkyAttackChargeMsg(std::string_view, std::string_view) const = 0;

	// Recoil
	virtual void DisplayJumpKickCrashMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayRecoilMsg(std::string_view, std::string_view) const = 0;

	// HP Results
	virtual void DisplayEnergyDrainedMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayRecoveredHPRestoredMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayHPFullMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayRestMsg(std::string_view, std::string_view) const = 0;

	// Status
	virtual void DisplayBurnSuccess(std::string_view, std::string_view) const = 0;

	virtual void DisplayFreezeSuccess(std::string_view, std::string_view) const = 0;

	virtual void DisplayParalyzeSuccess(std::string_view, std::string_view) const = 0;

	virtual void DisplayPoisonSuccess(std::string_view, std::string_view) const = 0;

	virtual void DisplayBadlyPoisonSuccess(std::string_view, std::string_view) const = 0;

	virtual void DisplaySleepSuccess(std::string_view, std::string_view) const = 0;

	virtual void DisplayBecameConfuseMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayAlreadyPoisonedMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayAlreadyParalyzedMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayAlreadyAsleepMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayDoesntAffectMsg(std::string_view, std::string_view) const = 0;

	// Stat Stage
	virtual void DisplayStatRaised2Msg(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayStatRaised1Msg(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayStatRaiseFailMsg(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayStatLowered2Msg(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayStatLowered1Msg(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayStatLoweredFailMsg(std::string_view, std::string_view, std::string_view) const = 0;

	// Volatile Status
	virtual void DisplayFocusEnergyMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayMistMsg(std::string_view) const = 0;

	virtual void DisplayProtectedByMistMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplaySeededMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayLightScreenMsg(std::string_view) const = 0;

	virtual void DisplayHazeMsg() const = 0;

	virtual void DisplayReflectMsg(std::string_view) const = 0;

	virtual void DisplayRageStartedMsg(std::string_view, std::string_view) const = 0;

	// Substitute
	virtual void DisplayAlreadyHasSubstituteMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayNotEnoughHPSubstituteMsg() const = 0;

	virtual void DisplayPutInSubstituteMsg(std::string_view, std::string_view) const = 0;

	// Copy
	virtual void DisplayLearnedMimicMoveMsg(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayTransformMsg(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayMetronomeMsg(std::string_view, std::string_view, std::string_view) const = 0;

	virtual void DisplayConversionMsg(std::string_view, std::string_view, std::string_view) const = 0;

	// Bide
	virtual void DisplayBideUnleashedMsg(std::string_view, std::string_view) const = 0;

	virtual void DisplayBideStoringEnergyMsg(std::string_view, std::string_view) const = 0;

	// Disabled
	virtual void DisplayMoveDisabledMsg(std::string_view, std::string_view, std::string_view) const = 0;

	// Switching
	virtual void SwitchOutNoFaintMsg(std::string_view playerName, std::string_view pokemonName) const = 0;

	virtual void SwitchOutMsg(std::string_view, std::string_view) const = 0;

	virtual void PlayerChoosesMsg(std::string_view, std::string_view) const = 0;
};