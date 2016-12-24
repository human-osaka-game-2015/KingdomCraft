/**
 * @file   GameTimeSpeedUI.cpp
 * @brief  GameTimeSpeedUIクラスの実装
 * @author morimoto
 */
#include "GameTimeSpeedUI.h"

const D3DXVECTOR2 GameTimeSpeedUI::m_TextPos = D3DXVECTOR2(-220, -30);
const D3DXVECTOR2 GameTimeSpeedUI::m_FontSize = D3DXVECTOR2(16, 32);


GameTimeSpeedUI::GameTimeSpeedUI(const D3DXVECTOR2* _pParentUIPos) :
TextUI(&D3DXVECTOR2(m_TextPos + *_pParentUIPos), &m_FontSize),
m_ParentUIPos(*_pParentUIPos)
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
