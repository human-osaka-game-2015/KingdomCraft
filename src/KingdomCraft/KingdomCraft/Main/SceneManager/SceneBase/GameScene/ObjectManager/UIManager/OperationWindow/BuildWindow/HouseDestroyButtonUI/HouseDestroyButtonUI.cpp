/**
 * @file   HouseDestroyButtonUI.cpp
 * @brief  HouseDestroyButtonUIクラスの実装
 * @author morimoto
 */
#include "HouseDestroyButtonUI.h"

const D3DXVECTOR2 HouseDestroyButtonUI::m_DefaultPos = D3DXVECTOR2(-26, -15);
const D3DXVECTOR2 HouseDestroyButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);


HouseDestroyButtonUI::HouseDestroyButtonUI() :
ButtonUI(&m_DefaultPos, &m_DefaultSize)
{
}

HouseDestroyButtonUI::~HouseDestroyButtonUI()
{
}

bool HouseDestroyButtonUI::Control()
{
	return IsClicked();
}

void HouseDestroyButtonUI::Draw()
{
}
