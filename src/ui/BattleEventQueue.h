#pragma once

#include <queue>

#include "BattleEvents.h"

class BattleEventQueue
{
public:
    void PushEvent(QueuedBattleEvent event);

    [[nodiscard]]
    bool Empty() const noexcept;

    [[nodiscard]]
    QueuedBattleEvent TakeNextEvent();

private:
    std::queue<QueuedBattleEvent> m_queue{};
};