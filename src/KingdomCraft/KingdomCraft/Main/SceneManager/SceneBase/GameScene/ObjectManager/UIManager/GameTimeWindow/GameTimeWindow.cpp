/**
 * @file   GameTimeWindow.cpp
 * @brief  GameTimeWindowクラスの実装
 * @author morimoto
 */
#include "GameTimeWindow.h"
#include "GameTimeOperationUI\GameTimeOperationUI.h"
#include "GameTimeUI\GameTimeUI.h"

const D3DXVECTOR2 GameTimeWindow::m_GameTimeWindowPos = D3DXVECTOR2(250, 80);
const D3DXVECTOR2 GameTimeWindow::m_GameTimeWindowSize = D3DXVECTOR2(500, 160);


GameTimeWindow::GameTimeWindow() :
WindowUI(&m_GameTimeWindowPos, &m_GameTimeWindowSize),
m_pGameTimeOperationUI(new GameTimeOperationUI(&m_GameTimeWindowPos)),
m_pGameTimeUI(new GameTimeUI(&m_GameTimeWindowPos))
{
}

GameTimeWindow::~GameTimeWindow()
{
	delete m_pGameTimeUI;
	delete m_pGameTimeOperationUI;
}

void GameTimeWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_pGameTimeOperationUI->Control();
	m_pGameTimeUI->Control();
}

void GameTimeWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	WindowDraw();

	m_pGameTimeOperationUI->Draw();
	m_pGameTimeUI->Draw();
}
