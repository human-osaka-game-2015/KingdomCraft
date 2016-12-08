/**
 * @file   UIManager.cpp
 * @brief  UIManagerクラスの実装
 * @author morimoto
 */
#include "UIManager.h"
#include "GameTimeWindow\GameTimeWindow.h"
#include "KingdomWindow\KingdomWindow.h"
#include "OperationWindow\OperationWindow.h"


UIManager::UIManager() :
m_pGameTimeWindow(new GameTimeWindow()),
m_pKingdomWindow(new KingdomWindow()),
m_pOperationWindow(new OperationWindow())
{
}

UIManager::~UIManager()
{
	delete m_pOperationWindow;
	delete m_pKingdomWindow;
	delete m_pGameTimeWindow;
}

void UIManager::Control()
{
	m_pGameTimeWindow->Control();
	m_pKingdomWindow->Control();
	m_pOperationWindow->Control();
}

void UIManager::Draw()
{
	m_pGameTimeWindow->Draw();
	m_pKingdomWindow->Draw();
	m_pOperationWindow->Draw();
}
