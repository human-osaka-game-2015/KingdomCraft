/**
 * @file BuildWindowEventListener.cpp
 * @brief BuildWindowEventListenerクラス実装
 * @author morimoto
 */
#include "BuildWindowEventListener.h"
#include "..\..\Event\BuildWindowEvent\BuildWindowEvent.h"


BuildWindowEventListener::BuildWindowEventListener()
{
}

BuildWindowEventListener::~BuildWindowEventListener()
{
}

void BuildWindowEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == BuildWindowEvent::GetInstance()->GetEventID())
	{
		if (m_EventTypeContainer.size() >= m_EventMessageMax)
		{
			m_EventTypeContainer.clear();	/// @todo 古い順から削除したいけどとりあえずこれでやる
		}

		BuildWindowEvent::EVENT_TYPE EventType = reinterpret_cast<BuildWindowEvent*>(_pEvent)->GetEventType();
		m_EventTypeContainer.push_back(EventType);
	}
}

int BuildWindowEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();		// イベント情報があれば最新のものを返す
	}

	return BuildWindowEvent::NONE;
}

void BuildWindowEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}

