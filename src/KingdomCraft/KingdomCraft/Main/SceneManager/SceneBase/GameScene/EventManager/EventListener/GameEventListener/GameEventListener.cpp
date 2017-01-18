/**
 * @file GameEventListener.cpp
 * @brief GameEventListenerクラス実装
 * @author morimoto
 */
#include "GameEventListener.h"
#include "..\..\Event\GameEvent\GameEvent.h"

const int GameEventListener::m_EventMessageMax = 30;


GameEventListener::GameEventListener()
{
}

GameEventListener::~GameEventListener()
{
}

void GameEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == GameEvent::GetInstance()->GetEventID())
	{
		if (m_EventTypeContainer.size() >= m_EventMessageMax)
		{
			m_EventTypeContainer.clear();
		}

		GameEvent::EVENT_TYPE EventType = reinterpret_cast<GameEvent*>(_pEvent)->GetEventType();
		m_EventTypeContainer.push_back(EventType);
	}
}

int GameEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();		// イベント情報があれば最新のものを返す
	}

	return GameEvent::NONE;
}

void GameEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}

