/**
 * @file TitleSaveDataButton.cpp
 * @brief TitleSaveDataButtonクラス実装
 * @author morimoto
 */
#include "TitleSaveDataButton.h"


TitleSaveDataButton::TitleSaveDataButton(const D3DXVECTOR2* const _pDrawPos, const D3DXVECTOR2* const _pDrawSize, LPCTSTR const _pTextureName) :
m_DrawPos(*_pDrawPos),
m_DrawSize(*_pDrawSize)
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
