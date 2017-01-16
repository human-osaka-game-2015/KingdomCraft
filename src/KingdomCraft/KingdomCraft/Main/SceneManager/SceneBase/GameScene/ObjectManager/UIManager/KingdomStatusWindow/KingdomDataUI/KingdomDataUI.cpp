/**
 * @file   KingdomDataUI.cpp
 * @brief  KingdomDataUIクラスの実装
 * @author morimoto
 */
#include "KingdomDataUI.h"

const D3DXVECTOR2 KingdomDataUI::m_MoneyTextPos = D3DXVECTOR2(-240, -45);
const D3DXVECTOR2 KingdomDataUI::m_PopulationTextPos = D3DXVECTOR2(-240, 0);
const D3DXVECTOR2 KingdomDataUI::m_DefaultFontSize = D3DXVECTOR2(16, 32);


KingdomDataUI::KingdomDataUI(const D3DXVECTOR2* _pParentUIPos) :
TextUI(&D3DXVECTOR2(*_pParentUIPos), &m_DefaultFontSize),
m_ParentUIPos(*_pParentUIPos)
{
}

KingdomDataUI::~KingdomDataUI()
{
}

void KingdomDataUI::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void KingdomDataUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_TextPos = m_ParentUIPos + m_MoneyTextPos;
	TextDraw("Money");

	m_TextPos = m_ParentUIPos + m_PopulationTextPos;
	TextDraw("Population");
}
