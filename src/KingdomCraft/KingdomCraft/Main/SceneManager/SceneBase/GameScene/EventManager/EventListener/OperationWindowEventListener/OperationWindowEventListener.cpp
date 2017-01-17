/**
 * @file OperationWindowEventListener.cpp
 * @brief OperationWindowEventListenerクラス実装
 * @author morimoto
 */
#include "OperationWindowEventListener.h"
#include "..\..\Event\OperationWindowEvent\OperationWindowEvent.h"


OperationWindowEventListener::OperationWindowEventListener()
{
}

OperationWindowEventListener::~OperationWindowEventListener()
{
}

void OperationWindowEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == OperationWindowEvent::GetInstance()->GetEventID())
	{
		if (m_EventTypeContainer.size() >= m_EventMessageMax)
		{
			m_EventTypeContainer.clear();	/// @todo 古い順から削除したいけどとりあえずこれでやる
		}

		OperationWindowEvent::EVENT_TYPE EventType = reinterpret_cast<OperationWindowEvent*>(_pEvent)->GetEventType();
		m_EventTypeContainer.push_back(EventType);
	}
}

int OperationWindowEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();		// イベント情報があれば最新のものを返す
	}

	return OperationWindowEvent::NONE;
}

void OperationWindowEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}
