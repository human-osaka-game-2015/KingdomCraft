/**
 * @file   SoldierDispatchButtonUI.cpp
 * @brief  SoldierDispatchButtonUIクラスの実装
 * @author morimoto
 */
#include "SoldierDispatchButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SoldierDispatchButtonUI::m_DefaultPos = D3DXVECTOR2(128, -170);
const D3DXVECTOR2 SoldierDispatchButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 SoldierDispatchButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.0f, 0.0f),
	D3DXVECTOR2(1.0f, 0.0f),
	D3DXVECTOR2(0.0f, 1.0f),
	D3DXVECTOR2(1.0f, 1.0f)
};


SoldierDispatchButtonUI::SoldierDispatchButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
ButtonUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pParentUIPos(_pParentUIPos),
m_TextureIndex(_textureIndex)
{
	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
}

SoldierDispatchButtonUI::~SoldierDispatchButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool SoldierDispatchButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void SoldierDispatchButtonUI::Draw()
{
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *m_pParentUIPos));
	m_pVertex2D->Draw();
}
