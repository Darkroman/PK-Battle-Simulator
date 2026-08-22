#pragma once

class Player;
struct BattleContext;

class WinChecker
{
public:
    WinChecker(BattleContext& context);

    bool CheckWinCondition(Player& sourcePlayer, Player& targetPlayer);

private:
    BattleContext& m_context;

};