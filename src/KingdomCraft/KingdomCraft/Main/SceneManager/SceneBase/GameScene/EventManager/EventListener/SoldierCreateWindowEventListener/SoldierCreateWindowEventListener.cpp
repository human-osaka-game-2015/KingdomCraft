#include "SoldierCreateWindowEventListener.h"
#include "Event\SoldierCreateWindowEvent\SoldierCreateWindowEvent.h"


SoldierCreateWindowEventListener::SoldierCreateWindowEventListener()
{
}

SoldierCreateWindowEventListener::~SoldierCreateWindowEventListener()
{
}

void SoldierCreateWindowEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == SoldierCreateWindowEvent::GetInstance()->GetEventID())
	{
		if (m_EventTypeContainer.size() >= m_EventMessageMax)
		{
			m_EventTypeContainer.clear();	/// @todo 古い順から削除したいけどとりあえずこれでやる
		}

		SoldierCreateWindowEvent::EVENT_TYPE EventType = reinterpret_cast<SoldierCreateWindowEvent*>(_pEvent)->GetEventType();
		m_EventTypeContainer.push_back(EventType);
	}
}

int SoldierCreateWindowEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();		// イベント情報があれば最新のものを返す
	}

	return SoldierCreateWindowEvent::NONE;
}

void SoldierCreateWindowEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}
