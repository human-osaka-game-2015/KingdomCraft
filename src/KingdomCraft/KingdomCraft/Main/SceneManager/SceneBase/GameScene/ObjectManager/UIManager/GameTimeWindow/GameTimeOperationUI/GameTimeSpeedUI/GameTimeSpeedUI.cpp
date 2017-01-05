/**
 * @file   GameTimeSpeedUI.cpp
 * @brief  GameTimeSpeedUIクラスの実装
 * @author morimoto
 */
#include "GameTimeSpeedUI.h"

const D3DXVECTOR2 GameTimeSpeedUI::m_DefaultTextPos = D3DXVECTOR2(-220, -30);
const D3DXVECTOR2 GameTimeSpeedUI::m_DefaultFontSize = D3DXVECTOR2(16, 32);


GameTimeSpeedUI::GameTimeSpeedUI(const D3DXVECTOR2* _pParentUIPos) :
TextUI(&D3DXVECTOR2(m_DefaultTextPos + *_pParentUIPos), &m_DefaultFontSize),
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
