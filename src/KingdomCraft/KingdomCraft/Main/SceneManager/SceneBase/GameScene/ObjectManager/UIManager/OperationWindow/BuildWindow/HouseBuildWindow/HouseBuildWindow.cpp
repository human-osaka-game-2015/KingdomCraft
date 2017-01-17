/**
 * @file   HouseBuildWindow.cpp
 * @brief  HouseBuildWindowクラスの実装
 * @author morimoto
 */
#include "HouseBuildWindow.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include "EventManager.h"
#include "Event\BuildWindowEvent\BuildWindowEvent.h"
#include "NormalHouseBuildButtonUI\NormalHouseBuildButtonUI.h"

const D3DXVECTOR2 HouseBuildWindow::m_DefaultPos = D3DXVECTOR2(-30, 0);
const D3DXVECTOR2 HouseBuildWindow::m_DefaultSize = D3DXVECTOR2(500, 500);
const D3DXVECTOR2 HouseBuildWindow::m_MovePos = D3DXVECTOR2(-30, 800);
const float HouseBuildWindow::m_MoveSpeed = 4.0f;


HouseBuildWindow::HouseBuildWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pEventListener(new BuildWindowEventListener()),
m_State(NONE),
m_ParentUIPos(*_pParentUIPos)
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);

	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\HouseBuildWindow.jpg"),
		&m_TextureIndex);

	m_pButtonUI.push_back(new NormalHouseBuildButtonUI(&m_WindowPos, m_TextureIndex));
}

HouseBuildWindow::~HouseBuildWindow()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		delete m_pButtonUI[i];
	}

	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;
}

void HouseBuildWindow::Control()
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

void HouseBuildWindow::Draw()
{
	if (m_State == NONE)
	{
		return;
	}

	WindowDraw();
	ButtonUIDraw();
}

void HouseBuildWindow::MouseCheckControl()
{
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
}

void HouseBuildWindow::StateControl()
{
	switch (m_State)
	{
	case NONE:
		switch (m_pEventListener->GetEventType())
		{
		case BuildWindowEvent::HOUSE_BUILD_BUTTON_CLICK:
			m_State = START_STATE;
			break;
		}
		break;
	}

	m_pEventListener->ClearEventType();
}

void HouseBuildWindow::StartControl()
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

void HouseBuildWindow::ProcControl()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_State = END_STATE;
	}

	ButtonUIControl();
}

void HouseBuildWindow::EndControl()
{
	m_WindowPos.y += m_MoveSpeed;

	if (m_WindowPos.y >= (m_DefaultPos + m_ParentUIPos).y)
	{
		m_WindowPos.y = (m_DefaultPos + m_ParentUIPos).y;	// 座標を合わせる
		m_State = NONE;

		BuildWindowEvent::GetInstance()->SetEventType(BuildWindowEvent::BUILD_WINDOW_BACK);	// 建設ウィンドウに処理を戻す
		EventManager::GetInstance()->SendEventMessage(BuildWindowEvent::GetInstance());
	}
}

void HouseBuildWindow::ButtonUIControl()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Control();
	}
}

void HouseBuildWindow::ButtonUIDraw()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Draw();
	}
}

