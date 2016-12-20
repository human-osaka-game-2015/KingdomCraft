/**
 * @file   GameTimeSpeedUI.cpp
 * @brief  GameTimeSpeedUIクラスの実装
 * @author morimoto
 */
#include "GameTimeSpeedUI.h"

const D3DXVECTOR2 GameTimeSpeedUI::m_TextPos = D3DXVECTOR2(30, 50);
const D3DXVECTOR2 GameTimeSpeedUI::m_FontSize = D3DXVECTOR2(32, 16);


GameTimeSpeedUI::GameTimeSpeedUI() :
TextUI(&m_TextPos, &m_FontSize)
{
}

GameTimeSpeedUI::~GameTimeSpeedUI()
{
}

void GameTimeSpeedUI::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void GameTimeSpeedUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	TextDraw("GameTimeSpeed");
}
