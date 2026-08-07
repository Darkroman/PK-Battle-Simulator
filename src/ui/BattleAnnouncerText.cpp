#include <algorithm>

#include "BattleAnnouncerText.h"

#include "../battle/BattleContext.h"
#include "../entities/BattlePokemon.h"
#include "../entities/Player.h"

#include <iostream>

void BattleAnnouncerText::ThrowOutFirstPokemon(const BattleContext& context) const
{
    std::cout << context.playerOne->GetPlayerNameView() << " chose " << context.playerOneCurrentPokemon->GetPokemonNameView() << "!\n";
    std::cout << context.playerTwo->GetPlayerNameView() << " chose " << context.playerTwoCurrentPokemon->GetPokemonNameView() << "!\n\n";
}

void BattleAnnouncerText::DisplayFightingPokemon(const BattleContext& context) const
{
    auto PrintPercent = [&](int currentHP, int maxHP)
    {
        if (currentHP >= maxHP)
        {
            std::cout << "100%";
            return;
        }

        const unsigned int HP_BAR_WIDTH = context.HP_BAR_WIDTH * 2;

        unsigned int pixelsOfHP = ((currentHP * HP_BAR_WIDTH) / maxHP) / 2;

        pixelsOfHP = std::max(1u, pixelsOfHP);

        unsigned int quarterPercent = pixelsOfHP * 25;

        unsigned int integer = quarterPercent / 100;
        unsigned int decimal = quarterPercent % 100;

        std::cout << integer << ".";
        if (decimal < 10) std::cout << "0";
        std::cout << decimal << "%";
    };

    auto PrintPokemon = [&](Player& player, BattlePokemon& pokemon, bool isAI)
        {
            if (isAI)
            {
                std::cout << player.GetPlayerNameView() << "'s Pokemon: " << pokemon.GetNameView() << " (";
                PrintPercent(pokemon.GetCurrentHP(), pokemon.GetMaxHP());
                std::cout << "/100%)\n";
            }
            else
            {
                std::cout << player.GetPlayerNameView() << "'s Pokemon: " << pokemon.GetNameView() << " ("
                          << pokemon.GetCurrentHP() << "/" << pokemon.GetMaxHP() << ")\n";
            }
        };

    bool isOneAI = context.playerOne->IsAI();
    PrintPokemon(*context.playerOne, *context.playerOneCurrentPokemon, isOneAI);

    bool isTwoAI = context.playerTwo->IsAI();
    PrintPokemon(*context.playerTwo, *context.playerTwoCurrentPokemon, isTwoAI);

    std::cout << '\n';
}

bool BattleAnnouncerText::AnnounceWinner(const BattleContext& context)
{
    if (context.playerOne->HasForfeited() && context.playerTwo->HasForfeited())
    {
        std::cout << "Both players have forfeited!\n\n";
        context.playerOne->SetWinCondition(false);
        context.playerTwo->SetWinCondition(false);
        return false;
    }

    if (context.playerOne->HasWon())
    {
        std::cout << '\n' << context.playerOne->GetPlayerNameView() << " wins!\n\n";
        return false;
    }

    if (context.playerTwo->HasWon())
    {
        std::cout << '\n' << context.playerTwo->GetPlayerNameView() << " wins!\n\n";
        return false;
    }

    return false;
}

void BattleAnnouncerText::NewLine() const
{
    std::cout << '\n';
}

void BattleAnnouncerText::DisplayTurnNumber(int turnCount) const
{
    std::cout << "TURN #" << turnCount << "\n\n";
}