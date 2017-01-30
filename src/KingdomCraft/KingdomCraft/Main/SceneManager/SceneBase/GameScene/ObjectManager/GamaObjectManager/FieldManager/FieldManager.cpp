/**
 * @file   FieldManager.cpp
 * @brief  FieldManagerクラスの実装
 * @author kotani
 */
#include "FieldManager.h"
#include "Ground\Ground.h"
#include "Sky\Sky.h"
#include "BasePoint\BasePoint.h"


FieldManager::FieldManager() :
m_pGround(new Ground()),
m_pSky(new Sky())
{
	m_pBasePoint.push_back(new BasePoint(&D3DXVECTOR3(0.3, 0, 0)));
}

FieldManager::~FieldManager()
{
	for (unsigned int i = 0; i < m_pBasePoint.size(); i++)
	{
		delete m_pBasePoint[i];
	}

	delete m_pSky;
	delete m_pGround;
}

void FieldManager::Control()
{
	m_pGround->Control();
	m_pSky->Control();

	for (unsigned int i = 0; i < m_pBasePoint.size(); i++)
	{
		m_pBasePoint[i]->Control();
	}
}

void FieldManager::Draw()
{
	m_pGround->Draw();
	m_pSky->Draw();

	for (unsigned int i = 0; i < m_pBasePoint.size(); i++)
	{
		m_pBasePoint[i]->Draw();
	}
}
