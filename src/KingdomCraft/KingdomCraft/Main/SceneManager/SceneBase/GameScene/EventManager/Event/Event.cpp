/**
 * @file Event.cpp
 * @brief Eventクラス実装
 * @author morimoto
 */
#include "Event.h"

const int Event::m_ErrorID = -1;
int Event::m_EventNum = 0;


Event::Event()
{
	m_EventNum++;
}

Event::~Event()
{
}
