/**
 * @file EventManager.cpp
 * @brief EventManagerクラス実装
 * @author morimoto
 */
#include "EventManager.h"
#include "EventListener\EventListener.h"
#include "Event\Event.h"

EventManager* EventManager::m_pEventManager = NULL;


EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::AddEventListener(EventListener* _pEventListener)
{
	m_EventListeners.push_back(_pEventListener);
}

void EventManager::RemoveEventListener(EventListener* _pEventListener)
{
	for (unsigned int i = 0; i < m_EventListeners.size(); i++)
	{
		if (m_EventListeners[i]->GetEventListenerID() == _pEventListener->GetEventListenerID())
		{
			m_EventListeners.erase(m_EventListeners.begin() + i);
		}
	}
}

void EventManager::SendEventMessage(Event* _pEvent)
{
	for (unsigned int i = 0; i < m_EventListeners.size(); i++)
	{
		m_EventListeners[i]->EventMessage(_pEvent);
	}
}
