/**
 * @file   GameObjectManager.cpp
 * @brief  GameObjectManagerクラスの実装
 * @author kotani
 */
#include "GameObjectManager.h"
#include "MainCamera\MainCamera.h"
#include "EnemyManager\EnemyManager.h"
#include "FieldManager\FieldManager.h"
#include "HouseManager\HouseManager.h"
#include "HumanManager\HumanManager.h"
#include "RoadManager\RoadManager.h"
#include "GameTimeManager\GameTimeManager.h"


GameObjectManager::GameObjectManager() :
m_pMainCamera(new MainCamera()),
m_pEnemyManager(new EnemyManager()),
m_pFieldManager(new FieldManager()),
m_pHouseManager(new HouseManager()),
m_pHumanManager(new HumanManager()),
m_pRoadManager(new RoadManager()),
m_pGameTimeManager(new GameTimeManager())
{
}

GameObjectManager::~GameObjectManager()
{
	delete m_pGameTimeManager;
	delete m_pRoadManager;
	delete m_pHumanManager;
	delete m_pHouseManager;
	delete m_pFieldManager;
	delete m_pEnemyManager;
	delete m_pMainCamera;
}

void GameObjectManager::Control()
{
	m_pMainCamera->Control();
	m_pEnemyManager->Control();
	m_pFieldManager->Control();
	m_pHouseManager->Control();
	m_pHumanManager->Control();
	m_pRoadManager->Control();
	m_pGameTimeManager->Control();
}

void GameObjectManager::Draw()
{
	m_pEnemyManager->Draw();
	m_pFieldManager->Draw();
	m_pHouseManager->Draw();
	m_pHumanManager->Draw();
	m_pRoadManager->Draw();
	m_pGameTimeManager->Draw();
}
