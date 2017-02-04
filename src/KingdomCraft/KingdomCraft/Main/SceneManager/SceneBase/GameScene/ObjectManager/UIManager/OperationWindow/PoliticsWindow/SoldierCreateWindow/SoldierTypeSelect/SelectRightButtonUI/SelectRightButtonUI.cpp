/**
 * @file   SelectRightButtonUI.cpp
 * @brief  SelectRightButtonUIクラスの実装
 * @author morimoto
 */
#include "SelectRightButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SelectRightButtonUI::m_DefaultPos = D3DXVECTOR2(70, 0);
const D3DXVECTOR2 SelectRightButtonUI::m_DefaultSize = D3DXVECTOR2(32, 32);
const D3DXVECTOR2 SelectRightButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.0625f, 0.5f),
	D3DXVECTOR2(0.125f,  0.5f),
	D3DXVECTOR2(0.0625f, 0.625f),
	D3DXVECTOR2(0.125f,  0.625f)
};


SelectRightButtonUI::SelectRightButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
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

SelectRightButtonUI::~SelectRightButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool SelectRightButtonUI::Control()
{
	m_ButtonPos = *m_pParentUIPos + m_DefaultPos;
	return IsClicked();
}

void SelectRightButtonUI::Draw()
{
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *m_pParentUIPos));
	m_pVertex2D->Draw();
}
