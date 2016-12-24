/**
 * @file   GameTimeUI.cpp
 * @brief  GameTimeUIクラスの実装
 * @author morimoto
 */
#include "GameTimeUI.h"

const D3DXVECTOR2 GameTimeUI::m_TextPos = D3DXVECTOR2(-200, 50);
const D3DXVECTOR2 GameTimeUI::m_FontSize = D3DXVECTOR2(16, 32);


GameTimeUI::GameTimeUI(const D3DXVECTOR2* _pParentUIPos) :
TextUI(&D3DXVECTOR2(m_TextPos + *_pParentUIPos), &m_FontSize),
m_ParentUIPos(*_pParentUIPos)
{
}

GameTimeUI::~GameTimeUI()
{
}

void GameTimeUI::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void GameTimeUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	TextDraw("GameTimeUI");
}
