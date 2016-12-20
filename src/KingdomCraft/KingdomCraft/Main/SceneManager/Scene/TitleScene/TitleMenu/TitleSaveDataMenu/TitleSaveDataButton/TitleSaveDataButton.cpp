/**
 * @file TitleSaveDataButton.cpp
 * @brief TitleSaveDataButtonクラス実装
 * @author morimoto
 */
#include "TitleSaveDataButton.h"


TitleSaveDataButton::TitleSaveDataButton(const D3DXVECTOR2* _pButtonPos, const D3DXVECTOR2* _pButtonSize, LPCTSTR _pTextureName) :
m_ButtonPos(*_pButtonPos),
m_ButtonSize(*_pButtonSize)
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
