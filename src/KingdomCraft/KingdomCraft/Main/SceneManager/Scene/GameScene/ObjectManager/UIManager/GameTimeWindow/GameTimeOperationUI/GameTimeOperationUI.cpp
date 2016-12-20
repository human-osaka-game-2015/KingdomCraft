/**
 * @file   GameTimeOperationUI.cpp
 * @brief  GameTimeOperationUIクラスの実装
 * @author morimoto
 */
#include "GameTimeOperationUI.h"
#include "DecelerateOfTimeButtonUI\DecelerateOfTimeButtonUI.h"
#include "AccelerateOfTimeButtonUI\AccelerateOfTimeButtonUI.h"
#include "NormalTimeButtonUI\NormalTimeButtonUI.h"
#include "GameTimeSpeedUI\GameTimeSpeedUI.h"


GameTimeOperationUI::GameTimeOperationUI() : 
m_pDecelerateButton(new DecelerateOfTimeButtonUI()),
m_pAccelerateButton(new AccelerateOfTimeButtonUI()),
m_pNormalButton(new NormalTimeButtonUI()),
m_pGameTimeSpeed(new GameTimeSpeedUI())
{
}

GameTimeOperationUI::~GameTimeOperationUI()
{
	delete m_pGameTimeSpeed;
	delete m_pNormalButton;
	delete m_pAccelerateButton;
	delete m_pDecelerateButton;
}

void GameTimeOperationUI::Control()
{
	m_pDecelerateButton->Control();
	m_pAccelerateButton->Control();
	m_pNormalButton->Control();
	m_pGameTimeSpeed->Control();
}

void GameTimeOperationUI::Draw()
{
	m_pDecelerateButton->Draw();
	m_pAccelerateButton->Draw();
	m_pNormalButton->Draw();
	m_pGameTimeSpeed->Draw();
}
