#pragma once

class BattlePokemon;
class IMoveResultsUI;
class Player;
struct BattleContext;

class SwitchExecutor
{
public:
	SwitchExecutor(BattleContext&, IMoveResultsUI&);

	void ExecuteSwitch(Player& player, BattlePokemon*& pokemon);

private:
	BattleContext& m_context;
	IMoveResultsUI& m_moveResultsUI;
};