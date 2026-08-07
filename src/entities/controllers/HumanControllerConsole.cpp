#include <iostream>
#include <istream>
#include <string>
#include <utility>
#include <memory>

#include "HumanControllerConsole.h"

#include "IPlayerController.h"
#include "../PlayerDecisionOutcome.h"
#include "../pokemonMove.h"
#include "../BattlePokemon.h"
#include "../Player.h"
#include "../../battle/BattleAction.h"
#include "../../common/InputValidation.h"
#include "../../ui/views/PokemonTextView.h"

void read_input_worker(std::string& input)
{
    std::getline(std::cin >> std::ws, input);
}

std::unique_ptr<IPlayerController> HumanControllerConsole::clone() const
{
    return std::make_unique<HumanControllerConsole>(*this);
}

PlayerDecisionOutcome HumanControllerConsole::ChooseAction(Player& player, const Player& targetPlayer, BattlePokemon& currentPokemon, const BattlePokemon& targetMon, RandomEngine& rng)
{
    std::cout << player.GetPlayerNameView() << " choose your action\n";

    while (m_decisionOutcome.action == BattleAction::None)
    {
        std::cout << "1. Fight \t";
        std::cout << "2. Switch Pokemon";
        std::cout << ((player.CanSwitch()) ? " \t" : "(X) \t");
        std::cout << "3. Forfeit\n";

        std::string input{};
        std::cout << "Option: ";
        std::getline(std::cin >> std::ws, input);
        std::cout << '\n';

        if (!IsDigits(input) || input.size() > 10)
        {
            std::cout << "Invalid input!\n\n";
            continue;
        }

        int choice = std::stoi(input);

        switch (choice)
        {

        case 1:
            m_decisionOutcome.chosenMove = FightAction(player, currentPokemon, targetMon);

            if (!m_decisionOutcome.chosenMove)
            {
                m_decisionOutcome.action = BattleAction::None;
                continue;
            }

            /*
            if (m_decisionOutcome.chosenMove == &GetStruggle())
            {
                m_decisionOutcome.action = BattleAction::Struggle;
            }
            else
            {
                m_decisionOutcome.action = BattleAction::Fight;
            }
            */

            m_decisionOutcome.action = BattleAction::Fight;

            break;

        case 2:
            if (!player.CanSwitch())
            {
                std::cout << "You aren't able to switch Pokemon right now!\n";
                break;
            }
            m_decisionOutcome.action = BattleAction::SwitchPokemon;
            m_decisionOutcome.chosenPokemon = SwitchAction(player, currentPokemon);

            if (!m_decisionOutcome.chosenPokemon)
            {
                m_decisionOutcome.action = BattleAction::None;
                continue;
            }
            break;

        case 3:
            m_decisionOutcome.action = ForfeitAction(player);
            break;

        default:
            m_decisionOutcome.action = BattleAction::None;
            std::cout << "Invalid input!\n\n";
            break;
        }
    }

    return m_decisionOutcome;
}

void HumanControllerConsole::SkipChooseAction()
{
    m_decisionOutcome.action = BattleAction::Skip;
    b_hasDecision = true;
}

BattlePokemon* HumanControllerConsole::PromptForSwitch(Player& player, const Player& targetPlayer, const BattlePokemon& currentPokemon, const BattlePokemon& targetMon)
{
    m_decisionOutcome.chosenPokemon = SwitchAction(player, currentPokemon);
    return m_decisionOutcome.chosenPokemon;
}

bool HumanControllerConsole::HasDecision()
{
    return b_hasDecision;
}

PlayerDecisionOutcome HumanControllerConsole::TakeDecision()
{
    b_hasDecision = false;
    return std::exchange(m_decisionOutcome, {});
}

pokemonMove* HumanControllerConsole::FightAction(const Player& player, BattlePokemon& currentPokemon, const BattlePokemon& targetMon)
{
    if (currentPokemon.WillPerformStruggle())
    {
        std::cout << "You are out of PP for all moves. All you can do is Struggle.\n\n";
        b_hasDecision = true;
        return &GetStruggle();
    }

    pokemonMove* selectedMove{ nullptr };

    while (true)
    {
        std::cout << currentPokemon.GetNameView() << "'s current moves\n";
        PokemonTextView::DisplayMovesInBattle(currentPokemon, targetMon);

        std::string input;
        std::cout << "Option (0 to cancel): ";
        std::getline(std::cin >> std::ws, input);
        std::cout << '\n';

        if (!IsDigits(input) || input.size() > 10)
        {
            std::cout << "Invalid input!\n\n";
            continue;
        }

        int choice = std::stoi(input);

        if (choice == 0)
        {
            return nullptr;
        }

        if (choice > 4)
        {
            std::cout << "Invalid input!\n\n";
            continue;
        }

        if (currentPokemon.GetMove(choice).b_isDisabled)
        {
            std::cout << "This move is currently disabled!\n\n";
            continue;
        }

        if (currentPokemon.GetPP(choice) <= 0)
        {
            std::cout << "There's no PP left for this move!\n\n";
            continue;
        }

        if (!currentPokemon.GetMove(choice).HasMove())
        {
            std::cout << "There is no move there!\n\n";
            continue;
        }
        else
        {
            selectedMove = &currentPokemon.GetMove(choice);
            b_hasDecision = true;
            std::cout << player.GetPlayerNameView() << " has chosen " << selectedMove->GetName() << "\n\n";
            return selectedMove;
        }
    }
}

BattlePokemon* HumanControllerConsole::SwitchAction(Player& currentPlayer, const BattlePokemon& currentPokemon)
{
    std::cout << "Choose Pokemon to switch out! 0 to cancel.\n";

    BattlePokemon* selectedPokemon{};

    while (true)
    {
        PokemonTextView::DisplayPlayerPokemon(currentPlayer);

        std::string input;
        std::cout << "Option: ";
        std::getline(std::cin >> std::ws, input);
        std::cout << '\n';

        if (!IsDigits(input) || input.size() > 10)
        {
            std::cout << "Invalid input!\n\n";
            continue;
        }

        int choice = std::stoi(input);

        if (choice == 0 && currentPokemon.IsFainted())
        {
            std::cout << "Your " << currentPokemon.GetNameView() << " is fainted. You must select another pokemon to take its place!\n\n";
            continue;
        }
        else if (choice == 0)
        {
            return selectedPokemon;
        }

        if (choice > 6)
        {
            std::cout << "Invalid input!\n\n";
            continue;
        }

        if (!currentPlayer.GetBelt(choice).HasPokemon())
        {
            std::cout << "No Pokemon there!\n\n";
            continue;
        }

        if (currentPlayer.GetBelt(choice).IsFainted())
        {
            std::cout << "A fainted Pokemon cannot fight!\n\n";
            continue;
        }

        if (&currentPlayer.GetBelt(choice) == &currentPokemon)
        {
            std::cout << "That pokemon is already in play!\n\n";
            continue;
        }

        if (choice != 0)
        {
            selectedPokemon = &currentPlayer.GetBelt(choice);
            b_hasDecision = true;
            return selectedPokemon;
        }
    }
}

BattleAction HumanControllerConsole::ForfeitAction(const Player& sourcePlayer)
{
    std::cout << sourcePlayer.GetPlayerNameView() << " has forfeited!\n";
    b_hasDecision = true;
    return BattleAction::Forfeit;
}