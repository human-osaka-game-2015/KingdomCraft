/**
 * @file   BuildWindow.cpp
 * @brief  BuildWindowクラスの実装
 * @author morimoto
 */
#include "BuildWindow.h"
#include "..\..\..\..\EventManager\EventManager.h"
#include "..\..\..\..\EventManager\Event\OperationWindowEvent\OperationWindowEvent.h"

const D3DXVECTOR2 BuildWindow::m_DefaultPos = D3DXVECTOR2(-20, 295);
const D3DXVECTOR2 BuildWindow::m_DefaultSize = D3DXVECTOR2(500, 500);
const D3DXVECTOR2 BuildWindow::m_MovePos = D3DXVECTOR2(-20, 790);
const float BuildWindow::m_MoveSpeed = 4.0f;


BuildWindow::BuildWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pEventListener(new OperationWindowEventListener()),
m_State(NONE),
m_ParentUIPos(*_pParentUIPos)
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);
}

BuildWindow::~BuildWindow()
{
	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;
}

void BuildWindow::Control()
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

void BuildWindow::Draw()
{
	if (m_State == NONE)
	{
		return;
	}

	WindowDraw();

	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Draw();
	}
}

void BuildWindow::MouseCheckControl()
{
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
}

void BuildWindow::StateControl()
{
	switch (m_State)
	{
	case NONE:
		switch (m_pEventListener->GetEventType())
		{
		case OperationWindowEvent::BUILD_BUTTON_CLICK:
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

void BuildWindow::StartControl()
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

void BuildWindow::ProcControl()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_State = END_STATE;
	}

	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Control();
	}
}

void BuildWindow::EndControl()
{
	m_WindowPos.y += m_MoveSpeed;

	if (m_WindowPos.y >= (m_DefaultPos + m_ParentUIPos).y)
	{
		m_WindowPos.y = (m_DefaultPos + m_ParentUIPos).y;	// 座標を合わせる
		m_State = NONE;
	}
}
