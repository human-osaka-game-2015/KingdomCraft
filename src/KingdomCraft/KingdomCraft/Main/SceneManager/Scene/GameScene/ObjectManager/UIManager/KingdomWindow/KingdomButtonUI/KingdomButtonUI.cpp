/**
 * @file   KingdomButtonUI.cpp
 * @brief  KingdomButtonUIクラスの実装
 * @author morimoto
 */
#include "KingdomButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 KingdomButtonUI::m_ButtonPos = D3DXVECTOR2(1177, 33);
const D3DXVECTOR2 KingdomButtonUI::m_ButtonSize = D3DXVECTOR2(128, 64);
const D3DXVECTOR2 KingdomButtonUI::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


KingdomButtonUI::KingdomButtonUI() : 
UIButton(&m_ButtonPos, &m_ButtonSize)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\ObjectManager\\UIManager\\KingdomWindow\\KingdomButtonUI\\KingdomButton.png"),
		&m_ButtonTextureIndex);

	m_pButtonVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pButtonVertex->Init(&m_ButtonSize, m_ButtonTexel);
	m_pButtonVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_ButtonTextureIndex));
}

KingdomButtonUI::~KingdomButtonUI()
{
	m_pButtonVertex->Release();
	delete m_pButtonVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_ButtonTextureIndex);
}

bool KingdomButtonUI::Control()
{
	return IsClicked();
}

void KingdomButtonUI::Draw()
{
	m_pButtonVertex->Draw(&m_ButtonPos);
}
