/**
 * @file   FieldManager.cpp
 * @brief  FieldManagerクラスの実装
 * @author kotani
 */
#include "FieldManager.h"
#include "Ground\Ground.h"
#include "Sky\Sky.h"


FieldManager::FieldManager() :
m_pGround(new Ground()),
m_pSky(new Sky())
{
}

FieldManager::~FieldManager()
{
	delete m_pSky;
	delete m_pGround;
}

void FieldManager::Control()
{
	m_pGround->Control();
	m_pSky->Control();
}

void FieldManager::Draw()
{
	m_pGround->Draw();
	m_pSky->Draw();
}
