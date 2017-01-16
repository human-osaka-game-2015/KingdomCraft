/**
 * @file   GameTimeSpeedUI.cpp
 * @brief  GameTimeSpeedUIクラスの実装
 * @author morimoto
 */
#include "GameTimeSpeedUI.h"
#include "EventManager.h"
#include "..\GameDataManager\GameDataManager.h"

const D3DXVECTOR2 GameTimeSpeedUI::m_DefaultTextPos = D3DXVECTOR2(80, 20);
const D3DXVECTOR2 GameTimeSpeedUI::m_DefaultFontSize = D3DXVECTOR2(16, 32);


GameTimeSpeedUI::GameTimeSpeedUI(const D3DXVECTOR2* _pParentUIPos) :
TextUI(&D3DXVECTOR2(m_DefaultTextPos + *_pParentUIPos), &m_DefaultFontSize),
m_ParentUIPos(*_pParentUIPos)
{
}

GameTimeSpeedUI::~GameTimeSpeedUI()
{
}

void GameTimeSpeedUI::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void GameTimeSpeedUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	GameSpeedDraw();
}

void GameTimeSpeedUI::GameSpeedDraw()
{
	GameTimeManager::SPEED_STATE SpeedState = GameDataManager::GetInstance()->GetSpeedState();

	switch (SpeedState)
	{
	case GameTimeManager::NORMAL_SPEED:
		TextDraw("Speed 1");
		break;
	case GameTimeManager::ONE_POINT_FIVE_SPEED:
		TextDraw("Speed 1.5");
		break;
	case GameTimeManager::TWO_SPEED:
		TextDraw("Speed 2");
		break;
	case GameTimeManager::FOUR_SPEED:
		TextDraw("Speed 4");
		break;
	case GameTimeManager::SIX_SPEED:
		TextDraw("Speed 6");
		break;
	}
}
