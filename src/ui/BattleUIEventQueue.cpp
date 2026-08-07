#include <format>
#include <utility>
#include <string>
#include <string_view>
#include <variant>

#include "BattleUIEventQueue.h"

#include "BattleText.h"
#include "BattleEvents.h"
#include "interfaces/IOutputTarget.h"

void BattleUIEventQueue::PushEvent(QueuedUIEvent event)
{
	m_queue.push(std::move(event));
}

void BattleUIEventQueue::ProcessNextEvent(IOutputTarget& target)
{
	if (m_queue.empty())
	{
		return;
	}

    while (!m_queue.empty())
    {
        QueuedUIEvent currentEvent = std::move(m_queue.front());
        m_queue.pop();

        std::string formattedText{};

        switch (currentEvent.event)
        {
                // --- NO ARGUMENTS ---
            case BattleEvents::Noop:
            case BattleEvents::CriticalHit:
            case BattleEvents::Failed:
            case BattleEvents::Splash:
            case BattleEvents::NotEnoughHPSubstitute:
            case BattleEvents::Haze:
            case BattleEvents::HurtItselfConfusion:
            case BattleEvents::NewLine:
            case BattleEvents::NotVery:
            case BattleEvents::Super:
            case BattleEvents::OHKO:
            {
                formattedText = BattleText::GetFormat(currentEvent.event);
                break;
            }

            // --- SINGLE INT ARGUMENTS ---
            case BattleEvents::DirectDamage:
            case BattleEvents::BoundNotFound:
            {
                auto fmtStr = BattleText::GetFormat(currentEvent.event);
                formattedText = std::vformat(fmtStr,
                    std::make_format_args(std::get<unsigned int>(currentEvent.args[0])));
                break;
            }

            // --- SINGLE STRING ARGUMENTS ---
            case BattleEvents::EnemySwitch:
            case BattleEvents::Mist:
            case BattleEvents::LightScreen:
            case BattleEvents::Reflect:
            case BattleEvents::WokenUp:
            case BattleEvents::IsAsleep:
            case BattleEvents::FrozenSolid:
            case BattleEvents::Thawed:
            case BattleEvents::CantMoveParalysis:
            case BattleEvents::NoLongerProtectedMist:
            case BattleEvents::FlyCharge:
            case BattleEvents::DigCharge:
            {
                auto fmtStr = BattleText::GetFormat(currentEvent.event);
                formattedText = std::vformat(fmtStr,
                    std::make_format_args(std::get<std::string_view>(currentEvent.args[0])));
                break;
            }

            // --- TWO STRING ARGUMENTS ---
            case BattleEvents::No:
            case BattleEvents::AttackMissed:
            case BattleEvents::AttackAvoided:
            case BattleEvents::SubstituteDamage:
            case BattleEvents::NoMovesLeftStruggle:
            case BattleEvents::RazorWindCharge:
            case BattleEvents::SolarBeamCharge:
            case BattleEvents::SkullBashCharge:
            case BattleEvents::SkyAttackCharge:
            case BattleEvents::JumpKickCrash:
            case BattleEvents::Recoil:
            case BattleEvents::EnergyDrained:
            case BattleEvents::RestoredHP:
            case BattleEvents::HPFull:
            case BattleEvents::Rest:
            case BattleEvents::BurnSuccess:
            case BattleEvents::FreezeSuccess:
            case BattleEvents::ParalyzeSuccess:
            case BattleEvents::PoisonSuccess:
            case BattleEvents::BadlyPoisonSuccess:
            case BattleEvents::SleepSuccess:
            case BattleEvents::BecameConfused:
            case BattleEvents::AlreadyPoisoned:
            case BattleEvents::AlreadyParalyzed:
            case BattleEvents::AlreadyAsleep:
            case BattleEvents::StatusImmune:
            case BattleEvents::AlreadyHasSubstitute:
            case BattleEvents::PutInSubstitute:
            case BattleEvents::FocusEnergy:
            case BattleEvents::ProtectedByMist:
            case BattleEvents::BideUnleashed:
            case BattleEvents::BideStoringEnergy:
            case BattleEvents::SwitchOutNoFaint:
            case BattleEvents::SwitchOut:
            case BattleEvents::PlayerChooses:
            case BattleEvents::FellAsleep:
            case BattleEvents::NoLongerConfused:
            case BattleEvents::IsConfused:
            case BattleEvents::Flinch:
            case BattleEvents::Recharge:
            case BattleEvents::Seeded:
            case BattleEvents::LeechSeedSapped:
            case BattleEvents::RampageConfusion:
            case BattleEvents::RageStarted:
            case BattleEvents::SubstituteFaded:
            case BattleEvents::Fainted:
            case BattleEvents::FieldEffectFaded:
            {
                auto fmtStr = BattleText::GetFormat(currentEvent.event);
                    formattedText = std::vformat(fmtStr,
                    std::make_format_args(std::get<std::string_view>(currentEvent.args[0]),
                        std::get<std::string_view>(currentEvent.args[1])
                    ));
                break;
            }

            // --- TEXT MIXED TYPE ARGUMENTS ---
            case BattleEvents::MultiHit:
            {
                auto fmtStr = BattleText::GetFormat(currentEvent.event);
                formattedText = std::vformat(fmtStr,
                    std::make_format_args(std::get<std::string_view>(currentEvent.args[0]),
                                          std::get<int>(currentEvent.args[1])
                    ));
                break;
            }

            // --- THREE STRING ARGUMENTS ---
            case BattleEvents::UsedMove:
            case BattleEvents::StatRaised2:
            case BattleEvents::StatRaised1:
            case BattleEvents::StatRaiseFail:
            case BattleEvents::StatLowered2:
            case BattleEvents::StatLowered1:
            case BattleEvents::StatLoweredFail:
            case BattleEvents::LearnedMimicMove:
            case BattleEvents::Transform:
            case BattleEvents::Metronome:
            case BattleEvents::Conversion:
            case BattleEvents::MoveDisabled:
            case BattleEvents::DamagedByStatusPostTurn:
            case BattleEvents::HurtByBound:
            case BattleEvents::FreedFromBound:
            case BattleEvents::MoveIsDisabled:
            case BattleEvents::MoveNoLongerDisabled:
            {
                auto fmtStr = BattleText::GetFormat(currentEvent.event);
                formattedText = std::vformat(fmtStr,
                    std::make_format_args(std::get<std::string_view>(currentEvent.args[0]),
                        std::get<std::string_view>(currentEvent.args[1]),
                        std::get<std::string_view>(currentEvent.args[2])
                    ));
                break;
            }

            // --- Partial Trap moves ---
            case BattleEvents::Bind:
            case BattleEvents::Wrap:
            {
                auto fmtStr = BattleText::GetFormat(currentEvent.event);
                formattedText = std::vformat(fmtStr,
                    std::make_format_args(std::get<std::string_view>(currentEvent.args[0]),
                        std::get<std::string_view>(currentEvent.args[1]),
                        std::get<std::string_view>(currentEvent.args[2]),
                        std::get<std::string_view>(currentEvent.args[3])
                    ));
                break;
            }

            case BattleEvents::FireSpin:
            {
                auto fmtStr = BattleText::GetFormat(currentEvent.event);
                formattedText = std::vformat(fmtStr,
                    std::make_format_args(std::get<std::string_view>(currentEvent.args[0]),
                        std::get<std::string_view>(currentEvent.args[1])
                    ));
                break;
            }

            case BattleEvents::Clamp:
            {
                auto fmtStr = BattleText::GetFormat(currentEvent.event);
                formattedText = std::vformat(fmtStr,
                    std::make_format_args(std::get<std::string_view>(currentEvent.args[0]),
                        std::get<std::string_view>(currentEvent.args[1]),
                        std::get<std::string_view>(currentEvent.args[2]),
                        std::get<std::string_view>(currentEvent.args[3])
                    ));
                break;
            }
        }

        target.Emit(std::move(formattedText));
    }
}