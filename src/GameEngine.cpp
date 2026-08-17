#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <new>
#include <thread>
#include <vector>

#include "GameEngine.h"

#include "entities/Player.h"
#include "entities/controllers/AIController.h"
#include "entities/controllers/HumanControllerConsole.h"

#include "ui/interfaces/IOutputTarget.h"
#include "ui/ConsoleOutput.h"

#include "ui/interfaces/IBattleAnnouncerUI.h"
#include "ui/BattleAnnouncerText.h"
#include "ui/BattleAnnouncerHeadless.h"

#include "ui/interfaces/IMoveResultsUI.h"
#include "ui/MoveResultsQueued.h"
#include "ui/MoveResultsHeadless.h"

#include "ui/interfaces/IStatusEffectUI.h"
#include "ui/StatusEffectQueued.h"
#include "ui/StatusEffectHeadless.h"

#include "ui/ConsoleBattleEventProcessor.h"

#include "common/AppState.h"
#include "common/BattleState.h"

#include "battle/BattleContext.h"
#include "battle/RandomEngine.h"
#include "battle/BattleManager.h"

GameEngine::GameEngine()
    : players([&] {
        std::vector<std::unique_ptr<Player>> v;
        v.push_back(std::make_unique<Player>("Player One"));
        v.push_back(std::make_unique<Player>("Player Two"));
        v.at(0)->SetController(std::make_unique<HumanControllerConsole>(), ControllerType::Human);
        v.at(1)->SetController(std::make_unique<AIController>(Difficulty::Easy), ControllerType::AI);
        return v;
        }()),
    context(players),
    rng()
{
    Bootstrap();
}

void GameEngine::Bootstrap()
{
    context.playerOne = players[0].get();
    context.playerTwo = players[1].get();
}

void GameEngine::PresetupBattle()
{
    context.playerOne = players[0].get();
    context.playerTwo = players[1].get();

    context.vec_aiPlayers.clear();
    if (context.playerOne->IsAI()) context.vec_aiPlayers.emplace_back(context.playerOne);
    if (context.playerTwo->IsAI()) context.vec_aiPlayers.emplace_back(context.playerTwo);
}

void GameEngine::Run()
{
    while (currentState != AppState::Exit)
    {
        switch (currentState)
        {
            case AppState::MainMenu:
                if (!menu)
                {
                    menu.emplace(players);
                }
                m_pendingMenuResult = menu->RunMenu();
                currentState = m_pendingMenuResult.appState;

                break;
            
            case AppState::InitBattle:

                outputTarget = std::make_unique<ConsoleOutput>();
                battleAnnouncer = std::make_unique<BattleAnnouncerText>();
                moveResults = std::make_unique<MoveResultsQueued>(m_eventQueue);
                statusEffect = std::make_unique<StatusEffectQueued>(m_eventQueue);
                
                m_eventProcessor.emplace(m_eventQueue, *outputTarget);

                PresetupBattle();

                if (!battleManager)
                {
                    battleManager.emplace(context, rng, *battleAnnouncer, *moveResults, *statusEffect);
                }

                currentState = AppState::Battle;

                break;

            case AppState::Battle:
            {
                const BattleRunResult result = battleManager->RunBattle();

                if (result.playEvents)
                {
                    m_eventProcessor->ProcessEvents();

                }

                if (result.state == BattleState::Victory)
                {
                    currentState = AppState::Victory;
                }

                break;
            }

            case AppState::Victory:
                battleAnnouncer->AnnounceWinner(context);
                battleManager->ResetValues();
                battleManager.reset();
                currentState = AppState::MainMenu;

                break;

            case AppState::Simulate:
            {
                RunSimulations(m_pendingMenuResult.simIterations);

                currentState = AppState::MainMenu;

                break;
            }

            case AppState::Exit:
                return;

        }
    }
}

void GameEngine::RunSimulations(unsigned int simIterations)
{
    if (simIterations <= 0)
    {
        std::cerr << "Simulation iterations must be greater than zero.\n";
        return;
    }

    /*
    struct ThreadDebugInfo
    {
        unsigned int threadIndex{};
        uint64_t seed{};
        unsigned int localBattleIndex{};
        unsigned int turns{};
        uint64_t iterationNum{};
    };
    */

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    start = std::chrono::high_resolution_clock::now();

    //std::mutex localWinsMutex;

    unsigned int numThreads = std::thread::hardware_concurrency();

    if (numThreads == 0)
    {
        numThreads = 1;
    }

    numThreads = std::min(numThreads, simIterations);

    unsigned int baseBattlesPerThread = simIterations / numThreads;
    unsigned int remainder = simIterations % numThreads;

    //std::atomic<uint64_t> numOfIterations{};

    alignas (std::hardware_destructive_interference_size) std::atomic<uint64_t> pOneVictories{};
    alignas (std::hardware_destructive_interference_size) std::atomic<uint64_t> pTwoVictories{};

    alignas (std::hardware_destructive_interference_size) std::atomic<uint64_t> totalTurns{};

    std::vector<std::thread> workers;
    workers.reserve(numThreads);
    
    //std::vector<ThreadDebugInfo> debugResults;
    //std::mutex debugMutex;
    
    std::unique_ptr<IOutputTarget> outputTarget = std::make_unique<ConsoleOutput>();
    std::unique_ptr<IBattleAnnouncerUI> battleAnnouncer = std::make_unique<BattleAnnouncerHeadless>();
    std::unique_ptr<IMoveResultsUI> moveResults = std::make_unique<MoveResultsHeadless>();
    std::unique_ptr<IStatusEffectUI> statusEffect = std::make_unique<StatusEffectHeadless>();

    //std::atomic<bool> found{};
    //ThreadDebugInfo info;
    for (unsigned int t{}; t < numThreads; ++t)
    {
        workers.emplace_back([&, t]()
        {
            std::vector<std::unique_ptr<Player>> localPlayers;
            localPlayers.reserve(players.size());

            for (const auto& playerPtr : players)
            {
                localPlayers.push_back(std::make_unique<Player>(*playerPtr));
            }

            BattleContext localContext(localPlayers);

            RandomEngine localRng(t);

            localContext.playerOne = localPlayers[0].get();
            localContext.playerTwo = localPlayers[1].get();

            if (localContext.playerOne->IsAI()) localContext.vec_aiPlayers.emplace_back(localContext.playerOne);
            if (localContext.playerTwo->IsAI()) localContext.vec_aiPlayers.emplace_back(localContext.playerTwo);

            BattleManager localManager(localContext, localRng, *battleAnnouncer, *moveResults, *statusEffect);

            uint64_t localP1Wins = 0;
            uint64_t localP2Wins = 0;
            uint64_t localThreadTurns = 0;
            //uint64_t localNumOfIterations = 0;

            unsigned int battlesForThisThread =
            baseBattlesPerThread + (t < remainder ? 1 : 0);

            unsigned int i{};
            for (i; i < battlesForThisThread; ++i)
            {
                /*
                for (unsigned int j = 0; j < 332; ++j)
                {
                    localManager.RunBattleSimulation();
                    localManager.ResetValues();
                }
                
                //localRng.GetCallAmount();

                auto battleAnnouncerText = std::make_unique<BattleAnnouncerText>();
                auto moveResultsText = std::make_unique<MoveResultsText>(*outputTarget);
                auto statusEffectText = std::make_unique<StatusEffectText>(*outputTarget);

                BattleManager debugManager(
                    localContext,
                    localRng,
                    *battleAnnouncerText,
                    *moveResultsText,
                    *statusEffectText,
                    *outputTarget,
                    m_uiEventQueue);
                    

                debugManager.RunBattleSimulation();
                */
                localManager.RunBattleSimulation();

                if (localPlayers[0]->HasWon())
                {
                    ++localP1Wins;
                }
                else if (localPlayers[1]->HasWon())
                {
                    ++localP2Wins;
                }
                /*
                else
                {
                    info.threadIndex = t;
                    info.seed = 12345 + t;
                    info.localBattleIndex = i;
                    info.turns = localContext.battleTurn;
                    info.iterationNum = ++numOfIterations;

                    if (!found)
                    {
                        found = true;
                        debugResults.push_back(info);
                    }
                }
                //debugManager.ResetValues();
                //++localNumOfIterations;
                */
                localThreadTurns += localContext.battleTurn;
                localManager.ResetValues();
            }

            pOneVictories += localP1Wins;
            pTwoVictories += localP2Wins;
            totalTurns += localThreadTurns;

            /*
            ThreadDebugInfo info;
            info.threadIndex = t;
            info.seed = 12345 + t;
            info.localBattleIndex = i;
            info.turns = localContext.battleTurn;
            info.iterationNum = numOfIterations;
            */
            /*
            {
                std::scoped_lock lock(debugMutex);

                debugResults.push_back(info);
            }
            
            {
                std::scoped_lock lock(localWinsMutex);
            }
            */
        });
    }

    for (auto& th : workers) th.join();

    end = std::chrono::high_resolution_clock::now();
    /*
    std::sort(
        debugResults.begin(),
        debugResults.end(),
        [](const auto& a, const auto& b)
        {
            return a.threadIndex < b.threadIndex ||
                (a.threadIndex == b.threadIndex &&
                    a.localBattleIndex < b.localBattleIndex);
        });

    for (const auto& debug : debugResults)
    {
        std::cout
            << "Thread: " << debug.threadIndex
            << " Local Battle: " << debug.localBattleIndex
            << " Turns: " << debug.turns
            << " Iteration: " << debug.iterationNum
            << '\n';
    }
    */

    std::chrono::duration<double> elapsed = (end - start);

    std::cout << "Time it took to do simulation: " << elapsed.count() << " seconds" << "\n\n";

    std::cout << "Player One has won " << pOneVictories << " times\n";
    std::cout << "Player Two has won " << pTwoVictories << " times\n";
    std::cout << "Total turns taken: " << totalTurns << '\n';
}