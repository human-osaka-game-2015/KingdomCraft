/**
 * @file   PoliticsButtonUI.cpp
 * @brief  PoliticsButtonUIクラスの実装
 * @author morimoto
 */
#include "PoliticsButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 PoliticsButtonUI::m_ButtonPos = D3DXVECTOR2(964, 630);
const D3DXVECTOR2 PoliticsButtonUI::m_ButtonSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 PoliticsButtonUI::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0.125,	0),
	D3DXVECTOR2(0.25,	0),
	D3DXVECTOR2(0.125,	0.125),
	D3DXVECTOR2(0.25,	0.125)
};


PoliticsButtonUI::PoliticsButtonUI(int _textureIndex) :
UIButton(&m_ButtonPos, &m_ButtonSize),
m_TextureIndex(_textureIndex)
{
	m_pButtonVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pButtonVertex->Init(&m_ButtonSize, m_ButtonTexel);

	m_pButtonVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

PoliticsButtonUI::~PoliticsButtonUI()
{
	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);

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
	m_pButtonVertex->Draw(&m_ButtonPos);
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}
