#pragma once

struct BattleContext;
class Player;

class WinChecker
{
public:
    WinChecker(BattleContext& context);

    bool CheckWinCondition(Player& sourcePlayer, Player& targetPlayer);

private:
    BattleContext& m_context;

};