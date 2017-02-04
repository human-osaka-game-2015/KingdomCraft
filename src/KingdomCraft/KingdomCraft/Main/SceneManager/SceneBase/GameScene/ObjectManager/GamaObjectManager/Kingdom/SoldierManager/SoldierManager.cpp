/**
 * @file   SoldierManager.cpp
 * @brief  SoldierManagerクラスの実装
 * @author morimoto
 */
#include "SoldierManager.h"
#include "Soldier\Soldier.h"


SoldierManager::SoldierManager()
{
}

SoldierManager::~SoldierManager()
{
	for (unsigned int i = 0; i < m_pSoldiers.size(); i++)
	{
		delete m_pSoldiers[i];
	}
}

void SoldierManager::Control()
{
	for (unsigned int i = 0; i < m_pSoldiers.size(); i++)
	{
		m_pSoldiers[i]->Control();
	}
}

void SoldierManager::Draw()
{
	for (unsigned int i = 0; i < m_pSoldiers.size(); i++)
	{
		m_pSoldiers[i]->Draw();
	}
}
