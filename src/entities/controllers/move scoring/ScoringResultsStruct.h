#pragma once

enum class AIScoreTag;
struct PokemonMoveSlot;

struct ScoringResults
{
	PokemonMoveSlot* move{};
	AIScoreTag tag{};
	unsigned int damage{};
	int score{ 0 };
};