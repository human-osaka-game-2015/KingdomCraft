/**
 * @file   PoliticsButtonUI.cpp
 * @brief  PoliticsButtonUIクラスの実装
 * @author morimoto
 */
#include "PoliticsButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 PoliticsButtonUI::m_DefaultPos = D3DXVECTOR2(-26, -15);
const D3DXVECTOR2 PoliticsButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 PoliticsButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.125,	0),
	D3DXVECTOR2(0.25,	0),
	D3DXVECTOR2(0.125,	0.125),
	D3DXVECTOR2(0.25,	0.125)
};


PoliticsButtonUI::PoliticsButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
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

PoliticsButtonUI::~PoliticsButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool PoliticsButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void PoliticsButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex2D->Draw();
}
