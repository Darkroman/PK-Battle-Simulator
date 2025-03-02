#include "../include/Database.h"

Database::Database()
{
    pokedex.reserve(151); //Number of Pokemon
    movedex.reserve(165); //Number of moves

    auto m_futures = std::async(std::launch::async, [&] { LoadPokemon(); });

    //LoadPokemon();

    auto m_futures2 = std::async(std::launch::async, [&] { LoadMoves(); });

    //LoadMoves();

    std::vector<std::vector<size_t>> tmp_movelist;
    tmp_movelist.reserve(151);
    SetPokemonMoveListASync(tmp_movelist);

    m_futures.wait();
    for (size_t i = 0; i < tmp_movelist.size(); ++i)
    {
        pokedex[i].CopyMoveListVector(tmp_movelist[i]);
    }

    m_futures2.wait();

#if !defined NDEBUG
        TestingPokemonAndMoves();
#endif
}

Database& Database::GetInstance()
{
    static Database instance;
    return instance;
}

void Database::LoadPokemon()
{
    std::filesystem::path pDex = "data/pokedex.txt";

    std::ifstream iss(pDex);

    std::string tmp_NationalDexNumber = "";
    std::string tmp_name = "";
    std::string tmp_basehp = "";
    std::string tmp_baseattack = "";
    std::string tmp_basedefense = "";
    std::string tmp_basespecialattack = "";
    std::string tmp_basespecialdefense = "";
    std::string tmp_basespeed = "";
    std::string tmp_type1 = "";
    std::string tmp_type2 = "";
    std::string tmp_weight = "";
     
    while (tmp_NationalDexNumber != "151")
    {
        std::getline(iss, tmp_NationalDexNumber, ',');
        std::getline(iss, tmp_name, ',');
        std::getline(iss, tmp_basehp, ',');
        std::getline(iss, tmp_baseattack, ',');
        std::getline(iss, tmp_basedefense, ',');
        std::getline(iss, tmp_basespecialattack, ',');
        std::getline(iss, tmp_basespecialdefense, ',');
        std::getline(iss, tmp_basespeed, ',');
        std::getline(iss, tmp_type1, ',');
        std::getline(iss, tmp_type2, ',');
        std::getline(iss, tmp_weight, ',');
        iss >> std::ws;

        pokedex.emplace_back(std::stoi(tmp_NationalDexNumber), tmp_name,
            std::stoi(tmp_basehp), std::stoi(tmp_baseattack), std::stoi(tmp_basedefense),
            std::stoi(tmp_basespecialattack), std::stoi(tmp_basespecialdefense), std::stoi(tmp_basespeed),
            tmp_type1, ConvertStringToPokemonType(tmp_type1), tmp_type2, ConvertStringToPokemonType(tmp_type2), std::stod(tmp_weight));
    }
}

void Database::LoadMoves()
{
    std::filesystem::path mDex = "data/movedex.txt";

    std::ifstream iss(mDex);

    std::string tmp_movenum;
    std::string tmp_name;
    std::string tmp_type;
    std::string tmp_category;
    std::string tmp_priority;
    std::string tmp_secondaryFlag;
    std::string tmp_pp;
    std::string tmp_maxpp;
    std::string tmp_power;
    std::string tmp_accuracy;
    std::string tmp_contact;
    std::string tmp_protect;
    std::string tmp_magicCoat;
    std::string tmp_snatch;
    std::string tmp_mirrorMove;
    std::string tmp_kingRock;
    std::string tmp_soundBased;
    std::string tmp_bypassSubstitute;

    while (tmp_movenum != "165")
    {
        std::getline(iss, tmp_movenum, ',');
        std::getline(iss, tmp_name, ',');
        std::getline(iss, tmp_type, ',');
        std::getline(iss, tmp_category, ',');
        std::getline(iss, tmp_priority, ',');
        std::getline(iss, tmp_secondaryFlag, ',');
        std::getline(iss, tmp_pp, ',');
        std::getline(iss, tmp_maxpp, ',');
        std::getline(iss, tmp_power, ',');
        std::getline(iss, tmp_accuracy, ',');
        std::getline(iss, tmp_contact, ',');
        std::getline(iss, tmp_protect, ',');
        std::getline(iss, tmp_magicCoat, ',');
        std::getline(iss, tmp_snatch, ',');
        std::getline(iss, tmp_mirrorMove, ',');
        std::getline(iss, tmp_kingRock, ',');
        std::getline(iss, tmp_soundBased, ',');
        std::getline(iss, tmp_bypassSubstitute, ',');
        iss >> std::ws;

        movedex.emplace_back(std::stoi(tmp_movenum), tmp_name,
            tmp_type, ConvertStringToPokemonType(tmp_type), tmp_category, ConvertStringToCategory(tmp_category),
            std::stoi(tmp_priority), std::stoi(tmp_secondaryFlag),
            std::stoi(tmp_pp), std::stoi(tmp_maxpp), std::stoi(tmp_power), std::stoi(tmp_accuracy),
            ConvertStringToBool(tmp_contact), ConvertStringToBool(tmp_protect), ConvertStringToBool(tmp_magicCoat),
            ConvertStringToBool(tmp_snatch), ConvertStringToBool(tmp_mirrorMove), ConvertStringToBool(tmp_kingRock), ConvertStringToBool(tmp_soundBased), ConvertStringToBool(tmp_bypassSubstitute));
    }
}

// new way of setting movelist, can be done asynchronously as long as a loop copies the vector into the Pokemon's movelist after LoadPokemon() function finishes
void Database::SetPokemonMoveListASync(std::vector<std::vector<size_t>>& tmp_movelist)
{
    static std::istream::pos_type savedFilePosition{};

    if (savedFilePosition == -1) { return; }
    
    std::filesystem::path mList = "data/learnset.txt";

    std::ifstream iss(mList);

    std::string first{};
    std::string second{};
    std::string line{};

    std::string cntstr{};

    std::vector<size_t> tmp_movelist2;

    size_t numofmoves{};

    static size_t count{};

    tmp_movelist2.reserve(57);

    while (first != "151")
    {
        iss.seekg(savedFilePosition);
        while (std::getline(iss, line))
        {
            ++count;
            std::stringstream ss(line);
            std::getline(ss, first, ':');

            cntstr = std::to_string(count);

            if (first == cntstr)
            {
                while (std::getline(ss, second, ','))
                {
                    if (second == "\r")
                        break;
                    int secondint = std::stoi(second);
                    size_t secondsize_t = secondint;
                    tmp_movelist2.emplace_back(secondsize_t);
                }
                savedFilePosition = iss.tellg();
                tmp_movelist2.shrink_to_fit();
                tmp_movelist.push_back(tmp_movelist2);
                tmp_movelist2.clear();
                tmp_movelist2.reserve(57);
            }
            else if (savedFilePosition == -1)
            {
                return;
            }

            else
            {
                continue;
            }
        }
    }
}

void Database::TestingPokemonAndMoves()
{
    pokedex.emplace_back(152, "PokeTest", 100, 100, 100, 100, 100, 100, "Normal", ConvertStringToPokemonType("Normal"), "None", ConvertStringToPokemonType("None"), 1);

    std::vector<size_t> tmp_movelist2{};
    tmp_movelist2.reserve(165);
    for (size_t i = 1; i < 165; ++i)
    {
        tmp_movelist2.emplace_back(i);
    }

    pokedex[151].CopyMoveListVector(tmp_movelist2);
}

Pokemon* Database::GetPointerToPokedexNumber(size_t index)
{
    return &(pokedex[index]);
}

Move* Database::GetPointerToMovedexNumber(size_t index)
{
    return &(movedex[index]);
}

std::vector<Pokemon>::iterator Database::PokedexBegin()
{
    return pokedex.begin();
}

std::vector<Pokemon>::iterator Database::PokedexEnd()
{
    return pokedex.end();
}

std::vector<Pokemon>::const_iterator Database::cPokedexBegin() const
{
    return pokedex.cbegin();
}

std::vector<Pokemon>::const_iterator Database::cPokedexEnd() const
{
    return pokedex.cend();
}

std::vector<Move>::iterator Database::MovedexBegin()
{
    return movedex.begin();
}

std::vector<Move>::iterator Database::MovedexEnd()
{
    return movedex.end();
}

std::vector<Move>::const_iterator Database::cMovedexBegin() const
{
    return movedex.cbegin();
}

std::vector<Move>::const_iterator Database::cMovedexEnd() const
{
    return movedex.cend();
}

void Database::DisplayPokemon() const
{
    int colCount{};

    for (size_t i = 0; i < pokedex.size(); ++i)
    {
        ++colCount;

        size_t pokeNum = i + 1;

        if (pokeNum < 10)
        {
            std::cout << pokeNum << ":   ";
            std::cout << std::setw(15) << std::left << pokedex[i].GetName();
        }
        else if (pokeNum >= 10 && pokeNum <= 99)
        {
            std::cout << pokeNum << ":  ";
            std::cout << std::setw(15) << std::left << pokedex[i].GetName();
        }
        else
        {
            std::cout << pokeNum << ": ";
            std::cout << std::setw(15) << std::left << pokedex[i].GetName();
        }

        if (colCount % 6 == 0)
        {
            std::cout << '\n';
        }
    }
    std::cout << '\n';
}

void Database::DisplayMoves() const
{
    int colCount{};

    for (size_t i = 0; i < movedex.size(); ++i)
    {
        ++colCount;

        size_t moveNum = i + 1;

        if (moveNum < 10)
        {
            std::cout << moveNum << ":   ";
            std::cout << std::setw(15) << std::left << movedex[i].GetName();
        }
        else if (moveNum >= 10 && moveNum <= 99)
        {
            std::cout << moveNum << ":  ";
            std::cout << std::setw(15) << std::left << movedex[i].GetName();
        }
        else
        {
            std::cout << moveNum << ": ";
            std::cout << std::setw(15) << std::left << movedex[i].GetName();
        }

        if (colCount % 6 == 0)
        {
            std::cout << '\n';
        }
    }
    std::cout << '\n';
}

/* Old way of setting moves list which was done after instantiating each pokemon into the pokedex
void Database::SetPokemonMoveList(size_t sumnum)
{
    static std::istream::pos_type savedFilePosition{};

    if (savedFilePosition == -1) { return; }

    std::string filename = "data/learnset.txt";

    std::ifstream iss(filename);

    std::string first{};
    std::string second{};
    std::string line{};

    std::string cntstr{};

    int numofmoves{};

    static int count{};

    pokedex[count].ReserveMoveListVector(); // reserves vector size of 57, which is the max amount of moves that can be learned by a Pokemon (Mew in gen 1)

    while (first != "151")
    {
        iss.seekg(savedFilePosition);
        ++count;
        while (std::getline(iss, line))
        {
            std::stringstream ss(line);
            std::getline(ss, first, ':');

            cntstr = std::to_string(count);

            if (first == cntstr)
            {
                while (std::getline(ss, second, ','))
                {
                    if (second == "\r")
                        break;
                    int secondint = std::stoi(second);
                    int secondsize_t = secondint;
                    pokedex[sumnum].EmplaceBackIntoMoveList(secondsize_t);
                }
                savedFilePosition = iss.tellg();
                pokedex[sumnum].ShrinkToFitMoveList();
                //std::cout << "Loaded Movelist number " << sumnum + 1 << '\n';
                return;
            }
            else if (savedFilePosition == -1)
            {
                return;
            }

            else
            {
                continue;
            }
        }
    }
}
*/
