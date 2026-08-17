#include <utility>

#include "BattleEventQueue.h"

#include "BattleEvents.h"

void BattleEventQueue::PushEvent(QueuedBattleEvent event)
{
	m_queue.push(event);
}

bool BattleEventQueue::Empty() const noexcept
{
	return m_queue.empty();
}

QueuedBattleEvent BattleEventQueue::TakeNextEvent()
{
	QueuedBattleEvent event = std::move(m_queue.front());
	m_queue.pop();

	return event;
}