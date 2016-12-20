/**
 * @file   DecelerateOfTimeButtonUI.cpp
 * @brief  DecelerateOfTimeButtonUIクラスの実装
 * @author morimoto
 */
#include "DecelerateOfTimeButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 DecelerateOfTimeButtonUI::m_ButtonPos = D3DXVECTOR2(68, 100);
const D3DXVECTOR2 DecelerateOfTimeButtonUI::m_ButtonSize = D3DXVECTOR2(32, 32);
const D3DXVECTOR2 DecelerateOfTimeButtonUI::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


DecelerateOfTimeButtonUI::DecelerateOfTimeButtonUI() :
UIButton(&m_ButtonPos, &m_ButtonSize)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\ObjectManager\\UIManager\\GameTimeWindow\\GameTimeOperationUI\\DecelerateOfTimeButtonUI\\DecelerateOfTimeButtonUI.png"),
		&m_TextureIndex);

	m_pButtonVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pButtonVertex->Init(&m_ButtonSize, m_ButtonTexel);
	m_pButtonVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

DecelerateOfTimeButtonUI::~DecelerateOfTimeButtonUI()
{
	m_pButtonVertex->Release();
	delete m_pButtonVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

bool DecelerateOfTimeButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void DecelerateOfTimeButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_pButtonVertex->Draw(&m_ButtonPos);
}
