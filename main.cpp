#include "include/Game.h"

// Work in progress text based Pokemon battle simulator by Darkroman! Many things I still have to do:
/* TODO:
---DONE: Add in async for loading Pokemon and Moves
---DONE: Add in a move exclusion (or inclusion) list for each Pokemon object
---DONE: Check if Pokemon is able to learn a move
---DONE: Add in move flags for their secondary effects (e.g increased critical hit, multi-attack moves, recharge, stat modifiers etc)
---DONE: Creating menu class to traverse, and modify data of Players and BattlePokemon
---DONE: Save and load party setups
---IN PROGRESS: Creating the Battle class which will handle all the logic associated with the attributes of BattlePokemon selected by Player
---Battle class will have many states e.g: send out Pokemon, handle type advantages/disadvantages, move status effects, relaying message of state to user, update Pokemon stats
---Computer A.I.
---LEARN: The whole point of writing this program was to teach myself how to go about doing things if I wanted to make my own application, and learn how to best structure code
---       using OOP as I go along. I always have the mindset of "Can I do this better?" when writing this.
---       I'm also still reading from C++ Primer, C++ Professional, and PP&P (and a lot of Google+Youtube)
// SCOPE:
---Only using 1st generation Pokemon, and no abilities or natures
---Pokemon will have their original 1st generation typing (no fairy, dark or steel types)
---Moves will use the latest (as of time of this writing 9th generation) attributes, but only will include moves from 1st generation
---Moves such as Bite will have dark typing
---Will have split special stats and move physical/special split. The former happened in Gen 2, and the latter happened in Gen 4.
---SCOPE MAY CHANGE IN FUTURE UPDATES depending on how deep I want to go into this (e.g more moves, more Pokemon, and *shudders* add in abilities and held items)
// NOTES:
---Database loads Pokemon and moves from text files and instantiates each Pokemon and Move object into their respective vector of objects
*/

int main(int argc, char* argv[])
{
    RunGame();
}