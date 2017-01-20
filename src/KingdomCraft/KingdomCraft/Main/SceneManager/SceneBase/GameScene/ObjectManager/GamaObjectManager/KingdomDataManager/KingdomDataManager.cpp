/**
 * @file   KingdomDataManager.cpp
 * @brief  KingdomDataManagerクラスの実装
 * @author morimoto
 */
#include "KingdomDataManager.h"
#include "..\GameDataManager\GameDataManager.h"


KingdomDataManager::KingdomDataManager() : 
m_KingdomData(0, 0, 0, 0, 0, 0, 0, 0.f)
{
}

KingdomDataManager::~KingdomDataManager()
{
}

void KingdomDataManager::Control()
{
	MoneyControl();

	GameDataManager::GetInstance();
}

void KingdomDataManager::Draw()
{
}

void KingdomDataManager::MoneyControl()
{
	if (false)	// @todo 月が切り替わったら通るようにする
	{
		int Tax = static_cast<int>(m_KingdomData.Population * m_KingdomData.TaxRate);
		m_KingdomData.Money += Tax;
	}
}

