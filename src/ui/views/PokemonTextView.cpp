#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ios>
#include <format>
#include <string_view>

#include "PokemonTextView.h"

#include "../../common/EnumUtils.h"

#include "../../entities/pokemonMove.h"
#include "../../entities/BattlePokemon.h"
#include "../../entities/Player.h"
#include "../../data/Database.h"
#include "../../data/Pokemon.h"
#include "../../data/Move.h"
#include "../../data/StringToTypes.h"
#include "../../moves/MoveEffectEnums.h"
#include "../../battle/Typechart.h"

namespace PokemonTextView
{
    void DisplayStats(const BattlePokemon& pokemon)
    {
        std::cout << "Pokemon: " << pokemon.GetPokemonNameView() << '\n';

        if (!pokemon.HasNickname())
        {
            std::cout << "No nickname\n";
        }
        else
        {
            std::cout << "Nickname: " << pokemon.GetNicknameView() << '\n';
        }

        std::cout << "Type: "
            << pokemon.GetTypeOne()
            << "/"
            << pokemon.GetTypeTwo()
            << '\n';

        std::cout << "Level: " << pokemon.GetLevel() << '\n';

        std::cout << std::left << std::setw(17) << "HP: " << std::setw(3) << pokemon.GetMaxHP()

            << " -- [IV: " << std::right << std::setw(2) << pokemon.GetHPIV() << "]"
            << " -- [EV: " << std::setw(3) << pokemon.GetHPEV() << "]\n";

        std::cout << std::left << std::setw(17) << "Attack: " << std::setw(3) << pokemon.GetAttack()

            << " -- [IV: " << std::right << std::setw(2) << pokemon.GetAttackIV() << "]"
            << " -- [EV: " << std::setw(3) << pokemon.GetAttackEV() << "]\n";

        std::cout << std::left << std::setw(17) << "Defense: " << std::setw(3) << pokemon.GetDefense()

            << " -- [IV: " << std::right << std::setw(2) << pokemon.GetDefenseIV() << "]"
            << " -- [EV: " << std::setw(3) << pokemon.GetDefenseEV() << "]\n";

        std::cout << std::left << std::setw(17) << "Special Attack: " << std::setw(3) << pokemon.GetSpecialAttack()

            << " -- [IV: " << std::right << std::setw(2) << pokemon.GetSpecialAttackIV() << "]"
            << " -- [EV: " << std::setw(3) << pokemon.GetSpecialAttackEV() << "]\n";

        std::cout << std::left << std::setw(17) << "Special Defense: " << std::setw(3) << pokemon.GetSpecialDefense()

            << " -- [IV: " << std::right << std::setw(2) << pokemon.GetSpecialDefenseIV() << "]"
            << " -- [EV: " << std::setw(3) << pokemon.GetSpecialDefenseEV() << "]\n";

        std::cout << std::left << std::setw(17) << "Speed: " << std::setw(3) << pokemon.GetSpeed()

            << " -- [IV: " << std::right << std::setw(2) << pokemon.GetSpeedIV() << "]"
            << " -- [EV: " << std::setw(3) << pokemon.GetSpeedEV() << "]\n";
    }

    void DisplayLearnableMoves(const BattlePokemon& pokemon)
    {
        const Pokemon* basePokemon = pokemon.GetPokemonDatabasePointer();

        auto movelist = basePokemon->GetMoveList();

        int colCount = 0;

        for (auto moveId : movelist)
        {
            ++colCount;

            size_t moveIndex = basePokemon->FetchMoveNumber(moveId);
            const Move* move = Database::GetPointerToBaseMoveByIndex(moveIndex);

            size_t displayIndex = moveIndex + 1;

            std::cout
                << std::right << std::setw(3) << displayIndex << ": "
                << std::left << std::setw(15) << move->GetName();

            if (colCount % 6 == 0)
            {
                std::cout << '\n';
            }
        }

        std::cout << '\n';
    }

    void DisplayIVs(const BattlePokemon& pokemon)
    {
        std::cout << "IVs:\n";
        std::cout << std::left << std::setw(20) << "HP IV: " << std::right << std::setw(2) << pokemon.GetHPIV() << '\n';
        std::cout << std::left << std::setw(20) << "Attack IV: " << std::right << std::setw(2) << pokemon.GetAttackIV() << '\n';
        std::cout << std::left << std::setw(20) << "Defense IV: " << std::right << std::setw(2) << pokemon.GetDefenseIV() << '\n';
        std::cout << std::left << std::setw(20) << "Special Attack IV: " << std::right << std::setw(2) << pokemon.GetSpecialAttackIV() << '\n';
        std::cout << std::left << std::setw(20) << "Special Defense IV: " << std::right << std::setw(2) << pokemon.GetSpecialDefenseIV() << '\n';
        std::cout << std::left << std::setw(20) << "Speed IV: " << std::right << std::setw(2) << pokemon.GetSpeedIV() << '\n';
    }

    void DisplayEVs(const BattlePokemon& pokemon)
    {
        std::cout << std::left << std::setw(20) << "HP EV: " << std::right << std::setw(3) << pokemon.GetHPEV() << '\n';
        std::cout << std::left << std::setw(20) << "Attack EV: " << std::right << std::setw(3) << pokemon.GetAttackEV() << '\n';
        std::cout << std::left << std::setw(20) << "Defense EV: " << std::right << std::setw(3) << pokemon.GetDefenseEV() << '\n';
        std::cout << std::left << std::setw(20) << "Special Attack EV: " << std::right << std::setw(3) << pokemon.GetSpecialAttackEV() << '\n';
        std::cout << std::left << std::setw(20) << "Special Defense EV: " << std::right << std::setw(3) << pokemon.GetSpecialDefenseEV() << '\n';
        std::cout << std::left << std::setw(20) << "Speed EV: " << std::right << std::setw(3) << pokemon.GetSpeedEV() << "\n\n";
    }

    void DisplayLearnedMoves(const BattlePokemon& pokemon)
    {
        for (size_t moveSlot = 1; moveSlot < 5; ++moveSlot)
        {
            if (moveSlot != 1)
            {
                std::cout << " ";
            }

            if (pokemon.GetMove(moveSlot).HasMove())
            {
                std::cout << std::format("{:<13}", pokemon.GetMove(moveSlot).GetName());
                std::cout << " ";
            }
            else
            {
                std::cout << std::format("{:^13}", "---");
                std::cout << " ";
            }

            if (moveSlot != 4)
            {
                std::cout << "/";
            }
        }
        std::cout << '\n';
    }

    void DisplayLearnedMovesExpanded(const BattlePokemon& pokemon)
    {
        for (size_t moveSlot = 1; moveSlot < 5; ++moveSlot)
        {
            const auto& move = pokemon.GetMove(moveSlot);
            if (move.HasMove())
            {
                std::cout << moveSlot << ". "
                    << std::left << std::setw(13) << move.GetName() << " PP("
                    << std::right << std::setw(2) << move.m_currentPP << "/"
                    << std::right << std::setw(2) << move.m_maxPP << ") "
                    << std::left << "- Power: " << std::setw(4) << move.GetPower()
                    << std::left << "- Accuracy: " << std::setw(4) << move.GetAccuracy()
                    << std::left << "- Type: " << std::setw(9) << move.GetMoveType()
                    << std::left << "- Category: " << std::setw(9) << move.GetCategory()
                    << '\n';

            }
            else
            {
                std::cout << moveSlot << ". " << "---\n";
            }
        }
    }

    void DisplayMovesInBattle(const Player& player, const Player& targetPlayer, const BattlePokemon& pokemon, const BattlePokemon& target)
    {
        for (size_t moveSlot = 1; moveSlot < 5; ++moveSlot)
        {
            const auto& move = pokemon.GetMove(moveSlot);
            if (move.HasMove())
            {
                if (move.b_isDisabled)
                {
                    std::cout << moveSlot << ". "
                        << std::left << std::setw(13) << move.GetName()
                        << std::format("{:^11}", "(Disabled!)")
                        << '\n';
                }
                else
                {
                    bool isStatus = move.GetCategoryEnum() == Category::Status;

                    std::cout << moveSlot << ". "
                        << std::left << std::setw(13) << move.GetName() << " PP("
                        << std::right << std::setw(2) << move.m_currentPP << "/"
                        << std::right << std::setw(2) << move.m_maxPP << ") "
                        << std::left << "- Type: " << std::setw(9) << move.GetMoveType()
                        << std::left << "- Category: " << std::setw(9) << move.GetCategory()
                        << std::left << "- Effectiveness: " << std::setw(15) << (isStatus ? CalculateStatusMoveEffectiveness(player, targetPlayer, pokemon, target, move) : CalculateDamageMoveEffectiveness(target, move))
                        << '\n';
                }
            }
            else
            {
                std::cout << moveSlot << ". " << "---\n";
            }
        }
    }

    void DisplayPlayerPokemon(const Player& player)
    {
        int count{ 1 };
        std::cout << "---" << player.GetPlayerName() << "'s Pokemon---\n";

        for (const auto& p : player.GetBeltArray())
        {
            if (!p.HasPokemon())
            {
                std::cout << count << ". ---\n";
            }
            else
            {
                std::string_view status = DisplayPokemonStatus(p);
                std::cout
                    << count << ". "
                    << std::left << std::setw(11) << p.GetNameView()
                    << " HP("
                    << std::right << std::setw(3) << p.GetCurrentHP() << "/"
                    << std::right << std::setw(3) << p.GetMaxHP() << ") - "
                    << std::right << std::setw(4) << status
                    << " - Level: "
                    << std::right << std::setw(3) << p.GetLevel()
                    << " - Moves: ";
                DisplayLearnedMoves(p);
            }
            ++count;
        }
        std::cout << '\n';
    }

    std::string_view DisplayPokemonStatus(const BattlePokemon& pokemon)
    {
        Status currentStatus = pokemon.GetStatus();

        switch (currentStatus)
        {
        case Status::Burned:
            return "BRN";
            break;

        case Status::Frozen:
            return "FRZ";
            break;

        case Status::Paralyzed:
            return "PAR";
            break;

        case Status::Poisoned:
            return "PSN";
            break;

        case Status::Badly_Poisoned:
            return "BPSN";
            break;

        case Status::Sleeping:
            return "SLP";
            break;
        }

        if (pokemon.IsFainted())
        {
            return "FNT";
        }
        else if (pokemon.IsConfused())
        {
            return "CNF";
        }
        else
        {
            return "NOR";
        }

    }

    std::string_view CalculateStatusMoveEffectiveness(const Player& self, const Player& targetPlayer, const BattlePokemon& selfMon, const BattlePokemon& targetMon, const pokemonMove& currentMove)
    {
        constexpr int MaxStage = 12;
        constexpr int MinStage = 0;

        int selfAttackStage = selfMon.GetAttackStage();
        int selfDefenseStage = selfMon.GetDefenseStage();
        int selfSpecialAttackStage = selfMon.GetSpecialAttackStage();
        int selfSpecialDefenseStage = selfMon.GetSpecialDefenseStage();
        int selfSpeedStage = selfMon.GetSpeedStage();
        int selfEvasionStage = selfMon.GetEvasionStage();

        if ((currentMove.GetMoveEffectEnum() == MoveEffect::AttackUp2 ||
            currentMove.GetMoveEffectEnum() == MoveEffect::AttackUp) &&
            selfAttackStage >= MaxStage)
        {
            return "Ineffective";
        }

        if ((currentMove.GetMoveEffectEnum() == MoveEffect::DefenseUp2 ||
            currentMove.GetMoveEffectEnum() == MoveEffect::DefenseUp) &&
            selfDefenseStage >= MaxStage)
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Growth &&
            selfAttackStage >= MaxStage && selfSpecialAttackStage >= MaxStage)
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::SpecialDefenseUp2 &&
            selfSpecialDefenseStage >= MaxStage)
        {
            return "Ineffective";
        }

        if ((currentMove.GetMoveEffectEnum() == MoveEffect::EvasionUp ||
            currentMove.GetMoveEffectEnum() == MoveEffect::Minimize) &&
            selfEvasionStage >= MaxStage)
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::SpeedUp2 &&
            selfSpeedStage >= MaxStage)
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Splash)
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Mist && self.HasMist())
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Teleport && self.GetPokemonLeft() <= 1)
        {
            return "Ineffective";
        }

        if ((currentMove.GetMoveEffectEnum() == MoveEffect::HealHalfHP || currentMove.GetMoveEffectEnum() == MoveEffect::Rest) && selfMon.GetCurrentHP() == selfMon.GetMaxHP())
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::LightScreen && self.HasLightScreen())
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Reflect && self.HasReflect())
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::FocusEnergy && selfMon.HasFocusEnergy())
        {
            return "Ineffective";
        }

        /*
        if (currentMove.GetMoveEffectEnum() == MoveEffect::MirrorMove) // Leaving out last used move nullptr check on purpose because of turn order can vary
        {
            return "Ineffective";
        }
        */

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Rest && selfMon.GetStatus() == Status::Sleeping)
        {
            return "Ineffective";
        }

        unsigned int substituteCost = selfMon.GetMaxHP() / 4;
        if (currentMove.GetMoveEffectEnum() == MoveEffect::Substitute && (selfMon.HasSubstitute() ||
             selfMon.GetCurrentHP() <= substituteCost))
        {
            return "Ineffective";
        }

        bool isStatStageLoweringMove =
            currentMove.GetMoveEffectEnum() == MoveEffect::AccuracyDown ||
            currentMove.GetMoveEffectEnum() == MoveEffect::AttackDown ||
            currentMove.GetMoveEffectEnum() == MoveEffect::DefenseDown2 ||
            currentMove.GetMoveEffectEnum() == MoveEffect::DefenseDown ||
            currentMove.GetMoveEffectEnum() == MoveEffect::SpeedDown2;

        bool hasMist = targetPlayer.HasMist();

        bool cannotBypassSubstitute = targetMon.HasSubstitute() && !currentMove.CanBypassSubstitute();

        if (isStatStageLoweringMove && (hasMist || cannotBypassSubstitute))
        {
            return "Ineffective";
        }

        int targetAccuracyStage = targetMon.GetAccuracyStage();
        int targetAttackStage = targetMon.GetAttackStage();
        int targetDefenseStage = targetMon.GetDefenseStage();
        int targetSpeedStage = targetMon.GetSpeedStage();

        if (currentMove.GetMoveEffectEnum() == MoveEffect::AccuracyDown && targetAccuracyStage <= MinStage)
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::AttackDown && targetAttackStage <= MinStage)
        {
            return "Ineffective";
        }

        if ((currentMove.GetMoveEffectEnum() == MoveEffect::DefenseDown2 || currentMove.GetMoveEffectEnum() == MoveEffect::DefenseDown) && targetDefenseStage <= MinStage)
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::SpeedDown2 && targetSpeedStage <= MinStage)
        {
            return "Ineffective";
        }

        bool isForceSwitchMove = currentMove.GetMoveEffectEnum() == MoveEffect::ForceSwitch;

        /* None that exist in gen 1 
        if (isForceSwitchMove && cannotBypassSubstitute)
        {
            return "Ineffective";
        }
        */

        if (isForceSwitchMove && targetPlayer.GetPokemonLeft() <= 1)
        {
            return "Ineffective";
        }

        bool inflictsVolatileStatus =
            currentMove.GetMoveEffectEnum() == MoveEffect::Confuse ||
            currentMove.GetMoveEffectEnum() == MoveEffect::Disable ||
            currentMove.GetMoveEffectEnum() == MoveEffect::LeechSeed;

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Confuse && targetMon.IsConfused())
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Disable && targetMon.MoveIsDisabled())
        {
            return "Ineffective";
        }

        bool inflictsNonVolatileStatus =
            currentMove.GetMoveEffectEnum() == MoveEffect::SleepMove ||
            currentMove.GetMoveEffectEnum() == MoveEffect::SleepPowder ||
            currentMove.GetMoveEffectEnum() == MoveEffect::Paralyze ||
            currentMove.GetMoveEffectEnum() == MoveEffect::StunSpore ||
            currentMove.GetMoveEffectEnum() == MoveEffect::PoisonGas ||
            currentMove.GetMoveEffectEnum() == MoveEffect::PoisonPowder ||
            currentMove.GetMoveEffectEnum() == MoveEffect::Toxic;

        if (inflictsNonVolatileStatus && (targetMon.GetStatus() != Status::Normal))
        {
            return "Ineffective";
        }

        if (inflictsNonVolatileStatus && targetMon.GetStatus() == Status::Normal && cannotBypassSubstitute)
        {
            return "Ineffective";
        }

        bool isGrassImmune = (currentMove.GetMoveEffectEnum() == MoveEffect::PoisonPowder
            || currentMove.GetMoveEffectEnum() == MoveEffect::StunSpore
            || currentMove.GetMoveEffectEnum() == MoveEffect::SleepPowder
            || currentMove.GetMoveEffectEnum() == MoveEffect::LeechSeed)
            && (targetMon.GetTypeOneEnum() == PokemonType::Grass || targetMon.GetTypeTwoEnum() == PokemonType::Grass);

        bool isParalyzeImmune = (currentMove.GetMoveEffectEnum() == MoveEffect::Paralyze || currentMove.GetMoveEffectEnum() == MoveEffect::StunSpore)
            && (targetMon.GetTypeOneEnum() == PokemonType::Electric || targetMon.GetTypeTwoEnum() == PokemonType::Electric);

        bool isThunderWaveImmune = (currentMove.GetMoveTypeEnum() == PokemonType::Electric
            && (targetMon.GetTypeOneEnum() == PokemonType::Ground || targetMon.GetTypeTwoEnum() == PokemonType::Ground));

        bool isPoisonImmune = (currentMove.GetMoveTypeEnum() == PokemonType::Poison)
            && ((targetMon.GetTypeOneEnum() == PokemonType::Poison || targetMon.GetTypeTwoEnum() == PokemonType::Poison)
                || (targetMon.GetTypeOneEnum() == PokemonType::Steel || targetMon.GetTypeTwoEnum() == PokemonType::Steel));

        if (currentMove.GetMoveEffectEnum() == MoveEffect::LeechSeed && (targetMon.IsSeeded() || isGrassImmune))
        {
            return "Ineffective";
        }

        if (inflictsVolatileStatus && cannotBypassSubstitute)
        {
            return "Ineffective";
        }

        if (isGrassImmune || isParalyzeImmune || isThunderWaveImmune || isPoisonImmune)
        {
            return "Ineffective";
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Mimic) // move bypasses substitute
        {
            const pokemonMove* targetLastUsedMove = targetMon.GetLastUsedMove();

            if (targetLastUsedMove == nullptr)
            {
                return "Ineffective";
            }

            bool alreadyHasMove{};

            for (const auto& move : selfMon.GetMoveArray())
            {
                if (!move.HasMove())
                {
                    continue;
                }

                if (targetLastUsedMove->GetMoveID() == move.GetMoveID())
                {
                    alreadyHasMove = true;
                    break;
                }
            }

            bool fail =
                alreadyHasMove ||
                targetLastUsedMove->GetMoveID() == MoveID::Transform ||
                targetLastUsedMove->GetMoveID() == MoveID::Struggle ||
                targetLastUsedMove->GetMoveID() == MoveID::Metronome ||
                selfMon.IsTransformed();

            if (fail)
            {
                return "Ineffective";
            }
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Transform) // move does not bypass substitute
        {
            if (selfMon.IsTransformed() || targetMon.IsTransformed() || targetMon.HasSubstitute())
            {
                return "Ineffective";
            }
        }

        if (currentMove.GetMoveEffectEnum() == MoveEffect::Conversion)
        {
            if (selfMon.GetTypeOneEnum() == currentMove.GetMoveTypeEnum() ||
                selfMon.GetTypeTwoEnum() == currentMove.GetMoveTypeEnum() ||
                selfMon.IsConverted())
            {
                return "Ineffective";
            }
        }

        return "Effective";
    }

    std::string_view CalculateDamageMoveEffectiveness(const BattlePokemon& target, const pokemonMove& currentMove)
    {
        if (currentMove.GetMoveEffectEnum() == MoveEffect::Struggle)
        {
            return "Effective";
        }

        unsigned int moveType = EnumIndex(currentMove.GetMoveTypeEnum());
        unsigned int defensiveTypeOne = EnumIndex(target.GetTypeOneEnum());
        unsigned int defensiveTypeTwo = EnumIndex(target.GetTypeTwoEnum());

        unsigned int effect1 = typeChart[moveType][defensiveTypeOne];
        unsigned int effect2 = (defensiveTypeTwo == 18) ? 4096 : typeChart[moveType][defensiveTypeTwo];

        unsigned int product = effect1 * effect2;
        unsigned int moveEffectiveness = product / 4096;

        if (moveEffectiveness == 0)
        {
            return "Immune";
        }
        else if (moveEffectiveness < 4096)
        {
            return "Not Effective";
        }
        else if (moveEffectiveness == 4096)
        {
            return "Effective";
        }
        else
        {
            return "Super Effective";
        }
    }
}