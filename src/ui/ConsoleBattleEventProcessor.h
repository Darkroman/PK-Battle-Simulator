#pragma once

class BattleEventQueue;
class IOutputTarget;

class ConsoleBattleEventProcessor
{
public:
	ConsoleBattleEventProcessor(BattleEventQueue& eventQueue, IOutputTarget& outputTarget);

	void ProcessEvents();

private:
	BattleEventQueue& m_eventQueue;
	IOutputTarget& m_outputTarget;
};