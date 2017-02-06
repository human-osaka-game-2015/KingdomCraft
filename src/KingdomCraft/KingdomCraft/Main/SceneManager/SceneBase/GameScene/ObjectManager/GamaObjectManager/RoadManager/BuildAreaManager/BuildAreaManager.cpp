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
