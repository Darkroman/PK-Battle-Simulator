**_main.cpp_** has just one function which is **RunGame()** declared and defined in _Game.h_.

**_Game.h_** instantiates a **Database** object and 2 **Player** objects in a vector and passes them to the **Menu** and **BattleSystem** constructors. The top game loop is here. std::chrono is also used here around timing the instantiation of the Database object.

**_Pokemon.h/cpp_** is the base **Pokemon** class that will be instantiated based on data read from a text file through the **Database** class. It will hold data such as their name, typing, and base stats.

**_Move.h/cpp_** is the base **Move** class that will be instantiated based on data read from a text file through the **Database** class. It will hold data such as the move's name, its max PP, base power, physical/special/status category and typing, secondary move effect flag, as well as special boolean flags.

**_Database.h/cpp_** is the **Database** Meyer's Singleton class that reads from 3 text files to instantiate the **Pokemon** class instances in the pokedex std::vector, **Move** class instances to the movedex std::vector, and loads the respective Pokemon movesets to their own internal moveset vectors held in the **Pokemon** instances. The **LoadPokemon()** and **LoadMoves()** methods are launched via std::async in the class constructor. **SetPokemonMoveListAsync()** is the method that loads the movesets for each Pokemon.

**_Player.h/cpp_** is the **Player** class that holds an array of 6 default initialized **BattlePokemon** class instances, as well as player's name, and field effects. It also keeps track of Pokemon count and fainted count.

**_Menu.h/cpp_** class is all methods to expose to the user for adding and changing a player's Pokemon, its moves, its stats, as well as the player's name and type (human or A.I). It also has a save party and load party feature so you don't have to remake your party everytime you relaunch the program. You also start the battle from here.

**_BattlePokemon.h/cpp_** is the **BattlePokemon** class. Its instances are set through the **Menu** class methods based on user's choices. On construction it assigns a pointer to the respective **Pokemon** instance to derive all its stats and movepool from. It also holds their non-volatile status effects in an enum class, since only one of those can be applied at a time, and volatile statuses are held via a bool each since those can all be active at once, as well as methods to act on them.

**_BattleSystem.h/cpp_** is the BattleSystem class which has all the battle related data and methods. It has methods for calculating critical hits, stat stage modifiers, overall damage and the flow of the variety of status conditions and field effects.
There are some static data members so the child class **IMoveEffects** and its derived methods can share some of the same data members.
It also exposes the user to options for battling, where you can choose a move for your Pokemon, switch to other Pokemon mid-battle, or forfeit battle.
BattleLoop() is the main loop of the class.

**_MoveEffects.h/cpp_** is how all the secondary move effects are implemented and called. They're implemented via a factory method pattern. **IMoveEffects** is an interface, or pure virtual class derived from **BattleSystem**. Every secondary move effect is derived from the **IMoveEffects** class.
The **MoveEffectsFactory** class has the **Call()** method that takes in the user's selected move's secondary flag as a parameter. The **Call()** method then returns a std::unique_ptr based on the switch case. **MoveEffectsFactory** is instantiated in the **BattleSystem's BattleLoop()** method, as well as **Metronome** and **MirrorMove** methods.

**_LoadParty.h/cpp_** is a class that receives input from the user to read a txt file from disk, either PlayerOneSave.txt or PlayerTwoSave.txt, and instantiates a Player's name, and their saved party of Pokemon, moves, and stats.

**_SaveParty.h/cpp_** is a class writes in truncation mode to either PlayerOneSave.txt or PlayerTwoSave.txt and saves their respective player name, Pokemon, moves, and stats.

**_StringToTypes.h/cpp_** defines std::maps for converting strings to enums and functions to convert the strings to their respective enum class types used in instantiating Pokemon and Move objects. It also holds a function to convert a string to a bool.

**_InputValidation.h_** has a couple free functions to check user input on whether the std::cin **IsDigits** and a **CheckUserInput** method that utilizes the std::transform algorithm so the input isn't case sensitive.
