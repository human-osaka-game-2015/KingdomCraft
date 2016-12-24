/**
 * @file   PoliticsButtonUI.cpp
 * @brief  PoliticsButtonUIクラスの実装
 * @author morimoto
 */
#include "PoliticsButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 PoliticsButtonUI::m_ButtonPos = D3DXVECTOR2(-26, -15);
const D3DXVECTOR2 PoliticsButtonUI::m_ButtonSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 PoliticsButtonUI::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0.125,	0),
	D3DXVECTOR2(0.25,	0),
	D3DXVECTOR2(0.125,	0.125),
	D3DXVECTOR2(0.25,	0.125)
};


PoliticsButtonUI::PoliticsButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
ButtonUI(&D3DXVECTOR2(m_ButtonPos + *_pParentUIPos), &m_ButtonSize),
m_pButtonVertex(NULL),
m_ButtonTextureIndex(_textureIndex),
m_ParentUIPos(*_pParentUIPos)
{
	m_pButtonVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pButtonVertex->Init(&m_ButtonSize, m_ButtonTexel);
	m_pButtonVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_ButtonTextureIndex));
	m_pButtonVertex->WriteConstantBuffer(&D3DXVECTOR2(m_ButtonPos + *_pParentUIPos));
}

PoliticsButtonUI::~PoliticsButtonUI()
{
	m_pButtonVertex->Release();
	delete m_pButtonVertex;
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
	m_pButtonVertex->Draw();
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}
