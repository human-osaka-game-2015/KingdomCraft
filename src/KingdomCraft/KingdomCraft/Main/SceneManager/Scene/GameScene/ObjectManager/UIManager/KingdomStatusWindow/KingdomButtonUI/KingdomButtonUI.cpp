/**
 * @file   KingdomButtonUI.cpp
 * @brief  KingdomButtonUIクラスの実装
 * @author morimoto
 */
#include "KingdomButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 KingdomButtonUI::m_ButtonPos = D3DXVECTOR2(187, -60);
const D3DXVECTOR2 KingdomButtonUI::m_ButtonSize = D3DXVECTOR2(128, 60);
const D3DXVECTOR2 KingdomButtonUI::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


KingdomButtonUI::KingdomButtonUI(const D3DXVECTOR2* _pParentUIPos) :
ButtonUI(&D3DXVECTOR2(m_ButtonPos + *_pParentUIPos), &m_ButtonSize),
m_pButtonVertex(NULL),
m_ButtonTextureIndex(TextureManager::m_InvalidIndex),
m_ParentUIPos(*_pParentUIPos)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\KingdomButton.png"),
		&m_ButtonTextureIndex);

	m_pButtonVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pButtonVertex->Init(&m_ButtonSize, m_ButtonTexel);
	m_pButtonVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_ButtonTextureIndex));
	m_pButtonVertex->WriteConstantBuffer(&D3DXVECTOR2(m_ButtonPos + *_pParentUIPos));
}

KingdomButtonUI::~KingdomButtonUI()
{
	m_pButtonVertex->Release();
	delete m_pButtonVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_ButtonTextureIndex);
}

bool KingdomButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void KingdomButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_pButtonVertex->Draw();
}
