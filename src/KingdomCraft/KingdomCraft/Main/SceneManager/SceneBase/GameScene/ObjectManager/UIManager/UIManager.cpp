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
#include "GameEventLogWindow\GameEventLogWindow.h"


UIManager::UIManager() :
m_pGameTimeWindow(new GameTimeWindow()),
m_pKingdomStatusWindow(new KingdomStatusWindow()),
m_pOperationWindow(new OperationWindow()),
m_pKingdomWindow(new KingdomWindow()),
m_pGameEventLogWindow(new GameEventLogWindow())
{
}

UIManager::~UIManager()
{
	delete m_pGameEventLogWindow;
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
	m_pGameEventLogWindow->Control();
}

void UIManager::Draw()
{
	m_pGameTimeWindow->Draw();
	m_pKingdomStatusWindow->Draw();
	m_pOperationWindow->Draw();
	m_pKingdomWindow->Draw();
	m_pGameEventLogWindow->Draw();
}
