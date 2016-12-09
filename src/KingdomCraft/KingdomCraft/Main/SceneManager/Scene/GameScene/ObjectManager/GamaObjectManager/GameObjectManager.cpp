/**
 * @file   GameObjectManager.cpp
 * @brief  GameObjectManagerクラスの実装
 * @author kotani
 */
#include "GameObjectManager.h"
#include "EnemyManager\EnemyManager.h"
#include "FieldManager\FieldManager.h"
#include "HouseManager\HouseManager.h"
#include "HumanManager\HumanManager.h"
#include "RoadManager\RoadManager.h"


GameObjectManager::GameObjectManager() :
m_pEnemyManager(new EnemyManager()),
m_pFieldManager(new FieldManager()),
m_pHouseManager(new HouseManager()),
m_pHumanManager(new HumanManager()),
m_pRoadManager(new RoadManager())
{
}

GameObjectManager::~GameObjectManager()
{
	delete m_pRoadManager;
	delete m_pHumanManager;
	delete m_pHouseManager;
	delete m_pFieldManager;
	delete m_pEnemyManager;
}

void GameObjectManager::Control()
{
	m_pEnemyManager->Control();
	m_pFieldManager->Control();
	m_pHouseManager->Control();
	m_pHumanManager->Control();
	m_pRoadManager->Control();
}

void GameObjectManager::Draw()
{
	m_pEnemyManager->Draw();
	m_pFieldManager->Draw();
	m_pHouseManager->Draw();
	m_pHumanManager->Draw();
	m_pRoadManager->Draw();
}
