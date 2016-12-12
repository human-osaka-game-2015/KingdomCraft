/**
 * @file   BuildButtonUI.cpp
 * @brief  BuildButtonUIクラスの実装
 * @author morimoto
 */
#include "BuildButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 BuildButtonUI::m_ButtonPos = D3DXVECTOR2(900, 630);
const D3DXVECTOR2 BuildButtonUI::m_ButtonSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 BuildButtonUI::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0,		0),
	D3DXVECTOR2(0.125,	0),
	D3DXVECTOR2(0,		0.125),
	D3DXVECTOR2(0.125,	0.125)
};


BuildButtonUI::BuildButtonUI(int _textureIndex) :
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

BuildButtonUI::~BuildButtonUI()
{
	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);

	m_pButtonVertex->Release();
	delete m_pButtonVertex;
}

bool BuildButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void BuildButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pButtonVertex->Draw(&m_ButtonPos);
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}
