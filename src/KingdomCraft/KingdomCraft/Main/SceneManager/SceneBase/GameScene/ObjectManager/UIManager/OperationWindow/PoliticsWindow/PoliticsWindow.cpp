/**
 * @file   PoliticsWindow.cpp
 * @brief  PoliticsWindowクラスの実装
 * @author morimoto
 */
#include "PoliticsWindow.h"
#include "EventManager.h"
#include "Event\OperationWindowEvent\OperationWindowEvent.h"
#include "EventListener\OperationWindowEventListener\OperationWindowEventListener.h"
#include "Event\PoliticsWindowEvent\PoliticsWindowEvent.h"
#include "EventListener\PoliticsWindowEventListener\PoliticsWindowEventListener.h"
#include "SoldierManageButtonUI\SoldierManageButtonUI.h"
#include "SoldierManageWindow\SoldierManageWindow.h"
#include "SoldierCreateWindow\SoldierCreateWindow.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 PoliticsWindow::m_DefaultPos = D3DXVECTOR2(-70, 300);
const D3DXVECTOR2 PoliticsWindow::m_DefaultSize = D3DXVECTOR2(500, 500);
const D3DXVECTOR2 PoliticsWindow::m_MovePos = D3DXVECTOR2(-70, 820);
const float PoliticsWindow::m_MoveSpeed = 4.0f;


PoliticsWindow::PoliticsWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pParentEventListener(new OperationWindowEventListener()),
m_pEventListener(new PoliticsWindowEventListener()),
m_State(NONE),
m_ParentUIPos(*_pParentUIPos)
{
	EventManager::GetInstance()->AddEventListener(m_pParentEventListener);
	EventManager::GetInstance()->AddEventListener(m_pEventListener);

	TextureManager::GetInstance()->LoadTexture("Resource\\Texture\\GameScene\\UI\\PoliticsWindow.png", &m_TextureIndex);

	m_pWindowUI.push_back(new SoldierManageWindow(&m_WindowPos));
	m_pWindowUI.push_back(new SoldierCreateWindow());

	m_pButtonUI.push_back(new SoldierManageButtonUI(&m_WindowPos, m_TextureIndex));
}

PoliticsWindow::~PoliticsWindow()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		delete m_pButtonUI[i];
	}

	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		delete m_pWindowUI[i];
	}

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);

	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;

	EventManager::GetInstance()->RemoveEventListener(m_pParentEventListener);
	delete m_pParentEventListener;
}

void PoliticsWindow::Control()
{
	MouseCheckControl();
	StateControl();

	switch (m_State)
	{
	case WAIT_STATE:
		WaitControl();
		break;
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
	
	ButtonUIDraw();
	WindowUIDraw();
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
		switch (m_pParentEventListener->GetEventType())
		{
		case OperationWindowEvent::POLITICS_BUTTON_CLICK:
			m_State = START_STATE;
			break;
		}
		break;
	case WAIT_STATE:
		switch (m_pEventListener->GetEventType())
		{
		case PoliticsWindowEvent::POLITICS_WINDOW_BACK:
			m_State = PROC_STATE;
			break;
		}
		break;
	case PROC_STATE:
		switch (m_pEventListener->GetEventType())
		{
		case PoliticsWindowEvent::SOLDIER_MANAGE_BUTTON_CLICK:
			m_State = WAIT_STATE;
			break;
		}
		break;
	}

	m_pParentEventListener->ClearEventType();
	m_pEventListener->ClearEventType();
}

void PoliticsWindow::WaitControl()
{
	ButtonUIControl();
	WindowUIControl();
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

	ButtonUIControl();
	WindowUIControl();
}

void PoliticsWindow::EndControl()
{
	m_WindowPos.y += m_MoveSpeed;

	if (m_WindowPos.y >= (m_DefaultPos + m_ParentUIPos).y)
	{
		m_WindowPos.y = (m_DefaultPos + m_ParentUIPos).y;	// 座標を合わせる
		m_State = NONE;

		OperationWindowEvent::GetInstance()->SetEventType(OperationWindowEvent::OPERATION_WINDOW_BACK);	// 操作ウィンドウに処理を戻す
		EventManager::GetInstance()->SendEventMessage(OperationWindowEvent::GetInstance());
	}
}

void PoliticsWindow::ButtonUIControl()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Control();
	}
}

void PoliticsWindow::ButtonUIDraw()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Draw();
	}
}

void PoliticsWindow::WindowUIControl()
{
	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		m_pWindowUI[i]->Control();
	}
}

void PoliticsWindow::WindowUIDraw()
{
	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		m_pWindowUI[i]->Draw();
	}
}

