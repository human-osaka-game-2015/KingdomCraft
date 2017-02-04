/**
 * @file   SoldierManageWindow.cpp
 * @brief  SoldierManageWindowクラスの実装
 * @author morimoto
 */
#include "SoldierManageWindow.h"
#include "EventManager.h"
#include "EventListener\PoliticsWindowEventListener\PoliticsWindowEventListener.h"
#include "EventListener\SoldierManageWindowEventListener\SoldierManageWindowEventListener.h"
#include "Event\PoliticsWindowEvent\PoliticsWindowEvent.h"
#include "Event\SoldierManageWindowEvent\SoldierManageWindowEvent.h"
#include "SoldierCreateButtonUI\SoldierCreateButtonUI.h"
#include "SoldierDestroyButtonUI\SoldierDestroyButtonUI.h"
#include "SoldierDispatchButtonUI\SoldierDispatchButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SoldierManageWindow::m_DefaultPos = D3DXVECTOR2(-30, 0);
const D3DXVECTOR2 SoldierManageWindow::m_DefaultSize = D3DXVECTOR2(500, 500);
const D3DXVECTOR2 SoldierManageWindow::m_MovePos = D3DXVECTOR2(-30, 800);
const float	SoldierManageWindow::m_MoveSpeed = 5.0f;


SoldierManageWindow::SoldierManageWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pParentEventListener(new PoliticsWindowEventListener()),
m_pEventListener(new SoldierManageWindowEventListener()),
m_State(NONE),
m_ParentUIPos(*_pParentUIPos)
{
	EventManager::GetInstance()->AddEventListener(m_pParentEventListener);
	EventManager::GetInstance()->AddEventListener(m_pEventListener);

	TextureManager::GetInstance()->LoadTexture("Resource\\Texture\\GameScene\\UI\\SoldierManageWindow.png", &m_TextureIndex);

	m_pButtonUI.push_back(new SoldierCreateButtonUI(&m_WindowPos, m_TextureIndex));
	m_pButtonUI.push_back(new SoldierDestroyButtonUI(&m_WindowPos, m_TextureIndex));
	m_pButtonUI.push_back(new SoldierDispatchButtonUI(&m_WindowPos, m_TextureIndex));
}

SoldierManageWindow::~SoldierManageWindow()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		delete m_pButtonUI[i];
	}

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);

	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;

	EventManager::GetInstance()->RemoveEventListener(m_pParentEventListener);
	delete m_pParentEventListener;
}

void SoldierManageWindow::Control()
{
	MouseCheckControl();
	EventMessageControl();

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

void SoldierManageWindow::Draw()
{
	if (m_State == NONE)
	{
		return;
	}

	WindowDraw();
	ButtonUIDraw();
}

void SoldierManageWindow::MouseCheckControl()
{
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
}

void SoldierManageWindow::EventMessageControl()
{
	switch (m_State)
	{
	case NONE:
		switch (m_pParentEventListener->GetEventType())
		{
		case PoliticsWindowEvent::SOLDIER_MANAGE_BUTTON_CLICK:
			m_State = START_STATE;
			break;
		}
		break;
	case WAIT_STATE:
		switch (m_pEventListener->GetEventType())
		{
		case SoldierManageWindowEvent::SOLDIER_MANAGE_WINDOW_BACK:
			m_State = PROC_STATE;
			break;
		}
		break;
	case PROC_STATE:
		switch (m_pEventListener->GetEventType())
		{
		case SoldierManageWindowEvent::SOLDIER_CREATE_BUTTON_CLICK:
			m_State = WAIT_STATE;
			break;
		case SoldierManageWindowEvent::SOLDIER_DESTROY_BUTTON_CLICK:
			m_State = WAIT_STATE;
			break;
		case SoldierManageWindowEvent::SOLDIER_DISPATCH_BUTTON_CLICK:
			m_State = WAIT_STATE;
			break;
		}
		break;
	}

	m_pParentEventListener->ClearEventType();
	m_pEventListener->ClearEventType();
}

void SoldierManageWindow::WaitControl()
{
	ButtonUIControl();
}

void SoldierManageWindow::StartControl()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_State = END_STATE;
	}

	m_WindowPos.y -= m_MoveSpeed;

	if (m_WindowPos.y <= m_MovePos.y)
	{
		m_WindowPos.y = m_MovePos.y;
		m_State = PROC_STATE;
	}
}

void SoldierManageWindow::ProcControl()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_State = END_STATE;
	}

	ButtonUIControl();
}

void SoldierManageWindow::EndControl()
{
	m_WindowPos.y += m_MoveSpeed;

	if (m_WindowPos.y >= D3DXVECTOR2(m_DefaultPos + m_ParentUIPos).y)
	{
		m_WindowPos.y = D3DXVECTOR2(m_DefaultPos + m_ParentUIPos).y;	// 座標を合わせる
		m_State = NONE;

		PoliticsWindowEvent::GetInstance()->SetEventType(PoliticsWindowEvent::POLITICS_WINDOW_BACK);
		EventManager::GetInstance()->SendEventMessage(PoliticsWindowEvent::GetInstance());
	}
}

void SoldierManageWindow::ButtonUIControl()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Control();
	}
}

void SoldierManageWindow::ButtonUIDraw()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Draw();
	}
}

