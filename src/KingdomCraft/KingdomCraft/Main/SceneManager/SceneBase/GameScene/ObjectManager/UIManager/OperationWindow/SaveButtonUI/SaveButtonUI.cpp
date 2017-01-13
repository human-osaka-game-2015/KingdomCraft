/**
 * @file   SaveButtonUI.cpp
 * @brief  SaveButtonUIクラスの実装
 * @author morimoto
 */
#include "SaveButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SaveButtonUI::m_DefaultPos = D3DXVECTOR2(38, -15);
const D3DXVECTOR2 SaveButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 SaveButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.25,	0),
	D3DXVECTOR2(0.375,	0),
	D3DXVECTOR2(0.25,	1),
	D3DXVECTOR2(0.375,	1)
};


SaveButtonUI::SaveButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
ButtonUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pVertex2D(NULL),
m_TextureIndex(_textureIndex),
m_ParentUIPos(*_pParentUIPos)
{
	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
}

SaveButtonUI::~SaveButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool SaveButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void SaveButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex2D->Draw();
}
