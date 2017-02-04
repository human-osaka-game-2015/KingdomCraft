/**
 * @file   SelectLeftButtonUI.cpp
 * @brief  SelectLeftButtonUIクラスの実装
 * @author morimoto
 */
#include "SelectLeftButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SelectLeftButtonUI::m_DefaultPos = D3DXVECTOR2(-75, 0);
const D3DXVECTOR2 SelectLeftButtonUI::m_DefaultSize = D3DXVECTOR2(32, 32);
const D3DXVECTOR2 SelectLeftButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.0f,    0.5f),
	D3DXVECTOR2(0.0625f, 0.5f),
	D3DXVECTOR2(0.0f,    0.625f),
	D3DXVECTOR2(0.0625f, 0.625f)
};


SelectLeftButtonUI::SelectLeftButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
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

SelectLeftButtonUI::~SelectLeftButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool SelectLeftButtonUI::Control()
{
	m_ButtonPos = *m_pParentUIPos + m_DefaultPos;
	return IsClicked();
}

void SelectLeftButtonUI::Draw()
{
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *m_pParentUIPos));
	m_pVertex2D->Draw();
}
