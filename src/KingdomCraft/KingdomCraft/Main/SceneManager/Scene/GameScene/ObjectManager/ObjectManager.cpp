/**
 * @file   ObjectManager.cpp
 * @brief  ObjectManagerクラスの実装
 * @author kotani
 */
#include "ObjectManager.h"
#include "GamaObjectManager\GameObjectManager.h"
#include "UIManager\UIManager.h"


ObjectManager::ObjectManager() :
m_pGameObjectManager(new GameObjectManager()),
m_pUIManager(new UIManager())
{
}

ObjectManager::~ObjectManager()
{
	delete m_pUIManager;
	delete m_pGameObjectManager;
}

void ObjectManager::Control()
{
	m_pGameObjectManager->Control();
	m_pUIManager->Control();
}

void ObjectManager::Draw()
{
	m_pGameObjectManager->Draw();
	m_pUIManager->Draw();
}
