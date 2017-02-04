/**
 * @file   SoldierCreater.cpp
 * @brief  SoldierCreaterクラスの実装
 * @author morimoto
 */
#include "SoldierCreater.h"
#include "..\Soldier\SwordSoldier\SwordSoldier.h"


SoldierCreater::SoldierCreater()
{
}

SoldierCreater::~SoldierCreater()
{
}

void SoldierCreater::SetSoldierType(SoldierManager::SOLDIER_TYPE _type)
{
	m_SoldierType = _type;
}

Soldier* SoldierCreater::SoldierCreate()
{
	Soldier* pSoldier = NULL;

	switch (m_SoldierType)
	{
	case SoldierManager::SWORDSOLDIER_TYPE:
		pSoldier = new SwordSoldier();
		break;
	}

	return pSoldier;
}
