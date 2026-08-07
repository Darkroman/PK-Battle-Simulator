#pragma once

#include <optional>
#include <vector>
#include <memory>

#include "entities/Player.h"
#include "battle/BattleContext.h"
#include "battle/RandomEngine.h"
#include "ui/interfaces/IOutputTarget.h"
#include "ui/interfaces/IBattleAnnouncerUI.h"
#include "ui/interfaces/IMoveResultsUI.h"
#include "ui/interfaces/IStatusEffectUI.h"
#include "ui/BattleUIEventQueue.h"
#include "common/AppState.h"
#include "ui/Menu.h"
#include "battle/BattleManager.h"

class GameEngine
{
public:
    GameEngine();
    void Run();
    void RunSimulations();

private:
    void Bootstrap();
    void PresetupBattle();

    std::vector<std::unique_ptr<Player>> players;
    BattleContext context;
    RandomEngine rng;

    std::unique_ptr<IOutputTarget> outputTarget;
    std::unique_ptr<IBattleAnnouncerUI> battleAnnouncer;
    std::unique_ptr<IMoveResultsUI> moveResults;
    std::unique_ptr<IStatusEffectUI> statusEffect;

    BattleUIEventQueue m_uiEventQueue;

    AppState currentState = AppState::MainMenu;
    std::optional<Menu> menu;
    std::optional<BattleManager> battleManager;

    unsigned int simIterations{ 1 };
    int playerOneVictories{};
    int playerTwoVictories{};
};