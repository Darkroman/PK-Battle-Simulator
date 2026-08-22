#pragma once

#include "battle/BattleManager.h"
#include "battle/RandomEngine.h"

#include "common/AppState.h"

#include "entities/Player.h"

#include "ui/BattleEventQueue.h"
#include "ui/ConsoleBattleEventProcessor.h"
#include "ui/Menu.h"

#include "ui/interfaces/IOutputTarget.h"
#include "ui/interfaces/IBattleAnnouncerUI.h"
#include "ui/interfaces/IMoveResultsUI.h"
#include "ui/interfaces/IStatusEffectUI.h"

#include <memory>
#include <optional>
#include <vector>

class GameEngine
{
public:
    GameEngine();
    void Run();
    void RunSimulations(unsigned int simIterations);

private:
    std::vector<std::unique_ptr<Player>> players;
    RandomEngine rng;

    std::unique_ptr<IOutputTarget> outputTarget;
    std::unique_ptr<IBattleAnnouncerUI> battleAnnouncer;
    std::unique_ptr<IMoveResultsUI> moveResults;
    std::unique_ptr<IStatusEffectUI> statusEffect;
    std::optional<ConsoleBattleEventProcessor> m_eventProcessor;
    
    BattleEventQueue m_eventQueue;

    AppState currentState = AppState::MainMenu;
    MenuResult m_pendingMenuResult{};
    std::optional<Menu> menu;
    std::optional<BattleManager> battleManager;
};