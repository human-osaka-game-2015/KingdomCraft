/**
 * @file KingdomWindowEventListener.cpp
 * @brief KingdomWindowEventListenerクラス実装
 * @author morimoto
 */
#include "KingdomWindowEventListener.h"
#include "..\..\Event\KingdomWindowEvent\KingdomWindowEvent.h"


KingdomWindowEventListener::KingdomWindowEventListener()
{
}

KingdomWindowEventListener::~KingdomWindowEventListener()
{
}

void KingdomWindowEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == KingdomWindowEvent::GetInstance()->GetEventID())
	{
		KingdomWindowEvent::EVENT_TYPE EventType = reinterpret_cast<KingdomWindowEvent*>(_pEvent)->GetEventType();

		m_EventTypeContainer.push_back(EventType);
	}
}

int KingdomWindowEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();
	}

	return KingdomWindowEvent::NONE;
}

void KingdomWindowEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}
