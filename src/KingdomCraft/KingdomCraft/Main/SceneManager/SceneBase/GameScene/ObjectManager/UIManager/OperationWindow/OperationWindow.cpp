/**
 * @file   OperationWindow.cpp
 * @brief  OperationWindowクラスの実装
 * @author morimoto
 */
#include "OperationWindow.h"
#include "BuildButtonUI\BuildButtonUI.h"
#include "PoliticsButtonUI\PoliticsButtonUI.h"
#include "SaveButtonUI\SaveButtonUI.h"
#include "LoadButtonUI\LoadButtonUI.h"
#include "BackToTitleButtonUI\BackToTitleButtonUI.h"
#include "BuildWindow\BuildWindow.h"
#include "PoliticsWindow\PoliticsWindow.h"
#include "SaveWindow\SaveWindow.h"
#include "LoadWindow\LoadWindow.h"
#include "BackToTitleWindow\BackToTitleWindow.h"
#include "EventManager.h"
#include "Event\OperationWindowEvent\OperationWindowEvent.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 OperationWindow::m_DefaultPos = D3DXVECTOR2(1065, 660);
const D3DXVECTOR2 OperationWindow::m_DefaultSize = D3DXVECTOR2(450, 140);


OperationWindow::OperationWindow() :
WindowUI(&m_DefaultPos, &m_DefaultSize),
m_pEventListener(new OperationWindowEventListener()),
m_IsButtonActive(true)
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);

	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\MainUI.png"),
		&m_TextureIndex);

	m_pButtonUI.push_back(new BuildButtonUI(&m_DefaultPos, m_TextureIndex));
	m_pButtonUI.push_back(new PoliticsButtonUI(&m_DefaultPos, m_TextureIndex));
	m_pButtonUI.push_back(new SaveButtonUI(&m_DefaultPos, m_TextureIndex));
	m_pButtonUI.push_back(new LoadButtonUI(&m_DefaultPos, m_TextureIndex));
	m_pButtonUI.push_back(new BackToTitleButtonUI(&m_DefaultPos, m_TextureIndex));

	m_pWindowUI.push_back(new BuildWindow(&m_DefaultPos));
	m_pWindowUI.push_back(new PoliticsWindow(&m_DefaultPos));
	m_pWindowUI.push_back(new SaveWindow(&m_DefaultPos));
	m_pWindowUI.push_back(new LoadWindow(&m_DefaultPos));
	m_pWindowUI.push_back(new BackToTitleWindow(&m_DefaultPos));
}

OperationWindow::~OperationWindow()
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
}

void OperationWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}

	StateControl();
	ButtonUIControl();
	WindowUIControl();
}

void OperationWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	WindowDraw();

	ButtonUIDraw();
	WindowUIDraw();
}

void OperationWindow::StateControl()
{
	switch (m_pEventListener->GetEventType())
	{
	case OperationWindowEvent::OPERATION_WINDOW_BACK:
		m_IsButtonActive = true;
		break;
	case OperationWindowEvent::BUILD_BUTTON_CLICK:
		m_IsButtonActive = false;
		break;
	case OperationWindowEvent::POLITICS_BUTTON_CLICK:
		m_IsButtonActive = false;
		break;
	case OperationWindowEvent::SAVE_BUTTON_CLICK:
		m_IsButtonActive = false;
		break;
	case OperationWindowEvent::LOAD_BUTTON_CLICK:
		m_IsButtonActive = false;
		break;
	case OperationWindowEvent::BACK_TO_TITLE_BUTTON_CLICK:
		m_IsButtonActive = false;
		break;
	}

	m_pEventListener->ClearEventType();
}

void OperationWindow::WindowUIControl()
{
	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		m_pWindowUI[i]->Control();
	}
}

void OperationWindow::ButtonUIControl()
{
	if (m_IsButtonActive == true)
	{
		for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
		{
			m_pButtonUI[i]->Control();
		}
	}
}

void OperationWindow::WindowUIDraw()
{
	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		m_pWindowUI[i]->Draw();
	}
}

void OperationWindow::ButtonUIDraw()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Draw();
	}
}
