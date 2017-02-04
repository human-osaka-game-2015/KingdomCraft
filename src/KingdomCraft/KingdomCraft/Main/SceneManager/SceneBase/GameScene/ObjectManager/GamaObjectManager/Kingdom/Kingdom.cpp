/**
 * @file   Kingdom.cpp
 * @brief  Kingdomクラスの実装
 * @author morimoto
 */
#include "Kingdom.h"
#include "..\GameDataManager\GameDataManager.h"
#include "SoldierManager\SoldierManager.h"


Kingdom::Kingdom() : 
m_KingdomData(0, 0, 0, 0, 0, 0, 0, 0.f),
m_pSoldierManager(new SoldierManager())
{
}

Kingdom::~Kingdom()
{
	delete m_pSoldierManager;
}

void Kingdom::Control()
{
	m_pSoldierManager->Control();

	MoneyControl();

	GameDataManager::GetInstance()->SetKingdomData(m_KingdomData);
}

void Kingdom::Draw()
{
}

void Kingdom::MoneyControl()
{
	if (false)	// @todo 月が切り替わったら通るようにする
	{
		int Tax = static_cast<int>(m_KingdomData.Population * m_KingdomData.TaxRate);
		m_KingdomData.Money += Tax;
	}
}

