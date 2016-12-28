/**
 * @file TitleSaveDataButton.cpp
 * @brief TitleSaveDataButtonクラス実装
 * @author morimoto
 */
#include "TitleSaveDataButton.h"


TitleSaveDataButton::TitleSaveDataButton(const D3DXVECTOR2* _pPos, const D3DXVECTOR2* _pSize, LPCTSTR _pTextureName) :
m_Pos(*_pPos),
m_Size(*_pSize)
{
}

TitleSaveDataButton::~TitleSaveDataButton()
{
}

bool TitleSaveDataButton::Control()
{
	return false;
}

void TitleSaveDataButton::Draw()
{
}
