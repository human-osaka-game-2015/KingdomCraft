/**
 * @file   HouseBuildButtonUI.cpp
 * @brief  HouseBuildButtonUIクラスの実装
 * @author morimoto
 */
#include "HouseBuildButtonUI.h"

const D3DXVECTOR2 HouseBuildButtonUI::m_DefaultPos = D3DXVECTOR2(-90, -15);
const D3DXVECTOR2 HouseBuildButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);


HouseBuildButtonUI::HouseBuildButtonUI() : 
ButtonUI(&m_DefaultPos, &m_DefaultSize)
{
}

HouseBuildButtonUI::~HouseBuildButtonUI()
{
}

bool HouseBuildButtonUI::Control()
{
	return IsClicked();
}

void HouseBuildButtonUI::Draw()
{
}
