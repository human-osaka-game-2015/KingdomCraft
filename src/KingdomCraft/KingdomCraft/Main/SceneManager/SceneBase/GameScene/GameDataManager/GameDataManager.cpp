/**
 * @file GameDataManager.cpp
 * @brief GameDataManagerクラス実装
 * @author morimoto
 */
#include "GameDataManager.h"

GameDataManager* GameDataManager::m_pGameDataManager = NULL;


GameDataManager::GameDataManager() :
m_GameTime(0, 0, 0, 0),
m_SpeedState(GameTimeManager::NORMAL_SPEED)
{
}

GameDataManager::~GameDataManager()
{
}
