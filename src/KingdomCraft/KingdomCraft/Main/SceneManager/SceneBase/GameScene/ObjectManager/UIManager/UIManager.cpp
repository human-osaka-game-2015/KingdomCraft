/**
 * @file   UIManager.cpp
 * @brief  UIManagerクラスの実装
 * @author morimoto
 */
#include "UIManager.h"
#include "GameTimeWindow\GameTimeWindow.h"
#include "KingdomStatusWindow\KingdomStatusWindow.h"
#include "OperationWindow\OperationWindow.h"
#include "KingdomWindow\KingdomWindow.h"


UIManager::UIManager() :
m_pGameTimeWindow(new GameTimeWindow()),
m_pKingdomStatusWindow(new KingdomStatusWindow()),
m_pOperationWindow(new OperationWindow()),
m_pKingdomWindow(new KingdomWindow())
{
}

UIManager::~UIManager()
{
	delete m_pKingdomWindow;
	delete m_pOperationWindow;
	delete m_pKingdomStatusWindow;
	delete m_pGameTimeWindow;
}

void UIManager::Control()
{
	m_pGameTimeWindow->Control();
	m_pKingdomStatusWindow->Control();
	m_pOperationWindow->Control();
	m_pKingdomWindow->Control();
}

void UIManager::Draw()
{
	m_pGameTimeWindow->Draw();
	m_pKingdomStatusWindow->Draw();
	m_pOperationWindow->Draw();
	m_pKingdomWindow->Draw();
}
