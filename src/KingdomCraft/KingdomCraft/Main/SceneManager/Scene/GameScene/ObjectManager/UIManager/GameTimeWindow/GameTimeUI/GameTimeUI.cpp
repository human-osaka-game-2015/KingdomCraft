/**
 * @file   GameTimeUI.cpp
 * @brief  GameTimeUIクラスの実装
 * @author morimoto
 */
#include "GameTimeUI.h"

const D3DXVECTOR2 GameTimeUI::m_TextPos = D3DXVECTOR2(45, 110);
const D3DXVECTOR2 GameTimeUI::m_FontSize = D3DXVECTOR2(64, 32);


GameTimeUI::GameTimeUI() : 
TextUI(&m_TextPos, &m_FontSize)
{
}

GameTimeUI::~GameTimeUI()
{
}

void GameTimeUI::Control()
{
}

void GameTimeUI::Draw()
{
	TextDraw("Test");
}
