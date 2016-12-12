/**
 * @file   SaveButtonUI.cpp
 * @brief  SaveButtonUIクラスの実装
 * @author morimoto
 */
#include "SaveButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SaveButtonUI::m_ButtonPos = D3DXVECTOR2(1028, 630);
const D3DXVECTOR2 SaveButtonUI::m_ButtonSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 SaveButtonUI::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0.25,	0),
	D3DXVECTOR2(0.375,	0),
	D3DXVECTOR2(0.25,	0.125),
	D3DXVECTOR2(0.375,	0.125)
};


SaveButtonUI::SaveButtonUI(int _textureIndex) :
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

SaveButtonUI::~SaveButtonUI()
{
	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);

	m_pButtonVertex->Release();
	delete m_pButtonVertex;
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
	m_pButtonVertex->Draw(&m_ButtonPos);
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}
