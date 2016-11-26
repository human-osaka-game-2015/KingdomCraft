#include "DebugFont.h"

DebugFont* DebugFont::m_pDebugFont = NULL;


DebugFont::DebugFont()
{
}

DebugFont::~DebugFont()
{
}

bool DebugFont::Init(LPDIRECT3DDEVICE9 _pDevice, int _fontSize)
{
	D3DXFONT_DESC FontDesc = 
	{ 
		_fontSize, 
		0, 
		0, 
		1, 
		0, 
		SHIFTJIS_CHARSET, 
		OUT_TT_ONLY_PRECIS,
		PROOF_QUALITY, 
		FIXED_PITCH | FF_MODERN, 
		TEXT("ＭＳ ゴシック") 
	};

	if (FAILED(D3DXCreateFontIndirect(_pDevice, &FontDesc, &m_pFont)))
	{
		return false;
	}

	return true;
}

void DebugFont::Release()
{
	m_pFont->Release();
}

void DebugFont::DrawFont(RECT _rect, LPCTSTR _font)
{
	m_pFont->DrawText(NULL, _font, -1, &_rect, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, 0xff000000);
}
