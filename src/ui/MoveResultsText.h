#pragma once

#include <string_view>

#include "interfaces/IMoveResultsUI.h"

class IOutputTarget;
enum class MoveID;
enum class EffectivenessText;

class MoveResultsText : public IMoveResultsUI
{
public:
	MoveResultsText(IOutputTarget& target)
		: m_target(target) {
	}

	// Basic Move Results
	void DisplayNoopMsg() const override;

	void UsedTextDialog(std::string_view, std::string_view, std::string_view) const override;

	void DisplayCritTextDialog(bool) const override;

	void DisplayOHKOTextDialog() const override;

	void DisplayEffectivenessTextDialog(std::string_view, std::string_view, EffectivenessText) const override;

	void DisplayAttackMissedTextDialog(std::string_view, std::string_view) const override;

	void DisplayAttackAvoidedTextDialog(std::string_view, std::string_view) const override;

	void DisplayFailedTextDialog() const override;

	void DisplayDirectDamageInflictedMsg(unsigned int) const override;

	void DisplaySubstituteDamageTextDialog(std::string_view, std::string_view, int, bool, bool) const override;

	// Specialized Results
	void DisplayMultiAttackMsg(std::string_view, int) const override;

	void DisplayEnemySwitchMsg(std::string_view) const override;

	void BoundMoveText(std::string_view, std::string_view, std::string_view, std::string_view, MoveID) const override;

	void DisplaySplashMsg() const override;

	void DisplayNoMovesLeftStruggleMsg(std::string_view, std::string_view) const override;

	// Charging
	void DisplayRazorWindChargeMsg(std::string_view, std::string_view) const override;

	void DisplayFlyChargeMsg(std::string_view, std::string_view) const override;

	void DisplaySolarBeamChargeMsg(std::string_view, std::string_view) const override;

	void DisplayDigChargeMsg(std::string_view, std::string_view) const override;

	void DisplaySkullBashChargeMsg(std::string_view, std::string_view) const override;

	void DisplaySkyAttackChargeMsg(std::string_view, std::string_view) const override;

	// Recoil
	void DisplayJumpKickCrashMsg(std::string_view, std::string_view) const override;

	void DisplayRecoilMsg(std::string_view, std::string_view) const override;

	// HP Results
	void DisplayEnergyDrainedMsg(std::string_view, std::string_view) const override;

	void DisplayRecoveredHPRestoredMsg(std::string_view, std::string_view) const override;

	void DisplayHPFullMsg(std::string_view, std::string_view) const override;

	void DisplayRestMsg(std::string_view, std::string_view) const override;

	// Status
	void DisplayBurnSuccess(std::string_view, std::string_view) const override;

	void DisplayFreezeSuccess(std::string_view, std::string_view) const override;

	void DisplayParalyzeSuccess(std::string_view, std::string_view) const override;

	void DisplayPoisonSuccess(std::string_view, std::string_view) const override;

	void DisplayBadlyPoisonSuccess(std::string_view, std::string_view) const override;

	void DisplaySleepSuccess(std::string_view, std::string_view) const override;

	void DisplayBecameConfuseMsg(std::string_view, std::string_view) const override;

	void DisplayAlreadyPoisonedMsg(std::string_view, std::string_view) const override;

	void DisplayAlreadyParalyzedMsg(std::string_view, std::string_view) const override;

	void DisplayAlreadyAsleepMsg(std::string_view, std::string_view) const override;

	void DisplayDoesntAffectMsg(std::string_view, std::string_view) const override;

	// Stat Stage
	void DisplayStatRaised2Msg(std::string_view, std::string_view, std::string_view) const override;

	void DisplayStatRaised1Msg(std::string_view, std::string_view, std::string_view) const override;

	void DisplayStatRaiseFailMsg(std::string_view, std::string_view, std::string_view) const override;

	void DisplayStatLowered2Msg(std::string_view, std::string_view, std::string_view) const override;

	void DisplayStatLowered1Msg(std::string_view, std::string_view, std::string_view) const override;

	void DisplayStatLoweredFailMsg(std::string_view, std::string_view, std::string_view) const override;

	// Volatile Status
	void DisplayFocusEnergyMsg(std::string_view, std::string_view) const override;

	void DisplayMistMsg(std::string_view) const override;

	void DisplayProtectedByMistMsg(std::string_view, std::string_view) const override;

	void DisplaySeededMsg(std::string_view, std::string_view) const override;

	void DisplayLightScreenMsg(std::string_view) const override;

	void DisplayHazeMsg() const override;

	void DisplayReflectMsg(std::string_view) const override;

	void DisplayRageStartedMsg(std::string_view, std::string_view) const override;

	// Substitute
	void DisplayAlreadyHasSubstituteMsg(std::string_view, std::string_view) const override;

	void DisplayNotEnoughHPSubstituteMsg() const override;

	void DisplayPutInSubstituteMsg(std::string_view, std::string_view) const override;

	// Copy
	void DisplayLearnedMimicMoveMsg(std::string_view, std::string_view, std::string_view) const override;

	void DisplayTransformMsg(std::string_view, std::string_view, std::string_view) const override;

	void DisplayMetronomeMsg(std::string_view, std::string_view, std::string_view) const override;

	void DisplayConversionMsg(std::string_view, std::string_view, std::string_view) const override;

	// Bide
	void DisplayBideUnleashedMsg(std::string_view, std::string_view) const override;

	void DisplayBideStoringEnergyMsg(std::string_view, std::string_view) const override;

	// Disabled
	void DisplayMoveDisabledMsg(std::string_view, std::string_view, std::string_view) const override;

	// Switching
	void SwitchOutNoFaintMsg(std::string_view playerName, std::string_view pokemonName) const override;

	void SwitchOutMsg(std::string_view, std::string_view) const override;

	void PlayerChoosesMsg(std::string_view, std::string_view) const override;

private:
	IOutputTarget& m_target;

};