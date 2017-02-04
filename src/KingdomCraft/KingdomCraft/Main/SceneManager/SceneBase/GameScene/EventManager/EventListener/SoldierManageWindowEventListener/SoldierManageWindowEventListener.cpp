/**
 * @file SoldierManageWindowEventListener.cpp
 * @brief SoldierManageWindowEventListenerクラス実装
 * @author morimoto
 */
#include "SoldierManageWindowEventListener.h"
#include "..\..\Event\SoldierManageWindowEvent\SoldierManageWindowEvent.h"


SoldierManageWindowEventListener::SoldierManageWindowEventListener()
{
}

SoldierManageWindowEventListener::~SoldierManageWindowEventListener()
{
}

void SoldierManageWindowEventListener::EventMessage(Event* _pEvent)
{
	if (_pEvent->GetEventID() == SoldierManageWindowEvent::GetInstance()->GetEventID())
	{
		if (m_EventTypeContainer.size() >= m_EventMessageMax)
		{
			m_EventTypeContainer.clear();	/// @todo 古い順から削除したいけどとりあえずこれでやる
		}

		SoldierManageWindowEvent::EVENT_TYPE EventType = reinterpret_cast<SoldierManageWindowEvent*>(_pEvent)->GetEventType();
		m_EventTypeContainer.push_back(EventType);
	}
}

int SoldierManageWindowEventListener::GetEventType()
{
	if (!m_EventTypeContainer.empty())
	{
		return m_EventTypeContainer.back();		// イベント情報があれば最新のものを返す
	}

	return SoldierManageWindowEvent::NONE;
}

void SoldierManageWindowEventListener::ClearEventType()
{
	m_EventTypeContainer.clear();
}
