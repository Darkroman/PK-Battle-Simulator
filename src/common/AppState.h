#pragma once

enum class AppState
{ 
	MainMenu, 
	InitBattle, 
	Battle, 
	Victory,
	Simulate,
	Exit
};

struct MenuResult
{
	AppState appState;
	unsigned int simIterations{ 1 };
};