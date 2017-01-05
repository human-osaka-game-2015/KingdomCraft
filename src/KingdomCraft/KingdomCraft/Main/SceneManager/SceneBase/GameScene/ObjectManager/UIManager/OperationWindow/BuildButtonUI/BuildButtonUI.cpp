/**
 * @file   BuildButtonUI.cpp
 * @brief  BuildButtonUIクラスの実装
 * @author morimoto
 */
#include "BuildButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 BuildButtonUI::m_DefaultPos = D3DXVECTOR2(-90, -15);
const D3DXVECTOR2 BuildButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 BuildButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0,		0),
	D3DXVECTOR2(0.125,	0),
	D3DXVECTOR2(0,		0.125),
	D3DXVECTOR2(0.125,	0.125)
};


BuildButtonUI::BuildButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
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

BuildButtonUI::~BuildButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
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
	m_pVertex2D->Draw();
}
