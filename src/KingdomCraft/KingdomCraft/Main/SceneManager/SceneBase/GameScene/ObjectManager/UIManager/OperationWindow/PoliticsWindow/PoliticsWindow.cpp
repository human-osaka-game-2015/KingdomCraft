/**
 * @file   PoliticsWindow.cpp
 * @brief  PoliticsWindowクラスの実装
 * @author morimoto
 */
#include "PoliticsWindow.h"
#include "..\..\..\..\EventManager\EventManager.h"
#include "..\..\..\..\EventManager\Event\OperationWindowEvent\OperationWindowEvent.h"

const D3DXVECTOR2 PoliticsWindow::m_DefaultPos = D3DXVECTOR2(-375, 300);
const D3DXVECTOR2 PoliticsWindow::m_DefaultSize = D3DXVECTOR2(600, 500);
const D3DXVECTOR2 PoliticsWindow::m_MovePos = D3DXVECTOR2(-375, 400);
const float PoliticsWindow::m_MoveSpeed = 8.0f;


PoliticsWindow::PoliticsWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pEventListener(new OperationWindowEventListener()),
m_State(NONE),
m_ParentUIPos(*_pParentUIPos)
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);
}

PoliticsWindow::~PoliticsWindow()
{
	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;
}

void PoliticsWindow::Control()
{
	MouseCheckControl();
	StateControl();

	switch (m_State)
	{
	case START_STATE:
		StartControl();
		break;
	case PROC_STATE:
		ProcControl();
		break;
	case END_STATE:
		EndControl();
		break;
	}
}

void PoliticsWindow::Draw()
{
	if (m_State == NONE)
	{
		return;
	}

	WindowDraw();
}

void PoliticsWindow::MouseCheckControl()
{
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
}

void PoliticsWindow::StateControl()
{
	switch (m_State)
	{
	case NONE:
		switch (m_pEventListener->GetEventType())
		{
		case OperationWindowEvent::POLITICS_BUTTON_CLICK:
			m_State = START_STATE;
			m_pEventListener->ClearEventType();		// イベントの処理を行ったので履歴を消去
			break;
		}
		break;
	default:
		m_pEventListener->ClearEventType();

		break;
	}
}

void PoliticsWindow::StartControl()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_State = END_STATE;
	}

	m_WindowPos.y -= m_MoveSpeed;

	if (m_WindowPos.y <= m_MovePos.y)
	{
		m_WindowPos.y = m_MovePos.y;// 座標を合わせる
		m_State = PROC_STATE;		// 次の状態に遷移
	}
}

void PoliticsWindow::ProcControl()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_State = END_STATE;
	}

}

void PoliticsWindow::EndControl()
{
	m_WindowPos.y += m_MoveSpeed;

	if (m_WindowPos.y >= (m_DefaultPos + m_ParentUIPos).y)
	{
		m_WindowPos.y = (m_DefaultPos + m_ParentUIPos).y;	// 座標を合わせる
		m_State = NONE;
	}
}

