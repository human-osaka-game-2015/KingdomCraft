/**
 * @file   KingdomStatusWindow.cpp
 * @brief  KingdomStatusWindowクラスの実装
 * @author morimoto
 */
#include "KingdomStatusWindow.h"
#include "KingdomDataUI\KingdomDataUI.h"
#include "KingdomDemandUI\KingdomDemandUI.h"
#include "KingdomButtonUI\KingdomButtonUI.h"

const D3DXVECTOR2 KingdomStatusWindow::m_DefaultPos = D3DXVECTOR2(990, 60);
const D3DXVECTOR2 KingdomStatusWindow::m_DefaultSize = D3DXVECTOR2(600, 120);


KingdomStatusWindow::KingdomStatusWindow() :
WindowUI(&m_DefaultPos, &m_DefaultSize),
m_pKingdomDataUI(new KingdomDataUI(&m_DefaultPos)),
m_pKingdomDemandUI(new KingdomDemandUI(&m_DefaultPos)),
m_pKingdomButtonUI(new KingdomButtonUI(&m_DefaultPos))
{
}

KingdomStatusWindow::~KingdomStatusWindow()
{
	delete m_pKingdomButtonUI;
	delete m_pKingdomDemandUI;
	delete m_pKingdomDataUI;
}

void KingdomStatusWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_pKingdomDataUI->Control();
	m_pKingdomDemandUI->Control();
	m_pKingdomButtonUI->Control();
}

void KingdomStatusWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	WindowDraw();

	m_pKingdomDataUI->Draw();
	m_pKingdomDemandUI->Draw();
	m_pKingdomButtonUI->Draw();
}
