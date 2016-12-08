/**
 * @file   GameTimeWindow.cpp
 * @brief  GameTimeWindowクラスの実装
 * @author morimoto
 */
#include "GameTimeWindow.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 GameTimeWindow::m_GameTimeWindowSize = D3DXVECTOR2(100, 100);
const D3DXVECTOR2 GameTimeWindow::m_GameTimeWindowPos = D3DXVECTOR2(0, 0);


GameTimeWindow::GameTimeWindow() :
UIWindow(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(0, 0))
{
}

GameTimeWindow::~GameTimeWindow()
{
}

void GameTimeWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void GameTimeWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}
}
