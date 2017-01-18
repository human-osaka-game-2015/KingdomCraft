/**
 * @file EventListener.cpp
 * @brief EventListenerクラス実装
 * @author morimoto
 */
#include "EventListener.h"

const unsigned int EventListener::m_EventMessageMax = 30;
int EventListener::m_EventListenerNum = 0;


EventListener::EventListener()
{
	m_EventListenerNum++;
	m_EventListenerID = m_EventListenerNum;
}

EventListener::~EventListener()
{
}

void EventListener::EventMessage(Event* _pEvent)
{

}
