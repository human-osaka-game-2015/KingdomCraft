/**
 * @file   KingdomWindow.cpp
 * @brief  KingdomWindowクラスの実装
 * @author morimoto
 */
#include "KingdomWindow.h"
#include "KingdomDataUI\KingdomDataUI.h"
#include "KingdomDemandUI\KingdomDemandUI.h"
#include "KingdomParameterUI\KingdomParameterUI.h"
#include "KingdomButtonUI\KingdomButtonUI.h"

const D3DXVECTOR2 KingdomWindow::m_KingdomWindowPos = D3DXVECTOR2(990, 100);
const D3DXVECTOR2 KingdomWindow::m_KingdomWindowSize = D3DXVECTOR2(600, 200);


KingdomWindow::KingdomWindow() :
UIWindow(&m_KingdomWindowPos, &m_KingdomWindowSize),
m_pKingdomDataUI(new KingdomDataUI()),
m_pKingdomDemandUI(new KingdomDemandUI()),
m_pKingdomParameterUI(new KingdomParameterUI()),
m_pKingdomButtonUI(new KingdomButtonUI())
{
}

KingdomWindow::~KingdomWindow()
{
	delete m_pKingdomButtonUI;
	delete m_pKingdomParameterUI;
	delete m_pKingdomDemandUI;
	delete m_pKingdomDataUI;
}

void KingdomWindow::Control()
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

void KingdomWindow::Draw()
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
