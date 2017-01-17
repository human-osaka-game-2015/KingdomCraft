/**
 * @file GameTimeEventListener.cpp
 * @brief GameTimeEventListenerクラス実装
 * @author morimoto
 */
#include "GameTimeEventListener.h"
#include "..\..\Event\GameTimeEvent\GameTimeEvent.h"


GameTimeEventListener::GameTimeEventListener()
{
}

GameTimeEventListener::~GameTimeEventListener()
{
}

void GameTimeEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == GameTimeEvent::GetInstance()->GetEventID())
	{
		if (m_EventTypeContainer.size() >= m_EventMessageMax)
		{
			m_EventTypeContainer.clear();	/// @todo 古い順から削除したいけどとりあえずこれでやる
		}

		GameTimeEvent::EVENT_TYPE EventType = reinterpret_cast<GameTimeEvent*>(_pEvent)->GetEventType();
		m_EventTypeContainer.push_back(EventType);
	}
}

int GameTimeEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();		// イベント情報があれば最新のものを返す
	}

	return GameTimeEvent::NONE;
}

void GameTimeEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}
