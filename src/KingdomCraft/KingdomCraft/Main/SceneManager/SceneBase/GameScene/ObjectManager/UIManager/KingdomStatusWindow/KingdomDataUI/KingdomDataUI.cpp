/**
 * @file   KingdomDataUI.cpp
 * @brief  KingdomDataUIクラスの実装
 * @author morimoto
 */
#include "KingdomDataUI.h"

const D3DXVECTOR2 KingdomDataUI::m_DefaultTextPos = D3DXVECTOR2(-290, 70);
const D3DXVECTOR2 KingdomDataUI::m_DefaultFontSize = D3DXVECTOR2(16, 32);


KingdomDataUI::KingdomDataUI(const D3DXVECTOR2* _pParentUIPos) :
TextUI(&D3DXVECTOR2(m_DefaultTextPos + *_pParentUIPos), &m_DefaultFontSize),
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

	TextDraw("KingdomDataUI");
}
