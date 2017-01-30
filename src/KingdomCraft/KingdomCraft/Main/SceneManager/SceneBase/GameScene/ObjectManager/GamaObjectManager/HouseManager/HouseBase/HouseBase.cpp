/**
 * @file   HouseBase.cpp
 * @brief  HouseBaseクラスの実装
 * @author morimoto
 */
#include "HouseBase.h"


HouseBase::HouseBase(const D3DXVECTOR3* _pHousePos, float _houseAngle) : 
m_HousePos(*_pHousePos),
m_Angle(_houseAngle)
{
}

HouseBase::~HouseBase()
{
}

void HouseBase::Control()
{
}

void HouseBase::Draw()
{
}

