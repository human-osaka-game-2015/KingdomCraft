/**
 * @file   NormalTimeButtonUI.cpp
 * @brief  NormalTimeButtonUIクラスの実装
 * @author morimoto
 */
#include "NormalTimeButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 NormalTimeButtonUI::m_ButtonPos = D3DXVECTOR2(100, 100);
const D3DXVECTOR2 NormalTimeButtonUI::m_ButtonSize = D3DXVECTOR2(32, 32);
const D3DXVECTOR2 NormalTimeButtonUI::m_ButtonTexel[4] = 
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


NormalTimeButtonUI::NormalTimeButtonUI() : 
UIButton(&m_ButtonPos, &m_ButtonSize)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\ObjectManager\\UIManager\\GameTimeWindow\\GameTimeOperationUI\\NormalTimeButtonUI\\NormalTimeButtonUI.png"), 
		&m_TextureIndex);

	m_pButtonVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pButtonVertex->Init(&m_ButtonSize, m_ButtonTexel);
	m_pButtonVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

NormalTimeButtonUI::~NormalTimeButtonUI()
{
	m_pButtonVertex->Release();
	delete m_pButtonVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

bool NormalTimeButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void NormalTimeButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_pButtonVertex->Draw(&m_ButtonPos);
}
