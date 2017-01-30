/**
 * @file   HouseManager.cpp
 * @brief  HouseManagerクラスの実装
 * @author morimoto
 */
#include "HouseManager.h"
#include "EventManager.h"
#include "Event\HouseBuildWindowEvent\HouseBuildWindowEvent.h"
#include "HouseCreater\HouseCreater.h"
#include "HouseBase\HouseBase.h"
#include "Event\HouseBuildWindowEvent\HouseBuildWindowEvent.h"
#include "EventListener\HouseBuildWindowEventListener\HouseBuildWindowEventListener.h"
#include "..\MousePosConverter\MousePosConverter.h"


HouseManager::HouseManager() : 
m_pHouseCreater(new HouseCreater()),
m_pEventListener(new HouseBuildWindowEventListener()),
m_State(NONE)
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);
}

HouseManager::~HouseManager()
{
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		delete m_pHouse[i];
	}

	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;
	delete m_pHouseCreater;
}

void HouseManager::Control()
{
	MouseCheck();
	StateControl();

	switch (m_State)
	{
	case NONE:

		break;
	case BUILD_STATE:
		BuildControl();
		break;
	}
}

void HouseManager::Draw()
{
	for (unsigned int i = 0; i < m_pHouse.size(); i++)
	{
		m_pHouse[i]->Draw();
	}
}

void HouseManager::MouseCheck()
{
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
}

void HouseManager::StateControl()
{
	switch (m_State)
	{
	case NONE:
		switch (m_pEventListener->GetEventType())
		{
		case HouseBuildWindowEvent::NORMAL_HOUSE_BUILD_BUTTON_CLICK:
			m_State = BUILD_STATE;
			m_BuildType = NORMAL_HOUSE;
			break;
		}
		break;
	case BUILD_STATE:
		switch (m_pEventListener->GetEventType())
		{
		case HouseBuildWindowEvent::NORMAL_HOUSE_BUILD_BUTTON_CLICK:
			m_State = BUILD_STATE;
			m_BuildType = NORMAL_HOUSE;
			break;
		}
		break;
	}

	m_pEventListener->ClearEventType();
}

void HouseManager::BuildControl()
{
	if (m_MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_RELEASE)
	{
		m_pHouseCreater->SetHousePos(&MousePosConverter::GetInstance()->GetConvertPos());
		m_pHouseCreater->SetHouseAngle(0.0f);
		m_pHouseCreater->SetHouseType(m_BuildType);
		m_pHouse.push_back(m_pHouseCreater->HouseCreate());
	}
	else if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_RELEASE)
	{
		m_State = NONE;
		HouseBuildWindowEvent::GetInstance()->SetEventType(HouseBuildWindowEvent::HOUSE_BUILD_WINDOW_EVENT_BACK);
		EventManager::GetInstance()->SendEventMessage(HouseBuildWindowEvent::GetInstance());
	}
}

