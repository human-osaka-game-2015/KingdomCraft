/**
 * @file   KingdomWindow.cpp
 * @brief  KingdomWindowクラスの実装
 * @author morimoto
 */
#include "KingdomWindow.h"
#include "EventManager.h"
#include "Event\KingdomWindowEvent\KingdomWindowEvent.h"
#include "EventListener\KingdomWindowEventListener\KingdomWindowEventListener.h"

const D3DXVECTOR2 KingdomWindow::m_DefaultWindowPos = D3DXVECTOR2(640, 340);
const D3DXVECTOR2 KingdomWindow::m_DefaultWindowSize = D3DXVECTOR2(700, 700);


KingdomWindow::KingdomWindow() :
WindowUI(&D3DXVECTOR2(m_DefaultWindowPos), &m_DefaultWindowSize),
m_pEventListener(new KingdomWindowEventListener()),
m_State(NONE)
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);
}

KingdomWindow::~KingdomWindow()
{
	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;
}

void KingdomWindow::Control()
{
	MouseCheckControl();
	StateControl();

	if (m_IsVisible == false)
	{
		return;
	}

	switch (m_State)
	{
	case PROC_STATE:
		ProcControl();
		break;
	}
}

void KingdomWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	switch (m_State)
	{
	case PROC_STATE:
		WindowDraw();
		break;
	}
}

void KingdomWindow::StateControl()
{
	switch (m_State)
	{
	case NONE:
		switch (m_pEventListener->GetEventType())
		{
		case KingdomWindowEvent::PUSH_BUTTON:
			m_State = PROC_STATE;
			break;
		}
		break;
	}

	m_pEventListener->ClearEventType();
}

void KingdomWindow::MouseCheckControl()
{
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
}

void KingdomWindow::ProcControl()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_RELEASE)
	{
		m_State = NONE;
	}
}
