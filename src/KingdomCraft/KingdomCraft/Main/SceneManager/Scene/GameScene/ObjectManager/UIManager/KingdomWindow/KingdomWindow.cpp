/**
 * @file   KingdomWindow.cpp
 * @brief  KingdomWindowクラスの実装
 * @author morimoto
 */
#include "KingdomWindow.h"

const D3DXVECTOR2 KingdomWindow::m_KingdomWindowSize = D3DXVECTOR2(100, 100);
const D3DXVECTOR2 KingdomWindow::m_KingdomWindowPos = D3DXVECTOR2(0, 0);


KingdomWindow::KingdomWindow() :
UIWindow(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(0, 0))
{
}

KingdomWindow::~KingdomWindow()
{
}

void KingdomWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void KingdomWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}
}
