/**
 * @file   KingdomStatusWindow.cpp
 * @brief  KingdomStatusWindowクラスの実装
 * @author morimoto
 */
#include "KingdomStatusWindow.h"
#include "KingdomDataUI\KingdomDataUI.h"
#include "KingdomDemandUI\KingdomDemandUI.h"
#include "KingdomParameterUI\KingdomParameterUI.h"
#include "KingdomButtonUI\KingdomButtonUI.h"

const D3DXVECTOR2 KingdomStatusWindow::m_KingdomWindowPos = D3DXVECTOR2(990, 90);
const D3DXVECTOR2 KingdomStatusWindow::m_KingdomWindowSize = D3DXVECTOR2(600, 180);


KingdomStatusWindow::KingdomStatusWindow() :
WindowUI(&m_KingdomWindowPos, &m_KingdomWindowSize),
m_pKingdomDataUI(new KingdomDataUI(&m_KingdomWindowPos)),
m_pKingdomDemandUI(new KingdomDemandUI(&m_KingdomWindowPos)),
m_pKingdomParameterUI(new KingdomParameterUI(&m_KingdomWindowPos)),
m_pKingdomButtonUI(new KingdomButtonUI(&m_KingdomWindowPos))
{
}

KingdomStatusWindow::~KingdomStatusWindow()
{
	delete m_pKingdomButtonUI;
	delete m_pKingdomParameterUI;
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
	m_pKingdomParameterUI->Control();
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
	m_pKingdomParameterUI->Draw();
	m_pKingdomButtonUI->Draw();
}
