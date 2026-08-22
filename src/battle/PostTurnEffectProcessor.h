#pragma once

class BattleCalculations;
class BattlePokemon;
class IStatusEffectUI;
class Player;
class StatusEffectProcessor;
class SwitchExecutor;
class WinChecker;
struct BattleContext;

class PostTurnEffectProcessor
{
public:
    explicit PostTurnEffectProcessor(BattleContext&, BattleCalculations&, IStatusEffectUI&, StatusEffectProcessor&, WinChecker&, SwitchExecutor&);

    bool ProcessAllPostTurnEffects();
    void DeterminePostFaintSwitchOrder();
    void ProcessPostKOSwitches();

private:
    bool CheckSeededStatuses();
    bool CheckDamagingStatuses();
    void BurnedStatus(const Player& player, BattlePokemon& pokemon);
    void PoisonedStatus(const Player& player, BattlePokemon& pokemon);
    void BadlyPoisonedStatus(const Player& player, BattlePokemon& pokemon);
    bool CheckBoundStatuses();
    void CheckDisabledStatus();
    void CheckFieldEffects();

    void ProcessPostKOSwitch(Player& sourcePlayer, Player& targetPlayer, const BattlePokemon& sourcePokemon, const BattlePokemon& targetPokemon);

    BattleContext& m_context;
    BattleCalculations& m_calculations;
    IStatusEffectUI& m_statusEffectUI;
    StatusEffectProcessor& m_statusProcessor;
    WinChecker& m_winChecker;
    SwitchExecutor& m_switchExecutor;
};