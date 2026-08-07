#pragma once

#include <queue>
#include <variant>
#include <array>
#include <string_view>

#include "BattleEvents.h"
#include "EffectivenessText.h"
#include "../entities/BattlePokemon.h"

class IOutputTarget;

struct QueuedUIEvent
{
	BattleEvents event;
	using UIArg = std::variant<std::monostate, std::string_view, unsigned int, int, size_t, EffectivenessText, Status>;
	std::array<UIArg, 4> args{};
};

class BattleUIEventQueue
{
public:
	void PushEvent(QueuedUIEvent event);
	void ProcessNextEvent(IOutputTarget&);

private:
	std::queue<QueuedUIEvent> m_queue{};
};