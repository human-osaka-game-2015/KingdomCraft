/**
 * @file   TextUI.cpp
 * @brief  TextUIクラスの実装
 * @author morimoto
 */
#include "TextUI.h"
#include "DX11Manager\DX11Manager.h"


TextUI::TextUI(const D3DXVECTOR2* _pTextPos, const D3DXVECTOR2* _pFontSize, bool _isVisible) :
m_TextPos(*_pTextPos),
m_FontSize(*_pFontSize),
m_IsVisible(_isVisible)
{
	m_pDebugFont = new DebugFont(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext());

	m_pDebugFont->Init(DX11Manager::GetInstance()->GetWindowHandle());

	m_pDebugFont->InitFont(m_FontSize.y, m_FontSize.x, 0xffffffff);
}

TextUI::~TextUI()
{
	m_pDebugFont->Release();
	delete m_pDebugFont;
}

void TextUI::Control()
{
}

void TextUI::Draw()
{
}

void TextUI::TextDraw(LPCTSTR _pStr)
{
	m_pDebugFont->DrawFont(&m_TextPos, _pStr);
}
