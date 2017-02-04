/**
 * @file   SoldierCreateWindow.cpp
 * @brief  SoldierCreateWindowクラスの実装
 * @author morimoto
 */
#include "SoldierCreateWindow.h"
#include "EventManager.h"
#include "Event\SoldierManageWindowEvent\SoldierManageWindowEvent.h"
#include "EventListener\SoldierManageWindowEventListener\SoldierManageWindowEventListener.h"
#include "SoldierNumSelect\SoldierNumSelect.h"
#include "SoldierTypeSelect\SoldierTypeSelect.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SoldierCreateWindow::m_DefaultPos = D3DXVECTOR2(640, 1000);
const D3DXVECTOR2 SoldierCreateWindow::m_DefaultSize = D3DXVECTOR2(500, 500);
const D3DXVECTOR2 SoldierCreateWindow::m_MovePos = D3DXVECTOR2(0, 400);
const float	SoldierCreateWindow::m_MoveSpeed = 8.0f;


SoldierCreateWindow::SoldierCreateWindow() : 
WindowUI(&m_DefaultPos, &m_DefaultSize),
m_pEventListener(new SoldierManageWindowEventListener())
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);

	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\SoldierCreateWindow.png"), 
		&m_TextureIndex);

	m_pSoldierNumSelect = new SoldierNumSelect();
	m_pSoldierTypeSelect = new SoldierTypeSelect(&m_WindowPos, m_TextureIndex);
}

SoldierCreateWindow::~SoldierCreateWindow()
{
	delete m_pSoldierTypeSelect;
	delete m_pSoldierNumSelect;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);

	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;
}

void SoldierCreateWindow::Control()
{
	MouseCheckControl();
	EventMessageControl();

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

void SoldierCreateWindow::Draw()
{
	if (m_State == NONE)
	{
		return;
	}

	WindowDraw();
	m_pSoldierTypeSelect->Draw();
}

void SoldierCreateWindow::MouseCheckControl()
{
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
}

void SoldierCreateWindow::EventMessageControl()
{
	switch (m_State)
	{
	case NONE:
		switch (m_pEventListener->GetEventType())
		{
		case SoldierManageWindowEvent::SOLDIER_CREATE_BUTTON_CLICK:
			m_State = START_STATE;
			break;
		}
		break;
	}

	m_pEventListener->ClearEventType();
}

void SoldierCreateWindow::StartControl()
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

void SoldierCreateWindow::ProcControl()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_State = END_STATE;
	}

	m_pSoldierTypeSelect->Control();
}

void SoldierCreateWindow::EndControl()
{
	m_WindowPos.y += m_MoveSpeed;

	if (m_WindowPos.y >= m_DefaultPos.y)
	{
		m_WindowPos.y = m_DefaultPos.y;	// 座標を合わせる
		m_State = NONE;

		SoldierManageWindowEvent::GetInstance()->SetEventType(SoldierManageWindowEvent::SOLDIER_MANAGE_WINDOW_BACK);
		EventManager::GetInstance()->SendEventMessage(SoldierManageWindowEvent::GetInstance());
	}
}

