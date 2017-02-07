/**
 * @file   BuildArea.cpp
 * @brief  BuildAreaクラスの実装
 * @author kotani
 */
#include "BuildArea.h"


BuildArea::BuildArea(bool _isLeft, D3DXVECTOR3 _roadStartPos, D3DXVECTOR3 _roadEndPos) :
m_isLeft(_isLeft),
m_StartPos(_roadStartPos),
m_EndPos(_roadEndPos),
m_BuildAreaNum(4)
{
}

BuildArea::~BuildArea()
{
}

void BuildArea::Control()
{
}

void BuildArea::Draw()
{
}
