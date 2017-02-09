/**
 * @file   BuildAreaManager.cpp
 * @brief  BuildAreaManagerクラスの実装
 * @author kotani
 */
#include "BuildAreaManager.h"
#include "BuildArea\BuildArea.h"

BuildAreaManager::BuildAreaManager()
{
}

BuildAreaManager::~BuildAreaManager()
{
	for (int i = 0; i < m_pBuildArea.size(); i++)
	{
		delete m_pBuildArea[i];
	}
}

void BuildAreaManager::Control()
{
	for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
	{
		m_pBuildArea[i]->Control();
	}
}

void BuildAreaManager::Draw()
{
	for (unsigned int i = 0; i < m_pBuildArea.size(); i++)
	{
		m_pBuildArea[i]->Draw();
	}
}

void BuildAreaManager::BuildAreaCreate(std::vector<D3DXVECTOR3>* _pRoadCenterLine)
{
	m_pBuildArea.push_back(new BuildArea(true, _pRoadCenterLine));
	m_pBuildArea.push_back(new BuildArea(false, _pRoadCenterLine));
}
