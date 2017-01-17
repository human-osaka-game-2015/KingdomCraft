/**
 * @file HouseBuildWindowEventListener.cpp
 * @brief HouseBuildWindowEventListenerクラス実装
 * @author morimoto
 */
#include "HouseBuildWindowEventListener.h"
#include "Event\HouseBuildWindowEvent\HouseBuildWindowEvent.h"


HouseBuildWindowEventListener::HouseBuildWindowEventListener()
{
}

HouseBuildWindowEventListener::~HouseBuildWindowEventListener()
{
}

void HouseBuildWindowEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == HouseBuildWindowEvent::GetInstance()->GetEventID())
	{
		HouseBuildWindowEvent::EVENT_TYPE EventType = reinterpret_cast<HouseBuildWindowEvent*>(_pEvent)->GetEventType();
		m_EventTypeContainer.push_back(EventType);
	}
}

int HouseBuildWindowEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();		// イベント情報があれば最新のものを返す
	}

	return HouseBuildWindowEvent::NONE;
}

void HouseBuildWindowEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}
