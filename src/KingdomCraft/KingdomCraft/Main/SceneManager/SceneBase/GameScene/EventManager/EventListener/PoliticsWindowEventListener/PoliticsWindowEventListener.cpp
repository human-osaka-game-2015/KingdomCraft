/**
 * @file PoliticsWindowEventListener.cpp
 * @brief PoliticsWindowEventListenerクラス実装
 * @author morimoto
 */
#include "PoliticsWindowEventListener.h"
#include "..\..\Event\PoliticsWindowEvent\PoliticsWindowEvent.h"


PoliticsWindowEventListener::PoliticsWindowEventListener()
{
}

PoliticsWindowEventListener::~PoliticsWindowEventListener()
{
}

void PoliticsWindowEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == PoliticsWindowEvent::GetInstance()->GetEventID())
	{
		if (m_EventTypeContainer.size() >= m_EventMessageMax)
		{
			m_EventTypeContainer.clear();	/// @todo 古い順から削除したいけどとりあえずこれでやる
		}

		PoliticsWindowEvent::EVENT_TYPE EventType = reinterpret_cast<PoliticsWindowEvent*>(_pEvent)->GetEventType();
		m_EventTypeContainer.push_back(EventType);
	}
}

int PoliticsWindowEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();		// イベント情報があれば最新のものを返す
	}

	return PoliticsWindowEvent::NONE;
}

void PoliticsWindowEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}
