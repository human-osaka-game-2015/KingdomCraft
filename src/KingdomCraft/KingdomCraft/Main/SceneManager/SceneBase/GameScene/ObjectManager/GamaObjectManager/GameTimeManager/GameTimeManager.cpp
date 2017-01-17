/**
 * @file GameTimeManager.cpp
 * @brief GameTimeManagerクラス実装
 * @author morimoto
 */
#include "GameTimeManager.h"
#include "..\..\..\GameDataManager\GameDataManager.h"
#include "..\..\..\EventManager\EventManager.h"
#include "..\..\..\EventManager\EventListener\GameTimeEventListener\GameTimeEventListener.h"
#include "..\..\..\EventManager\Event\GameTimeEvent\GameTimeEvent.h"

const float GameTimeManager::m_TimeSpeed[STATE_MAX] =
{
	1.0f,
	1.5f,
	2.0f,
	4.0f,
	6.0f
};

const int GameTimeManager::m_YearMax = 9999;
const int GameTimeManager::m_MonthMax = 4;
const int GameTimeManager::m_DayMax = 30;
const int GameTimeManager::m_HourMax = 24;


GameTimeManager::GameTimeManager() : 
m_Time(0.0f),
m_GameTime(0, 0, 0, 0),
m_SpeedState(NORMAL_SPEED),
m_pEventListener(new GameTimeEventListener())
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);
}

GameTimeManager::~GameTimeManager()
{
	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;
}

void GameTimeManager::Control()
{
	StateControl();
	AdvanceTime();

	GameDataManager::GetInstance()->SetGameTime(m_GameTime);
}

void GameTimeManager::Draw()
{
}

void GameTimeManager::StateControl()
{
	switch (m_pEventListener->GetEventType())
	{
	case GameTimeEvent::NORMAL_TIME:		// 時間を通常時に戻す

		m_SpeedState = NORMAL_SPEED;

		break;
	case GameTimeEvent::ACCELERATE_TIME:	// 時間を一段階加速させる

		AccelerateTime();

		break;
	case GameTimeEvent::DECELERATE_TIME:	// 時間を一段階減速させる

		DecelerateTime();

		break;
	}

	m_pEventListener->ClearEventType();	// イベントの処理を行ったので履歴を消去
	GameDataManager::GetInstance()->SetSpeedState(m_SpeedState);	// 状態が更新されたのでセット
}

void GameTimeManager::AccelerateTime()
{
	switch (m_SpeedState)
	{
	case NORMAL_SPEED:
		m_SpeedState = ONE_POINT_FIVE_SPEED;
		break;
	case ONE_POINT_FIVE_SPEED:
		m_SpeedState = TWO_SPEED;
		break;
	case TWO_SPEED:
		m_SpeedState = FOUR_SPEED;
		break;
	case FOUR_SPEED:
		m_SpeedState = SIX_SPEED;
		break;
	case SIX_SPEED:
		break;
	}
}

void GameTimeManager::DecelerateTime()
{
	switch (m_SpeedState)
	{
	case NORMAL_SPEED:
		break;
	case ONE_POINT_FIVE_SPEED:
		m_SpeedState = NORMAL_SPEED;
		break;
	case TWO_SPEED:
		m_SpeedState = ONE_POINT_FIVE_SPEED;
		break;
	case FOUR_SPEED:
		m_SpeedState = TWO_SPEED;
		break;
	case SIX_SPEED:
		m_SpeedState = FOUR_SPEED;
		break;
	}
}

void GameTimeManager::AdvanceTime()
{
	m_Time += m_TimeSpeed[m_SpeedState];	// 現在の状態によって時間の進むスピードを変えてる

	if (m_Time >= 60.0f)	///@todo GameDataManagerでゲームのFpsを取得できるようにしたい
	{
		AdvanceHour();
		m_Time = 0.0f;
	}
}

void GameTimeManager::AdvanceHour()
{
	m_GameTime.Hour++;

	if (m_GameTime.Hour > m_HourMax)
	{
		m_GameTime.Hour = 0;
		AdvanceDay();
	}
}

void GameTimeManager::AdvanceDay()
{
	m_GameTime.Day++;

	if (m_GameTime.Day > m_DayMax)
	{
		m_GameTime.Day = 0;
		AdvanceMonth();
	}
}

void GameTimeManager::AdvanceMonth()
{
	m_GameTime.Month++;

	if (m_GameTime.Month > m_MonthMax)
	{
		m_GameTime.Month = 0;
		AdvanceYear();
	}
}

void GameTimeManager::AdvanceYear()
{
	m_GameTime.Year++;

	if (m_GameTime.Year > m_YearMax)
	{
		m_GameTime.Year = 0;	/// @todo 年数が上限を超えた場合とりあえず0入れてる
	}
}

