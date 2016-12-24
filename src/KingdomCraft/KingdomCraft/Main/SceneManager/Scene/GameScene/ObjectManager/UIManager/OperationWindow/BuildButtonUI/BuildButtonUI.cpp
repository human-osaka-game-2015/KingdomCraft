/**
 * @file   BuildButtonUI.cpp
 * @brief  BuildButtonUIクラスの実装
 * @author morimoto
 */
#include "BuildButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 BuildButtonUI::m_ButtonPos = D3DXVECTOR2(-90, -15);
const D3DXVECTOR2 BuildButtonUI::m_ButtonSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 BuildButtonUI::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0,		0),
	D3DXVECTOR2(0.125,	0),
	D3DXVECTOR2(0,		0.125),
	D3DXVECTOR2(0.125,	0.125)
};


BuildButtonUI::BuildButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
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

BuildButtonUI::~BuildButtonUI()
{
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
	m_pButtonVertex->Draw();
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}
