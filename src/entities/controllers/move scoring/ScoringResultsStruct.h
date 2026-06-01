#pragma once

#include "AIScoreTag.h"

struct pokemonMove;

struct ScoringResults
{
	unsigned int damage{};
	int score{ 0 };
	pokemonMove* move{};
	AIScoreTag tag{};
};