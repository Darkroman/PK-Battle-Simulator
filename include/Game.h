#pragma once

#include "Menu.h"
#include "BattleSystem.h"

void RunGame()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    start = std::chrono::high_resolution_clock::now();
    Database* db = Database::GetInstance();
    end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> ms = (end - start) * 1000;

    std::cout << "Time it took to load database: " << ms.count() << "ms" << "\n\n";

    std::vector<Player> players;
    players.reserve(2);

    players.emplace_back("Player One", db);
    players.emplace_back("Player Two", db);

    Menu menu(players);
    BattleSystem battle(players);

    bool exit = false;
    while (exit == false)
    {
        exit = menu.RunMenu();

        if (exit == true)
        {
            return;
        }

        exit = battle.StartBattle();

        exit = battle.AnnounceWinner();
    }
}