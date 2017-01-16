/**
 * @file   BuildWindow.cpp
 * @brief  BuildWindowクラスの実装
 * @author morimoto
 */
#include "BuildWindow.h"
#include "TextureManager\TextureManager.h"
#include "EventManager.h"
#include "Event\OperationWindowEvent\OperationWindowEvent.h"
#include "Event\BuildWindowEvent\BuildWindowEvent.h"
#include "HouseBuildButtonUI\HouseBuildButtonUI.h"
#include "HouseDestroyButtonUI\HouseDestroyButtonUI.h"
#include "RoadLayingButtonUI\RoadLayingButtonUI.h"
#include "HouseBuildWindow\HouseBuildWindow.h"

const D3DXVECTOR2 BuildWindow::m_DefaultPos = D3DXVECTOR2(-70, 300);
const D3DXVECTOR2 BuildWindow::m_DefaultSize = D3DXVECTOR2(500, 500);
const D3DXVECTOR2 BuildWindow::m_MovePos = D3DXVECTOR2(-70, 820);
const float BuildWindow::m_MoveSpeed = 4.0f;


BuildWindow::BuildWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pParentEventListener(new OperationWindowEventListener()),
m_pEventListener(new BuildWindowEventListener()),
m_State(NONE),
m_ParentUIPos(*_pParentUIPos)
{
	EventManager::GetInstance()->AddEventListener(m_pParentEventListener);
	EventManager::GetInstance()->AddEventListener(m_pEventListener);

	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\BuildUI.jpg"),
		&m_TextureIndex);

	m_pButtonUI.push_back(new HouseBuildButtonUI(&m_WindowPos, m_TextureIndex));
	m_pButtonUI.push_back(new HouseDestroyButtonUI(&m_WindowPos, m_TextureIndex));
	m_pButtonUI.push_back(new RoadLayingButtonUI(&m_WindowPos, m_TextureIndex));

	m_pWindowUI.push_back(new HouseBuildWindow(&m_WindowPos));
}

BuildWindow::~BuildWindow()
{
	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		delete m_pWindowUI[i];
	}

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

void BuildWindow::Control()
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

void BuildWindow::Draw()
{
	if (m_State == NONE)
	{
		return;
	}

	WindowDraw();
	ButtonUIDraw();
	WindowUIDraw();
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
		switch (m_pParentEventListener->GetEventType())
		{
		case OperationWindowEvent::BUILD_BUTTON_CLICK:
			m_State = START_STATE;
			break;
		}
		break;
	case WAIT_STATE:
		switch (m_pEventListener->GetEventType())
		{
		case BuildWindowEvent::BUILD_WINDOW_BACK:
			m_State = PROC_STATE;
			break;
		}
		break;
	case PROC_STATE:
		switch (m_pEventListener->GetEventType())
		{
		case BuildWindowEvent::HOUSE_BUILD_BUTTON_CLICK:
			m_State = WAIT_STATE;
			break;
		}
		break;
	}

	m_pParentEventListener->ClearEventType();
	m_pEventListener->ClearEventType();
}

void BuildWindow::WaitControl()
{
	WindowUIControl();
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

	ButtonUIControl();
	WindowUIControl();
}

void BuildWindow::EndControl()
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

void BuildWindow::ButtonUIControl()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Control();
	}
}

void BuildWindow::WindowUIControl()
{
	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		m_pWindowUI[i]->Control();
	}
}

void BuildWindow::ButtonUIDraw()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Draw();
	}
}

void BuildWindow::WindowUIDraw()
{
	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		m_pWindowUI[i]->Draw();
	}
}
