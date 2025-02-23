# PK-Battle-Simulator

## UPDATES
### 2/23/2025
- Fixed damage calculation bug
- Metronome and Mirror Move should now work correctly.

### 2/19/2025:
- Fixed damage calculation bug when light screen or reflect are up.
- "Set EV" menu now displays correctly max EV per stat as 252 instead of 255
- When showing stats in edit stats menu, speed stat now outputs.
- Counter correctly does 2x damage taken (originally had it like that but I changed stuff around and just forgot to readd in multiplying the variable by 2)
- Disable should now correctly fail when used on Struggle
- When choosing to fight with no moves left, will now automatically choose Struggle

### 2/18/2025:
- Added easy A.I (just picks random move and switches to next Pokemon in line when it faints).
- Note the default player settings is human. Make sure to set one of em to A.I if you wanna play against the computer, or both to A.I for funsies.
- Some bug fixes with Bound damage, Reflect actually checking if it's already up rather than Light Screen, and some text dialog fixes.

## BUILD NOTES
My IDE of choice is Visual Studio, utilizing C++20 standard. Uploaded is a simple CMake build, as well as a binary release if you just want to download and play. Only tested on Windows.

## GENERAL INFO
This is just a small console based Pokemon battle simulator program. I started this project a long time ago and have been working on it off and on while also learning C++. I wanted to put what I've learned to practice, and Pokemon is one of my most cherished gaming series of all time. I don't plan on making this into a full graphical game (as there are also some copyright issues with that in any case). Just something to put out there to show what I've learned so far. Along with future updates I hope to be more proficient at architectural/code organization design.

## FEATURES
- All of the generation 1 Pokemon
- All 165 moves and their respective secondary effects
- IVs, and EVs
- Mechanics are based on latest generation (except fairy, steel, and dark typing, besides the move "Bite")
- No natures, held items, or abilities.
- Physical/Special move split from gen 4 onward implemented.

## PLANNED UPDATES
- More sophisticated A.I
- Code architectural/organizational choices
- Not sure if I'll ever add in later generation stuff
