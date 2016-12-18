/**
 * @file   KingdomDataUI.cpp
 * @brief  KingdomDataUIクラスの実装
 * @author morimoto
 */
#include "KingdomDataUI.h"

const D3DXVECTOR2 KingdomDataUI::m_TextPos = D3DXVECTOR2(700, 160);
const D3DXVECTOR2 KingdomDataUI::m_FontSize = D3DXVECTOR2(32, 16);


KingdomDataUI::KingdomDataUI() :
TextUI(&m_TextPos, &m_FontSize)
{
}

KingdomDataUI::~KingdomDataUI()
{
}

void KingdomDataUI::Control()
{
}

void KingdomDataUI::Draw()
{
	TextDraw("KingdomDataUI");
}
